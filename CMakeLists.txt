cmake_minimum_required(VERSION 3.20)

project(Geometry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app)

target_sources(app
    PRIVATE
        src/main.cpp
        src/Application.cpp
        src/FileReader.cpp
        src/CommandExecutor.cpp
        src/SocketServer.cpp
    
)

target_include_directories(app
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)