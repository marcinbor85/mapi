cmake_minimum_required(VERSION 3.22)

project(mapi LANGUAGES C CXX VERSION 0.1.0)

enable_testing()

set(CMAKE_C_FLAGS "-Werror -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wno-unused-parameter")

add_subdirectory(${PROJECT_SOURCE_DIR}/mapi)
add_subdirectory(${PROJECT_SOURCE_DIR}/example)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
