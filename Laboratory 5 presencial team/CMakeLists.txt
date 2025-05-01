cmake_minimum_required(VERSION 3.10)
project(lab5io)

include_directories(include)

add_executable(${CMAKE_PROJECT_NAME} 
    src/lab5io.c src/main.c)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ncurses)