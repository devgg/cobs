set(DEPENDENCY_DIR ${CMAKE_BINARY_DIR}/dependencies)

# Download and unpack googletest at configure time
configure_file(dependencies/gtest.cmake dependencies/gtest/download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${DEPENDENCY_DIR}/gtest/download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${DEPENDENCY_DIR}/gtest/download)
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
add_subdirectory(${DEPENDENCY_DIR}/gtest/src ${DEPENDENCY_DIR}/gtest/build)

configure_file(dependencies/stxxl.cmake dependencies/stxxl/download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${DEPENDENCY_DIR}/stxxl/download)
if(result)
    message(FATAL_ERROR "CMake step for stxxl failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${DEPENDENCY_DIR}/stxxl/download)
if(result)
    message(FATAL_ERROR "Build step for stxxl failed: ${result}")
endif()
add_subdirectory(${DEPENDENCY_DIR}/stxxl/src)

