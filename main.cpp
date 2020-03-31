#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <execution>

#include "point.hpp"
#include "generator.hpp"
#include "closest.hpp"

int main(int argc, char **argv) {
    std::chrono::high_resolution_clock clock;
    gen g;

    std::cout << "points\ttime (us)\ttime bf (us)" << std::endl;
    constexpr int reps = 10;

    for (int i = 0; i < 25; i++)
    {
        const int count = (i + 1) * 200;
        double total_time = 0;
        double total_time_bf = 0;
        for (int rep = 0; rep < reps; rep++) {
            std::vector<point_t> points;
            g.generate(points, count);

            auto start_bf = clock.now();
            auto res_bf = find_closest_bf(points, 0, count);
            auto end_bf = clock.now();

            auto start = clock.now();
            std::sort(points.begin(), points.end(), 
                [](const point_t &a, const point_t &b) {
                return a.x < b.x;
            });
            auto res = find_closest(points, 0, count);
            auto end = clock.now();

            float dist = std::get<2>(res);
            float dist_bf = std::get<2>(res_bf);

            if (std::abs(dist - dist_bf) > 0.0001f) {
                std::cout << "CHYBA: " << std::endl
                    << "\t expected: " << dist_bf << " got: " << dist << std::endl;
                return 1;
            }

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            total_time_bf += std::chrono::duration_cast<std::chrono::microseconds>(end_bf - start_bf).count();
        }
        std::cout << count << "\t" << total_time / (double)reps << "\t" << total_time_bf / (double)reps << std::endl;
    }

    for (int i = 25; i < 500; i++)
    {
        const int count = (i + 1) * 200;
        double total_time = 0;
        for (int rep = 0; rep < reps; rep++) {
            std::vector<point_t> points;
            g.generate(points, count);

            auto start = clock.now();
            std::sort(points.begin(), points.end(),
                [](const point_t &a, const point_t &b) {
                return a.x < b.x;
            });
            auto res = find_closest(points, 0, count);
            auto end = clock.now();

            float dist = std::get<2>(res);

            total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        std::cout << count << "\t" << total_time / (double)reps << "\t" << std::endl;
    }

    return 0;
}