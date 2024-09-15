cmake_minimum_required(VERSION 3.28.3)

project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Here is where we set output directories
set( OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")

# Here is where we set output directories
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDir}/${PROJECT_NAME}")

set(Sources main.cpp )

add_executable(${PROJECT_NAME} ${Sources} )