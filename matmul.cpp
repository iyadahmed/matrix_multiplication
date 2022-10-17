#include <iostream>
#include "Matrix.hpp"

int main()
{
    Matrix4x4 A, B, result;
    std::cout << "Enter first 4x4 matrix elements" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cin >> A.element(i, j);
        }
    }

    std::cout << "Enter second 4x4 matrix elements" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cin >> B.element(i, j);
        }
    }

    A.mat_mul(result, B);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << result.element(i, j) << " ";
        }
        std::cout << "\n";
    }
}