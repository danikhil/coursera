#include <math.h>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

#define fast std::ios_base::sync_with_stdio(false)

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

const double EPS = 1e-6;
const int PRECISION = 20;

void normalize_row(Matrix &X, double temp, int i, int j)
{
    for(int k=0;k<X.size();k++)
    {
        X[i][k]-=(temp)*(X[j][k]);
    }
}

void gaussian_elemination(Matrix &X, Column &Y)
{
    int n=X.size();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            Y[i]-=X[i][j]*Y[j];
            normalize_row(X, X[i][j], i, j);
        }
        double temp = X[i][i];
        Y[i]/=temp;
        for(int j=0;j<n;j++)
        {
            X[i][j]/=temp;
        }
    }
}

void find_solution(Matrix &X, Column &Y)
{
    int n=X.size();
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i+1;j<n;j++)
        {
            Y[i]-=(Y[j])*(X[i][j]);
        }
        Y[i]/=X[i][i];
    }
}

int main()
{
    fast;
    int n;
    cin >> n;
    Matrix X(n, vector<double> (n, 0.0));
    Column Y(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> X[i][j];
            X[i][j]+=EPS;
        }
        cin >> Y[i];
        Y[i]+=EPS;
    }
    gaussian_elemination(X, Y);
    // for(int i=0;i<n;i++)
    // {
    //     for(int j=0;j<n;j++)
    //     {
    //         cout << X[i][j] << ' ';
    //     }
    //     cout << Y[i] << '\n';
    // }
    find_solution(X,Y);
    cout.precision(PRECISION);
    for(int i=0;i<n;i++)
    cout << Y[i] << ' ';
    return 0;
}