set(CMAKE_CXX_STANDARD 23)

option(BUILD_EDITOR "Build Explosion editor" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

add_definitions(-DBUILD_CONFIG_DEBUG=$<IF:$<CONFIG:Debug>,1,0>)

add_definitions(-DPLATFORM_WINDOWS=$<IF:$<PLATFORM_ID:Windows>,1,0>)
add_definitions(-DPLATFORM_LINUX=$<IF:$<PLATFORM_ID:Linux>,1,0>)
add_definitions(-DPLATFORM_MACOS=$<IF:$<PLATFORM_ID:Darwin>,1,0>)

add_definitions(-DCOMPILER_MSVC=$<IF:$<STREQUAL:$<CXX_COMPILER_ID>,"MSVC">,1,0>)
add_definitions(-DCOMPILER_APPLE_CLANG=$<IF:$<STREQUAL:$<CXX_COMPILER_ID>,"AppleClang">,1,0>)
add_definitions(-DCOMPILER_GCC=$<IF:$<STREQUAL:$<CXX_COMPILER_ID>,"GNU">,1,0>)

add_definitions(-DBUILD_EDITOR=$<BOOL:BUILD_EDITOR>)
