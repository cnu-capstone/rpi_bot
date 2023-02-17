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

## Building the Project

### Ubuntu (Unix-based Systems)

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

## Changelog

#### 2/16/23
Added "motor\_controller" subdirectory for development of motor control logic (i.e. propogating motor state based on received instructions). The C file "motor\_controller.c" simply alternates the direction of Motor 1 (in accordance with "V2 \- Automated Trash Can System Design Report") by changing the state of GPIO pins 20 and 21 on the Raspberry Pi PICO. This file is currently in the testing stage for the purposes of demonstration.

Altered "motor\_controller.c" to utilize GPIO pins 18 and 21 as enable pins for Motor 1 and Motor 2 respectively. GPIO pins 19 and 20 are utilized to indicate the positive forward voltage for the motors. The script also currently utilizes a stop/start method of modulating the signal at a specific duty cycle.

#### 1/29/23
Added "parse\_input" subdirectory for development of communication channel between the Raspberry Pi 4B and the Raspberry Pi PICO W. The C file "parse\_input.c" reads the state of GPIO pins 2, 3, 4, and 5 on the PICO W and propogates the respective state to a LED connected to GPIO pin 22 with 1 second (or 1000 ms) intervals. This file is currently in its testing stage of development.

#### 1/19/23
This project now entirely contains the scripts and applications to support the Raspberry Pi PICO. All routing and such scripts have been moved to the "rpi\_routing" repository at [link](https://github.com/cnu-capstone/rpi_routing.git).
