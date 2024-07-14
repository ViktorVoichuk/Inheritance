#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry
{
	enum Color	//enum (Enumeration) - это перечисление. Перечисление - это набор целочисленных констант
	{
		CONSOLE_BLUE = 0x99,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07,
		PICTURE_RED = RGB(255, 0, 0),
		PICTURE_GREEN = RGB(0, 255, 0),
		PICTURE_BLUE = RGB(0, 0, 255)
	};

	class Shape
	{
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Color get_color()const
		{
			return color;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;	//длина стороны
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		virtual ~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, get_color());
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
			cout << endl;
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, Color color) :Shape(color)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();	//1) Получаем десткриптор окна консоли.
											//description
											//HWND - Handler to Window (Обработчик (Дескриптор) окна)
			HDC hdc = GetDC(hwnd);			//2) Получаем констукст устройства (Device Context) окна консоли.
											//	 DC - это то, на чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());	//3) Создаем карандаш. pen рисует контур фигуры.
																//PS_SOLID - сплошная линия
																//5 - толщина линии в пикселах
			HBRUSH hBrush = CreateSolidBrush(get_color());

			//5) Выбираем чем и на чем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:
			::Rectangle(hdc, 500, 230, 700, 310);

			//7) Освбождаем ресурсы:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);

		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << get_width() << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};

	class Ellips :public Shape
	{
		double radius;
	public:
		Ellips(double radius, Color color) :Shape(color)
		{
			set_radius(radius);
		}
		~Ellips() {}
		double get_area()const override
		{
			return ((radius * radius) * 3.14);
		}
		double get_perimeter()const override
		{
			return (radius * 3.14) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			//Выбираем чем и на чем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//Рисуем овал:
			::Ellipse(hdc, 500, 340, 570, 410);

			//Освбождаем ресурсы:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			this->radius = radius;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << get_radius() << endl;
			Shape::info();
		}
	};
	class Triangle : public Shape  //Треугольик
	{
	private:
		double a;
		double b;
		double c;
	public:
		const double get_a()const
		{
			return a;
		}
		void set_a(double a)
		{
			this->a = a;
		}
		const double get_b()const
		{
			return b;
		}
		void set_b(double b)
		{
			this->b = b;
		}
		const double get_c()const
		{
			return c;
		}
		void set_c(double c)
		{
			this->c = c;
		}
		Triangle(double a, double b, double c, Color color) :Shape(color)
		{
			set_a(a);
			set_b(b);
			set_c(c);
		}
		virtual ~Triangle() {};
		double get_area()const override
		{
			return sqrt((a + b + c) / 2 * (((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) * ((a + b + c) / 2 - c)));
		}
		double get_perimeter()const override
		{
			return (a + b + c);
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//определяем массив точек которые образуют треугольник
			POINT point[] =
			{
				{point[0].x = 500,point[0].y = 530},
				{point[1].x = 550, point[1].y = 460},
				{point[2].x = 600, point[2].y = 530}
			};
			// Рисуем треугольник:
			Polygon(hdc, point, 3);
			// Освобождаем ресурсы:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона a: " << get_a() << endl;
			cout << "Сторона b: " << get_b() << endl;
			cout << "Сторона c: " << get_c() << endl;
			Shape::info();
		}
	};
}


void main()
{
	setlocale(LC_ALL, "");
	/*Shape shape(Color::CONSOLE_BLUE);*/
	Geometry::Square square(5, Geometry::Color::CONSOLE_GREEN);
	/*cout << "Длина стороны клвадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата:  " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect{ 15, 8, Geometry::Color::PICTURE_BLUE };
	rect.info();

	Geometry::Ellips circle{ 10,Geometry::Color::PICTURE_RED };
	circle.info();

	Geometry::Triangle triangle(20, 20, 20, Geometry::Color::PICTURE_GREEN);
	triangle.info();

	cout << endl << endl << endl << endl;
}