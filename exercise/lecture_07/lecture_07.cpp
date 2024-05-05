#include <vector>
#include <iostream>
#include "lecture_07.h"

template <typename T>
void print (std::vector<T> vec) {
    std::cout << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}";
}

template <typename T>
std::ostream &operator << (std::ostream &os, const std::vector<T>& vec){
    os << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) {
            os << ",";
        }
    }
    os << "}";
    return os;
}

int main(){
    print(std::vector<int>{1,2,3});
    std::cout << (std::vector<int>{1,2,3});

    std::cout << std::vector{1,2,3} << std::endl; // should still print "{1,2,3}"
    std::cout << std::vector{2.7,3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl;

    using vi = decltype(std::vector{1,2,3});
    std::cout << vi {3,4,5};
}