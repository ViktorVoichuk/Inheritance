#include <iostream>
#include <math.h>

using namespace std;


#define M_PI 3.14159265358979323846
#define delimiter "\n--------------------------\n"


class geometric_figures
{

protected:
	int value;

public:
	const int get_value()const
	{
		return value;
	}
	void set_value(int value)
	{
		this->value = value;
	}
	geometric_figures()
	{
		this->value = 2;
	}
	geometric_figures(int value)
	{
		this->value = value;
		cout << "GFConstructor:\t" << this << endl;
	}
	virtual ~geometric_figures()
	{
		cout << "GFDestructor\t" << this << endl;
	}
	virtual double area()const = 0;
	virtual double perimeter()const = 0;
	virtual void print()const = 0;
};

class Triangle : public geometric_figures //треугольник
{
	int b;
	int c;
public:
	const int get_b()const
	{
		return b;
	}
	const int get_c()const
	{
		return c;
	}
	int set_b(int b)
	{
		this->b = b;
	}
	int set_c(int c)
	{
		this->c = c;
	}
	Triangle() :geometric_figures()
	{
		b = 2;
		c = 2;
		cout << "TConstructor:\t" << this << endl;
	}
	Triangle(int value, int b, int c) :geometric_figures(value)
	{
		this->b = 2;
		this->c = 2;
		cout << "TConstructor:\t" << this << endl;
	}
	~Triangle()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	double perimeter()const override
	{
		double P = value + b + c;
		return P;
	}
	double area()const override
	{
		double PP = perimeter() / 2;
		double S = sqrt(PP * ((PP - value) * (PP - b) * (PP - c)));
		return S;
	}

	void print()const override
	{
		cout << "Perimeter" << string(strchr(typeid(*this).name(), ' ')) << " = " << perimeter() << endl;
		cout << "Area" << string(strchr(typeid(*this).name(), ' ')) << " = " << area() << endl;
	}
};

class Square : public geometric_figures //квадрат
{

public:
	Square() :geometric_figures()
	{
		cout << "SConstructor:\t" << this << endl;
	}
	Square(int value) :geometric_figures(value)
	{
		cout << "SConstructor:\t" << this << endl;
	}
	~Square()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	double perimeter()const override
	{
		double P = 2 * (value + value);
		return P;
	}
	double area()const override
	{
		double S = (value * value);
		return S;
	}
	void print()const override
	{
		cout << "Perimeter" << string(strchr(typeid(*this).name(), ' ')) << " = " << perimeter() << endl;
		cout << "Area" << string(strchr(typeid(*this).name(), ' ')) << " = " << area() << endl;
	}
};

class Rectangle : public geometric_figures //прямоугольник
{
	int z;
public:
	const int get_z()const
	{
		return z;
	}
	int set_z(int z)
	{
		this->z = z;
	}
	Rectangle() :geometric_figures()
	{
		this->z = 2;
		cout << "RConstructor:\t" << this << endl;
	}
	Rectangle(int value, int z) :geometric_figures(value)
	{
		this->z = z;
		cout << "RConstructor:\t" << this << endl;
	}
	~Rectangle()
	{
		cout << "RDestructor:\t" << this << endl;
	}
	double perimeter()const override
	{
		double P = 2 * (value + z);
		return P;
	}
	double area()const override
	{
		double S = (value * z);
		return S;
	}
	void print()const override
	{
		cout << "Perimeter" << string(strchr(typeid(*this).name(), ' ')) << " = " << perimeter() << endl;
		cout << "Area" << string(strchr(typeid(*this).name(), ' ')) << " = " << area() << endl;
	}
};

class Circle : public geometric_figures //круг
{

public:

	Circle() :geometric_figures()
	{
		cout << "CConstructor:\t" << this << endl;
	}
	Circle(int value) :geometric_figures(value)
	{
		cout << "CConstructor:\t" << this << endl;
	}
	~Circle()
	{
		cout << "CDestructor:\t" << this << endl;
	}
	double perimeter()const override
	{
		double C = 2 * (M_PI * value);
		return C;
	}
	double area()const override
	{
		double S = M_PI * (value * value);
		return S;
	}
	void print()const override
	{
		cout << "Perimeter" << string(strchr(typeid(*this).name(), ' ')) << " = " << perimeter() << endl;
		cout << "Area" << string(strchr(typeid(*this).name(), ' ')) << " = " << area() << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");

	Square sq(4);
	sq.print();
	cout << delimiter << endl;

	Rectangle rec(2, 3);
	rec.print();
	cout << delimiter << endl;

	Circle cir(4);
	cir.print();
	cout << delimiter << endl;

	Triangle tr(3, 4, 5);
	tr.print();
	cout << delimiter << endl;

	system("pause");

	return 0;
}