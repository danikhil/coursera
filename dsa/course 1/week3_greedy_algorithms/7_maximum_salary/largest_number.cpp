#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::string;
using std::vector;

string largest_number(vector<string> a)
{
  //write your code here
  std::sort(a.begin(), a.end(), [](const string x, const string y) {
    return x + y > y + x;
  });
  string result;
  for (size_t i = 0; i < a.size(); i++)
  {
    result += a[i];
  }

  return result;
}

int main()
{
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++)
  {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
