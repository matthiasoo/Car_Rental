cmake_minimum_required(VERSION 3.28)
project(Library)

include_directories(include/model)

set(SOURCE_FILES
        src/model/Client.cpp
        src/model/Address.cpp
        src/model/Vehicle.cpp
        src/model/Rent.cpp
        src/repositories/ClientRepository.cpp
        src/repositories/VehicleRepository.cpp
        src/repositories/RentRepository.cpp
        src/repositories/StorageContainer.cpp
        src/model/Bicycle.cpp
        src/model/MotorVehicle.cpp
        src/model/Moped.cpp
        src/model/Car.cpp
        src/model/ClientType.cpp
        src/managers/ClientManager.cpp
        src/managers/VehicleManager.cpp
        include/managers/RentManager.h
        src/managers/RentManager.cpp
)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC
        include
        # to consider
        include/model
        include/repositories
        include/managers
)

enable_testing()

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(SOURCE_TEST_FILES
        test/master.cpp
        test/ClientTest.cpp
        test/AddressTest.cpp
        test/VehicleTest.cpp
        test/RentTest.cpp
        test/RepositoriesTest.cpp
        test/ManagersTest.cpp
)

add_executable(LibraryTester ${SOURCE_TEST_FILES})

target_link_libraries(
        LibraryTester
        Library
        ${Boost_LIBRARIES}
)

add_test(LibraryTest LibraryTester)

add_custom_target(check
        ${CMAKE_COMMAND} -E env
        ${CMAKE_BINARY_DIR}/Library/LibraryTester
        --report_level=detailed
        --log_level=all
        DEPENDS LibraryTester
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)