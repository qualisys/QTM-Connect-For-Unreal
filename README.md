# QTM Connect for Unreal

QTM Connect for Unreal is an Unreal plugin that supports streaming of 6DOF data between Qualisys Track Manager and Unreal.

## Installation of the plugin

Copy the entire Qualisys plugin directory to C:\Program Files\Epic Games\UE_4.xx\Engine\Plugins.
The plugin should appear in the plugin window as "QTM Connect For Unreal".

## How to use the QualisysClient actor object and QualisysRigidBody actorcomponent object

1. The QualisysClient object is available in the UE4 Modes panel. This object handles the data streaming between QTM and Unreal.
2. Drag and drop the QualisysClient object in the world.
3. Select the QualisysClient instance and edit it's properties. (IP address of the machine running QTM, UdpPort to stream on (0 will use TCP streaming instead) and stream rate (StreamRate of 0 will stream as quick as possible).
4. Add a Qualisys RigidBody component to a object in the World Outliner pane.
5. Set the RigidBody name to the name of the RigidBody in QTM.
6. Play scene. It should connect to QTM and stream 6DOF data.

## Supported Unreal version(s)

4.16.3
