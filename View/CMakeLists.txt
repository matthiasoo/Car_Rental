cmake_minimum_required(VERSION 3.28)
project(View)

set(SOURCE_FILES
        src/main.cpp
)

add_executable(CarRental ${SOURCE_FILES})

target_link_libraries(CarRental Library)

target_include_directories(CarRental PUBLIC include/model)