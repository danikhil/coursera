#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define mn 9999999999.9

struct point
{
  long double x, y;

  int index;
};

point makepoint(double a, double b, int i)
{
  point temp;

  temp.x = a;
  temp.y = b;
  temp.index = i;

  return temp;
}

double dist(point p1, point p2)
{
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareX(point a, point b)
{
  return a.x < b.x;
}

bool compareY(point a, point b)
{
  return a.y < b.y;
}

int indexa, indexb;

double ans = 999999999;

double bruteforce(point p[], int n)
{
  double d = mn;

  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      double dtemp = dist(p[i], p[j]);

      if (dtemp < d)
      {
        d = dtemp;

        if (d < ans)
        {
          ans = d;

          indexa = p[i].index;

          indexb = p[j].index;
        }
      }
    }
  }

  return d;
}

double closest(point points[], int n)
{
  if (n <= 3)

    return bruteforce(points, n);

  int mid = n / 2;

  double left = closest(points, mid);

  double right = closest(points + mid, n - mid);

  double d = min(left, right);

  point strip[n];

  int stripsize = 0;

  point midpoint = points[mid];

  for (int i = 0; i < n; i++)
  {
    if (abs(points[i].x - midpoint.x) < d)

      strip[stripsize++] = points[i];
  }

  sort(strip, strip + stripsize, compareY);

  for (int i = 0; i < stripsize; i++)
  {
    for (int j = i + 1; j < stripsize; j++)
    {
      double tempdist = dist(strip[i], strip[j]);

      if (tempdist >= d)
        break;

      d = tempdist;

      if (d < ans)
      {
        ans = d;
        indexa = strip[i].index;
        indexb = strip[j].index;
      }
    }
  }

  return d;
}

int main()
{
  int n;

  cin >> n;

  point points[n];

  double a, b;

  for (int i = 0; i < n; i++)
  {
    scanf("%lf%lf", &a, &b);
    points[i] = makepoint(a, b, i);
  }

  sort(points, points + n, compareX);

  double d = closest(points, n);

  if (indexa > indexb)
    swap(indexa, indexb);
  printf("%lf\n", ans);

  return 0;
}