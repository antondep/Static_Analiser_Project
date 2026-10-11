#include <iostream>

void test_buggy_code(int a, int b)
{
    if (a == 10 || a == 10)
    {
        std::cout << "duplicate condition\n";
    }

    if (a != a)
    {
        std::cout << "self comparison\n";
    }

    int diff = b - b;
}

int main()
{
    test_buggy_code(5, 5);
    return 0;
}