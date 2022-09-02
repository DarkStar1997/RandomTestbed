function(add_code name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} fmt::fmt)
endfunction()

function(add_par_code name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} fmt::fmt tbb)
endfunction()
