#include <iostream>

int main()
{
    int x = 6098123;
    int y = 60981239;

    long val = x + (y << sizeof(int));
    std::cout << x << " " << y << " " << val << std::endl;


    return 0;
}