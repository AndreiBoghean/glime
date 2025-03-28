there are 2 separate workflows to follow when using this project.
one for a PineTime user that wants to develop an application using the abstraction library
and one for a OS maintainer or independent developer that wants to add support for the library to their own OS.

<details>

<summary>as an application developer</summary>

##### setup
setup should be as simple as cloning the respective OS which you wish to run your app on,  
and following the repository's instructions for dependencies, building, and optionally installing glime support if it's not enabled by default.

for most people, **you should not clone glime directly unless you wish to swap between multiple operating systems**, only then should you pre-emptively clone glime and then follow the OS's instructions for using an _existing_ glime download.

<!--
1. clone this repo
2. clone the respective modified OS which you wish to run your app on.
3. follow the operating system's instructions for dependencies, building, and optionally installing glime support if it's not enabled by default.
-->

##### usage
**your entire application will be situated within `glime/externApp.cpp`**  
the glime compatability library pre-configures an application in the host operating system, which wraps arround the application you write
within extern_main(), and executes it when the watch user launches the wrapper app.
**note:** the main entry point for your application is demonstrated in `glime/externApp.h`

**you are limited to using the functions provided in `compat.h`**, however the compatability library requires these functions
are implemented in every supporting operating system, ensuring your application's cross-compatability.
</details>

<details>

<summary>as an OS maintainer</summary>

1. clone this repo
2. augment your watch operating system to provide implementations for the functions defined in `compat.h`
3. also introduce a wrapper application which delegates execution to `glime/wrapApp.cpp` when the app is executed.

the **ideal** approach may include glime as a submodule, and use a symlink to integrate compat.h.

however when modifying someone else's operating system, an alternative **minimally intrusive** approach is to  
create a `glimeSupport/installGlime.sh` script which clones this repository and manually modifies the OS code,  
using symlinks to introduce compat.h and the implementation.  
this approach is demonstrated in the "sister repositories" above.

</details>
