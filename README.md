# QTM Connect for Unreal

QTM Connect for Unreal is an Unreal plugin that supports streaming of skeleton, rigid body, marker, force and timecode data between Qualisys Track Manager and Unreal Engine.

## Installation of the plugin
You can find the plugin on unreal engine marketplace [here](https://www.unrealengine.com/marketplace/en-US/product/qualisys-qtm-connect-live-link)

## How to use the QTM Connect LiveLink plugin
### Start live link source
1. Start QTM in preview mode or file mode being sure there is a skeleton to stream. An example qtm file including a skeleton is provided in `.\Example Project`
2. Enable `LiveLink` and `QTMConnectLiveLink` in Unreal under `Edit->Plugins`.
3. Go to `Window->Live Link`, click `Add->QTM Connect LiveLink`
4. Enter the QTM IP address and port and click Create.
### Stream skeleton data
1. If the Skeleton of the Skeletal Mesh that you wish to animate matches the skeleton data being streamed from QTM (same bone names and hierarchy), then skip steps 5-7.
2. In the Content Browser, click `Add New->Blueprint Class` and expand `All Classes` and search for `QualisysLiveLinkRetargetAsset`, and click `Select`.
3. Double-click the retarget asset and go to `Details->Bone Mapping` and expand the `Bone Mapping` variable.
4. In the right column, fill in the names of the Skeleton bones that best correspond to the QTM skeleton bones seen in the left column. If there is no corresponding 
   bone or the bone name already matches the QTM bone name, leave it as "None".
5. In the Content Browser, go to the Skeletal Mesh that you wish to animate and `Right-click->Create->Anim Blueprint`. Give it a name and then double click on it.
6. Right-click anywhere in the animation graph and search for the Live Link Pose node.
7. Enter the subject name (the name of the skeleton being streamed from QTM), and connect the output pose to the input pose of the Final Animation Pose node.
8. Click on the `Live Link Pose` node and go to `Details->Retarget->Retarget Asset` and select the retarget asset you created in step 5, or choose the QualisysLiveLinkRetargetAsset 
   if you skipped steps 5-7. 
9. Click Compile, and you should see the mesh moving in the preview window. 
10. Drag the animation blueprint you created in step 8 into your scene, then click Play.
### Stream rigid body data
1. Select your actor and Add Component `Live Link Controller`.
2. Enter the rigid body name as subject name and `LiveLinkTransformRole` as role.

**Note: If you want to stream your rigid body as an camera role prefix the rigid body name with `cam_` (eg. `cam_rigidbody`)**

### Stream force data
1. Each force plate is a livelink subject with the `basic` role. 
2. The force subject contains the following 9 properties in order. (`Force X`, `Force Y`, `Force Z`, `Moment X`, `Moment Y`, `Moment Z`, `Application Point X`, `Application Point Y`, `Application Point Z`)

*Note: Avoid mixing the LiveLink plugin data with the QualisysClient plugin. Synchronization of data might differ.*

## Video tutorials

1. *[Streaming tutorial video](https://www.youtube.com/watch?v=lJ3CwEu2OxY)*
2. *[Bone mapping tutorial video](https://www.youtube.com/watch?v=YZ24RH2_LZM)*
3. *[How to import a Qualisys Track Manager exported FBX](https://www.youtube.com/watch?v=IC70NnnBw60)*

## Supported Unreal Build Platforms

* Windows 64bit
