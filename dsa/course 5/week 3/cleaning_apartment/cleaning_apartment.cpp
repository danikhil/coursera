#include <bits/stdc++.h>
using namespace std;

struct ConvertHampathToSat {
    int numVertices;
    int C,V;
    vector<vector<bool>> matrix;
    vector<vector<int>> var;
    string ans;

    ConvertHampathToSat(int n, int m) : C(0),
        numVertices(n), matrix(n, vector<bool>(n)), var(n, vector<int>(n))
    {
        for (int i = 0, c = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                var[i][j] = ++c;
            }
        }
    }

    void each_node_appear() {

        for(int i=0;i<numVertices;i++,C++)
        {
            for(int j=0;j<numVertices;j++)
            {
                ans += to_string(var[i][j]) + " ";
            }
            ans+= "0\n";
        }
    }

    void not_appear_twice() {

        for(int i=0;i<numVertices;i++)
        {
            for(int j=0;j<numVertices;j++)
            {
                for(int k=i+1;k<numVertices;k++,C++)
                {
                    ans+= to_string(-var[i][j]) + " " + to_string(-var[k][j]) + " 0\n";
                }
            }
        }
    }

    void every_position_occupied() {

        for(int i=0;i<numVertices;i++,C++)
        {
            for(int j=0;j<numVertices;j++)
            {
                ans+= to_string(var[j][i]) + " ";
            }
            ans+="0\n";
        }
    }

    void not_occupy_same() {

        for(int i=0;i<numVertices;i++)
        {
            for(int j=0;j<numVertices;j++)
            {
                for(int k=j+1;k<numVertices;k++,C++)
                {
                    ans+= to_string(-var[i][j]) + " " + to_string(-var[i][k]) + " 0\n";
                }
            }
        }
    }

    void nonAdjacent_not_adjacent() {

        for(int i=0;i<numVertices;i++)
        {
            for(int j=0;j<numVertices;j++)
            {
                if (matrix[i][j] || j == i)
                continue;
                for(int k=0;k<numVertices-1;k++, C++)
                {
                    ans+= to_string(-var[i][k]) + " " + to_string(-var[j][k+1]) + " 0\n";
                }
            }
        }

    }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.

        V = numVertices*numVertices;

        each_node_appear();
        not_appear_twice();
        every_position_occupied();
        not_occupy_same();
        nonAdjacent_not_adjacent();

        printf("%d %d\n%s", C, V, ans.c_str());
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        int p,q;
        cin >> p>> q;
        converter.matrix[p-1][q-1]=converter.matrix[q-1][p-1]=true;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
