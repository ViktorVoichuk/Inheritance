#include <iostream>
#include <math.h>

using namespace std;


#define M_PI 3.14159265358979323846
#define delimiter "\n--------------------------\n"

enum tFigures
{
	tSquare,
	tRectangle,
	tTriangle,
	tCircle
};

class geometric_figures
{
	static int counter;
protected:
	int value;

public:
	static const int get_counter()
	{
		return counter;
	}
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
		counter++;
	}
	geometric_figures(int value)
	{
		this->value = value;
		cout << "GFConstructor:\t" << this << endl;
		counter++;
	}
	virtual ~geometric_figures()
	{
		cout << "GFDestructor\t" << this << endl;
		counter--;
	}
	virtual double area()const = 0;
	virtual double perimeter()const = 0;
	virtual void print()const = 0;
};
int geometric_figures::counter = 0;

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
		this->b = b;
		this->c = c;
		cout << "TConstructor:\t" << this << endl;
	}
	~Triangle()override
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
		cout << (strchr(typeid(*this).name(), ' ') + 1) << " with the parties " << get_value() << " " << get_b() << " " << get_c() << endl;
		cout << "Perimeter " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << perimeter() << endl;
		cout << "Area " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << area() << endl;
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
	~Square()override
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
		cout << (strchr(typeid(*this).name(), ' ') + 1) << " with the parties " << get_value() << endl;
		cout << "Perimeter " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << perimeter() << endl;
		cout << "Area " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << area() << endl;
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
	~Rectangle()override
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
		cout << (strchr(typeid(*this).name(), ' ') + 1) << " with the parties " << get_value() << " end " << get_z() << endl;
		cout << "Perimeter " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << perimeter() << endl;
		cout << "Area " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << area() << endl;
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
	~Circle()override
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
		cout << "Radius " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << get_value() << endl;
		cout << "Perimeter " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << perimeter() << endl;
		cout << "Area " << (strchr(typeid(*this).name(), ' ') + 1) << " = " << area() << endl;
	}
};

geometric_figures** FiguresFactory(int a)
{
	geometric_figures** group = nullptr;
	group = new geometric_figures * [a];
	srand(time(NULL));
	const int size = 3;
	int* arr = new int[a];
	int arr2[size];
	for (int i = 0; i < a; i++)
	{
		arr[i] = rand() % sizeof(tFigures);
	}
	for (int i = 0; i < a; i++)
	{
		for (int i = 0; i < size; i++)
		{
			arr2[i] = (rand() % 10) + 1;
		}
		switch (arr[i])
		{
		case tSquare:
			group[i] = new Square(arr2[0]);
			break;
		case tRectangle:
			group[i] = new Rectangle(arr2[0], arr2[1]);
			break;
		case tTriangle:
			group[i] = new Triangle(arr2[0], arr2[0], arr2[0]);
			break;
		case tCircle:
			group[i] = new Circle(arr2[0]);
			break;
		default:
			break;
		}
	}

	delete[] arr;

	return group;
}
void clear(geometric_figures* group[])
{
	int a = geometric_figures::get_counter();
	for (int i = 0; i < a; i++)
	{
		delete group[i];
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	geometric_figures** group;
	group = FiguresFactory(7);

	for (int i = 0; i < geometric_figures::get_counter(); i++)
	{
		cout << delimiter << endl;
		cout << "Figure " << i + 1 << endl;
		group[i]->print();
	}

	clear(group);

	system("pause");

	return 0;
}