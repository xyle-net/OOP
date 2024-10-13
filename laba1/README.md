# **Лабараторная по ООП №1**

## Задача:
Ваша компания, Timaty Pizza, является вторым по величине интернет-магазином замороженной
пиццы. Вы владеете несколькими международными складами, которые используются для
хранения замороженной пиццы, и вам необходимо определить, сколько ящиков пиццы вы можете
хранить на каждом из них.
Компания Timaty недавно стандартизировала свои контейнеры для хранения: все пиццы
помещаются в кубические ящики со стороной 16 дюймов. Ящики очень прочные, поэтому их
можно укладывать как угодно высоко.
Напишите функцию box_capacity(), которая определяет, сколько ящиков можно хранить на
данном складе. Функция должна принимать три аргумента: длину, ширину и высоту склада (в
футах) и возвращать целое число, представляющее количество ящиков, которые можно хранить
на этом пространстве.
Например: склад длиной 32 фута, шириной 64 фута и высотой 16 футов может вместить 13 824
ящика, поскольку в нем можно разместить 24 ящика в поперечнике, 48 ящиков в глубину и 12
ящиков в высоту, поэтому box_capacity(32, 64, 16) должна возвращать 13824.

### Решение:

**main.cpp**
```
#include <iostream>
#include "solution.cpp"

int main(){
    int length, width, height;
    std::cout << "Input: \n";
    std::cin >> length >> width >> height;
    std::cout << box_capacity( length, width, height) << std::endl;
}
```

**solution.cpp**
```
#include "solution.h"

int box_capacity(int length,int width,int height){ 
    return ((length * 12) / 16) * ((width * 12) / 16) * ((height * 12) / 16); 
}
```

**CMakeLists**
```
cmake_minimum_required(VERSION 3.10)
project(lab)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1  
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(MyExecutable main.cpp)

add_executable(MyTests tests.cpp)

target_link_libraries(MyTests gtest gtest_main)

add_test(NAME MyTests COMMAND MyTests)
```