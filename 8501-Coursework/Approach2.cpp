#include "Approach2.h"
#include "Sets.h"
#include <iostream>
namespace Approach2 {
    void run() {
        int order = -1;
        int leadCoeff = -1;
        int test[]{ 4,17,54,127,248 };
        set_order_and_lead_coeff(test,&order,&leadCoeff);
        std::cout << "order " << order << " leadCoeff " << leadCoeff;

        return;
    }
    int factorial(int num) {
        if (num == 1) { return 1; }
        return num * factorial(num - 1);
    }
    
    void set_order_and_lead_coeff(int* input, int* order, int* leadCoeff) {
        int values[4][5]{};
        for (int x = 0; x < 5; x++)
        {
            values[0][x] = input[x];
        }
        int constantDifference = 0;
        int currentOrder = 1;
        while (true) {
            for (int x = 0; x < 5-currentOrder; x++)
            {
                values[currentOrder][x] = values[currentOrder - 1][x + 1] - values[currentOrder - 1][x];
            }
            if (values[currentOrder][0] == values[currentOrder][1]) {
                std::cout << "constant difference";
                *order = currentOrder;
                *leadCoeff = values[currentOrder][0] / factorial(currentOrder);
                return;
            }
            currentOrder++;
        }
    }

}
