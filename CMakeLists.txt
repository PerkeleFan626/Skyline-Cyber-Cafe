cmake_minimum_required(VERSION 4.1)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cafe main.cpp
        DataManager/DataManagerStructs.h
        DataManager/DataManagerStructs.h
        DataManager/DataManager.h
        DataManager/DataManager.cpp
        DataManager/DataManager.cpp
        UserManager/UserManager.h
        UserManager/UserManager.cpp
        Globals/CallingClassGlobal.h
        Globals/Globals.h
        Security/SecurityManager.h
        Security/SecurityManager.cpp)
