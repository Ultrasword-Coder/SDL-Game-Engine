#include <unordered_map>
#include <iostream>

int main()
{
    std::unordered_map<int, int> nums;

    for (int i = 0; i < 10; i++)
        nums[i] = 10000 + i;

    for (int i = 0; i < 20; i++)
    {
        std::cout << nums[i] << std::endl;
    }

    return 0;
}