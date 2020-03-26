cmake_minimum_required(VERSION 2.8)
project(scapremai-preliminary CXX)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
add_custom_target(
        format
	COMMAND ${CMAKE_SOURCE_DIR}/run-clang-format.py -r ${CMAKE_SOURCE_DIR}/
        ${ALL_SOURCE_FILES}
)

add_library(scapremai_mapried_sampling
    STATIC
    scapremai/mapried/sampling/jsoncpp.cpp
    scapremai/mapried/sampling/jsoncpp.h
    scapremai/mapried/sampling/parse.cpp
    scapremai/mapried/sampling/parse.h
    scapremai/mapried/sampling/types.h)

add_executable(scapremai_sampler scapremai/sampler.cpp)
target_link_libraries(scapremai_sampler
    scapremai_mapried_sampling
    ${CONAN_LIBS})
