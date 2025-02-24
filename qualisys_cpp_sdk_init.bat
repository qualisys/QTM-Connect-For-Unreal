@echo off

set "dir_private=Qualisys\QTMConnectLiveLink\Source\QTMConnectLiveLink\Private\RTClientSDK"
echo Ensuring directory exists...
if not exist "%dir_private%" mkdir "%dir_private%"
echo Copying files from qualisys_cpp_sdk into %dir_private%
xcopy /Y "qualisys_cpp_sdk\Deserializer.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Deserializer.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\LICENSE.md" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Network.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Network.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\RTPacket.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\RTPacket.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\RTProtocol.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\RTProtocol.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Serializer.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Serializer.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Settings.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\Settings.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\SettingsDeserializer.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\SettingsDeserializer.h" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\SettingsSerializer.cpp" "%dir_private%\"
xcopy /Y "qualisys_cpp_sdk\SettingsSerializer.h" "%dir_private%\"
echo Done copying files from qualisys_cpp_sdk into %dir_private%

set "tinyxml2_private=Qualisys\QTMConnectLiveLink\Source\QTMConnectLiveLink\Private\RTClientSDK\External\tinyxml2"
echo Ensuring directory exists...
if not exist "%tinyxml2_private%" mkdir "%tinyxml2_private%"
echo Copying files from qualisys_cpp_sdk into %tinyxml2_private%
xcopy /Y "qualisys_cpp_sdk\External\tinyxml2\LICENSE.txt" "%tinyxml2_private%\"
xcopy /Y "qualisys_cpp_sdk\External\tinyxml2\tinyxml2.cpp" "%tinyxml2_private%\"
xcopy /Y "qualisys_cpp_sdk\External\tinyxml2\tinyxml2.h" "%tinyxml2_private%\"
echo Done copying files from qualisys_cpp_sdk into %tinyxml2_private%
