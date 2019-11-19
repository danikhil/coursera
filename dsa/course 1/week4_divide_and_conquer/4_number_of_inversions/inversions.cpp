#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>

using std::vector;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;

ll merge(vector<int> &a, int l, int mid, int r)
{

  // for (auto i : a)
  //   std::cout << i << ' ';
  // std::cout << '\n';
  ll inv_c = 0;
  vi left(a.begin() + l, a.begin() + mid + 1);
  vi right(a.begin() + mid + 1, a.begin() + r + 1);

  // for (auto i : left)
  //   std::cout << i << ' ';
  // std::cout << '\n';

  // for (auto i : right)
  //   std::cout << i << ' ';
  // std::cout << '\n';

  //std::cout << left[mid] << ' ';

  int i = 0, j = 0, k = l;

  while (i < left.size() && j < right.size())
  {
    if (left[i] <= right[j])
      a[k++] = left[i++];
    else
    {
      a[k++] = right[j++];
      inv_c += mid - (i + l) + 1;
      //std::cout << inv_c << '\n';
    }
  }
  while (i < left.size())
  {
    a[k++] = left[i++];
  }
  while (j < right.size())
  {
    a[k++] = right[j++];
  }
  return inv_c;
}

long long merge_sort(vector<int> &a, int l, int r)
{
  ll inv_c = 0;
  if (l == r)
    return inv_c;
  int mid = (l + r) / 2;
  inv_c = merge_sort(a, l, mid);
  inv_c += merge_sort(a, mid + 1, r);
  inv_c += merge(a, l, mid, r);
  return inv_c;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right)
{
  long long number_of_inversions = merge_sort(a, left, right - 1);

  // for (auto i : a)
  //   std::cout << i << ' ';
  return number_of_inversions;
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++)
  {
    std::cin >> a[i];
  }
  vector<int> b = a;
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
