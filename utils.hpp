#pragma once

#include <xmmintrin.h>

inline float fastSqrtf(float f)
{
    float ret;
    //SSE sqrtss -> fast and precise. (2x - 3x faster than std::sqrt(float)) (MSVC compiler and Ivy Bridge CPU)
    _mm_store_ss(&ret, _mm_sqrt_ss(_mm_load_ss(&f)));
    return ret;
}
