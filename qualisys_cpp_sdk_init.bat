@echo off

set "dir_private=Qualisys\QTMConnectLiveLink\Source\QTMConnectLiveLink\Private\RTClientSDK"

echo Ensuring directories exist...
if not exist "%dir_private%" (
    mkdir "%dir_private%"
    echo Created %dir_private%
)

echo Copying files from qualisys_cpp_sdk into %dir_private%
copy /Y "qualisys_cpp_sdk\Markup.cpp" "%dir_private%"
copy /Y "qualisys_cpp_sdk\Network.cpp" "%dir_private%"
copy /Y "qualisys_cpp_sdk\RTPacket.cpp" "%dir_private%"
copy /Y "qualisys_cpp_sdk\RTProtocol.cpp" "%dir_private%"
copy /Y "qualisys_cpp_sdk\Markup.h" "%dir_private%"
copy /Y "qualisys_cpp_sdk\Network.h" "%dir_private%"
copy /Y "qualisys_cpp_sdk\RTPacket.h" "%dir_private%"
copy /Y "qualisys_cpp_sdk\RTProtocol.h" "%dir_private%"
echo Copying files from qualisys_cpp_sdk into %dir_private%