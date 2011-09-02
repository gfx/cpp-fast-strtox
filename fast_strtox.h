// a faster replacement of strtof(3), strtod(3) and simple version of
// strtol(3)
//
// strtof() and strtod() are originated from a Perl module JSON::XS's
// implementation
// Copyright (c) Marc Lehmann <schmorp@schmorp.de>,  http://home.schmorp.de/
// The COPYING says "This module is licensed under the same terms as perl itself."
//

#pragma once
#include <cmath>   // for std::pow()
#include <climits> // for ULONG_MAX
#include <cassert>

#define strtof fast_strtof
#define strtod fast_strtod
#define strtol fast_strtol

namespace {
    typedef unsigned char uchar_t;
    using std::pow;

    const char* fast_strtod_scan1(const char* s,
         double* const accum, int* const expo, int const postdp, int maxdepth)
    {
        unsigned long uaccum = 0;
        int eaccum = 0;

        // if we recurse too deep, skip all remaining digits
        // to avoid a stack overflow attack
        if (--maxdepth <= 0) {
            while (((uchar_t)*s - (uchar_t)'0') < 10) {
              ++s;
            }
        }

        for (;;) {
            uchar_t dig = (uchar_t)*s - (uchar_t)'0';

            if (dig >= 10) {
                if (dig == (uchar_t)((uchar_t)'.' - (uchar_t)'0')) {
                    ++s;
                    s = fast_strtod_scan1(s, accum, expo, 1, maxdepth);
                }
                else if ((dig | ' ') == 'e' - '0') {
                    int exp2 = 0;
                    bool neg = false;

                    ++s;

                    if (*s == '-') {
                        ++s;
                        neg = true;
                    }
                    else if (*s == '+') {
                        ++s;
                    }

                    while ((dig = (uchar_t)*s - (uchar_t)'0') < 10) {
                        exp2 = exp2 * 10 + *s++ - '0';
                    }

                    *expo += neg ? -exp2 : exp2;
                }

                break;
            }

            ++s;

            uaccum = uaccum * 10 + dig;
            ++eaccum;

            // if we have too many digits, then recurse for more
            // we actually do this for rather few digits
            if (uaccum >= (ULONG_MAX - 9) / 10) {
                if (postdp) *expo -= eaccum;
                s = fast_strtod_scan1(s, accum, expo, postdp, maxdepth);
                if (postdp) *expo += eaccum;

                break;
            }
        }

        // this relies greatly on the quality of the pow ()
        // implementation of the platform, but a good
        // implementation is hard to beat.
        // (IEEE 754 conformant ones are required to be exact)
        if (postdp) *expo -= eaccum;
        *accum += uaccum * pow(10.0, *expo);
        *expo += eaccum;
        return s;
    }

    template <typename Float>
    Float fast_str_to_float(const char* nptr, const char** endptr) {
        double accum = 0.0;
        int expo     = 0;
        bool neg     = false;

        if(*nptr == '-') {
            ++nptr;
            neg = true;
        }
        nptr = fast_strtod_scan1(nptr, &accum, &expo, 0, 10);
        if(endptr) {
            *endptr = nptr;
        }
        return static_cast<Float>( neg ? -accum : accum );
    }

    inline float fast_strtof(const char* nptr, char** endptr) {
        return fast_str_to_float<float>(nptr, (const char**)endptr);
    }
    inline double fast_strtod(const char* nptr, char** endptr) {
        return fast_str_to_float<double>(nptr, (const char**)endptr);
    }


    static inline
    long fast_strtol(const char* s, char** endp, int const base) {
        assert(base == 10); // only support base=10

        bool neg = false;
        if(*s == '-') {
            ++s;
            neg = true;
        }

        long result = 0;

        while(true) {
            if((uchar_t)*s > (uchar_t)'9' || (uchar_t)*s < (uchar_t)'0') {
                break;
            }
            result = result * 10 + (uchar_t)*s - (uchar_t)'0';
            ++s;
        }
        *endp = (char*)s;

        return neg ? -result : result;
    }

} // end namespace

