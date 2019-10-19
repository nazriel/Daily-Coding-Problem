cmake_minimum_required(VERSION 3.9)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(solution solution.cpp)
set_property(TARGET solution PROPERTY CXX_STANDARD 17)
target_link_libraries(solution ${Boost_LIBRARIES})

add_custom_target(run
    COMMAND solution
    DEPENDS solution
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
