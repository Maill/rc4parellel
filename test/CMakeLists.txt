function(add_test_helper test_name source_file)
    set(TARGET_NAME test_${test_name})
    add_executable(${TARGET_NAME} ${source_file} ${LIBRC4_SOURCES_FILES} MD5.cpp MD5.h)
    target_link_libraries(${TARGET_NAME} gtest gtest_main)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

add_test_helper(RC4 test.cpp)
