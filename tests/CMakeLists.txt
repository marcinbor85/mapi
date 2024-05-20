add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

function(create_test TARGET)
    add_executable(${TARGET})

    target_sources(${TARGET} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${ARGN}
    )

    target_include_directories(${TARGET} PRIVATE
        ${GTEST_INCLUDE_DIRS}
    )

    target_link_libraries(${TARGET}
        gmock_main
        gtest_main
    )
    
    add_test(${TARGET} ${TARGET})
endfunction()

add_subdirectory(tests)
