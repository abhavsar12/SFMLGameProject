cmake_minimum_required(VERSION 3.6)
project(Homework5)

#define EXECUTABLE NAME HERE
set(EXECUTABLE_NAME "h5")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

set(SOURCE_FILES
        main.cpp
        Game.cpp Game.h GameObject.cpp GameObject.h)

#copy file to where my executable is
file(COPY "content/Title.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/Story1.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/Story2.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/dragon.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/fire.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/Snakes.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/GameOver.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/background.png" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/Apple Chancery.ttf" DESTINATION "${CMAKE_BINARY_DIR}")



add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})