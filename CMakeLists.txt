cmake_minimum_required(VERSION 3.0.0)
project(LearnGL VERSION 0.1.0)

include(CTest)
enable_testing()

aux_source_directory(src SOURCE)

add_compile_options(-Wall)

add_executable(LearnGL ${SOURCE})

include_directories(include)

find_library(GLFW_LIB GLFW)

target_link_libraries(LearnGL ${GLFW_LIB})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
