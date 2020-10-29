cmake_minimum_required(VERSION 3.5)

project(hello_BT)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(BehaviorTreeV3)

add_executable(create_bt src/create_bt.cpp)
target_link_libraries(create_bt BT::behaviortree_cpp_v3)