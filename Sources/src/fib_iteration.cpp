/* Common implementation 2: Iteration algorithm */

#include <iostream>

int main(int argc, const char* argv[]) {
    (void)argc;
    (void)argv;

    unsigned long long f, f0 = 0, f1 = 1;

    for (int i = 0; i <= 48; i++) {
        if (i > 1) {
            f = f0 + f1;
            f0 = f1;
            f1 = f;
        } else
            f = static_cast<unsigned  long long>(i);
    }

    std::cout << f << std::endl;

    return 0;
}

