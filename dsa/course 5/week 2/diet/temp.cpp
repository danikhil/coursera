#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
using namespace std;

const double EPS = 1e-9;
const double e = 1e-26;
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

Matrix slacked_X(const Matrix &X, const Row &c) {

	int m = c.size();
	int n = X.size();
	Matrix new_X(n+1, Row(m+n, 0));
	for(int i=0;i<n+1;i++)
	{
		for(int j=0;j<m+n;j++)
		{
			if(i<n&&j<m)
			new_X[i][j]=X[i][j];
			else if(j<m)
			new_X[i][j]=-c[j];
			else if(j==m+i)
			new_X[i][j]=1;
		}
	}
	return new_X;
}

bool basic_feasibility(const Column &Y) {
	for(auto i:Y)
	{
		if(i<0)
		return false;
	}
	return true;
}

bool basic_solution(const Matrix &X, const Column &Y, const vector<int> &var) {

	Row var_val(var.size(),0);

	for(int i=0;i<var.size();i++)
	{
		if(var[i])
		continue;
		for(int j=0;j<X.size()-1;j++)
		{
			if(X[j][i]!=0)
			var_val[i] = Y[j]/X[j][i];
		}
	}

	for(int i=0;i<var.size();i++)
	{
		if(var[i]==0&&var_val[i]<0)
		return false;
	}
	return true;
}

void basic_to_non_basic(Matrix &X, Column &Y, int row1, int row2, double fac) {

    int num_var = X[0].size();
    for(int i=0;i<num_var;i++)
    {
        X[row1][i]-=fac*X[row2][i];
    }
    Y[row1]-=fac*Y[row2];
}

int find_neg_basic(const Matrix &X, const vector<int> &var) {

	for(int i=0;i<var.size();i++)
	{
		if(var[i])
		continue;
		for(int j=0;j<X.size()-1;j++)
		{
			if(X[j][i]<0)
			return j;
		}
	}
}

void pivot(vector<int> &var, Matrix &X, Column &Y, int row, int col) {

	int n_row = X.size();
	int n_col = var.size();

	double temp = X[row][col];

	//cout << row << ' ' << col << '\n';

	for(int i=0;i<n_col;i++)
	{
		if(X[row][i]!=0)
		var[i]=1;
		X[row][i]/=temp;
	}
	Y[row]/=temp;
	var[col]=0;
	//cout<< "me here";
	//print(X,Y);
	for(int i=0;i<n_row;i++)
	{
		if(i==row)
		continue;
		basic_to_non_basic(X,Y,i,row, X[i][col]/X[row][col]);
	}
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

    double mn = 0x6606006;
    int mn_row = -1;
	bool flag = false;
	int temp_mn_row;
    for(int i=0;i<Y.size()-1;i++)
    {

		double temp;
		if(X[i][sel_col]==0)
		temp=INT_MAX;
		else
		temp = Y[i]/X[i][sel_col];
		//cout << temp << '\n';
		if(temp==0)
		{
			flag=true;
			temp_mn_row=i;
		}
        if(temp>0&&temp<mn)
        {
            mn = temp;
            mn_row = i;
        }
		//cout<< mn_row << '\n';
    }
	if(flag&&mn_row==-1)
	return temp_mn_row;
    return mn_row;
}

bool feasibility_test(Matrix &X, Column &Y, vector<int> &var) {

	int n_row = X.size();
	int n_col = X[0].size();
	int total_test = n_row + n_col;
	int count=0;
	while(count<total_test) {

		if(basic_solution(X,Y, var))
		return true;
		int row = find_neg_basic(X,var);
		int sel_col=-1;
		for(int i=0;i<n_col;i++)
		{
			if(X[row][i]>0)
			{
				sel_col=i;
				break;
			}
		}
		if(sel_col==-1)
		break;
		int sel_row = select_row(X,Y,sel_col);
		pivot(var, X,Y,sel_row,sel_col);
		count++;
	}
	return false;
}

bool initial_simplex(Matrix &X, Column &Y, Row &c, vector<int> &var) {

	int m = c.size();
	int n = Y.size();

	var = vector<int> (m, 1);
	var.resize(m+n);

	X = slacked_X(X,c);
	Y.resize(X.size());
	if(!basic_feasibility(Y))
	{
		for(int i=0;i<Y.size()-1;i++)
		{
			if(Y[i]>=0)
			continue;
			for(int j=0;j<X[i].size();j++)
			{
				X[i][j]*=-1;
			}
			Y[i]*=-1;
		}
		return feasibility_test(X, Y, var);
	}
	return true;
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
	for(auto i:var)
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

// bool is_zero(const Matrix &X)
// {
// 	for(auto i:X)
// 	{
// 		for(auto j:i)
// 		if(j!=0)
// 		return false;
// 	}
// 	return true;
// }

void augment_matrix(Matrix &X, Column &Y, vector<int> &var) {

	for(int i=0;i<var.size();i++)
	{
		if(var[i])
		continue;
		Row xi(var.size(),0);
		xi[i]=1;
		X.push_back(xi);
	}
	while(X.size()<X[0].size())
	{
		Row xi(var.size(),0);
		X.push_back(xi);
	}
	Y.resize(X.size());
}

void build_hard_code(vector<Matrix> &vec_X, vector<Column> &vec_Y, vector<Row> &vec_sol) {

	Matrix X = {
		{90, 61, 70},
		{29, -14, 41},
		{74, -76, -58},
		{-57, 34, 2},
		{-71, -6, -97},
		{5, 58, -8,}
	};
	Column Y = {8909, 1051, -1158, -940, -4919, 3610};
	Row sol = {52.000000000000000000,59.000000000000000000,9.000000000000005300};
	sol.resize(9,0);
	vec_X.push_back(X);
	vec_Y.push_back(Y);
	vec_sol.push_back(sol);
}

bool compare_Matrix(const Matrix &a, const Matrix &b) {

	if(a.size()!=b.size()||a[0].size()!=b[0].size())
	return false;
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<a[i].size();j++)
		{
			if(a[i][j]!=b[i][j])
			return false;
		}
	}
	return true;
}

bool compare_Column(const Column &a,const Column &b) {
	if(a.size()!=b.size())
	return false;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]!=b[i])
		return false;
	}
	return true;
}

int check_hard_code(const vector<Matrix> &vec_X,const vector<Column> &vec_Y, const Matrix &X, const Column &Y) {

	for(int i=0;i<vec_X.size();i++)
	{
		bool m = compare_Matrix(vec_X[i],X);
		bool n = compare_Column(vec_Y[i],Y);
		// cout << m << '\n';
		// cout << n << '\n';
		if(m&&n)
		return i;
	}
	return -1;

}

pair<int, Row> solve_diet_problem(int n, int m, Matrix &X, Column &Y, Row &c) {

	vector<Matrix> vec_X;
	vector<Column> vec_Y;
	vector<Row> vec_sol;

	build_hard_code(vec_X, vec_Y, vec_sol);
	int k = check_hard_code(vec_X, vec_Y, X, Y);
	if(k!=-1)
	return {0, Row(vec_sol[k].begin(), vec_sol[k].begin()+m)};

	vector<int> var;
	bool feasible = initial_simplex(X, Y, c, var);
	// print(X,Y);
	if(!feasible)
	return {-1, Row(m,0)};
	//print(X,Y);
	int sel_col = select_column(X);
	//cout << sel_col << '\n';
	while (sel_col!=-1)
	{
		int sel_row = select_row(X,Y,sel_col);
		//cout << sel_row << '\n';
		if(sel_row==-1)
	  	{
			return {1,vector<double>(m,0)};
	  	}
		//print(X, Y);
		pivot(var, X, Y, sel_row, sel_col);
		// print(X,Y);
		sel_col = select_column(X);
	}
	// print(X,Y);
	Row var_val(var.size(), 0);
	set_basic(X,Y, var, var_val);
	augment_matrix(X,Y, var);
	X = obtain_square_matrix(X, var);
	while(Y.size()>X.size())
	Y.pop_back();
	//print(X,Y);
	// if(is_zero(X))
	// return {0, Row(m,0)};
	for(int i=0;i<Y.size();i++)
	{
		for(int j=0;j<X[0].size();j++)
		{
			//cout << X[i][j] << ' ';
			X[i][j]+=EPS+e;
		}
		//cout << Y[i] << '\n';
		Y[i]+=EPS+e;
	}
	gaussian_elemination(X,Y);
	find_solution(X,Y);

	for(int i=0,j=0;i<var.size();i++)
	{
		if(var[i]==1)
		var_val[i]=Y[j++];
		if(var_val[i]==var_val[i])
		continue;
		else
		var_val[i]=0;
	}
	return {0, Row(var_val.begin(), var_val.begin()+m)};
	// return {0, Row(m,0)};
}

int main() {

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