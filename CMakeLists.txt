cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 11)

# Adds all header files in the include folder to the project
include_directories(include)

# Adds all the source files in the src folder to the project
# file(GLOB SOURCES "src/*.cpp")
set(MAIN main.cpp include/Snake.h src/Snake.cpp src/Food.cpp)

# Creates project executable
add_executable(SnakeGame ${MAIN})


# Copies the resource files to the build directory
file(COPY resources DESTINATION ./)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
