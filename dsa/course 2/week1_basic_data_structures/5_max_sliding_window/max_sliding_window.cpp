#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <queue>
#include <list>

using std::cin;
using std::cout;
using std::list;
using std::max_element;
using std::string;
using std::vector;

class SlidingWindowMax
{
    list<int> queue;
    int maxE;

public:
    void Push(const vector<int> &v, int i, int w)
    {
        while (!queue.empty() && queue.front() < i - w + 1)
            queue.pop_front();
        while (!queue.empty() && v[queue.back()] < v[i])
        {
            queue.pop_back();
        }
        queue.push_back(i);
    }

    int Max(const vector<int> &v) const
    {
        return v[queue.front()];
    }
};

void max_sliding_window_naive(vector<int> const &A, int w)
{
    SlidingWindowMax queue;

    for (int i = 0; i < A.size(); i++)
    {
        queue.Push(A, i, w);
        if (i >= w - 1)
            std::cout << queue.Max(A) << ' ';
    }

    return;
}

int main()
{
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
