#include "Approach2.h"
#include <iostream>
#include <math.h>
namespace Approach2 {
    
    result run(const int* input) {
        int highorder = -1;
        int leadCoeff = -1;
        int set[20];
        for (int x = 0; x < 20; x++)
        {
            set[x] = input[x];
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
                for (int y = 0; y < 4 - x; y++)
                {
                    values[x][y] = values[x - 1][y + 1] - values[x - 1][y];
                }


            }
            terms[5 - order] = values[order - 1][0] / factorial(order - 1);
        }
        std::cout << terms[0] << "x^4 + " << terms[1] << "x^3 + " << terms[2] << "x^2 + " << terms[3] << "x + " << terms[4] << '\n';
        result r{ terms[0],terms[1],terms[2],terms[3],terms[4] };
        return r;
    }
    int factorial(int num) {
        if (num <= 1) { return 1; }
        return num * factorial(num - 1);
    }
    
    void set_order_and_lead_coeff(int* input, int* order, int* leadCoeff) {
        int values[5][5]{};
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
            if (values[currentOrder][0] == values[currentOrder][1] || (currentOrder == 4)) {
                *order = currentOrder;
                *leadCoeff = values[currentOrder][0] / factorial(currentOrder);
                return;
            }
            currentOrder++;
        }
    }

}
