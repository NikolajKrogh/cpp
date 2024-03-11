//
// Created by nikol on 20-02-2024.
//

#include <vector>
#include <memory>
#include <chrono>
#include <iostream>
#include "dynamic_polymorphism.h"

void dynamic_polymorphism::increment() {
    x++;
}

void dynamic_polymorphism::decrement() {
    x--;
}

void Derived::increment() {
    dynamic_polymorphism::increment();
    x+2;
}

int main(){
    int size = 10'000'000;
    std::vector<std::shared_ptr<dynamic_polymorphism>> vector;
    for (int i = 0; i < size; ++i) {
        std::shared_ptr<dynamic_polymorphism> derived(new Derived());
        vector.push_back(std::make_shared<Derived>());

    }

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    for(auto &i : vector){
        i->increment();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Increment: " << std::chrono::duration<double, std::milli>(end - start).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(auto &i : vector){
        i->decrement();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Decrement: " << std::chrono::duration<double, std::milli>(end - start).count() << "ms\n";

    std::vector<Derived> vector2;
    vector2.reserve(size);
    for (int i = 0; i < size; ++i) {
        vector2.emplace_back();
    }

    start = std::chrono::high_resolution_clock::now();
    for(auto &i : vector2){
        i.increment();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Increment (no pointer): " << std::chrono::duration<double, std::milli>(end - start).count() << "ms\n";
}