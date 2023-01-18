# rpi_bot
Overarching repository for Raspberry Pi Libraries and Routing Code.

This project uses git submodules to integrate the Pico-SDK [Using Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules)

In short, to initially clone this project, use the following command in the code block below instead of the normal `git clone {url}`.
```
git clone --recurse-submodules {url}
```

If you have already cloned the repo and would like to add the submodule, run the following terminal commands to download and update the submodule.
```
git submodule init
git submodule update
```

The Pico-SDK Repository can be found [here](https://github.com/raspberrypi/pico-sdk/tree/2e6142b15b8a75c1227dd3edbe839193b2bf9041).

###Building the Project

####Ubuntu (Unix-based Systems)

To compile a project and generate a .uf2 executable for the PICO: Follow the steps below as seen in the "Getting Started with Raspberry Pi Pico".

```
mkdir build
cd build
```

Then, you have to define the pico-sdk path for the cmake to run (Only on the first time you run the cmake).

```
export PICO_SDK_PATH=../pico-sdk
```

Finally, to build the executable: Run the commands below in the terminal to generate the executables under the 'build' folder.

```
cmake ..
make
```

Instead of make, you may use `make -jX`. Where X is the number of threads available on your PC.
