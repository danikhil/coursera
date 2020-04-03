#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int r,b,g;

    Node() : r(-1),b(-1),g(-1) { }
    Node(int r, int b, int g): r(r), b(b), g(g) {}
    bool operator==(const Node &inp) {
        return (this->r==inp.r && this->b==inp.b && this->g==inp.g);
    }

    Node operator++() {
        if(this== new Node(1,0,0))
        {
            return Node(0,1,0);
        }
        else if(this== new Node(0,1,0))
        {
            return Node(0,0,1);
        }
        else if(this== new Node(0,0,1))
        {
            return Node(1,0,0);
        }
    }

    friend ostream &operator<< (ostream &out, const Node &inp)
    {
        if(inp == Node(1,0,0))
        out << 1 << ' ' << -2 << ' ' << -3 << ' ';
        else if(inp == Node(1,0,0))
        out << -1 << ' ' << 2 << ' ' << -3 << ' ';
        else if(inp == Node(1,0,0))
        out << -1 << ' ' << -2 << ' ' << 3 << ' ';
        return out;
    }
};

struct Edge {
    int from;
    int to;
};

class Graph {

    vector<vector<int> > adjlist;

    public:
    Graph(const vector<Edge> &edges, int numVertices)
    {
        adjlist.resize(numVertices);
        for(auto edge: edges)
        {
            adjlist[edge.from-1].push_back(edge.to-1);
            // adjlist[edge.to-1].push_back(edge.from-1);
        }
    }

    vector<Node> find_solution(int numVertices)
    {
        vector<bool> visited(numVertices, false);
        vector<Node> vertices(numVertices, Node());

        queue<int> q;
        for(int i=0;i<numVertices;i++)
        {
            if(visited[i])
            continue;
            visited[i]=true;
            q.push(i);
            vertices[i] = Node(1,0,0);

            while(!q.empty())
            {
                int u = q.front();
                q.pop();

                for(auto v:adjlist[u])
                {
                    //cout << v << '\n';
                    if(vertices[u].r==1&&vertices[v].r==-1)
                    {
                        vertices[v] = Node(0,1,0);
                    }
                    else if(vertices[u].b==1&&vertices[v].b==-1)
                    {
                        vertices[v] = Node(0,0,1);
                    }
                    else if(vertices[u].g==1&&vertices[v].g==-1)
                    {
                        vertices[v] = Node(1,0,0);
                    }
                    else if(vertices[u] == vertices[v])
                    {
                        vertices[v]++;
                    }
                    if(visited[v])
                    continue;
                    q.push(v);
                    visited[v]=true;
                }
            }
        }
        return vertices;
    }

};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;
    vector<Node> vertices;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    { }

    void printEquisatisfiableSatFormula() {
        
        Graph graph(edges, numVertices);
        vertices = graph.find_solution(numVertices);
        
        cout << numVertices << ' ' << 3 << '\n';

        for(int i=0;i<numVertices;i++)
        {
            cout << vertices[i] ;
            cout << 0 << '\n';
        } 
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
