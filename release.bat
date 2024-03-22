@echo off
set source_folder=.\
set taget_folder=.\release
set src_file=*.c
set inc_file=*.h

md %taget_folder%\inc
md %taget_folder%\src

del /q/a/f/s %taget_folder%\*.*

for /r %source_folder% %%i in (%src_file%) do (
	echo %%~dpi | findstr "__init" >nul ||(
		echo %%~dpi | findstr "release" >nul ||(
			copy %%i %taget_folder%\src
		)
	)
)
for /r %source_folder% %%i in (%inc_file%) do (
	echo %%~dpi | findstr "__init" >nul ||(
		echo %%~dpi | findstr "release" >nul ||(
			echo %%~dpi | findstr "Config" >nul ||(
				copy %%i %taget_folder%\inc
			)
		)
	)
)

copy .\Config %taget_folder%
