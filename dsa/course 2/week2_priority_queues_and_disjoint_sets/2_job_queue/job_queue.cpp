#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::cin;
using std::cout;
using std::pair;
using std::priority_queue;
using std::vector;

typedef pair<long long, int> pi;

class JobQueue
{
private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const
  {
    for (int i = 0; i < jobs_.size(); ++i)
    {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData()
  {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs()
  {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    priority_queue<pi, vector<pi>, std::greater<pi>> threads;
    //vector<int> thread_free(num_workers_, 0);
    for (int i = 0; i < num_workers_; i++)
      threads.push({0, i});
    for (int i = 0; i < jobs_.size(); i++)
    {
      pi thread = threads.top();
      threads.pop();
      assigned_workers_[i] = thread.second;
      start_times_[i] = thread.first;
      thread.first += jobs_[i];
      threads.push(thread);
    }
  }

public:
  void Solve()
  {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
