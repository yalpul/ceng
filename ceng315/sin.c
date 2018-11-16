#include <stdio.h>
#define ERROR 0.000001
#define PI 3.1415926535897

double power(double base, int exp){
    double result = 1;
    while(exp--){
        result *= base;
    }
    return result;
}

double factorial(int n){
    double result = n;
    while(--n > 0){
        result *= n;
    }
    return result;
}

double absolute(double d){
    return d<0 ? -1*d : d;
}

double sine_r(double x, double old, int curr, int iter_lim)
{
	double num=0, diff;
	num = old + power(-1, curr-1) /factorial(2*(curr-1)+1) * power(x, 2*(curr-1)+1);
	diff = num - old;
	if (absolute(diff) <=ERROR)
		return num;
	printf("sin(%f) = %f at recursive call %d\n", x, num, curr);


	if ( curr == iter_lim)
		return num;

	return sine_r(x, num, curr+1, iter_lim);
}

double sine(double x, int iter)
{
	printf("sin(%f) = %f at recursive call %d\n", x, x, 1);
	return sine_r(x, x, 2, iter);
}

double sine_r(double x, double old, int curr, int iter_lim)
{
	double minus1 = power(-1, curr);
	double fact = factorial(2*curr+1);
	double xx = power(x, 2*curr+1);
	double num = old + minus1 * xx / fact;
	double diff = num - old;
	if (absolute(diff) <= ERROR || curr+1 == iter_lim)
		return num;
	printf("sin(%f) = %f at recursive call %d\n", x, num, curr+1);
	return sine_r(x, num, curr+1, iter_lim);
}

double sine(double x, int iter)
{
	return sine_r(x, 0, 0, iter);
}

int main()
{
	sine(PI/6, 10);
	return 0;
}
