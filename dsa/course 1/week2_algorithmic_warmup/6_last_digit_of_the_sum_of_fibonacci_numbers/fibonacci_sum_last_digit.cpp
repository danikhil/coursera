#include <iostream>

long long f[10001] = {0};

long long get_period(long long m)
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
    return p;
}

int fibonacci_sum_naive(long long n)
{
    long long p = get_period(10);

    long long sum = 0;
    for (long long i = 0; i < p; i++)
        sum = (sum + f[i]) % 10;

    long long k = n / p;

    sum = (sum * (k % 10)) % 10;
    for (long long i = 0; i <= n % p; i++)
        sum = (sum + f[i]) % 10;
    return (int)sum;
}

int main()
{
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_naive(n);
}
