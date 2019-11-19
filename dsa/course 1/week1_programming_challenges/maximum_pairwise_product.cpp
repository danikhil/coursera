#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long MaxPairwiseProduct(const std::vector<int> &numbers)
{
    int max_product = 0;
    int n = numbers.size();

    long long max1 = max(numbers[0], numbers[1]);
    long long max2 = min(numbers[0], numbers[1]);

    for (int i = 2; i < n; i++)
    {
        if (numbers[i] > max1)
        {
            max2 = max1;
            max1 = numbers[i];
        }
        else if (numbers[i] > max2)
            max2 = numbers[i];
    }

    return max1 * max2;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
