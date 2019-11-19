#include <iostream>
#include <cstring>
#include <cstdlib>

long long f[10001] = {0};

long long fibo(long long n, long long m)
{
    f[0] = 0;
    f[1] = 1;
    long long p;
    for (long long i = 2; i < 10000; i++)
    {
        f[i] = (f[i - 1] + f[i - 2]) % m;
        if (f[i] == 1 && f[i - 1] == 0)
        {
            p = i - 1;
            break;
        }
    }
    return f[n % p];
}

int main()
{
    long long n, m;
    std::cin >> n >> m;
    std::cout << fibo(n, m) << '\n';
}
