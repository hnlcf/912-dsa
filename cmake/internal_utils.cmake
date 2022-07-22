
## Custom Test Function
function(dsa_test test_file)
    get_filename_component(test_name "${test_file}" NAME_WE)
    set(test_target_name "dsa_${test_name}")

    add_executable("${test_target_name}")
    target_sources("${test_target_name}" PRIVATE
            "${test_file}"
            )
    target_include_directories("${test_target_name}" PRIVATE
            "test"
            "src"
            "exercise"
            "lib/catch2"
            )
    target_link_libraries("${test_target_name}" PRIVATE bitmap example Catch2::Catch2WithMain)
    add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
endfunction(dsa_test)
