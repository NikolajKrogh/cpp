#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;
using namespace std::chrono;

constexpr int arr_size = 10'000'000;
vector<int> vec(arr_size); // Vector is always on the heap

void swap_ends(int arr[], int size) {
    for (int i = size/2 - 1, j = size - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}
void swap_ends(vector<int>& arr) { // overloading the same fn-name
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_ends_memcpy(int arr[], int size) {
    std::memcpy(dest, arr, sizeof dest);
}

void do_work_vector(){
    swap_ends(vec);
}

void do_work_array(){
    int dest[]
    int c_arr[arr_size]; // When having a large array, it is faster to have it on the stack
    swap_ends(c_arr, arr_size);
}



int main(){
    // do some warm up work here
    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        do_work_vector();
    }
    auto t1 = high_resolution_clock::now();
    std::cout <<"Vector: " << duration<double, std::milli>(t1-t0).count() << "ms\n";
    for (int i = 0; i < 100; ++i) {
        do_work_array();
    }
    auto t2 = high_resolution_clock::now();
    std::cout << "Array: " << duration<double, std::milli>(t2-t1).count() << "ms\n";
}