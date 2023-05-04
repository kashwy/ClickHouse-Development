# Overview
The goal of this document is to show certain features of Visual Studio Code that make it a powerful IDE when used to the fullest extent.

*Note: build times debugger start-up times are measured against an 8 Core 16GB 250GB x86-64 Fyre VM.*



# Prerequisites

2. Install [Visual Studio Code](https://code.visualstudio.com/docs/setup/setup-overview) on your local machine
3. Connect to your Fyre VM as described at [Remote Development using SSH](https://code.visualstudio.com/docs/remote/ssh)
4. [Getting Started Guide for Building ClickHouse](https://clickhouse.com/docs/en/development/developer-instruction)
5. Install [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) on the remote workspace
6. Install GDB (eg. `sudo apt-get install gdb`)

# Useful Extensions
* [C++ TestMate](https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter) for running, filtering and debugging unit tests.
* [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) for debugging using LLDB.
* [SonarLint](https://marketplace.visualstudio.com/items?itemName=SonarSource.sonarlint-vscode) for running Sonar scans locally.

# Glossary
When this guide instructs to `run` a command, it means pressing `Ctrl + Shift + P`, then typing the command and pressing `Enter`.

# Automatic Code Formatting
Run `Format Document`. It's going to use `clang-format` and will take into account repository's own `.clang-format` configuration.

# CMake Integration
Visual Studio Code will prompt you for certain steps automatically, but make sure to go through all the steps. Please note that most of the steps below can be completed using the GUI as well, which is located in the horizontal bar at the bottom of the window.

## Configuration
1. Run `Preferences: Open Remote Settings (JSON) ()`.

    Add `"cmake.clearOutputBeforeBuild": false` to your existing configuration or use `{ "cmake.clearOutputBeforeBuild": false }`. 
2. Run `CMake: Scan for Kits`.
3. Run `CMake: Select a Kit`. Choose your preferred compiler, which should be some version of `Clang`.
4. Run `CMake: Select Variant`. Choose whichever you wish to configure (eg. `Debug`).
5. Run `CMake: Configure`.

## Building
1. Run `CMake: Set Build Target`. Choose whichever you wish to build exclusively (eg. `clickhouse`, `unit_tests_dbms` or `all` if you wish to build everything).
2. Run `CMake: Build`.

### Cutting Build Times (unavailable as of 23.1, because support for it was completely removed)
ClickHouse by default builds and links both external and internal components statically. The outcome of this is a roughly 1.5-minute build time, which can be hard to bear when performing many round-trips of coding and building.

Luckily, [the means are provided](https://clickhouse.com/docs/en/development/developer-instruction/#split-build) to improve this by building and linking both external and internal components dynamically. This results in build times of 5-10 seconds on average, effectively reducing it by more than 90%.

One can run either `CMake: Edit CMake Cache` or `CMake: Edit CMake Cache (UI)` to set the required flags (the ones not mentioned directly by the ClickHouse documentation are in *italic*):
* *FLATBUFFERS_BUILD_SHAREDLIB = 1*
* *GLIBC_COMPATIBILITY = 0*
* USE_STATIC_LIBRARIES = 0
* SPLIT_SHARED_LIBRARIES = 1

## Debugging
1. Open any C++ source file, then under the `Run and Debug` tab press `create a launch.json file`.
2. Press `Add Configuration...` in the bottom right corner. Choose `C/C++: (gdb) Launch`.

    Use `"program": "${command:cmake.launchTargetPath}"` and `"cwd": "${workspaceFolder}/programs"` then specify command-line arguments as necessary.

    Examples:
     - for debugging the `clickhouse` executable with certain arguments `"args": ["local", "--dialect=kusto_auto", "--multiquery"]`
     - for debugging the `unit_tests_dbms` executable with a filter for KQL unit tests `"args": ["--gtest_filter='ParserKQLQuery*'"]`
3. Apply the pretty printing capabilities from [Using-gdb-to-troubleshoot-Clickhouse]()
4. Run `CMake: Set Debug Target`. Choose whichever you wish to debug.
5. Run `CMake: Debug`.

Once the application starts, you should be able to query variables in the `DEBUG CONSOLE` tab and access a terminal with the application of your choice already started in the `TERMINAL` tab.

### Improving Debugger Start-up Time
When using GDB for debugging, one will usually encounter start-up times of 2.5 minutes, which can be very time-consuming when iterating numerous times.

When using [LLDB](https://lldb.llvm.org), start-up times of around 50 seconds are to be expected. In addition to that, stepping should feel more responsive and no additional pretty printers are necessary to support [libc++](https://libcxx.llvm.org), an STL implementation by LLVM that the project uses.

1. Install [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) **!!on the remote workspace only!!**
2. Perform the same steps as [Debugging, Step 2](#debugging) with the exception of selecting `CodeLLDB: Launch` when adding a launch configuration.

# Troubleshooting
1. Whenever I reopen Visual Studio Code, a complete rebuild occurs.

    Make sure to turn the `cmake.clearOutputBeforeBuild` setting off, as described in the [CMake Integration](#cmake-integration) section.
2. I'm getting cryptic error messages when trying to initiate a debug session.

    Make sure to install GDB as mentioned in the [Prerequisites](#prerequisites) section and configure your `launch.json` as described in the [Debugging](#debugging) section.
3. While debugging using LLDB, I cannot step into a function call after having built shared libraries as explained in [Building, Cutting Build Times](#cutting-build-times).

   This is bug in version 14 of LLDB that should be fixed in version 15 (Reference: https://github.com/vadimcn/vscode-lldb/issues/587 & https://github.com/llvm/llvm-project/issues/54250).
4. When trying to build for the first time after I get an error similar to the one that follows:
```
[build] [16/6660   0% :: 0.375] Configuring NATIVE LLVM...
[build] FAILED: contrib/llvm-project/llvm/NATIVE/CMakeCache.txt /root/ClickHouse/build/contrib/llvm-project/llvm/NATIVE/CMakeCache.txt 
[build] cd /root/ClickHouse/build/contrib/llvm-project/llvm/NATIVE && /usr/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM="/usr/bin/ninja" /root/ClickHouse/contrib/llvm-project/llvm -DLLVM_TARGET_IS_CROSSCOMPILE_HOST=TRUE -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD="" -DLLVM_DEFAULT_TARGET_TRIPLE="x86_64-unknown-linux-gnu" -DLLVM_TARGET_ARCH="host" -DLLVM_ENABLE_PROJECTS="" -DLLVM_EXTERNAL_PROJECTS="" -DLLVM_ENABLE_RUNTIMES="" -DLLVM_TEMPORARILY_ALLOW_OLD_TOOLCHAIN="OFF" -DCMAKE_BUILD_TYPE=Release
[build] -- The CXX compiler identification is unknown
[build] CMake Error at CMakeLists.txt:58 (project):
[build]   No CMAKE_CXX_COMPILER could be found.
[build] 
[build]   Tell CMake where to find the compiler by setting either the environment
[build]   variable "CXX" or the CMake cache entry CMAKE_CXX_COMPILER to the full path
[build]   to the compiler, or to the compiler name if it is in the PATH.
[build] 
[build] 
[build] -- Configuring incomplete, errors occurred!
[build] See also "/root/ClickHouse/build/contrib/llvm-project/llvm/NATIVE/CMakeFiles/CMakeOutput.log".
[build] See also "/root/ClickHouse/build/contrib/llvm-project/llvm/NATIVE/CMakeFiles/CMakeError.log".
```

Apply this setting below to your CMakeCache.txt and delete the `build/contrib/llvm-project/llvm/NATIVE` folder, then continue building.
```
CROSS_TOOLCHAIN_FLAGS_NATIVE:STRING=-DCMAKE_C_COMPILER=/usr/bin/clang-15;-DCMAKE_CXX_COMPILER=/usr/bin/clang++-15
```
