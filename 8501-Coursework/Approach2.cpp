#include "Approach2.h"
#include "Sets.h"
#include <iostream>
#include <math.h>
namespace Approach2 {
    void run() {
        int highorder = -1;
        int leadCoeff = -1;
        int set[20];
        for (int x = 0; x < 20; x++)
        {
            set[x] = Sets::f[x];
        }
        int terms[5]{};
        set_order_and_lead_coeff(set,&highorder,&leadCoeff);
        terms[4-highorder] = leadCoeff;
        int values[4][4]{};
        for (int order = highorder; order > 0; order--)
        {
            for (int x = 0; x < order + 1; x++)
            {
                set[x] -= terms[4 - order] * pow(x, order);
                values[0][x] = set[x];
            }
            for (int x = 1; x < order; x++)
            {
                for (int y = 0; y < 4 - x; y++)//we now know that we are left with a maximum degree of 3, requiring 4 initial values to determine constant difference
                {
                    values[x][y] = values[x - 1][y + 1] - values[x - 1][y];
                }


            }
            terms[5 - order] = values[order - 1][0] / factorial(order - 1);
        }


        std::cout << "order " << highorder << " leadCoeff " << leadCoeff;

        return;
    }
    int factorial(int num) {
        if (num <= 1) { return 1; }
        return num * factorial(num - 1);
    }
    
    void set_order_and_lead_coeff(int* input, int* order, int* leadCoeff) {
        int values[5][5]{};
        for (int x = 0; x < 5; x++)//we know degree will be no higher than 4, which requires 5 initial values to determine constant difference
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
            if (values[currentOrder][0] == values[currentOrder][1] || (currentOrder == 4)) {
                std::cout << "constant difference or order 4\n";
                *order = currentOrder;
                *leadCoeff = values[currentOrder][0] / factorial(currentOrder);
                return;
            }
            currentOrder++;
        }
    }

}
