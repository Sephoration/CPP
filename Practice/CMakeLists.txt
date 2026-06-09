cmake_minimum_required(VERSION 3.14)

# 练习代码子目录
set(PRACTICE_TARGETS
    Algorithms/sort_bubble.cpp
    Algorithms/sort_quick.cpp
    Algorithms/binary_search.cpp
    ModernCpp/lambda_demo.cpp
    ModernCpp/move_semantics.cpp
    ModernCpp/variadic_template.cpp
    ModernCpp/constexpr_demo.cpp
    DataStructures/linked_list.cpp
    DataStructures/stack_impl.cpp
    DataStructures/hash_table_simple.cpp
    DesignPatterns/singleton.cpp
    DesignPatterns/observer.cpp
    DesignPatterns/factory.cpp
    SystemProgramming/file_io.cpp
    SystemProgramming/process_info.cpp
)

foreach(src ${PRACTICE_TARGETS})
    get_filename_component(name ${src} NAME_WE)
    get_filename_component(dir ${src} DIRECTORY)
    add_executable(practice_${name} ${src})
    set_target_properties(practice_${name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${dir}
    )
endforeach()
