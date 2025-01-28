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

## Video tutorial: How to use the Skeleton Solver with Unreal

https://www.qualisys.com/my/qacademy/#!/tutorials/how-to-use-the-skeleton-solver-with-unreal

## Supported Unreal Build Platforms

* Windows 64bit
* MacOS
* Linux



## Building the Plugin with Unreal Engine
Note: In most cases, you can simply install and use this plugin directly from the Unreal Marketplace. The instructions below are for those who need or prefer to build the plugin from source (e.g., for custom development or modifications).
1. **Set Up Your Environment**  
   - Make sure your environment is ready to [build plugins](https://dev.epicgames.com/community/learning/tutorials/qz93/unreal-engine-building-plugins).  
   - Use a C++ Unreal Engine project and have the necessary SDKs installed (e.g., Visual Studio on Windows, Xcode on macOS, etc.).

2. **Clone This Repository (With Submodules)**  
   - **Important**: **Do not** clone it **inside** your existing UE project folder. Pick a separate directory.  
   - Example:
     ```bash
     git clone --recurse-submodules https://github.com/qualisys/QTM-Connect-For-Unreal.git
     ```
   - If you already cloned without submodules, run:
     ```bash
     cd QTM-Connect-For-Unreal
     git submodule update --init --recursive
     ```

3. **Run the Copy Script**  
  This script copies necessary files from the `qualisys_cpp_sdk` submodule into the plugin’s internal directories.
   - On **Windows**:
     ```cmd
     .\copy_sdk.bat
     ```
   - On **macOS/Linux**:
        ```bash
        chmod +x copy_sdk.sh
        ./copy_sdk.sh
        ```

1. **Copy the `Qualisys` Folder to Your UE Project’s `Plugins` Folder**  
   - Copy the entire `Qualisys` folder (for example, `Qualisys/QTMConnectLiveLink`) to your UE project’s `Plugins` folder.  
   - If a `Plugins` folder does not exist in your project, create one at the root of the project directory.  
   - Your final structure might look like this:
     ```
     YourProject
     ┣━ Plugins
     ┃  ┗━ Qualisys
     ┃     ┗━ QTMConnectLiveLink
     ┃        ┣━ Source
     ┃        ┣━ ...
     ┣━ Source
     ┣━ YourProject.uproject
     ```

2. **Open the Project in Unreal Engine**  
   - Launch the Unreal Editor and open your `.uproject` file.  
   - When prompted, allow Unreal to rebuild your plugin automatically.  
   - After the rebuild completes, the plugin should be available for use in your project.
