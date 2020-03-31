#pragma once
#include <tuple>
#include <limits>
#include <algorithm>
#include <vector>

#include "point.hpp"
#include "utils.hpp"

constexpr int treshold = 10;


std::tuple<point_t, point_t, float> find_closest_bf(const std::vector<point_t>& buf, int start, int count) {
    float min_dist = std::numeric_limits<float>::max();
    int min_i = 0;
    int min_j = min_i + 1;

    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            float cur_dist = buf[start + i].dist2(buf[start + j]);
            if (cur_dist < min_dist) {
                min_dist = cur_dist;
                min_i = i;
                min_j = j;
            }
        }
    }

    return std::tuple<point_t, point_t, float>(buf[start + min_i], buf[start + min_j], fastSqrtf(min_dist));
}

std::tuple<point_t, point_t, float> find_closest(const std::vector<point_t>& buf, int start, int count) {   
    if (count < treshold) {
        return find_closest_bf(buf, start, count);
    }
    else {
        int offset = count / 2;
        int count2 = count - offset;
        auto cl1 = find_closest(buf, start, offset);
        auto cl2 = find_closest(buf, start + offset, count2);

        float minDist = std::min<float>(std::get<2>(cl1), std::get<2>(cl2));

        float partition = (buf[start + offset - 1].x + buf[start + offset].x) * 0.5f;

        int min_i = start;
        int max_i = start + count;
        for (int i = start; i < start + offset; ++i) {
            if (buf[i].x >= partition - minDist) {
                min_i = i;
                break;
            }
        }
        for (int i = start + offset; i < start + count; ++i) {
            if (buf[i].x >= partition + minDist) {
                max_i = i + 1;
                break;
            }
        }

        float min_dist = std::numeric_limits<float>::max();
        int min_k = min_i;
        int min_j = start + offset;
        for (int k = min_i; k < start + offset; ++k) {
            for (int j = start + offset; j < max_i; ++j) {
                float cur_dist = buf[k].dist2(buf[j]);
                if (cur_dist < min_dist) {
                    min_dist = cur_dist;
                    min_k = k;
                    min_j = j;
                }
            }
        }
        min_dist = fastSqrtf(min_dist);

        if (min_dist < minDist) {
            return std::tuple<point_t, point_t, float>(buf[min_k], buf[min_j], min_dist);
        }
        return std::get<2>(cl1) < std::get<2>(cl2) ? cl1 : cl2;
    }
}
