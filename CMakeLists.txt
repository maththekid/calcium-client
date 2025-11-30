cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

project(calcium)

find_package(cpr REQUIRED)
find_package(RapidJSON REQUIRED)

include_directories("src" "vendors")

file(GLOB_RECURSE source "vendors/*.cpp" "vendors/*.c" "src/*.cpp" "src/*.c")
file(GLOB libs "libs/*.lib" "libs/*.dll")

add_library(calcium SHARED ${source})

target_link_libraries(calcium PRIVATE opengl32.lib cpr::cpr rapidjson ${libs})
