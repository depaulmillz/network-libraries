cmake_minimum_required(VERSION 3.14)

#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
#        CACHE STRING "Vcpkg toolchain file")

project(network-libraries LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libfabric)