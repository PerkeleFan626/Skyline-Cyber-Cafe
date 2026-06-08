cmake_minimum_required(VERSION 4.1)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)


add_executable(Cafe main.cpp
        homepage/homepage.hpp
        homepage/homepage.cpp
        DataManager/DataManagerStructs.h
        DataManager/DataManager.h
        DataManager/DataManager.cpp
        UserManager/UserManager.h
        UserManager/UserManager.cpp
        Globals/CallingClassGlobal.h
        Globals/Globals.h
        AdminManager/AdminStruct.h
        AdminManager/AdminManager.h
        AdminManager/AdminManager.cpp
        TransactionManager/TransactionManager.h
        TransactionManager/TransactionManager.cpp
        SessionManager/SessionManager.h
        SessionManager/SessionManager.cpp)
