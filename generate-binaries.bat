@echo off

rem Init qualisys_cpp_sdk submodule
git submodule init
git submodule update

rem copy qualisys_cpp_sdk files
call qualisys_cpp_sdk_init.bat

fltmc >nul 2>&1 && (
  rem Running as admin.
) || (
  echo "ERROR: Installer must be run as admin."
  pause
  exit 1
)

rem Change working directory to directory of batch file using (not always same as script dir)
cd /D "%~dp0"

set "UE_64_ROOT_PATH=C:\Program Files\Epic Games"
set "UE_32_ROOT_PATH=C:\Program Files (x86)\Epic Games"
set UE_ROOT_PATH=""
set CUSTOM_UE_ROOT_PATH=""

rem Localize Unreal Engine root path:
echo.

:while_root_not_found

if exist "%UE_64_ROOT_PATH%" (
    echo "Found 64bit"
    set "UE_ROOT_PATH=%UE_64_ROOT_PATH%"
) else if exist "%UE_32_ROOT_PATH%" (
    echo "Found 32bit"
    set "UE_ROOT_PATH=%UE_32_ROOT_PATH%"
) else if exist "%CUSTOM_UE_ROOT_PATH%" (
    echo "Found custom path %CUSTOM_UE_ROOT_PATH%"
    set "UE_ROOT_PATH=%CUSTOM_UE_ROOT_PATH%"
)

if exist "%UE_ROOT_PATH%\" (
    echo "Unreal Engine root found: %UE_ROOT_PATH%"
) else ( 
    echo "Unreal Engine installation folder not found: %UE_ROOT_PATH%"
    set /p CUSTOM_UE_ROOT_PATH="Please enter Unreal Engine installation path: "
    goto :while_root_not_found
)

:while_version_not_decided

rem Ask user which version of unreal to install to
echo.
echo "Installed versions:"
dir /A:D /B "%UE_ROOT_PATH%"
echo.
set /p UNREAL_VERSION_FOLDER="Select Unreal Engine version to build for: "

rem If nothing was typed by user
if "%UNREAL_VERSION_FOLDER%"=="" (
    goto :while_version_not_decided
)

set "SELECTED_PATH=%UE_ROOT_PATH%\%UNREAL_VERSION_FOLDER%"

if exist "%SELECTED_PATH%\" (
    echo "Unreal Engine version folder found: '%SELECTED_PATH%'."
    set "UE_ROOT_PATH=%SELECTED_PATH%"
) else (
    echo "Could not find path '%SELECTED_PATH%'."
    set UNREAL_VERSION_FOLDER=""
    goto :while_version_not_decided
)

rem Localize "QTM Connect Unreal" plugin root path:
echo.

set "UNREAL_PLUGIN_SOURCE_PATH=%cd%\Qualisys"
set "VERIFY_IF_CORRECT_FOLDER=%UNREAL_PLUGIN_SOURCE_PATH%\QTMConnectLiveLink"

if exist "%VERIFY_IF_CORRECT_FOLDER%" (
    echo "QTM Connect Unreal plugin found."
) else (
    echo "QTM Connect Unreal plugin not found. Installer must be in plugin root."
    pause
    exit 1
)

echo.

rem set "QTM_CONNECT_UNREAL_FOLDER_NAME=Qualisys"
set "UNREAL_PLUGIN_DEST_PATH=%UE_ROOT_PATH%\Engine\Plugins"
echo "Copying plugin to %UNREAL_PLUGIN_DEST_PATH%"


rem This is needed or else variables will only be assigned once
rem Also, expand variables in for loop (or, within parentheses) with !MY_VAR! else it will cache
setlocal enabledelayedexpansion
rem Copy files
for /d %%i in ("%UNREAL_PLUGIN_SOURCE_PATH%\*") do (
    rem Get folder path and name
    set "FOLDER_PATH=%%i"
    set "PLUGIN_NAME=%%~nxi"

    set "SOURCE_DIR=!FOLDER_PATH!"
    set "DEST_DIR=%UNREAL_PLUGIN_DEST_PATH%\!PLUGIN_NAME!\"
    echo "Copying plugin '!PLUGIN_NAME!'..."
    echo.
    xcopy "!SOURCE_DIR!" "!DEST_DIR!" /e /i /h /Y
    echo.
)

set "BUILD_ROOT=%UE_ROOT_PATH%\[TempFolder]\build"

rem Build plugins
for /d %%i in ("%UNREAL_PLUGIN_SOURCE_PATH%\*") do (
    rem Get folder path and name
    set "FOLDER_PATH=%%i"
    set "PLUGIN_NAME=%%~nxi"

    set "PLUGIN_BUILD_DIR=!BUILD_ROOT!\!PLUGIN_NAME!"
    set "PLUGIN_FILE=!UNREAL_PLUGIN_DEST_PATH!\!PLUGIN_NAME!\!PLUGIN_NAME!.uplugin"

    echo "Building plugin '!PLUGIN_NAME!'..."
    rem echo "PLUGIN_BUILD_DIR '!PLUGIN_BUILD_DIR!'"
    rem echo "PLUGIN_FILE '!PLUGIN_FILE!'"

    echo.
    rem Run in sub-processes to not clutter local variables
    start /WAIT /B CMD /C CALL "%UE_ROOT_PATH%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin^
     -Plugin="!PLUGIN_FILE!"^
     -Package="!PLUGIN_BUILD_DIR!"^
     -ClientConfig=Shipping^
     -Configuration=Shipping
    echo.
)

echo.

rem Open build folder
start "" "%BUILD_ROOT%"

if NOT ["%errorlevel%"]==["0"] pause

echo "DONE!"
pause