project(nes-chr++)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")

file(GLOB_RECURSE RESOURCES "resources/*")

file(COPY ${RESOURCES}
    DESTINATION ${CMAKE_BINARY_DIR}/resources
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} -L/usr/lib/x86_64-linux-gnu/
    SDL2
    SDL2_ttf
    )
