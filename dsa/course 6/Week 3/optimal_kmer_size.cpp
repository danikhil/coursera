#include <bits/stdc++.h>
using namespace std;

typedef unordered_map<string, forward_list<string> > Graph;

Graph build_graph(const vector<string> reads, size_t k)
{
    Graph graph;

    for(size_t i=0;i<reads.size();++i)
    {
        for(size_t j=1;j+k-1<=reads[i].size();++j)
        {
            string u = reads[i].substr(j-1, k-1);
            string v = reads[i].substr(j, k-1);
            graph[u].remove(v);
            graph[u].push_front(v);
        }
    }
    return graph;
}

bool cycle_exists(const Graph &graph)
{
    unordered_map<string, int> in, out;

    for(auto it=graph.begin();it!=graph.end();++it)
    {
        size_t count=0;
        for(auto tt = it->second.begin();tt!=it->second.end();++tt)
        {
            in[*tt]++;
            count++;
        }
        out[it->first]+=count;
    }

    for(auto it = in.begin(); it != in.end(); ++it)
        if(in[it->first] != out[(it->first)]) return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string> reads;
    string s;
    while(cin >> s)
    {
        reads.push_back(s);
    }
    size_t low_k = 2;
    size_t high_k = s.size()-1;

    size_t required_k;

    while(low_k<high_k)
    {
        int mid_k = (low_k+high_k)/2;
        Graph g_low, g_mid, g_high;
        g_low = build_graph(reads, low_k);
        g_mid = build_graph(reads, mid_k);
        g_high = build_graph(reads, high_k);
        bool low = cycle_exists(g_low),mid=cycle_exists(g_mid),high=cycle_exists(g_high);
        if(high)
        {
            required_k = high_k;
            break;
        }
        else if(mid)
        {
            if(high_k-mid_k==1)
            {
                required_k = mid_k;
                break;
            }
            low_k = mid_k;
        }
        else if(low)
        {
            if(mid_k-low_k==1)
            {
                required_k = low_k;
                break;
            }
            high_k = mid_k;
        }
    }
    cout << required_k << '\n';
    return 0;
}