# Cafe Management System


## Overview

This is a simple Cafe Management System built in C++ using Qt and CMake.  
It allows users to manage menu items, place orders, calculate bills, and save data.  
The project introduced us to GUI design and file handling for basic data storage.


By: Haiqa Nasir (<28100194>) & Sara Safdar (<28100141>)


## Features

- Add, update, and delete menu items  
- Place customer orders  
- Auto-calculate total bill  
- Store and retrieve order history using text files  
- GUI built with Qt for basic user interaction


## Execution Guide


### Dependencies


1. C++
2. Qt6
3. CMake
4. Ninja


### Environment Variables


1. Qt's `bin` folder in `PATH` variable.
2. `CMAKE_PREFIX_PATH` variable directing to the root directory of Qt (containing the `bin` folder).


### How to run?


Run the following command to setup the build directory (if not present):
```bash
cmake -S . -B build
```


Run the following command to compile the code:
```bash
cmake --build build
```


Open the `QtProject...` file in the `build` folder or execute it via a terminal:
```bash
./build/QtProject
```


