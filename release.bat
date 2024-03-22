@echo off
set source_folder=.

md %source_folder%\release\inc
md %source_folder%\release\src

del /q/a/f/s %source_folder%\release\*.*

for /r %%i in (*.c) do (
	echo %%~dpi | findstr "__init" >nul ||(
		echo %%~dpi | findstr "release" >nul ||(
			copy %%i %source_folder%\release\src
		)
	)
)
for /r %%i in (*.h) do (
	echo %%~dpi | findstr "__init" >nul ||(
		echo %%~dpi | findstr "release" >nul ||(
			copy %%i %source_folder%\release\inc
		)
	)
)
