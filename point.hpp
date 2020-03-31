#pragma once

#include "utils.hpp"

class point_t {
public:
    point_t(float X, float Y) : x(X), y(Y) {}
    point_t() : x(0), y(0) {}
    point_t(point_t&&) = default;
    point_t(const point_t&) = default;
    point_t& operator=(const point_t&) = default;
  
    float x;
    float y;

    inline float dist2(const point_t& other) const noexcept{
        float x_dif = x - other.x;
        float y_dif = y - other.y;

        return x_dif * x_dif + y_dif * y_dif;
    }

    inline float dist(const point_t& other) const noexcept {
        return fastSqrtf(dist2(other));
    }
};