#include <iostream>
int factorial(int num) {
    if (num == 1) { return 1; }
    return num * factorial(num - 1);
}
struct thirdOrderExpr {
    int y; //from input
    int a; //x^3
    int b; //x^2
    int c; //x
    int d; //constant
};

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
    std::cout << 18 / factorial(3);
    int input[21] = { 0, 3, 24, 81, 192, 375, 648, 1029, 1536, 2187, 3000, 3993, 5184, 6591, 8232, 10125, 12288, 14739, 17496, 20577, 24000 };
    //int input[] = { 5,19,49,101,181,295,449 };
    //int input[] = { 4,17,54,127,248,429 };
    int constantDifference = -1;
    int order = determine_order(input, &constantDifference);
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