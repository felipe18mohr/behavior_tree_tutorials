cmake_minimum_required(VERSION 3.5)

project(hello_BT)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(BehaviorTreeV3)

add_executable(create_bt src/Tutorial_1/create_bt.cpp)
target_link_libraries(create_bt BT::behaviortree_cpp_v3)

add_executable(basic_ports src/Tutorial_2/basic_ports.cpp)
target_link_libraries(basic_ports BT::behaviortree_cpp_v3)

add_executable(generic_ports src/Tutorial_3/generic_ports.cpp)
target_link_libraries(generic_ports BT::behaviortree_cpp_v3)

add_executable(sequences src/Tutorial_4/sequences.cpp)
target_link_libraries(sequences BT::behaviortree_cpp_v3)

add_executable(crossdoor src/Tutorial_5/crossdoor.cpp)
target_link_libraries(crossdoor BT::behaviortree_cpp_v3)

add_executable(ports_remapping src/Tutorial_6/ports_remapping.cpp)
target_link_libraries(ports_remapping BT::behaviortree_cpp_v3)

add_executable(wrapping_legacy src/Tutorial_7/wrapping_legacy.cpp)
target_link_libraries(wrapping_legacy BT::behaviortree_cpp_v3)

add_executable(additional_args src/Tutorial_8/additional_arguments.cpp)
target_link_libraries(additional_args BT::behaviortree_cpp_v3)

add_executable(coroutines src/Tutorial_9/coroutines.cpp)
target_link_libraries(coroutines BT::behaviortree_cpp_v3)
