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
    Polylines() = default; // default constructor

    Polylines(const Polylines& other){ // copy constructor
        points = other.points; // deep copy
    }

};


#endif //CPP_EXERCISE_01_H
