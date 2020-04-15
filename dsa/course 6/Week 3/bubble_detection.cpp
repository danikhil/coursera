#include <bits/stdc++.h>
using namespace std;

typedef map<size_t, vector<size_t> > Graph;
typedef vector<vector<size_t> > Path;
typedef pair<size_t, size_t> Pair;

class BubbleDetection
{
    private:
    size_t k, threshold;
    map<string, size_t> string_hash;
    Graph graph;
    map<size_t, size_t> incoming_edge;
    map<Pair, Path> paths;

    public:
    explicit BubbleDetection(size_t k, size_t t): k(k), threshold(t) {}

    void build_graph(const vector<string> &reads)
    {
        size_t c=0;
        for (auto read: reads)
        {
            for(size_t j=1;j+k-1<=read.size();++j)
            {
                string u = read.substr(j-1,k-1);
                string v = read.substr(j, k-1);
                if(u==v)
                continue;
                if(string_hash.find(u)==string_hash.end())
                string_hash[u]=c++;
                if(string_hash.find(v)==string_hash.end())
                {
                    string_hash[v]=c++;
                }
                size_t left = string_hash[u];
                size_t right = string_hash[v];
                if(find(graph[left].begin(), graph[left].end(), right)==graph[left].end())
                {
                    graph[left].push_back(right);
                    incoming_edge[right]++;
                }
            }
        }
    }

    bool multiple_incoming(size_t vertex)
    {
        if(incoming_edge[vertex]>1)
        return true;
        return false;
    }

    bool multiple_outgoing(size_t vertex)
    {
        if(graph[vertex].size()>1)
        return true;
        return false;
    }

    void dfs(vector<size_t> &path, size_t curr, size_t start, size_t depth)
    {
        if(curr!=start && multiple_incoming(curr))
            paths[{start, curr}].push_back(path);
        
        if(depth==threshold)
        return ;

        for(auto next_vertex: graph[curr])
        {
            if(find(path.begin(), path.end(), next_vertex)==path.end())
            {
                path.push_back(next_vertex);
                dfs(path, next_vertex, start, depth+1);
                path.pop_back();
            }
        }
    }

    size_t count_bubbles()
    {
        for(auto it=graph.begin();it!=graph.end();++it)
        {
            size_t start = it->first;
            vector<size_t> p(1, start);
            if(multiple_outgoing(start))
            dfs(p, start, start, 0);
        }

        for(auto it=paths.begin();it!=paths.end();++it)
        {
            for(auto p:generate_combination(it->second.size(), 2))
            {
                if(is_disjoint(it->second[p[0]], it->second[p[1]]))
                bubbles++;
            }
        }

        return bubbles;
    }

    void makeCombiUtil(vector<vector<size_t> >& ans, vector<size_t>& tmp, size_t N, size_t left, size_t R) 
    {
        if (R == 0) { 
            ans.push_back(tmp); 
            return; 
        } 
        for (size_t i = left; i < N; ++i) 
        { 
            tmp.push_back(i); 
            makeCombiUtil(ans, tmp, N, i + 1, R - 1);
            tmp.pop_back(); 
        } 
    } 

    vector<vector<size_t>> generate_combination(size_t N, size_t R)
    {
        vector<vector<size_t> > ans; 
        vector<size_t> tmp; 
        makeCombiUtil(ans, tmp, N, 0, R); 
        return ans; 
    }

    bool is_disjoint(vector<size_t> &p1, vector<size_t> &p2)
    {
        vector<size_t> tmp(p1.size()+p2.size());
        sort(p1.begin(), p1.end());
        sort(p2.begin(),p2.end());
        return ((set_intersection(p1.begin(), p1.end(), p2.begin(),p2.end(), tmp.begin())-tmp.begin()) == 2);
    }

    size_t bubbles=0;
};

BubbleDetection read_input()
{
    size_t k,t;
    cin >> k >> t;

    vector<string> reads;
    string s;
    while(cin >> s)
    reads.push_back(s);

    BubbleDetection deBrujinGraph(k,t);
    deBrujinGraph.build_graph(reads);

    return deBrujinGraph;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    BubbleDetection deBrujinGraph = read_input();
    cout << deBrujinGraph.count_bubbles();

    return 0;
}