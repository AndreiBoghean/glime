###### sister repositories:
modified infiniTime: https://github.com/AndreiBoghean/InfiniTime  
modified wasp-os: https://github.com/AndreiBoghean/wasp-os

#### guide:

##### as an application developer:
###### setup
setup should be as simple as cloning the respective modified OS which you wish to run your app on,  
and following the operating system's instructions for dependencies, building, and optionally installing glime support if it's not enabled by default.

if you wish to test multiple operating systems, you should pre-emptively clone glime and then follow the OS's instructions for using an existing glime download.

<!--
1. clone this repo
2. clone the respective modified OS which you wish to run your app on.
3. follow the operating system's instructions for dependencies, building, and optionally installing glime support if it's not enabled by default.
-->

###### usage
your entire application will be situated within glime/externApp.cpp  
the glime compatability library pre-configures an application in the host operating system, which wraps arround the application you write
within extern_main(), and executes it when the watch user launches the wrapper app.

within this environment, you are limited to using the functions provided in compat.h, however the compatability library requires these functions
are implemented in every supporting operating system, ensuring your application's cross-compatability.

##### as an OS maintainer:
1. clone this repo
2. augment your watch operating system to provide implementations for the functions defined in `compat.h`
3. also introduce a wrapper application which delegates execution to `glime/wrapApp.cpp` when the app is executed.

the **ideal** approach may include glime as a submodule, and use a symlink to integrate compat.h.

however when modifying someone else's operating system, an alternative **minimally intrusive** approach is to  
create a `glimeSupport/installGlime.sh` script which clones this repository and manually modifies the OS code,  
using symlinks to introduce compat.h and the implementation.  
this approach is demonstrated in the "sister repositories" above.
