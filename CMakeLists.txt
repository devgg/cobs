cmake_minimum_required(VERSION 3.2.2)
cmake_policy(VERSION 3.2.2)

project(thesis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wno-unused-function -fopenmp -std=c++17 -lstdc++fs -mavx2 -march=native")

file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/lib/*")
file(GLOB_RECURSE TEST_FILES "${PROJECT_SOURCE_DIR}/test/src/*.hpp" "${PROJECT_SOURCE_DIR}/test/src/*.cpp")
file(GLOB_RECURSE EXECUTABLE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

MESSAGE("SOURCE_FILES     ${SOURCE_FILES}")
MESSAGE("TEST_FILES       ${TEST_FILES}")
MESSAGE("EXECUTABLE_FILES ${EXECUTABLE_FILES}")

include(dependencies/dependency.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/CLI/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/xxHash/cmake_unofficial)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/xxHash)

file(COPY test/resources DESTINATION test)
include_directories(lib/ ${STXXL_INCLUDE_DIRS} ${DEPENDENCY_DIR}/xxhash/src ${DEPENDENCY_DIR}/cli11/src/include)

if(libstdc++fs)
    add_library(stdc++fs UNKNOWN IMPORTED)
    set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION ${libstdc++fs})
else()
    message(WARNING "libstdc++fs was not specified use: -D libstdc++fs=\"<path_to_libstdc++fs.a>\"")
endif()

set(libs stdc++fs ${STXXL_LIBRARIES} xxhash)

foreach(target ${EXECUTABLE_FILES})
    get_filename_component(target_name ${target} NAME_WE)
    add_executable(${target_name} ${target} ${SOURCE_FILES})
    target_link_libraries(${target_name} ${libs})
endforeach(target)

enable_testing()
add_executable(isi_tests ${TEST_FILES} ${SOURCE_FILES})
target_compile_definitions(isi_tests PRIVATE isi_test)
target_link_libraries(isi_tests ${libs} gtest gtest_main)
add_test(isi_tests isi_tests)
