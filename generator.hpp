#pragma once

#include "point.hpp"
#include <random>
#include <vector>

class gen {
public:
    inline void generate(std::vector<point_t>& buf, int count) {
        buf.resize(count);
        for (int i = 0; i < count; i++) {
            buf[i] = point_t(100 * random(), 100 * random());
        }
    }
private:
    std::default_random_engine generator;
    inline float random() {
        std::uniform_real_distribution<float> distr(0.0f, 1.0f);
        return distr(generator);
    }
};