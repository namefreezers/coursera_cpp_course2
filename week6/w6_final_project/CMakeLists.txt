# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("w6_final_project")

set(CMAKE_CXX_STANDARD 17)

file(GLOB ALL_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(w6_final_project ${ALL_SRC})
