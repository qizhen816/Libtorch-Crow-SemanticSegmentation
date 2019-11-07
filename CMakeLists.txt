cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(SerVer)

include_directories(/garage/crow/include/)
include_directories(/usr/local/include) 
include_directories(/garage/fastscnn-crow)

link_directories(/usr/local/lib)

set(Boost_USE_MULTITHREADED ON)
set(BOOST_ROOT "/usr/local/include/boost") 
set(BOOSTROOT "/usr/local/include/boost")
set(CMAKE_PREFIX_PATH "/libtoorch/libtorch")

find_package(Threads REQUIRED)
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(SerVer /garage/fastscnn-crow/server.cpp base64.cpp model.cpp)
target_link_libraries(SerVer boost_thread boost_system ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(SerVer "${TORCH_LIBRARIES}")
target_link_libraries(SerVer "${OpenCV_LIBRARIES}")
set_property(TARGET SerVer PROPERTY CXX_STANDARD 11)

