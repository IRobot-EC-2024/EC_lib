#include "BMI088driver.h"
#include "BMI088reg.h"
#include "cmsis_os.h"

#include <stdlib.h>
#include <string.h>

#define BMI088_GYRO_RX_BUF_DATA_OFFSET  1
#define BMI088_ACCEL_RX_BUF_DATA_OFFSET 2

#define SPI_DMA_GYRO_LENGHT       8
#define SPI_DMA_ACCEL_LENGHT      9
#define SPI_DMA_ACCEL_TEMP_LENGHT 4

static BMI088_t *bmi088_instance;
static uint8_t txdata[10];
static uint8_t rxdata[10];

static fp32 INS_palstance[3] = {0.0f, 0.0f, 0.0f};

uint8_t gyro_dma_rx_buf[SPI_DMA_GYRO_LENGHT];
static uint8_t gyro_dma_tx_buf[SPI_DMA_GYRO_LENGHT] = {0x82,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

uint8_t accel_dma_rx_buf[SPI_DMA_ACCEL_LENGHT];
static uint8_t accel_dma_tx_buf[SPI_DMA_ACCEL_LENGHT] = {0x92,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

uint8_t accel_temp_dma_rx_buf[SPI_DMA_ACCEL_TEMP_LENGHT];
static uint8_t accel_temp_dma_tx_buf[SPI_DMA_ACCEL_TEMP_LENGHT] = {0xA2,0xFF,0xFF,0xFF};

fp32 BMI088_ACCEL_SEN = BMI088_ACCEL_3G_SEN;
fp32 BMI088_GYRO_SEN = BMI088_GYRO_2000_SEN;

void BMI088_delay_ms(uint16_t ms)
{
    delayMs(ms);
}

void BMI088_delay_us(uint16_t us)
{
    delayUs(us);
}


#if defined(BMI088_USE_SPI)

#define BMI088_accel_write_single_reg(reg, data) 				\
    {                                            				\
		txdata[0]=reg; txdata[1]=data;							\
		spiSetMode(bmi088_instance->accel_spi,SPI_BLOCK_MODE);	\
		spiTransmit(bmi088_instance->accel_spi,txdata,2);		\
    }
#define BMI088_accel_read_single_reg(reg, data)					\
    {                                           				\
		txdata[0]=0x80 | reg; txdata[1]=0x55; txdata[2]=0x55;					\
		spiSetMode(bmi088_instance->accel_spi,SPI_BLOCK_MODE);	\
		spiTransRecv(bmi088_instance->accel_spi,rxdata,txdata,3);\
        (data) = rxdata[2];  									\
    }
//#define BMI088_accel_write_muli_reg( reg,  data, len) { BMI088_ACCEL_NS_L(); BMI088_write_muli_reg(reg, data, len); BMI088_ACCEL_NS_H(); }
#define BMI088_accel_read_muli_reg(reg, data, len) 				\
    {                                              				\
		txdata[0]=0x80 | reg;									\
		spiSetMode(bmi088_instance->accel_spi,SPI_BLOCK_MODE);	\
		spiTransRecv(bmi088_instance->accel_spi,rxdata,txdata,len+2);\
		memcpy(data,rxdata+2,len);								\
    }



#define BMI088_gyro_write_single_reg(reg, data) 				\
    {                                           				\
		txdata[0]=reg; txdata[1]=data;							\
		spiSetMode(bmi088_instance->gyro_spi,SPI_BLOCK_MODE);	\
		spiTransmit(bmi088_instance->gyro_spi,txdata,2);		\
    }
#define BMI088_gyro_read_single_reg(reg, data)  				\
    {                                           				\
		txdata[0]=0x80 | reg; txdata[1]=0x55;					\
		spiSetMode(bmi088_instance->gyro_spi,SPI_BLOCK_MODE);	\
		spiTransRecv(bmi088_instance->gyro_spi,rxdata,txdata,2);\
        (data) = rxdata[1];  									\
    }
//#define BMI088_gyro_write_muli_reg( reg,  data, len) { BMI088_GYRO_NS_L(); BMI088_write_muli_reg( ( reg ), ( data ), ( len ) ); BMI088_GYRO_NS_H(); }
#define BMI088_gyro_read_muli_reg(reg, data, len)   			\
    {                                               			\
		txdata[0]=0x80 | reg;									\
		spiSetMode(bmi088_instance->gyro_spi,SPI_BLOCK_MODE);	\
        spiTransRecv(bmi088_instance->gyro_spi,rxdata,txdata,len+1);\
		memcpy(data,rxdata+1,len);								\
    }

static void BMI088_write_single_reg(uint8_t reg, uint8_t data);
static void BMI088_read_single_reg(uint8_t reg, uint8_t *return_data);
//static void BMI088_write_muli_reg(uint8_t reg, uint8_t* buf, uint8_t len );
static void BMI088_read_muli_reg(uint8_t reg, uint8_t *buf, uint8_t len);

#elif defined(BMI088_USE_IIC)


#endif

static uint8_t write_BMI088_accel_reg_data_error[BMI088_WRITE_ACCEL_REG_NUM][3] =
    {
        {BMI088_ACC_PWR_CTRL, BMI088_ACC_ENABLE_ACC_ON, BMI088_ACC_PWR_CTRL_ERROR},
        {BMI088_ACC_PWR_CONF, BMI088_ACC_PWR_ACTIVE_MODE, BMI088_ACC_PWR_CONF_ERROR},
        {BMI088_ACC_CONF,  BMI088_ACC_NORMAL| BMI088_ACC_800_HZ | BMI088_ACC_CONF_MUST_Set, BMI088_ACC_CONF_ERROR},
        {BMI088_ACC_RANGE, BMI088_ACC_RANGE_3G, BMI088_ACC_RANGE_ERROR},
        {BMI088_INT1_IO_CTRL, BMI088_ACC_INT1_IO_ENABLE | BMI088_ACC_INT1_GPIO_PP | BMI088_ACC_INT1_GPIO_LOW, BMI088_INT1_IO_CTRL_ERROR},
        {BMI088_INT_MAP_DATA, BMI088_ACC_INT1_DRDY_INTERRUPT, BMI088_INT_MAP_DATA_ERROR}

};

static uint8_t write_BMI088_gyro_reg_data_error[BMI088_WRITE_GYRO_REG_NUM][3] =
    {
        {BMI088_GYRO_RANGE, BMI088_GYRO_2000, BMI088_GYRO_RANGE_ERROR},
        {BMI088_GYRO_BANDWIDTH, BMI088_GYRO_1000_116_HZ | BMI088_GYRO_BANDWIDTH_MUST_Set, BMI088_GYRO_BANDWIDTH_ERROR},
        {BMI088_GYRO_LPM1, BMI088_GYRO_NORMAL_MODE, BMI088_GYRO_LPM1_ERROR},
        {BMI088_GYRO_CTRL, BMI088_DRDY_ON, BMI088_GYRO_CTRL_ERROR},
        {BMI088_GYRO_INT3_INT4_IO_CONF, BMI088_GYRO_INT3_GPIO_PP | BMI088_GYRO_INT3_GPIO_LOW, BMI088_GYRO_INT3_INT4_IO_CONF_ERROR},
        {BMI088_GYRO_INT3_INT4_IO_MAP, BMI088_GYRO_DRDY_IO_INT3, BMI088_GYRO_INT3_INT4_IO_MAP_ERROR}

};

static void imu_cmd_spi_dma(void)
{
    UBaseType_t uxSavedInterruptStatus;
    uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

    if((bmi088_instance->state.gyro_update_flag & (1 << IMU_DR_SHFITS)) && (bmi088_instance->gyro_spi->spi_work_mode == SPI_DMA_MODE)\
    && !(bmi088_instance->state.accel_update_flag & (1 << IMU_SPI_SHFITS)) && !(bmi088_instance->state.accel_temp_update_flag & (1 << IMU_SPI_SHFITS)))
    {
        bmi088_instance->state.gyro_update_flag &= ~(1 << IMU_DR_SHFITS);
        bmi088_instance->state.gyro_update_flag |= (1 << IMU_SPI_SHFITS);

        spiTransRecv(bmi088_instance->gyro_spi, gyro_dma_rx_buf, gyro_dma_tx_buf, SPI_DMA_GYRO_LENGHT);

        taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
        return;
    }

    if((bmi088_instance->state.accel_update_flag & (1 << IMU_DR_SHFITS)) && (bmi088_instance->accel_spi->spi_work_mode == SPI_DMA_MODE)\
    && !(bmi088_instance->state.gyro_update_flag & (1 << IMU_SPI_SHFITS)) && !(bmi088_instance->state.accel_temp_update_flag & (1 << IMU_SPI_SHFITS)))
    {
        bmi088_instance->state.accel_update_flag &= ~(1 << IMU_DR_SHFITS);
        bmi088_instance->state.accel_update_flag |= (1 << IMU_SPI_SHFITS);

        spiTransRecv(bmi088_instance->accel_spi, accel_dma_rx_buf, accel_dma_tx_buf, SPI_DMA_ACCEL_LENGHT);

        taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
        return;
    }
		
    if((bmi088_instance->state.accel_temp_update_flag & (1 << IMU_DR_SHFITS)) && (bmi088_instance->accel_spi->spi_work_mode == SPI_DMA_MODE)\
    && !(bmi088_instance->state.gyro_update_flag & (1 << IMU_SPI_SHFITS)) && !(bmi088_instance->state.accel_update_flag & (1 << IMU_SPI_SHFITS)))
    {
        bmi088_instance->state.accel_temp_update_flag &= ~(1 << IMU_DR_SHFITS);
        bmi088_instance->state.accel_temp_update_flag |= (1 << IMU_SPI_SHFITS);

        spiTransRecv(bmi088_instance->accel_spi, accel_temp_dma_rx_buf, accel_temp_dma_tx_buf, SPI_DMA_ACCEL_TEMP_LENGHT);

        taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
        return;
    }
    taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
}

static void bmi088AccelSpiCallback(SPI_Device_t* device){
	if(bmi088_instance->accel_spi == device){
        
        if(bmi088_instance->state.accel_update_flag & (1 << IMU_SPI_SHFITS))
        {
            bmi088_instance->state.accel_update_flag &= ~(1 << IMU_SPI_SHFITS);
			BMI088_accel_read_over(accel_dma_rx_buf + BMI088_ACCEL_RX_BUF_DATA_OFFSET, bmi088_instance->data.accel, &bmi088_instance->data.time);
        }
		if(bmi088_instance->state.accel_temp_update_flag & (1 << IMU_SPI_SHFITS))
		{
			bmi088_instance->state.accel_temp_update_flag &= ~(1 << IMU_SPI_SHFITS);
			BMI088_temperature_read_over(accel_temp_dma_rx_buf + BMI088_ACCEL_RX_BUF_DATA_OFFSET, &bmi088_instance->data.temp);
		}
		imu_cmd_spi_dma();
    }
	
}

static void bmi088AccelExtiCallback(GPIOInstance* instance){
	if(bmi088_instance->accel_exti == instance)
    {
        bmi088_instance->state.accel_update_flag |= 1 << IMU_DR_SHFITS;
        bmi088_instance->state.accel_temp_update_flag |= 1 << IMU_DR_SHFITS;
        if(bmi088_instance->accel_spi->spi_work_mode == SPI_DMA_MODE)
        {
            imu_cmd_spi_dma();
        }
    }
}

static void bmi088GyroSpiCallback(SPI_Device_t* device){
	if(bmi088_instance->gyro_spi == device){
        if(bmi088_instance->state.gyro_update_flag & (1 << IMU_SPI_SHFITS))
        {
            bmi088_instance->state.gyro_update_flag &= ~(1 << IMU_SPI_SHFITS);
			BMI088_gyro_read_over(gyro_dma_rx_buf + BMI088_GYRO_RX_BUF_DATA_OFFSET, bmi088_instance->data.gyro, INS_palstance);
        }
		imu_cmd_spi_dma();
    }
}

static void bmi088GyroExtiCallback(GPIOInstance* instance){
	if(bmi088_instance->gyro_exti == instance)
    {
        bmi088_instance->state.gyro_update_flag |= 1 << IMU_DR_SHFITS;
        if(bmi088_instance->gyro_spi->spi_work_mode == SPI_DMA_MODE)
        {
            imu_cmd_spi_dma();
        }
    }
}

BMI088_t *bmi088Register(BMI088_Register_t *reg){
	
	bmi088_instance = (BMI088_t *)malloc(sizeof(BMI088_t));
	SPI_Register_t spi_reg;
	PWM_Register_t pwm_reg;
    GPIO_Init_Config_s gpio_reg;
	
	spi_reg.spi_handle		= reg->spi_handle;
	spi_reg.spi_work_mode 	= SPI_BLOCK_MODE;
	spi_reg.GPIOx			= reg->accel_GPIOx;
	spi_reg.cs_pin			= reg->accel_cs_pin;
	spi_reg.callback		= bmi088AccelSpiCallback;
	bmi088_instance->accel_spi = spiRegister(&spi_reg);
	
	spi_reg.spi_work_mode 	= SPI_BLOCK_MODE;
	spi_reg.GPIOx			= reg->gyro_GPIOx;
	spi_reg.cs_pin			= reg->gyro_cs_pin;
	spi_reg.spi_handle		= reg->spi_handle;
	spi_reg.callback		= bmi088GyroSpiCallback;
	bmi088_instance->gyro_spi = spiRegister(&spi_reg);
	
    gpio_reg.GPIOx                  = reg->accel_INT1_GPIOx;
	gpio_reg.GPIO_Pin				= reg->accel_INT1_pin;
    gpio_reg.exti_mode              = GPIO_EXTI_MODE_FALLING;
    gpio_reg.gpio_model_callback    = bmi088AccelExtiCallback;
	bmi088_instance->accel_exti = GPIORegister(&gpio_reg);

    gpio_reg.GPIOx                  = reg->gyro_INT1_GPIOx;
	gpio_reg.GPIO_Pin				= reg->gyro_INT1_pin;
    gpio_reg.exti_mode              = GPIO_EXTI_MODE_FALLING;
    gpio_reg.gpio_model_callback    = bmi088GyroExtiCallback;
	bmi088_instance->gyro_exti = GPIORegister(&gpio_reg);
	
	pwm_reg.htim 		= reg->tim_handle;
	pwm_reg.channel		= reg->channel;
	pwm_reg.period		= 1e6;
	pwm_reg.dutyratio	= 0.0f;
	bmi088_instance->pwm_info = pwmRegister(&pwm_reg);
	
	bmi088_instance->statu =0;
	
	return bmi088_instance;
}

uint8_t BMI088_init()
{
    uint8_t error = BMI088_NO_ERROR;
    // GPIO and SPI  Init .
	
	
    // self test pass and init
    if (bmi088_accel_self_test() != BMI088_NO_ERROR)
    {
        error |= BMI088_SELF_TEST_ACCEL_ERROR;
    }
    else
    {
        error |= bmi088_accel_init();
    }

    if (bmi088_gyro_self_test() != BMI088_NO_ERROR)
    {
        error |= BMI088_SELF_TEST_GYRO_ERROR;
    }
    else
    {
        error |= bmi088_gyro_init();
    }
	
	if(error == BMI088_NO_ERROR){
		spiSetMode(bmi088_instance->accel_spi,SPI_DMA_MODE);
		spiSetMode(bmi088_instance->gyro_spi,SPI_DMA_MODE);
		spiTransRecv(bmi088_instance->accel_spi,accel_dma_rx_buf,accel_dma_tx_buf,SPI_DMA_ACCEL_LENGHT);
		spiTransRecv(bmi088_instance->gyro_spi,gyro_dma_rx_buf,gyro_dma_tx_buf,SPI_DMA_GYRO_LENGHT);
	}
	
    return error;
}

bool_t bmi088_accel_init(void)
{
    volatile uint8_t res = 0;
    uint8_t write_reg_num = 0;

    //check commiunication
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    //accel software reset
    BMI088_accel_write_single_reg(BMI088_ACC_SOFTRESET, BMI088_ACC_SOFTRESET_VALUE);
    BMI088_delay_ms(BMI088_LONG_DELAY_TIME);

    //check commiunication is normal after reset
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    // check the "who am I"
    if (res != BMI088_ACC_CHIP_ID_VALUE)
    {
        return BMI088_NO_SENSOR;
    }

    //set accel sonsor config and check
    for (write_reg_num = 0; write_reg_num < BMI088_WRITE_ACCEL_REG_NUM; write_reg_num++)
    {

        BMI088_accel_write_single_reg(write_BMI088_accel_reg_data_error[write_reg_num][0], write_BMI088_accel_reg_data_error[write_reg_num][1]);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        BMI088_accel_read_single_reg(write_BMI088_accel_reg_data_error[write_reg_num][0], res);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        if (res != write_BMI088_accel_reg_data_error[write_reg_num][1])
        {
            return write_BMI088_accel_reg_data_error[write_reg_num][2];
        }
    }
    return BMI088_NO_ERROR;
}

bool_t bmi088_gyro_init(void)
{
    uint8_t write_reg_num = 0;
    uint8_t res = 0;

    //check commiunication
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    //reset the gyro sensor
    BMI088_gyro_write_single_reg(BMI088_GYRO_SOFTRESET, BMI088_GYRO_SOFTRESET_VALUE);
    BMI088_delay_ms(BMI088_LONG_DELAY_TIME);
    //check commiunication is normal after reset
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    // check the "who am I"
    if (res != BMI088_GYRO_CHIP_ID_VALUE)
    {
        return BMI088_NO_SENSOR;
    }

    //set gyro sonsor config and check
    for (write_reg_num = 0; write_reg_num < BMI088_WRITE_GYRO_REG_NUM; write_reg_num++)
    {

        BMI088_gyro_write_single_reg(write_BMI088_gyro_reg_data_error[write_reg_num][0], write_BMI088_gyro_reg_data_error[write_reg_num][1]);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        BMI088_gyro_read_single_reg(write_BMI088_gyro_reg_data_error[write_reg_num][0], res);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        if (res != write_BMI088_gyro_reg_data_error[write_reg_num][1])
        {
            return write_BMI088_gyro_reg_data_error[write_reg_num][2];
        }
    }

    return BMI088_NO_ERROR;
}

bool_t bmi088_accel_self_test(void)
{

    int16_t self_test_accel[2][3];

    uint8_t buf[6] = {0, 0, 0, 0, 0, 0};
    volatile uint8_t res = 0;

    uint8_t write_reg_num = 0;

    static const uint8_t write_BMI088_ACCEL_self_test_Reg_Data_Error[6][3] =
        {
            {BMI088_ACC_CONF, BMI088_ACC_NORMAL | BMI088_ACC_1600_HZ | BMI088_ACC_CONF_MUST_Set, BMI088_ACC_CONF_ERROR},
            {BMI088_ACC_PWR_CTRL, BMI088_ACC_ENABLE_ACC_ON, BMI088_ACC_PWR_CTRL_ERROR},
            {BMI088_ACC_RANGE, BMI088_ACC_RANGE_24G, BMI088_ACC_RANGE_ERROR},
            {BMI088_ACC_PWR_CONF, BMI088_ACC_PWR_ACTIVE_MODE, BMI088_ACC_PWR_CONF_ERROR},
            {BMI088_ACC_SELF_TEST, BMI088_ACC_SELF_TEST_POSITIVE_SIGNAL, BMI088_ACC_PWR_CONF_ERROR},
            {BMI088_ACC_SELF_TEST, BMI088_ACC_SELF_TEST_NEGATIVE_SIGNAL, BMI088_ACC_PWR_CONF_ERROR}

        };

    //check commiunication is normal
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    // reset  bmi088 accel sensor and wait for > 50ms
    BMI088_accel_write_single_reg(BMI088_ACC_SOFTRESET, BMI088_ACC_SOFTRESET_VALUE);
    BMI088_delay_ms(BMI088_LONG_DELAY_TIME);

    //check commiunication is normal
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    if (res != BMI088_ACC_CHIP_ID_VALUE)
    {
        return BMI088_NO_SENSOR;
    }

    // set the accel register
    for (write_reg_num = 0; write_reg_num < 4; write_reg_num++)
    {

        BMI088_accel_write_single_reg(write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num][0], write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num][1]);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        BMI088_accel_read_single_reg(write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num][0], res);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        if (res != write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num][1])
        {
            return write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num][2];
        }
        // accel conf and accel range  . the two register set need wait for > 50ms
        BMI088_delay_ms(BMI088_LONG_DELAY_TIME);
    }

    // self test include postive and negative
    for (write_reg_num = 0; write_reg_num < 2; write_reg_num++)
    {

        BMI088_accel_write_single_reg(write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num + 4][0], write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num + 4][1]);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        BMI088_accel_read_single_reg(write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num + 4][0], res);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        if (res != write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num + 4][1])
        {
            return write_BMI088_ACCEL_self_test_Reg_Data_Error[write_reg_num + 4][2];
        }
        // accel conf and accel range  . the two register set need wait for > 50ms
        BMI088_delay_ms(BMI088_LONG_DELAY_TIME);

        // read response accel
        BMI088_accel_read_muli_reg(BMI088_ACCEL_XOUT_L, buf, 6);

        self_test_accel[write_reg_num][0] = (int16_t)((buf[1]) << 8) | buf[0];
        self_test_accel[write_reg_num][1] = (int16_t)((buf[3]) << 8) | buf[2];
        self_test_accel[write_reg_num][2] = (int16_t)((buf[5]) << 8) | buf[4];
    }

    //set self test off
    BMI088_accel_write_single_reg(BMI088_ACC_SELF_TEST, BMI088_ACC_SELF_TEST_OFF);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(BMI088_ACC_SELF_TEST, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    if (res != (BMI088_ACC_SELF_TEST_OFF))
    {
        return BMI088_ACC_SELF_TEST_ERROR;
    }

    //reset the accel sensor
    BMI088_accel_write_single_reg(BMI088_ACC_SOFTRESET, BMI088_ACC_SOFTRESET_VALUE);
    BMI088_delay_ms(BMI088_LONG_DELAY_TIME);

    if ((self_test_accel[0][0] - self_test_accel[1][0] < 1365) || (self_test_accel[0][1] - self_test_accel[1][1] < 1365) || (self_test_accel[0][2] - self_test_accel[1][2] < 680))
    {
        return BMI088_SELF_TEST_ACCEL_ERROR;
    }

    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    return BMI088_NO_ERROR;
}
bool_t bmi088_gyro_self_test(void)
{
    uint8_t res = 0;
    uint8_t retry = 0;
    //check commiunication is normal
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    //reset the gyro sensor
    BMI088_gyro_write_single_reg(BMI088_GYRO_SOFTRESET, BMI088_GYRO_SOFTRESET_VALUE);
    BMI088_delay_ms(BMI088_LONG_DELAY_TIME);
    //check commiunication is normal after reset
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, res);
    BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    BMI088_gyro_write_single_reg(BMI088_GYRO_SELF_TEST, BMI088_GYRO_TRIG_BIST);
    BMI088_delay_ms(BMI088_LONG_DELAY_TIME);

    do
    {

        BMI088_gyro_read_single_reg(BMI088_GYRO_SELF_TEST, res);
        BMI088_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
        retry++;
    } while (!(res & BMI088_GYRO_BIST_RDY) && retry < 10);

    if (retry == 10)
    {
        return BMI088_SELF_TEST_GYRO_ERROR;
    }

    if (res & BMI088_GYRO_BIST_FAIL)
    {
        return BMI088_SELF_TEST_GYRO_ERROR;
    }

    return BMI088_NO_ERROR;
}

void BMI088_read_gyro_who_am_i(void)
{
    uint8_t buf;
    BMI088_gyro_read_single_reg(BMI088_GYRO_CHIP_ID, buf);
}


void BMI088_read_accel_who_am_i(void)
{
    volatile uint8_t buf;
    BMI088_accel_read_single_reg(BMI088_ACC_CHIP_ID, buf);
    buf = 0;

}





void BMI088_temperature_read_over(uint8_t *rx_buf, fp32 *temperate)
{
    bmi088_instance->raw_data.temp = (int16_t)((rx_buf[0] << 3) | (rx_buf[1] >> 5));

    if (bmi088_instance->raw_data.temp > 1023)
    {
        bmi088_instance->raw_data.temp -= 2048;
    }
    *temperate = bmi088_instance->raw_data.temp * BMI088_TEMP_FACTOR + BMI088_TEMP_OFFSET;

}

void BMI088_accel_read_over(uint8_t *rx_buf, fp32 accel[3], fp32 *time)
{
    uint32_t sensor_time;
	
    bmi088_instance->raw_data.accel[0] = (int16_t)((rx_buf[1]) << 8) | rx_buf[0];
    accel[0] = bmi088_instance->raw_data.accel[0] * BMI088_ACCEL_SEN;
    bmi088_instance->raw_data.accel[1] = (int16_t)((rx_buf[3]) << 8) | rx_buf[2];
    accel[1] = bmi088_instance->raw_data.accel[1] * BMI088_ACCEL_SEN;
    bmi088_instance->raw_data.accel[2] = (int16_t)((rx_buf[5]) << 8) | rx_buf[4];
    accel[2] = bmi088_instance->raw_data.accel[2] * BMI088_ACCEL_SEN;
	
    sensor_time = (uint32_t)((rx_buf[8] << 16) | (rx_buf[7] << 8) | rx_buf[6]);
    *time = sensor_time * 39.0625f;

}

void BMI088_gyro_read_over(uint8_t *rx_buf, fp32 gyro[3], fp32 palstance[3])
{
    bmi088_instance->raw_data.gyro[0] = (int16_t)((rx_buf[1]) << 8) | rx_buf[0];
    gyro[0] = bmi088_instance->raw_data.gyro[0] * BMI088_GYRO_SEN;
    palstance[0] = bmi088_instance->raw_data.gyro[0] / 32768.0f * 2000.0f;
    bmi088_instance->raw_data.gyro[1] = (int16_t)((rx_buf[3]) << 8) | rx_buf[2];
    gyro[1] = bmi088_instance->raw_data.gyro[1] * BMI088_GYRO_SEN;
    palstance[1] = bmi088_instance->raw_data.gyro[1] / 32768.0f * 2000.0f;
    bmi088_instance->raw_data.gyro[2] = (int16_t)((rx_buf[5]) << 8) | rx_buf[4];
    gyro[2] = bmi088_instance->raw_data.gyro[2] * BMI088_GYRO_SEN;
    palstance[2] = bmi088_instance->raw_data.gyro[2] / 32768.0f * 2000.0f;
}

void BMI088_read(fp32 gyro[3], fp32 accel[3], fp32 *temperate)
{
    uint8_t buf[8] = {0, 0, 0, 0, 0, 0};
    int16_t bmi088_raw_temp;

    BMI088_accel_read_muli_reg(BMI088_ACCEL_XOUT_L, buf, 6);

    bmi088_raw_temp = (int16_t)((buf[1]) << 8) | buf[0];
    accel[0] = bmi088_raw_temp * BMI088_ACCEL_SEN;
    bmi088_raw_temp = (int16_t)((buf[3]) << 8) | buf[2];
    accel[1] = bmi088_raw_temp * BMI088_ACCEL_SEN;
    bmi088_raw_temp = (int16_t)((buf[5]) << 8) | buf[4];
    accel[2] = bmi088_raw_temp * BMI088_ACCEL_SEN;

    BMI088_gyro_read_muli_reg(BMI088_GYRO_CHIP_ID, buf, 8);
    if(buf[0] == BMI088_GYRO_CHIP_ID_VALUE)
    {
        bmi088_raw_temp = (int16_t)((buf[3]) << 8) | buf[2];
        gyro[0] = bmi088_raw_temp * BMI088_GYRO_SEN;
        bmi088_raw_temp = (int16_t)((buf[5]) << 8) | buf[4];
        gyro[1] = bmi088_raw_temp * BMI088_GYRO_SEN;
        bmi088_raw_temp = (int16_t)((buf[7]) << 8) | buf[6];
        gyro[2] = bmi088_raw_temp * BMI088_GYRO_SEN;
    }
    BMI088_accel_read_muli_reg(BMI088_TEMP_M, buf, 2);

    bmi088_raw_temp = (int16_t)((buf[0] << 3) | (buf[1] >> 5));

    if (bmi088_raw_temp > 1023)
    {
        bmi088_raw_temp -= 2048;
    }

    *temperate = bmi088_raw_temp * BMI088_TEMP_FACTOR + BMI088_TEMP_OFFSET;
}

uint32_t get_BMI088_sensor_time(void)
{
    uint32_t sensor_time = 0;
    uint8_t buf[3];
    BMI088_accel_read_muli_reg(BMI088_SENSORTIME_DATA_L, buf, 3);

    sensor_time = (uint32_t)((buf[2] << 16) | (buf[1] << 8) | (buf[0]));

    return sensor_time;
}

fp32 get_BMI088_temperate(void)
{
    uint8_t buf[2];
    fp32 temperate;
    int16_t temperate_raw_temp;

    BMI088_accel_read_muli_reg(BMI088_TEMP_M, buf, 2);

    temperate_raw_temp = (int16_t)((buf[0] << 3) | (buf[1] >> 5));

    if (temperate_raw_temp > 1023)
    {
        temperate_raw_temp -= 2048;
    }

    temperate = temperate_raw_temp * BMI088_TEMP_FACTOR + BMI088_TEMP_OFFSET;

    return temperate;
}

void get_BMI088_gyro(int16_t gyro[3])
{
    uint8_t buf[6] = {0, 0, 0, 0, 0, 0};
    int16_t gyro_raw_temp;

    BMI088_gyro_read_muli_reg(BMI088_GYRO_X_L, buf, 6);

    gyro_raw_temp = (int16_t)((buf[1]) << 8) | buf[0];
    gyro[0] = gyro_raw_temp ;
    gyro_raw_temp = (int16_t)((buf[3]) << 8) | buf[2];
    gyro[1] = gyro_raw_temp ;
    gyro_raw_temp = (int16_t)((buf[5]) << 8) | buf[4];
    gyro[2] = gyro_raw_temp ;
}

void get_BMI088_accel(fp32 accel[3])
{
    uint8_t buf[6] = {0, 0, 0, 0, 0, 0};
    int16_t accel_raw_temp;

    BMI088_accel_read_muli_reg(BMI088_ACCEL_XOUT_L, buf, 6);

    accel_raw_temp = (int16_t)((buf[1]) << 8) | buf[0];
    accel[0] = accel_raw_temp * BMI088_ACCEL_SEN;
    accel_raw_temp = (int16_t)((buf[3]) << 8) | buf[2];
    accel[1] = accel_raw_temp * BMI088_ACCEL_SEN;
    accel_raw_temp = (int16_t)((buf[5]) << 8) | buf[4];
    accel[2] = accel_raw_temp * BMI088_ACCEL_SEN;
}
