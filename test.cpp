#include <bits/stdc++.h>
using namespace std;

double fun(double x)
{
	return (sin(100*x)/(1+40*x*x) - cos(200*x)/(1+80*x*x)+(sin(400*x)+cos(800*x))/(2+91*x*x)+8*x/(1+100*x)+1/(1+exp(-x)));
}

int main()
{
	ofstream cout("output.txt");
	double h = 2.0/20.0;
	double a = -1.0;
	for(int i=0; i<=20; i++) {
		double x = a + (double) i*h;
		cout << x << ' ' << fun(x)<< endl;
	}
	return 0;
}
