#include <iostream>
#include "solution.cpp"

int main(){
    int length, width, height;
    std::cout << "Input: \n";
    std::cin >> length >> width >> height;
    std::cout << box_capacity( length, width, height) << std::endl;
}