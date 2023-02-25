#include <iostream>

#include "Date.h"

int main() {
    Date d1(12, 6, 2023);
    Date d2(18, 12, 2023);

    std::cout<<d1-d2;

    return 0;
}