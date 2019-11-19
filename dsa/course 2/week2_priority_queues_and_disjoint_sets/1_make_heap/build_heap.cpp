#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder
{
private:
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  void WriteResponse() const
  {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i)
    {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData()
  {
    int n;
    cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void heapify(int i)
  {
    int min = i;
    if (2 * i + 1 < data_.size() && data_[min] > data_[2 * i + 1])
      min = 2 * i + 1;
    if (2 * i + 2 < data_.size() && data_[min] > data_[2 * i + 2])
      min = 2 * i + 2;
    if (min != i)
    {
      swap(data_[min], data_[i]);
      swaps_.push_back({min, i});
      heapify(min);
    }
  }

  void GenerateSwaps()
  {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    int k = (data_.size()) / 2;
    k -= 1;

    for (int i = k; i >= 0; i--)
    {
      heapify(i);
    }
  }

public:
  void Solve()
  {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
