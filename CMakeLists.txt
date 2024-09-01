cmake_minimum_required( VERSION 3.18 )

message( STATUS "==========================================================================\n" )
message( STATUS "project generation started" )

message( STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER_VERSION})" )
message( STATUS "target system: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_VERSION})" )
message( STATUS "host system: ${CMAKE_HOST_SYSTEM_NAME} (${CMAKE_HOST_SYSTEM_VERSION})" )

project( "CppReflection" VERSION 2023.1.31 LANGUAGES C CXX )

## language standard
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## 3rd party
set(llvm_include ${CMAKE_CURRENT_SOURCE_DIR}/3rd/LLVM/include)
set(llvm_lib ${CMAKE_CURRENT_SOURCE_DIR}/3rd/LLVM/lib/x64/libclang.lib)
set(llvm_dll ${CMAKE_CURRENT_SOURCE_DIR}/3rd/LLVM/bin/x64/libclang.dll)

set(mustache_include ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mustache/include)

set(3rd_party_include ${llvm_include} ${mustache_include})
set(3rd_party_lib ${llvm_lib})
set(3rd_party_dll ${llvm_dll})

add_subdirectory(Source)