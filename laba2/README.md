# **Лабараторная по ООП №2**


## Задача:
Создать класс ***Money*** для работы с денежными суммами. Сумма должна быть представлена массивом из 
элементов типа *unsigned char*, каждый элемент которого – десятичная цифра. Младший индекс 
соответствует младшей цифре денежной суммы. Младшие две цифры — копейки

### Решение:

**money.h**
```
#pragma once

#include <iostream>
#include <string>

class Money
{
public:

    Money();
    Money(const size_t & n, unsigned char t = 0);
    Money(const std::initializer_list< unsigned char> &t);
    Money(const std::string &t);
    Money(const Money& other);
    Money(Money&& other) noexcept;
    
    int get_size();
    unsigned char* get_array();
    std::string get_string_value();

    Money add(const Money& other);
    Money remove(const Money& other);
    bool bigger(const Money& other);
    bool equals(const Money& other);
    void print();

    virtual ~Money() noexcept;

private:
    int _size;
    unsigned char *_array;
};
```

**money.cpp**
```
#include <cstring>
#include "money.h"

Money::Money(): _size(1)
{
    _array = new unsigned char [1];
    _array[0] = '0';
}

// Реализация конструктора с заданным размером и значением
Money::Money(const size_t &n, unsigned char t)
{
    if(t < '0' or t > '9') throw std::logic_error("not digit input");
    _array = new unsigned char[n];
    for (int i{0}; i < n; ++i)
        _array[i] = t;
    _size = n;
}

// Реализация конструктора с инициализатором списка
Money::Money(const std::initializer_list<unsigned char> &t)
{
    _array = new unsigned char[t.size()];
    int i{0};
    for (auto elem : t){
        if(elem < '0' or elem > '9') throw std::logic_error("not digit input");
        _array[i++] = elem;
    }
    _size = t.size();
}

// Реализация конструктора из строки
Money::Money(const std::string &t)
{
    _array = new unsigned char[t.size()];
    _size  = t.size();

    for(int i{0}; i<_size; ++i){
        if(t[i] < '0' or t[i] > '9') throw std::logic_error("not digit input");
         _array[i] = t[i];
    }
}

// Конструктор копирования
Money::Money(const Money &other)
{
    _size  = other._size;
    _array = new unsigned char[_size];

    for(int i{0};i<_size;++i) _array[i] = other._array[i];
}

// Конструктор перемещения
Money::Money(Money &&other) noexcept
{
    _size = other._size;
    _array = other._array;

    other._size = 0;
    other._array = nullptr;
}

// Получение размера массива
int Money::get_size(){
    return _size;
}

// Получение указателя на массив
unsigned char* Money::get_array(){
    return _array;
}

// Получение строкового значения
std::string Money::get_string_value(){
    std::string result = "";

    for (int i{_size - 1}; i >= 0; --i) {
        result += _array[i];
    }

    return result;
}

// Метод для проверки равенства двух денежных сумм
bool Money::equals(const Money &other){
    if (_size > other._size){
        return false;
    }
    else if(_size < other._size){
        return false;
    }
    else{
        for(int i{_size-1};i>=0;--i){
            if(_array[i] != other._array[i])
                return false;
        }
    }
    return true;
}

// Метод для проверки, больше ли текущая сумма другой
bool Money::bigger(const Money &other){
    if (_size > other._size){
        return true;
    }
    else if(_size < other._size){
        return false;
    }
    else{
        for(int i{_size-1};i>=0;--i){
            if(_array[i] > other._array[i])
                return true;
        }
    }
    return false;
}

// Метод для сложения двух денежных сумм
Money Money::add(const Money &other)
{
    _size = std::max(_size,other._size);
    unsigned char* _new_array = new unsigned char [_size];
    memcpy(_new_array,_array,_size);

    int tranf{0}; 

    for(int i{0}; i < _size; ++i){

        if( _new_array[i] < '0' or _new_array[i] > '9') { _new_array[i] = '0';}
        if( other._array[i] < '0' or other._array[i] > '9'){ other._array[i] = '0';}

        int s = (_new_array[i] - '0') + (other._array[i] - '0') + tranf;
        tranf = s/10;
        _new_array[i] = '0' + s%10;
    }

    if(tranf){
        _array = new unsigned char [_size+1];
        memcpy(_array,_new_array,_size);
        _size++;
        _array[_size-1] = '0' + tranf;
    }
    else{
        _array = new unsigned char [_size+1];
        memcpy(_array,_new_array,_size);
    }

    delete[] _new_array;

    return *this;
}

// Метод для вычитания одной денежной суммы из другой
Money Money::remove(const Money &other){
    if( this->equals(other)){
        _array[0] = '0';
        _size = 1;
    }
    else if(!this->bigger(other)){
        throw std::logic_error("negative balance");
    }
    else{
        unsigned char* _new_array = new unsigned char [_size];
        memcpy(_new_array,other._array, other._size);
    
        for(int i{0}; i<_size; i++){

            if(_new_array[i] < '0' or _new_array[i] > '9') {_new_array[i] = '0';}
            
            if(_array[i] >= _new_array[i]){
                _array[i] = (_array[i] - _new_array[i]) + '0'; 
            }
            else{
                int tmp_id {i+1};

                while(_array[tmp_id] == '0'){
                    tmp_id++;
                }

                _array[tmp_id] = '0' + (_array[tmp_id] - '1');
                --tmp_id;

                _array[i] = (((_array[i] - '0') - (_new_array[i] - '0')) + 10) + '0';

                while(tmp_id != i){
                    _array[tmp_id] = '9';
                    --tmp_id;
                }
            }
        }

        delete[] _new_array;
        
        while(_array[_size - 1] == '0' and _size > 0){
            --_size;
        }
    }
    return *this;
}

// Метод для печати денежной суммы
void Money::print(){
    if(_size == 1){
        std::cout << "0.0" << _array[0];
    }
    else{
        for(int i{_size-1};i>=0; i--){
            if(i == 1){
                std::cout << '.';
            }
            std::cout<<_array[i];
        }
    }
    std::cout << std::endl;
}

// Деструктор
Money::~Money() noexcept
{
    if (_size > 0)
    {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}
```

**tests.cpp**
```
#include <gtest/gtest.h>
#include "money.cpp"

// Constructor

TEST(constructor_test01, default_constructor)
{
    Money a = Money();
    std::string b{'0'};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 1);
}

TEST(constructor_test02, fill_constructor)
{
    Money a = Money(5,'1');
    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(),5);
}

TEST(constructor_test03, initializer_list_constructor)
{
    Money a {'1','1','1','1','1'};
    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 5);
}

TEST(constructor_test04, string_constructor)
{
    std::string str = "11111";
    Money a = Money(str);

    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 5);
}

TEST(constructor_test05, copy_constructor)
{
    Money first {'1','1','1','1','1'};
    Money second = Money(first);

    std::string b{"11111"};

    EXPECT_EQ(second.get_string_value(), b);
    EXPECT_EQ(second.get_size(), 5);
}

TEST(constructor_test06, rvalue_constructor)
{
    Money a = {"11111"};
    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 5);
}

TEST(constructor_test07, error_input)
{
    try{
        Money a {"11ab4"};
    }catch(std::exception &ex){
        EXPECT_STREQ(ex.what(),"not digit input");
    }
}

// Operators testing
TEST(o_test01, basic_test_set)
{
    // 1.00 + 0.01 = 1.01
    Money a {"001"};
    Money b {'1'};
    Money c {"101"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test02, basic_test_set)
{
    // 500.00 + 500.00 = 1000.00
    Money a {"00005"};
    Money b {"00005"};
    Money c {"000001"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test03, basic_test_set)
{
    // 11.11 + 0.91 = 12.02
    Money a {"1111"};
    Money b {"19"};
    Money c {"2021"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test04, basic_test_set)
{
    // 0 + 543.21 = 543.21
    Money a {'0'};
    Money b {"12345"};
    Money c {"12345"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test05, basic_test_set)
{
    // 1000.99 + 0.01 = 1001.00
    Money a {"990001"};
    Money b {'1'};
    Money c {"001001"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test06, basic_test_set)
{
    // 0.01 - 5.00 = exeption
    Money a {"1"};
    Money b {"005"};
    try{
        a.remove(b);
    }catch(std::exception &ex){
        EXPECT_STREQ(ex.what(),"negative balance");
    }
}

TEST(o_test07, basic_test_set)
{
    // 115.00 - 15.00 = 100.00
    Money a {"00511"};
    Money b {"0051"};
    Money c {"00001"};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test08, basic_test_set)
{
    // 1.00 - 0.01 = 0.99
    Money a {"001"};
    Money b {'1'};
    Money c {"99"};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test09, basic_test_set)
{
    // 6543.21 - 6543.21 = 0
    Money a {"123456"};
    Money b {"123456"};
    Money c {'0'};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test10, basic_test_set)
{
    // 1000000.00 - 0.01 = 999999.99
    Money a {"000000001"};
    Money b {'1'};
    Money c {"99999999"};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test11, basic_test_set)
{
    // 0 + 6543.21 = 6543.21
    Money a  = Money();
    Money b {"123456"};
    Money c {"123456"};
    ASSERT_TRUE(c.equals(a.add(b)));
}
```

**CMakeLists.txt**
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
