set(TARGET example)

add_executable(${TARGET})

target_link_libraries(${TARGET} mapi)

target_include_directories(${TARGET} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api_calc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl_calc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl_utils.c
)
