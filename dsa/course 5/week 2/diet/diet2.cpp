#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const double EPS = 1e-8;
const int PRECISION = 20;

typedef vector<vector<double>> Matrix;
typedef vector<double> Column;

struct Equation {
    Matrix X;
    Column Y;
    int n;
    int m;
    vector<int> variable;

    Equation(Matrix &A, int n, int m, vector<double> &c, Column &b): n{n}, m{m} {
        slacked_matrix(A, c);
        update_column(b);
        variable = vector<int> (n+m);

        for(int i=0;i<n+m;i++)
        {
            if(i<m)
            variable[i]=1;
            else
            variable[i]=0;
        }
    }

    void update_column(Column &b) {

        Y = Column(n+1, 0);

        for(int i=0;i<n;i++)
        Y[i]=b[i];
    }

    void slacked_matrix(Matrix &A, vector<double> &c) {

        X = Matrix(n+1, vector<double>(n+m+1));

        for(int i=0;i<n+1;i++) {
            for(int j=0;j<m+n+1;j++)
            {
                if(i<n&&j<m)
                {
                    X[i][j]=A[i][j];
                }
                else if(i==n)
                {
                    if(j<m)
                    X[i][j]=-c[j];
                    else if(j<m+n)
                    X[i][j]=0;
                    else
                    {
                        X[i][j]=1;
                    }
                }
                else
                {
                    if(j==m+i)
                    X[i][j]=1;
                    else
                    {
                        X[i][j]=0;
                    }
                }
            }
        }
    }

    void print() {

        for(int i=0;i<X.size();i++)
        {
            for(int j=0;j<X[i].size();j++)
            {
                cout << X[i][j] << ' ';
            }
            cout << Y[i] << '\n';
        }
    }

    int select_column() {

        for(int i=0;i<m+n;i++)
        {
            if(X[X.size()-1][i]<0)
            return i;
        }
        return -1;
    }

    int select_row(int sel_col) {

        double mn = DBL_MAX;
        int mn_row = -1;

        for(int i=0;i<n;i++)
        {
            if(Y[i]&&X[i][sel_col]&&Y[i]/X[i][sel_col]<mn)
            {
                mn = Y[i]/X[i][sel_col];
                mn_row = i;
            }
        }
        return mn_row;
    }
};

bool is_feasible(Equation e) {


}

pair<int, vector<double>> solve_diet_problem(int n,int m,Matrix &A, vector<double> &b, vector<double> &c) {

  // Write your code here

  Equation e(A, n, m, c, b);

  while(true)
  {
	  if(e.select_column()==-1)
	  {
		  
	  }
	  else if(e.select_row==-1)
	  {
		  return {1,vector<double>(m,0)};
	  }
	  
  }


  
}

int main(){
  int n, m;
  cin >> n >> m;
  Matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1:
      printf("No solution\n");
      break;
    case 0:
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;
  }
  return 0;
}
