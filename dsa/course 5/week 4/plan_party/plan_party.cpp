#include <bits/stdc++.h>
#include <sys/resource.h>

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int solve(const Graph &tree, int vertex, int parent, Sum &array) {

    if(array[vertex]!=-1)
    return array[vertex];
    int ans1=tree[vertex].weight;
    for(auto child: tree[vertex].children)
    {
        if(child==parent)
        continue;
        for(auto sub_child: tree[child].children)
        {
            if(sub_child!=vertex)
            ans1+=solve(tree,sub_child, child, array);
        }
    }
    int ans2=0;
    for(auto child:tree[vertex].children)
    {
        if(child!=parent)
        ans2+=solve(tree, child, vertex, array);
    }
    array[vertex]=std::max(ans1, ans2);
    return array[vertex];
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {

    size_t size = tree.size();
    Sum array(size,-1);
    if (size == 0)
        return 0;
    
    // You must decide what to return.
    return solve(tree, 0, -1, array);
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
