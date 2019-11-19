#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <map>

using std::vector;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;

using std::vector;

#define fast std::ios_base::sync_with_stdio(false)

struct range
{
  int X, Y;
};

int brute_f(vector<range> &v, int s, int e, int x)
{
  int c = 0;
  for (int i = s; i <= e; i++)
  {
    //std::cout<< i <<' ';
    if (v[i].X <= x && v[i].Y >= x)
      c++;
  }
  return c;
}

int bin_search(vector<range> &r, int x)
{
  int s = 0, e = r.size() - 1;
  while (s <= e)
  {
    int mid = (s + e) / 2;
    if (r[mid].X > x)
      e = mid - 1;
    else
      return brute_f(r, s, e, x);
  }
  return 0;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points)
{
  int size = starts.size();
  vector<range> r(size);
  for (int i = 0; i < size; i++)
  {
    r[i].X = starts[i];
    r[i].Y = ends[i];
  }

  sort(r.begin(), r.end(), [](range &a, range &b) {
    return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
  });

  vector<int> cnt;

  for (auto i : points)
  {
    cnt.push_back(bin_search(r, i));
    //std::cout << '\n';
  }
  return cnt;
}

int main()
{
  fast;
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++)
  {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++)
  {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++)
  {
    std::cout << cnt[i] << ' ';
  }
}
