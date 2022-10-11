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
thirdOrderExpr derive_formula(const int* order, const int* input, const int* constantDifference) {
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
    int firstCoeff = (*constantDifference) / factorial(*order);
    int a = *order>= 4 ? (*order == 4 ? firstCoeff : 1) : 0;
    int b = *order>= 3 ? (*order == 3 ? firstCoeff : 1) : 0;
    int c = *order>= 2 ? (*order == 2 ? firstCoeff : 1) : 0;
    int d = *order>= 1 ? (*order == 1 ? firstCoeff : 1) : 0;
    int e = 1;
    for (int x = (*order); x>0; x--)
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
    if (input[1] - input[0] == input[2] - input[1]) { *constantDifference = input[1] - input[0]; return 1; }
    for (int a = 0; a < 5; a++)
    {
        first[a] = input[a + 1] - input[a];
    }
    if (first[1] - first[0] == first[2] - first[1]) { *constantDifference = first[1] - first[0]; return 2; }
    for (int b = 0; b < 4; b++)
    {
        second[b] = first[b + 1] - first[b];
    }
    if (second[1] - second[0] == second[2] - second[1]) { *constantDifference = second[1] - second[0]; return 3; }
    for (int c = 0; c < 3; c++)
    {
        third[c] = second[c + 1] - second[c];
    }
    if (third[1] - third[0] == third[2] - third[1]) { *constantDifference = third[1] - third[0]; return 4; }
    return -1;
}
int main()
{
    //3x^3
    int a[] = { 0, 3, 24, 81, 192, 375, 648, 1029, 1536, 2187, 3000, 3993, 5184, 6591, 8232, 10125, 12288, 14739, 17496, 20577, 24000 };
    
    //5x^4 - 9
    int b[] = { -9, -4, 71, 396, 1271, 3116, 6471, 11996, 20471, 32796, 49991, 73196, 103671, 142796, 192071, 253116, 327671, 417596, 524871, 651596, 799991 };

    //9x^3 + 7x^2 - 2x
    int c[] = { 0, 14, 96, 300, 680, 1290, 2184, 3416, 5040, 7110, 9680, 12804, 16536, 20930, 26040, 31920, 38624, 46206, 54720, 64220, 74760 };

    //-x^3 + 2x^2 + 5x + 7
    int d[] = { 7, 13, 17, 13, -5, -43, -107, -203, -337, -515, -743, -1027, -1373, -1787, -2275, -2843, -3497, -4243, -5087, -6035, -7093 };

    //-x^3 -3x + 114
    int e[] = { 114, 110, 100, 78, 38, -26, -120, -250, -422, -642, -916, -1250, -1650, -2122, -2672, -3306, -4030, -4850, -5772, -6802, -7946 };

    //-6x^2 -84x + 715
    int f[] = { 715, 625, 523, 409, 283, 145, -5, -167, -341, -527, -725, -935, -1157 };

    int constantDifference = -1;
    int order = determine_order(f, &constantDifference);
    thirdOrderExpr idk = derive_formula(&order, f, &constantDifference);
    if (order == -1) { std::cout << "order not detected"; }
}