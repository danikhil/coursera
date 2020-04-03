#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>

using std::vector;

int find(int W1, int W2, int W3, int i, int size, vector<int> s)
{
    if (i == size)
    {
        return (W1 == W2 && W2 == W3 && W1 == 0);
    }
    return (W1 >= s[i] && find(W1 - s[i], W2, W3, i + 1, size, s)) || (W2 >= s[i] && find(W1, W2 - s[i], W3, i + 1, size, s)) || (W3 >= s[i] && find(W1, W2, W3 - s[i], i + 1, size, s));
}

int partition3(vector<int> &A)
{
    int s = 0;
    for (auto i : A)
        s += i;
    //std::cout << s << '\n';
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
