cmake_minimum_required(VERSION 3.28)
project(onboarding_task_2)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------ INSTRUCTIONS ------------------------------
file(GLOB_RECURSE INSTRUCTIONS_SOURCE
        ${CMAKE_SOURCE_DIR}/instructions/instructions.cpp
        ${CMAKE_SOURCE_DIR}/instructions/instructions.h
        ${CMAKE_SOURCE_DIR}/instructions/types.h
)

set(INSTRUCTIONS_INCLUDES
        ${CMAKE_SOURCE_DIR}/instructions/
)

add_library(instructions STATIC ${INSTRUCTIONS_SOURCE})
target_include_directories(instructions PUBLIC ${INSTRUCTIONS_INCLUDES})

# ------------------------------ COMPILER ------------------------------
file(GLOB_RECURSE COMPILER_SOURCE
        ${CMAKE_SOURCE_DIR}/compiler/compiler.cpp
)

set(COMPILER_INCLUDES
        ${CMAKE_SOURCE_DIR}/compiler/
)

add_library(compiler STATIC ${COMPILER_SOURCE})
target_include_directories(compiler PUBLIC ${COMPILER_INCLUDES})
target_link_libraries(compiler instructions)

# ------------------------------ VM ------------------------------
file(GLOB_RECURSE VM_SOURCE
        ${CMAKE_SOURCE_DIR}/vm/vm.cpp
)

set(VM_INCLUDES
        ${CMAKE_SOURCE_DIR}/vm/
)

add_library(vm STATIC ${VM_SOURCE})
target_include_directories(vm PUBLIC ${VM_INCLUDES})
target_link_libraries(vm instructions)

# ------------------------------ TESTS ------------------------------
enable_testing()

file(GLOB_RECURSE TESTS_SOURCE
        ${CMAKE_SOURCE_DIR}/tests/*.cpp
)

set(TESTS_INCLUDES
        ${CMAKE_SOURCE_DIR}/tests/
)

add_executable(tests ${TESTS_SOURCE})
target_include_directories(tests PRIVATE ${TESTS_INCLUDES})
target_link_libraries(tests vm compiler CONAN_PKG::gtest)

add_test(NAME tests COMMAND tests)

# ------------------------------ CONAN ------------------------------
set(CONAN_CMAKE_MULTI OFF)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake" STATUS statusList)

    list(GET statusList 0 ERRCODE)

    if (${ERRCODE} GREATER 0)
        file(REMOVE "${CMAKE_BINARY_DIR}/conan.cmake")
        list(GET statusList 1 ERRMSG)
        message(SEND_ERROR "Failed to download conan.cmake with error: ${ERRMSG}, cmake error code ${ERRCODE}")
    endif ()
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
        BASIC_SETUP CMAKE_TARGETS
        CONANFILE conanfile.txt
        BUILD missing
)
