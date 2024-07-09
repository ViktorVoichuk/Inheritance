#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry
{
	enum Color	//enum (Enumeration) - ��� ������������. ������������ - ��� ����� ������������� ��������
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
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������:" << get_perimeter() << endl << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;	//����� �������
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
			cout << "����� �������: " << side << endl;
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
			HWND hwnd = GetConsoleWindow();	//1) �������� ����������� ���� �������.
											//description
											//HWND - Handler to Window (���������� (����������) ����)
			HDC hdc = GetDC(hwnd);			//2) �������� ��������� ���������� (Device Context) ���� �������.
											//	 DC - ��� ��, �� ��� �� ����� ��������
			HPEN hPen = CreatePen(PS_SOLID, 5, get_color());	//3) ������� ��������. pen ������ ������ ������.
																//PS_SOLID - �������� �����
																//5 - ������� ����� � ��������
			HBRUSH hBrush = CreateSolidBrush(get_color());

			//5) �������� ��� � �� ��� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) ������ �������������:
			::Rectangle(hdc, 500, 230, 700, 310);

			//7) ���������� �������:
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
			cout << "������: " << get_width() << endl;
			cout << "������: " << get_height() << endl;
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

			//�������� ��� � �� ��� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//������ ����:
			::Ellipse(hdc, 500, 340, 570, 410);

			//���������� �������:
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
			cout << "������: " << get_radius() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	/*Shape shape(Color::CONSOLE_BLUE);*/
	Geometry::Square square(5, Geometry::Color::CONSOLE_GREEN);
	/*cout << "����� ������� ���������: " << square.get_side() << endl;
	cout << "������� ��������:  " << square.get_area() << endl;
	cout << "�������� ��������: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect{ 15, 8, Geometry::Color::PICTURE_BLUE };
	rect.info();

	Geometry::Ellips circle{ 10,Geometry::Color::PICTURE_RED };
	circle.info();

	cout << endl << endl << endl << endl;
}