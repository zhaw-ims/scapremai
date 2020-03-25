cmake_minimum_required(VERSION 2.8)
project(scapremai-preliminary CXX)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
add_custom_target(
        format
	COMMAND ${CMAKE_SOURCE_DIR}/run-clang-format.py -r ${CMAKE_SOURCE_DIR}/
        ${ALL_SOURCE_FILES}
)

add_executable(scapremai_sampler scapremai/sampler.cpp)
target_link_libraries(scapremai_sampler ${CONAN_LIBS})
