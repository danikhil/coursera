#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
#include <limits.h>
using namespace std;

const double EPS = 1e-6;
const int PRECISION = 20;

typedef vector<vector<double>> Matrix;
typedef vector<double> Column;
typedef vector<double> Row;

void print(Matrix &X, Column &Y) {

	cout << '\n';
    for(int i=0;i<X.size();i++)
    {
        for(int j=0;j<X[i].size();j++)
        {
            cout << X[i][j] << ' ';
        }
        cout << Y[i] << '\n';
    }
	cout << '\n';
}


void basic_to_non_basic(Matrix &X, Column &Y, int row1, int row2, double fac) {

    int num_var = X[0].size()-1;
    for(int i=0;i<num_var;i++)
    {
        X[row1][i]-=fac*X[row2][i];
    }
    Y[row1]-=fac*Y[row2];
}


void pivot(vector<int> &var, Matrix &X, Column &Y, int row, int col) {

	// cout << "index_row: " << row << '\n';
	// cout << "index_col: " << col << '\n';

    int num_var = X[0].size()-1;
    for(int i=0;i<num_var;i++)
    {
		if(X[row][i]!=0)
        var[i]=1;
    }
    var[col]=0;

    for(int i=0;i<X.size();i++)
    {
        if(i==row)
		{
			double temp = X[row][col];
			for(int j=0;j<X[0].size();j++)
			{
				X[row][j]/=temp;
			}
			Y[row]/=temp;
		}
		else
        basic_to_non_basic(X, Y, i, row, X[i][col]/X[row][col]);
    }
	//print(X,Y);
}

bool check_Y(const Column &Y)
{
	for(int i:Y)
	{
		if(i<0)
		return false;
	}
	return true;
}

Matrix slacked_X(Matrix &X, vector<double> &c) {

	
	int m = c.size();
	int n = X.size();
	Matrix new_X(n+1, Row(m+n+1, 0));
	for(int i=0;i<n+1;i++)
	{
		for(int j=0;j<m+n+1;j++)
		{
			if(i<n&&j<m)
			{
				new_X[i][j]=X[i][j];
			}
			// else if(i<n+m)
			// {
			// 	if(j==i+m)
			// 	new_X[i][j]=1;
			// 	else if(j==i-n)
			// 	new_X[i][j]=-1;
			// 	else
			// 	new_X[i][j]=0;
			// }
			else
			{
				if(j<m)
				new_X[i][j]=-1*c[j];
				else if(j==m+i)
				{
					new_X[i][j]=1;
				}
			}
			
		}
	}
	return new_X;
}

int select_column(const Matrix &X) {

	//cout << "me here ";
    for(int i=0;i<X.back().size();i++)
    {
        if(X.back()[i]<0)
        {
			//cout << i << '\n';
			return i;
		}
    }
	
	return -1;
}

int select_row(const Matrix &X, const Column &Y, int sel_col) {

    double mn = INT_MAX;
    int mn_row = -1;

    for(int i=0;i<Y.size()-1;i++)
    {

		double temp;
		if(X[i][sel_col]==0)
		temp=INT_MAX;
		else
		temp = Y[i]/X[i][sel_col]; 
        if(temp>0&&temp<mn)
        {
            mn = Y[i]/X[i][sel_col];
            mn_row = i;
        }
    }
    return mn_row;
}

void set_basic(Matrix &X, Column &Y, const vector<int> &var, Row &var_val) {

	for(int i=0;i<var.size();i++)
	{
		if(var[i])
		continue;
		for(int j=0;j<Y.size()-1;j++)
		{
			if(X[j][i]!=0)
			{
				//cout << "Yi: " << Y[i] << " Xji: " << X[j][i] << '\n'; 
				var_val[i]=Y[j]/X[j][i];
				//cout << "var_val: " << var_val[i] << '\n';
				X[j][i]=0;
				Y[j]=0;
			}
		}
	}
	Y.back()=0;
}

Matrix obtain_square_matrix(Matrix &X, const vector<int> &var) {
	Matrix new_X;
	int size=0;
	for(int i:var)
	{
		if(i==1)
		size++;
	}
	for(int i=0;i<size;i++)
	{
		Row xi;
		for(int j=0;j<var.size();j++)
		{
			if(var[j]==1)
			xi.push_back(X[i][j]);
		}
		new_X.push_back(xi);
	}
	return new_X; 
}

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

void initial_simplex(Matrix &X, Column &Y, vector<double> &c, vector<int> &var) {

	int m = c.size();
	int n = Y.size();
	var = vector<int> (m+n, 0);
	for(int i=0;i<m;i++)
	var[i]=1;
	X = slacked_X(X, c);
	Y.resize(X.size());
	if(!check_Y(Y))
	{
		for(int i=0;i<Y.size();i++)
		{
			if(Y[i]>=0)
			continue;
			for(int j=0;j<X[0].size();j++)
			{
				X[i][j]=-1*X[i][j];
			}
			Y[i]*=-1;
		}
	}
	//print(X,Y);
}

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    Matrix &X, 
    vector<double> &Y, 
    vector<double> &c) {
    // Write your code here
	vector<int> var;

    bool flag = true;
	initial_simplex(X,Y,c,var);
	int sel_col=select_column(X);
	while(sel_col!=-1) {

		//cout << sel_col << '\n';
		int sel_row=select_row(X,Y,sel_col);
		if(sel_row==-1)
	  	{
			return {1,vector<double>(m,0)};
	  	}
		pivot(var, X, Y, sel_row, sel_col);
		sel_col = select_column(X);
		//print(X,Y);
		//cout << sel_col << '\n';
	}
	Row var_val(var.size(), 0);
	set_basic(X,Y, var, var_val);
	for(int i:var)
	cout << i << ' ';
	cout << '\n';
	for(int i:var_val)
	cout << i << ' ';
	cout << '\n';
	print(X,Y);
	X = obtain_square_matrix(X, var);
	while(Y.size()>X.size())
	Y.pop_back();
	// print(X,Y);
	for(int i=0;i<Y.size();i++)
	{
		for(int j=0;j<X[0].size();j++)
		{
			//cout << X[i][j] << ' ';
			X[i][j]+=EPS;
		}
		//cout << Y[i] << '\n';
		Y[i]+=EPS;
	}
	gaussian_elemination(X,Y);
	find_solution(X,Y);
	
	for(int i=0,j=0;i<var.size();i++)
	{
		if(var[i]==1)
		var_val[i]=Y[j++];
		// cout << var_val[i] << ' ';
		if((int)(1000*var_val[i])<0)
		return {-1, Row(m,0)};
	}
    return {0, vector<double>(var_val.begin(), var_val.begin()+m)};
	// return {0, Row(m,0)};
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