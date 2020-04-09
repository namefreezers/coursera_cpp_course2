# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("w4_t10_prefix_grouping")

set(CMAKE_CXX_STANDARD 17)

# Включите подпроекты.
add_executable (w4_t10_prefix_grouping src/w4_t10_prefix_grouping.cpp)
