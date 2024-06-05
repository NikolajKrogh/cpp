//
// Created by krogh on 6/5/24.
//

#ifndef EXAM_ARROW_H
#define EXAM_ARROW_H

#include <vector>
#include <string>

namespace stochastic {

    class Arrow {
    public:
        std::vector<std::string> source;
        std::vector<std::string> target;
        double rate;

        Arrow(std::vector<std::string> src, std::vector<std::string> tgt, double r);

        Arrow() = default;

        ~Arrow() = default;
    };

} // stochastic

#endif //EXAM_ARROW_H
