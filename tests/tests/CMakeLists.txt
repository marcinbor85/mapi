create_test(test_example
    ${CMAKE_CURRENT_SOURCE_DIR}/test_example.cpp
    ${PROJECT_SOURCE_DIR}/example/src/api_calc.c
    ${PROJECT_SOURCE_DIR}/example/src/api_utils.c
)

target_include_directories(test_example PRIVATE
    ${PROJECT_SOURCE_DIR}/example/include
    ${PROJECT_SOURCE_DIR}/mapi/include
)

target_link_libraries(test_example
    mapi
)

create_test(test_mapi
    ${CMAKE_CURRENT_SOURCE_DIR}/test_mapi.cpp
)

target_link_libraries(test_mapi
    mapi
)
