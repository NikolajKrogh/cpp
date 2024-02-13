//
// Created by nikol on 13-02-2024.
//

#include <iostream>
#include "exercise_01.h"

int main(void) {
    Polylines p;

    // Exercise 1: Add points to the polyline
    p += std::make_pair(1,2);
    p += std::make_pair(3,4);

    for (auto &point : p.points) {
        std::cout << "Point: " << point.first << " " << point.second << std::endl;
    }

    // Exercise 2: Copy the polyline
    Polylines p2 = p;
    for (auto &point : p2.points) {
        std::cout << "Point: " << point.first << " " << point.second << std::endl;
    }
}