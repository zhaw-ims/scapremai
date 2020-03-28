cmake_minimum_required(VERSION 2.8)
project(scapremai-preliminary CXX)

add_definitions("-std=c++17")

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    string(CONCAT MESSAGE
            "The file ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake doesn't exist, "
            "you have to run conan install first:\n"
            "$ cd ${CMAKE_BINARY_DIR}\n"
            "$ conan install ${CMAKE_SOURCE_DIR}")
    message(WARNING "${MESSAGE}")
endif ()

add_custom_target(
        format
        COMMAND ${CMAKE_SOURCE_DIR}/run-clang-format.py -r ${CMAKE_SOURCE_DIR}/scapremai
)

include_directories(${CMAKE_SOURCE_DIR})

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
