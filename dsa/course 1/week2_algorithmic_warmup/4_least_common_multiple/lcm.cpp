#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
  long long a, b;
  std::cin >> a >> b;
  std::cout << a * b / std::__gcd(a, b) << std::endl;
  return 0;
}
