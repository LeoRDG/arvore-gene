cmake_minimum_required(VERSION 3.16)
project(arvore_gene LANGUAGES CXX)

# Padrões sensatos
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Se ninguém disse o build type, use Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Fontes principais (sem o main)
set(CORE_SOURCES
        src/Arvore.cpp
        src/Data.cpp
        src/Pessoa.cpp
        src/util.cpp
        src/Regex.cpp
)

# Biblioteca com o núcleo da aplicação
add_library(arvorelib ${CORE_SOURCES})
target_include_directories(arvorelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Warnings que evitam lágrimas
if(MSVC)
    target_compile_options(arvorelib PRIVATE /W4 /permissive-)
else()
    target_compile_options(arvorelib PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow -fno-omit-frame-pointer
    )
endif()

# Sanitizers (Debug por padrão)
option(ENABLE_SANITIZERS "Enable Address/UB sanitizers (Clang/GCC)" ON)

if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    set(SAN_FLAGS "-fsanitize=address,undefined")
    add_compile_options(${SAN_FLAGS})
    add_link_options(${SAN_FLAGS})
endif()

# Executável principal
add_executable(arvore_gene src/main.cpp)
target_link_libraries(arvore_gene PRIVATE arvorelib)

# Executável de testes (opcional)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp)
    add_executable(arvore_tests src/test.cpp)
    target_link_libraries(arvore_tests PRIVATE arvorelib)
    enable_testing()
    add_test(NAME run_arvore_tests COMMAND arvore_tests)
endif()

# LTO para Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_ok OUTPUT ipo_msg)
    if(ipo_ok)
        set_property(TARGET arvorelib PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
        if(TARGET arvore_tests)
            set_property(TARGET arvore_tests PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
        endif()
    endif()
endif()
