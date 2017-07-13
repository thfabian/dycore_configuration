## 
##             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
##                     Version 2, December 2004
##
##  Copyright (C) 2017 Fabian Thuering
##
##  Everyone is permitted to copy and distribute verbatim or modified
##  copies of this license document, and changing it is allowed as long
##  as the name is changed.
##
##             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
##   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
##
##   0. You just DO WHAT THE FUCK YOU WANT TO.
##

project(DycoreConfiguration)
cmake_minimum_required(VERSION 3.3)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Test Test.cpp Configuration.cpp Configuration.hpp Configuration.inc)

