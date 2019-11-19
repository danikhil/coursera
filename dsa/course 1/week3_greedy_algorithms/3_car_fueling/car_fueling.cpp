#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::vector;

int compute_min_refills(int dist, int tank, vector<int> &stops)
{
    stops.push_back(dist);
    if (tank < stops[0])
        return -1;
    int n = 0, current = 0;
    for (int i = 0; i < stops.size(); i++)
    {
        if (stops[i] - current > tank)
        {
            if (current == stops[i - 1])
                return -1;
            else
            {
                current = stops[i - 1];
                i--;
            }
            n++;
        }
    }
    return n;
}

int main()
{
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
