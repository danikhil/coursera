#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>

using std::string;
using std::vector;

std::map<string, int> dp;

int find(int W1, int W2, int W3, int i, int size, vector<int> s)
{
    if (i == size)
        return (W1 == W2 && W2 == W3 && W3 == 0);
    string key1, key2, key3;
    if (W1 >= s[i])
    {
        key1 = std::to_string(W1 - s[i]) + '|' + std::to_string(W2) + '|' + std::to_string(W3) + '|' + std::to_string(i + 1);
        if (dp.find(key1) == dp.end())
            dp[key1] = find(W1 - s[i], W2, W3, i + 1, size, s);
    }
    if (W2 >= s[i])
    {
        key2 = std::to_string(W1) + '|' + std::to_string(W2 - s[i]) + '|' + std::to_string(W3) + '|' + std::to_string(i + 1);
        if (dp.find(key2) == dp.end())
            dp[key2] = find(W1, W2 - s[i], W3, i + 1, size, s);
    }
    if (W3 >= s[i])
    {
        key3 = std::to_string(W1) + '|' + std::to_string(W2) + '|' + std::to_string(W3 - s[i]) + '|' + std::to_string(i + 1);
        if (dp.find(key3) == dp.end())
            dp[key3] = find(W1, W2, W3 - s[i], i + 1, size, s);
    }
    return ((W1 >= s[i] && dp[key1]) || (W2 >= s[i] && dp[key2]) || (W3 >= s[i] && dp[key3]));
}

int partition3(vector<int> &A)
{
    int s = 0;
    for (auto i : A)
        s += i;
    if (s % 3)
        return 0;
    return find(s / 3, s / 3, s / 3, 0, A.size(), A);
}

int main()
{
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i)
    {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}
