#include <iostream>
#include "fast_strtox.h"

#undef strtof
#undef strtod
#undef strtol

int main() {
    int i = 0;

    std::cout << "# strtof()" << std::endl;
    {
        const char* const str = "3.14159265358979323846264338327950288,foo";
        char* e = NULL;
        char* d = NULL;

        float f = std::strtof(str, &e);
        float g = fast_strtof(str, &d);

        if(f == g) {
            std::cout << "ok " << ++i << "\n";
        }
        else {
            std::cout << "not ok " << ++i << "\n";
            std::cout << "got:      " << g << std::endl;
            std::cout << "expected: " << f << std::endl;
        }
        if(e ==  d) {
            std::cout << "ok " << ++i << "\n";
        }
        else {
            std::cout << "not ok " << ++i << "\n";
            std::cout << "got:      " << (str - d) << std::endl;
            std::cout << "expected: " << (str - e) << std::endl;
        }
    }

    std::cout << "# strtod()" << std::endl;
    {
        const char* const str = "3.14159265358979323846264338327950288,foo";
        char* e = NULL;
        char* d = NULL;

        float f = std::strtof(str, &e);
        float g = fast_strtof(str, &d);

        if(f == g) {
            std::cout << "ok " << ++i << "\n";
        }
        else {
            std::cout << "not ok " << ++i << "\n";
            std::cout << "got:      " << g << std::endl;
            std::cout << "expected: " << f << std::endl;
        }
        if(e ==  d) {
            std::cout << "ok " << ++i << "\n";
        }
        else {
            std::cout << "not ok " << ++i << "\n";
            std::cout << "got:      " << (str - d) << std::endl;
            std::cout << "expected: " << (str - e) << std::endl;
        }
    }
    
    std::cout << "# strtol()" << std::endl;
    {
        const char* const str = "3.14159265358979323846264338327950288,foo";
        char* e = NULL;
        char* d = NULL;

        float f = std::strtol(str, &e, 10);
        float g = fast_strtol(str, &d, 10);

        if(f == g) {
            std::cout << "ok " << ++i << "\n";
        }
        else {
            std::cout << "not ok " << ++i << "\n";
            std::cout << "got:      " << g << std::endl;
            std::cout << "expected: " << f << std::endl;
        }
        if(e ==  d) {
            std::cout << "ok " << ++i << "\n";
        }
        else {
            std::cout << "not ok " << ++i << "\n";
            std::cout << "got:      " << (str - d) << std::endl;
            std::cout << "expected: " << (str - e) << std::endl;
        }
    }
    return 0;
}

