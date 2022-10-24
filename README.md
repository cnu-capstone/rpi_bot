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

The Pico-SDK Repository can be found [here]().
