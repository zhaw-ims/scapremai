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

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../../release" CACHE PATH "default install directory" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

##
# Targets
##

add_library(mapried_sampling
        STATIC
        mapried/sampling/jsoncpp.cpp
        mapried/sampling/jsoncpp.h
        mapried/sampling/parse.cpp
        mapried/sampling/parse.h
        mapried/sampling/types.h)

add_executable(scapremai_sampler scapremai/sampler.cpp)
target_link_libraries(scapremai_sampler
        mapried_sampling
        ${CONAN_LIBS})


##
# Install
##

install(TARGETS scapremai_sampler DESTINATION bin)
