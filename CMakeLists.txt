cmake_minimum_required(VERSION 3.10)

project(CppWebsiteDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app main.cpp)

if(WIN32)
    target_link_libraries(app ws2_32)
endif()