#include <iostream>
#include "Approach1.h"
#include "Approach2.h"
int factorial(int num) {
    if (num == 1) { return 1; }
    return num * factorial(num - 1);
}

int main()
{
    
    Approach2::run();
    
}

