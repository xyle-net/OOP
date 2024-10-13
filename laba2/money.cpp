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
