#include <boost/timer.hpp>
#include <cstdlib>
#include <iostream>

#include "fast_strtox.h"


int main() {
    const char* const pistr  = "3.14159265358979323846264338327950288,foo";
    const char* const ansstr = "42,foo";
    {
        boost::timer t;
        for(int i = 0; i < (1 * 1000 * 1000); ++i) {
            char* tmp;
            float f = std::strtof(pistr, &tmp);
            (void)f;
        }
        std::cout << "std::strtof(): " << t.elapsed() << std::endl;
    }
    {
        boost::timer t;
        for(int i = 0; i < (1 * 1000 * 1000); ++i) {
            char* tmp;
            float f = fast_strtof(pistr, &tmp);
            (void)f;
        }
        std::cout << "fast_strtof(): " << t.elapsed() << std::endl;
    }

    {
        boost::timer t;
        for(int i = 0; i < (1 * 1000 * 1000); ++i) {
            char* tmp;
            double f = std::strtod(pistr, &tmp);
            (void)f;
        }
        std::cout << "std::strtod(): " << t.elapsed() << std::endl;
    }
    {
        boost::timer t;
        for(int i = 0; i < (1 * 1000 * 1000); ++i) {
            char* tmp;
            double f = fast_strtod(pistr, &tmp);
            (void)f;
        }
        std::cout << "fast_strtod(): " << t.elapsed() << std::endl;
    }

    {
        boost::timer t;
        for(int i = 0; i < (1 * 1000 * 1000); ++i) {
            char* tmp;
            float f = std::strtol(ansstr, &tmp, 10);
            (void)f;
        }
        std::cout << "std::strtol(): " << t.elapsed() << std::endl;
    }
    {
        boost::timer t;
        for(int i = 0; i < (1 * 1000 * 1000); ++i) {
            char* tmp;
            float f = fast_strtol(ansstr, &tmp, 10);
            (void)f;
        }
        std::cout << "fast_strtol(): " << t.elapsed() << std::endl;
    }

    return 0;
}

