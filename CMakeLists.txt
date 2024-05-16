cmake_minimum_required(VERSION 3.11)

project(set CXX)

set(CMAKE_CXX_STANDARD 23)

# —пецифичные настройки дл€ компил€тора Visual Studio
if(MSVC)
    # √енерируем статическую заглушку дл€ динамических библиотек
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # ¬ключаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# ќбъ€вл€ем библиотеку
add_library(set SHARED  "set.cpp")
target_include_directories(set PUBLIC "include")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ќбъ€вл€ем тесты
add_executable(set_tests "set_tests.cpp")
target_link_libraries(set_tests set GTest::gtest_main)


add_executable(console "time_calculations.cpp")
target_link_libraries(console set) 




