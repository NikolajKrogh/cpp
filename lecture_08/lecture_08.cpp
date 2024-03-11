#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    auto b = v.begin(), e = v.end();
    os << "{";
    if (b != e) {
        os << *b;
        while (++b != e)
            os << "," << *b;
    }
    return os << "}";
}

template <typename T>  // specialization
struct is_container<T,

> : std::true_type {}; // computes "true type"

int main(){
    std::cout << std::vector{1,2,3} << std::endl; // should print "{1,2,3}"
    std::cout << std::vector{2.7,3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl;
    // should print "{{hello,template}{world}}"
}