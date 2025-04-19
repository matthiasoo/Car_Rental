cmake_minimum_required(VERSION 3.28)
project(View)

include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/Menu.cpp
)

add_executable(CarRental ${SOURCE_FILES})

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

target_link_libraries(
        CarRental
        Library
)

target_include_directories(CarRental PUBLIC include/model)