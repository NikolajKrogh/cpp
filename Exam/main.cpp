#include <iostream>
#include "stochastic_simulation_library.h"
int main() {
    const auto gammaA = 1;
    auto v = stochastic_simulation_library::Vessel{"Circadian Rhythm"};
            const auto env = v.environment();
            const auto DA = v.add("DA", 1);
            const auto D_A = v.add("D_A", 0);
            const auto DR = v.add("DR", 1);
            const auto A = v.add("A", 0);
            v.add((A + DA) >> gammaA >>= D_A);
    return 0;
}
