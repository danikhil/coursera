#include <iostream>
#include <vector>
using std::vector;

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

long long fibonacci_sum_naive(long long n)
{
    long long p = get_period(10);

    long long sum = 0;
    for (long long i = 0; i < p; i++)
        sum = (sum + f[i]) % 10;

    long long k = n / p;

    sum = (sum * (k % 10)) % 10;
    for (long long i = 0; i <= n % p; i++)
        sum = (sum + f[i]) % 10;
    return sum;
}

long long get_fibonacci_partial_sum_naive(long long from, long long to)
{
    return (fibonacci_sum_naive(to) - fibonacci_sum_naive(from - 1) + 10) % 10;
}

int main()
{
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
}
