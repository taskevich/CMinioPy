cmake_minimum_required(VERSION 3.15...3.22)
project(cminiopy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(PYBIND11_FINDPYTHON ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(miniocpp CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

include_directories(include)

pybind11_add_module(cminiopy
    src/main.cpp
    src/MinioApi.cpp
)

target_link_libraries(cminiopy PRIVATE Python3::Python miniocpp::miniocpp)

set_target_properties(cminiopy PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
)
