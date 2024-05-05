#ifndef CPP_EXERCISE_01_H
#define CPP_EXERCISE_01_H


#include <vector>

class Polylines {
public:
    std::vector<std::pair<int, int>> points;
    Polylines& operator += (const std::pair<int,int> &other)
    {
        points.push_back(other);
        return *this;
    }
    // default constructor
    Polylines() = default;

    // copy constructor
    Polylines(const Polylines& other) : points (other.points) {}

    // move constructor
    Polylines(Polylines&& other) noexcept : points(std::move(other.points)) {}

    // copy assignment
    Polylines& operator = (const Polylines& other)
    {
        if (this != &other) {
            points = other.points;
        }
        return *this;
    }

};


#endif //CPP_EXERCISE_01_H
