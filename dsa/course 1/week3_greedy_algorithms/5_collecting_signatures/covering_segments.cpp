#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment
{
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments)
{
  vector<int> points;
  //write your code here

  std::sort(segments.begin(), segments.end(), [](const Segment a, const Segment b) {
    return a.end < b.end;
  });

  int pt = segments[0].end;
  points.push_back(pt);

  for (size_t i = 1; i < segments.size(); ++i)
  {
    if (pt < segments[i].start || pt > segments[i].end)
    {
      pt = segments[i].end;
      points.push_back(pt);
    }
  }
  return points;
}

int main()
{
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i)
  {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i)
  {
    std::cout << points[i] << " ";
  }
}
