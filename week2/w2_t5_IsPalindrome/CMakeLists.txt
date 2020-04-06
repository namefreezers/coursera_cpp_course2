# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("w2_t5_IsPalindrome")

# Включите подпроекты.
add_executable (w2_t5_IsPalindrome src/w2_t5_IsPalindrome.cpp)
