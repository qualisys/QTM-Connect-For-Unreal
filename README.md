# QTM Connect for Unreal

QTM Connect for Unreal is an Unreal plugin that supports streaming of skeleton, rigid body and marker data between Qualisys Track Manager and Unreal Engine.

## Installation of the plugin

*Note that the pre-built dll's for each version can be found here:*
- *[UE 4.24](https://github.com/qualisys/QTM-Connect-For-Unreal/tree/Prebuilt-UE_4.24)*
- *[UE 4.23](https://github.com/qualisys/QTM-Connect-For-Unreal/tree/Prebuilt-UE_4.23)*
- *[UE 4.22](https://github.com/qualisys/QTM-Connect-For-Unreal/tree/Prebuilt-UE_4.22)*
- *[UE 4.21](https://github.com/qualisys/QTM-Connect-For-Unreal/tree/Prebuilt-UE_4.21)*
- *Note: If the plugin should be used in a unsupported Unreal Engine version then put it in the `Unreal project folder\Plugins` and rebuild project.*

1. Copy the directory `.\Prebuilt\Qualisys` to `C:\Program Files\Epic Games\UE_4.xx\Engine\Plugins`.
    -  _Optional: Copy `.\Example Project` to `C:\Users\<user>\Documents\Unreal Projects`_
2. Start Unreal and create a project.
    -  _Optional: Open Project `QualisysAvatar` from step 1._
3. The plugin should appear in the plugin window as "QTM Connect For Unreal". Click Enable and restart Unreal to get it activated.

## How to use the QTM Connect LiveLink plugin

1. Start QTM in preview mode or file mode being sure there is a skeleton to stream. An example qtm file including a skeleton is provided in `.\Example Project`
2. Enable `LiveLink` and `QTMConnectLiveLink` in Unreal under `Edit->Plugins`.
3. Go to `Window->Live Link`, click `Add->QTM Connect LiveLink`, enter the QTM IP address and port and click ok.
4. If the Skeleton of the Skeletal Mesh that you wish to animate matches the skeleton data being streamed from QTM (same bone names and hierarchy), then skip steps 5-7.
5. In the Content Browser, click `Add New->Blueprint Class` and expand `All Classes` and search for `QualisysLiveLinkRetargetAsset`, and click `Select`.
6. Double-click the retarget asset and go to `Details->Bone Mapping` and expand the `Bone Mapping` variable.
7. In the right column, fill in the names of the Skeleton bones that best correspond to the QTM skeleton bones seen in the left column. If there is no corresponding 
   bone or the bone name already matches the QTM bone name, leave it as "None".
8. In the Content Browser, go to the Skeletal Mesh that you wish to animate and `Right-click->Create->Anim Blueprint`. Give it a name and then double click on it.
9. Right-click anywhere in the animation graph and search for the Live Link Pose node.
10. Enter the subject name (the name of the skeleton being streamed from QTM), and connect the output pose to the input pose of the Final Animation Pose node.
11. Click on the `Live Link Pose` node and go to `Details->Retarget->Retarget Asset` and select the retarget asset you created in step 5, or choose the QualisysLiveLinkRetargetAsset 
   if you skipped steps 5-7. 
12. Click Compile, and you should see the mesh moving in the preview window. 
13. Drag the animation blueprint you created in step 8 into your scene, then click Play.

## How to use the QualisysClient Actor object and QualisysRigidBody ActorComponent object

1. The QualisysClient object is available in the UE4 Modes panel. This object handles the data streaming between QTM and Unreal.
2. Drag and drop the QualisysClient object in the world.
3. Select the QualisysClient instance and edit it's properties. (IP address of the machine running QTM, UdpPort to stream on (0 will use TCP streaming) and stream rate (StreamRate of 0 will stream data as quick as possible).
4. Add a Qualisys RigidBody component to a object in the World Outliner pane.
5. Make sure the object is set to moveable.
6. Set the RigidBody name to the name of the RigidBody in QTM.
7. Play scene. It will automatically try and connect to QTM and receive 6DOF data.
8. Use DebugDrawing setting in QualisysClient to display all labeled trajectories as spheres and all rigid bodies as cubes.

*Note: To connect position of a component to position of a labeled trajectory use the QualisysTrajectory ActorComponent.*

## Video tutorials

1. *[Streaming tutorial video](https://www.youtube.com/watch?v=lJ3CwEu2OxY)*
2. *[Bone mapping tutorial video](https://www.youtube.com/watch?v=YZ24RH2_LZM)*
3. *[How to import a Qualisys Track Manager exported FBX](https://www.youtube.com/watch?v=IC70NnnBw60)*

## Supported Unreal Build Platforms

* Windows 64bit
