#include <iostream>
int factorial(int num) {
    if (num == 1) { return 1; }
    return num * factorial(num - 1);
}
struct thirdOrderExpr {
    int y; //from input
    int a; //x^4
    int b; //x^3
    int c; //x^2
    int d; //x
    int e; //constant
};
thirdOrderExpr operator-(const thirdOrderExpr lhs, const thirdOrderExpr rhs) {
    thirdOrderExpr result;
    result.y = lhs.y - rhs.y;
    result.a = lhs.a - rhs.a;
    result.b = lhs.b - rhs.b;
    result.c = lhs.c - rhs.c;
    result.d = lhs.d - rhs.d;
    result.e = lhs.e - rhs.e;
    return result;
}
struct result {
    int a; //x^4
    int b; //x^3
    int c; //x^2
    int d; //x
    int e; //constant
};
thirdOrderExpr derive_formula(const int* order, const int* input) {
    thirdOrderExpr formula{};
    thirdOrderExpr exprs[5][5] = {};
    //todo change this to start at index 0 to reduce required number of inputs
    
    for (int x = 0; x < (*order)+1; x++)
    {
        exprs[0][x].y = input[x + 1];
        exprs[0][x].a = *order>=4 ? pow(x + 1, 4) : 0;
        exprs[0][x].b = *order>=3 ? pow(x + 1, 3) : 0;
        exprs[0][x].c = *order>=2 ? pow(x + 1, 2) : 0;
        exprs[0][x].d = *order>=1 ? x+1 : 0;
        exprs[0][x].e = 1;
    }
    for (int x = 1; x < (*order)+1; x++)
    {
        for (int y = 0; y < (*order)+1-x; y++)
        {
            exprs[x][y] = exprs[x - 1][y + 1] - exprs[x - 1][y];
        }
    }
    int a = *order>= 4 ? 1 : 0;
    int b = *order>= 3 ? 1 : 0;
    int c = *order>= 2 ? 1 : 0;
    int d = *order>= 1 ? 1 : 0;
    int e = 1;
    for (int x = (*order)+1; x>0; x--)
    {
        thirdOrderExpr expr = exprs[x-1][0];
        expr.a *= a;
        expr.b *= b;
        expr.c *= c;
        expr.d *= d;
        expr.e *= e;
        switch (x-1) {
        case(0):
            e = (expr.y - expr.a - expr.b - expr.c - expr.d) / expr.e;
            break;
        case(1):
            d = (expr.y - expr.a - expr.b - expr.c - expr.e) / expr.d;
            break;
        case(2):
            c = (expr.y - expr.a - expr.b - expr.d - expr.e) / expr.c;
            break;
        case(3):
            b = (expr.y - expr.a - expr.c - expr.d - expr.e) / expr.b;
            break;
        } 
    }
    return formula;//doesnt actually return values, look at values of a through e for result
}
int determine_order(int* input, int* constantDifference) {
    int first[5]{};
    int second[4]{};
    int third[3]{};
    int fourth[2]{};
    if (input[1] - input[0] == input[2] - input[1]) { return 1; }
    for (int a = 0; a < 5; a++)
    {
        first[a] = input[a + 1] - input[a];
    }
    if (first[1] - first[0] == first[2] - first[1]) { return 2; }
    for (int b = 0; b < 4; b++)
    {
        second[b] = first[b + 1] - first[b];
    }
    if (second[1] - second[0] == second[2] - second[1]) { *constantDifference = second[1] - second[0]; return 3; }
    for (int c = 0; c < 3; c++)
    {
        third[c] = second[c + 1] - second[c];
    }
    if (third[1] - third[0] == third[2] - third[1]) { return 4; }
    return -1;
}
int main()
{
    //int input[21] = { 0, 3, 24, 81, 192, 375, 648, 1029, 1536, 2187, 3000, 3993, 5184, 6591, 8232, 10125, 12288, 14739, 17496, 20577, 24000 };
    //int input[] = { 5,19,49,101,181,295,449 };
    //int input[] = { 4,17,54,127,248,429 };
    int input[] = { 114, 110, 100, 78, 38, -26, -120, -250, -422, -642, -916, -1250, -1650, -2122, -2672, -3306, -4030, -4850, -5772, -6802, -7946 };
    int constantDifference = -1;
    int order = determine_order(input, &constantDifference);
    thirdOrderExpr idk = derive_formula(&order, input);
    if (order == -1) { std::cout << "order not detected"; }
    std::cout << order << '\n';
    switch (order) {
    case 3:
        thirdOrderExpr n0 = { input[1],1,1,1,1};
        thirdOrderExpr n1 = { input[2],8,4,2,1};
        thirdOrderExpr n2 = { input[3],27,9,3,1};
        thirdOrderExpr n3 = { input[4],64,16,4,1};
        //int a = constantDifference / factorial(3);
        thirdOrderExpr n4 = {
            n1.y - n0.y,
            n1.a - n0.a,
            n1.b - n0.b,
            n1.c - n0.c,
            n1.d - n0.d
        };
        std::cout << n4.y << ' ' << n4.a << ' ' << n4.b << ' ' << n4.c << ' ' << n4.d << '\n';
        thirdOrderExpr n5 = {
            n2.y - n1.y,
            n2.a - n1.a,
            n2.b - n1.b,
            n2.c - n1.c,
            n2.d - n1.d
        };
        std::cout << n5.y << ' ' << n5.a << ' ' << n5.b << ' ' << n5.c << ' ' << n5.d << '\n';
        thirdOrderExpr n6 = {
            n3.y - n2.y,
            n3.a - n2.a,
            n3.b - n2.b,
            n3.c - n2.c,
            n3.d - n2.d
        };
        std::cout << n6.y << ' ' << n6.a << ' ' << n6.b << ' ' << n6.c << ' ' << n6.d << '\n';


        thirdOrderExpr n7 = {
            n5.y - n4.y,
            n5.a - n4.a,
            n5.b - n4.b,
            n5.c - n4.c,
            n5.d - n4.d
        };
        std::cout << n7.y << ' ' << n7.a << ' ' << n7.b << ' ' << n7.c << ' ' << n7.d << '\n';

        thirdOrderExpr n8 = {
            n6.y - n5.y,
            n6.a - n5.a,
            n6.b - n5.b,
            n6.c - n5.c,
            n6.d - n5.d
        };
        std::cout << n8.y << ' ' << n8.a << ' ' << n8.b << ' ' << n8.c << ' ' << n8.d << '\n';

        thirdOrderExpr n9 = {
            n8.y - n7.y,
            n8.a - n7.a,
            n8.b - n7.b,
            n8.c - n7.c,
            n8.d - n7.d
        };
        std::cout << n9.y << ' ' << n9.a << ' ' << n9.b << ' ' << n9.c << ' ' << n9.d << '\n';
        int a = n9.y / n9.a;
        //n8.y = n8.a*a + n8.b*b 
        int b = (n8.y - a*n8.a)/n8.b;
        int c = n4.y - ((n4.a * a) + (n4.b * b));
        int d = input[1] - (a + b + c);
        std::cout << "a:" << a << " b:" << b << " c:" << c << " d:" << d << '\n';
        break;
    }
}