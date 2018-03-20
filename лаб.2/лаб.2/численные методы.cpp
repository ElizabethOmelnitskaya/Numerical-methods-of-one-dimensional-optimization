#include <iostream>
#include <conio.h>
#include <functional>
#include <vector>
#include <iomanip>
#include <cmath>

#define tay 1.618

using namespace std;
/* Функции для теста программы */
double F1(double x){
	return  fabs(x) + fabs(x + 1) - 1;			// min	
}

double F3(double x){
	return 1 + x - 2.5*x*x + 0.25*x*x*x*x;		// max
}

//---------------------------------------------------------------------------
double ab(double i) { //это модуль
	if (i<0) return -i; 
	else return i;
}   

//---------------------------------------------------------------------------

/*метод золотого сечения*/
void Gold(double a, double b, double eps){
	cout << "\n\n\tGold method:\n";

	//double g, h, fu1, fu2, x;
	//int k(0);

	//for (int i = -1; i <= 1; i += 2)//Сначало ищем минимум, затем максимум
	//{
	//	
	//	g = a + (b - a)*(0.38);
	//	h = b - 0.38*(b - a);
	//	fu1 = i*F3(g);
	//	fu2 = i*F3(h);

	/*	do{
			++k;
			if (fu1 <= fu2)
			{
				b = h;
				h = g;
				fu2 = fu1;
				g = a + (b - a)*(0.38);  //Основная формула
				fu1 = i*F3(g);
			}
			else
			{
				a = g;
				g = h;
				fu1 = fu2;
				h = b - 0.38*(b - a);  //Основная формула
				fu2 = i*F3(h);
			}
			x = (fu1 + fu2) / 2;
			cout << "[ " << a << " ; " << b << " ]"
				<< "\nx = " << x << "\t\tF(x) = " << F3(x) << "\t\tIteration: " << k << endl; // вывод результатов
		} while (ab(a - b) > eps); //Условие выхода
		i == -1 ? cout << "Minimum " : cout << "Maximum ";
		cout << "Result " << x << " v tochke " << h << endl;
	}*/

	double x1, x2, _x; // Точки, делящие текущий отрезок в отношении золотого сечения
	int k(0);
	while (fabs(b - a) > eps) {
		k++;
		x1 = b - (b - a) / tay;
		x2 = a + (b - a) / tay;
		if (F3(x1) <= F3(x2)) // Условие для поиска максимума
			a = x1;
		else
			b = x2;
		_x = (a + b) / 2;
		cout << "[ " << a << ";" << b << " ]"
			<< "\nx = " << _x << "\t\tF(x) = " << F3(_x) << "\t\tIteration: " << k << endl; // вывод результатов
	} // Выполняем, пока не достигнем заданной точности
}

int F(int n)
{
	int f, f1(1), f2(1), m(0);
	while (m < n - 1)
	{
		f = f1 + f2;
		f1 = f2;
		f2 = f;
		++m;
	}
	return f1;
}

void Fib(double a, double b, double eps) {
	cout << "\n\n\tFibonacci method:\n";
	double x1, x2, _x, xf1, xf2;
	int k(0);
	int N(0);
	double fn1(1), fn2(1), fn, f = (b - a) / eps;
	while (fn1 < f) {
		fn = fn1 + fn2;
		fn1 = fn2;
		fn2 = fn;
		++N;
	}
	// расчитываем начальные точки деления
	x1 = a + (double)F(N - 2) / F(N) * (b - a) - (N & 1 ? -1 : 1) * eps / F(N);
	x2 = a + (double)F(N - 1) / F(N) * (b - a) + (N & 1 ? -1 : 1) * eps / F(N);
	//а также значения целевых функций в этих точках :
	xf1 = F3(x1);
	xf2 = F3(x2);

	while (fabs(b - a) > eps){
		++k; // увеличиваем шаг итерации на +1
		if (xf1 >= xf2) {
			a = x1;
			x1 = x2;
			xf1 = xf2;
			x2 = a + (double)F(N - k - 1) / F(N - k) * (b - a) + ((N - k) & 1 ? -1 : 1) * eps / F(N - k); // новая точка
			xf2 = F3(x2);
		}
		else {
			b = x2;
			x2 = x1;
			xf2 = xf1;
			x1 = a + (double)F(N - k - 2) / F(N - k) * (b - a) - ((N - k) & 1 ? -1 : 1) * eps / F(N - k); // новая точка
			xf1 = F3(x1);
		}

		_x = (a + b) / 2;
		cout << "[ " << a << ";" << b << " ]" 
			<< "\nx = " << _x << "\t\tF(x) = " << F3(_x) << "\t\tIteration: " << k << endl; // вывод результатов
	}

}

/*void main(){
	double a, b, eps; 
	cout << "Input a: "; cin >> a; // задаем начало интервала
	cout << "Input b: "; cin >> b; // конец интервала
	cout << "Input eps: "; cin >> eps; // погрешность

	//Gold(a, b, eps); // метод золотого сечения
	Fib(a, b, eps); // метод фибоначчи
	//Dichotomy(a, b, eps); // метод половинного деления

	system("PAUSE");
}*/

double Dichotomy(double a, double b, double eps, bool flag)
{
	double x1, x2, xm, c;
	int k(0);
	c = fabs(b - a);

	if (flag)
	{
		while (c > eps)
		{
			xm = (a + b) / 2;
			x1 = xm - eps / 2;
			x2 = xm + eps / 2;
			if (F3(x1) >= F3(x2))
				a = xm;
			else
				b = xm;
			c = fabs(b - a);
			k++;
			cout << "[ " << a << ";" << b << " ]"
				<< "\nx = " << xm << "\t\tF(x) = " << F3(xm) << "\t\tIteration: " << k << endl; // вывод результатов
		}
	}
	else{
		while (c > eps)
		{
			xm = (a + b) / 2;
			x1 = xm - eps / 2;
			x2 = xm + eps / 2;

			if (F3(x1) <= F3(x2))
				a = xm;
			else
				b = xm;
			c = fabs(b - a);
			k++;
			cout << "[ " << a << ";" << b << " ]"
				<< "\nx = " << xm << "\t\tF(x) = " << F3(xm) << "\t\tIteration: " << k << endl; // вывод результатов
		}
	}
	return (a + b) / 2;
}

int main(){
	double a, b, min, max, eps;
	cout << "Interval:\n";
	cin >> a;
	cin >> b;
	cin >> eps;
	min = Dichotomy(a, b, eps, true);
	max = Dichotomy(a, b, eps, false);
	cout << '\n' << " min = " << min << endl;
	cout << "x  = " << max << endl;

	system("pause");
	return 0;
}