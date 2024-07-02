#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define delimiter "\n------------------------------------\n" //разделительная черта

// Для конструкторов класса Human и делигирующих конструкторов классов наследников
#define HUMAN_TAKE_PARAMETERS	const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age
class Human
{
	static const int HUMAN_TYPE_WIDTH = 10;		//Максимальная длинна имени класса
	static const int LAST_NAME_WIDTH = 15;		//Максимальная длинна фамилии
	static const int FIRS_NAME_WIDTH = 15;		//Максимальная длинна имени
	static const int AGE_WIDTH = 5;
	std::string last_name;						//Поле фамилии
	std::string first_name;						//Поле имени
	unsigned int age;							//Поле возраст

protected:
	void read_to_string(ifstream& ifs, string& str, const int& size);	//Чтение из потока в переменную стринг

public:
	const std::string& get_last_name()const		//Возврат Фамилии
	{
		return last_name;
	}
	const std::string& get_first_name()const	//Возврат Имени
	{
		return first_name;
	}
	const unsigned int get_age()const			//Возврат возраста
	{
		return age;
	}
	void set_last_name(const std::string& last_name)		//Заполнение Фамилии
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)		//Заполнение имени
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)							//Заполнение возраста
	{
		this->age = age;
	}

	//				Constructors:
	Human()									//Конструктор по умолчанию
	{

	}
	Human(HUMAN_TAKE_PARAMETERS)			//Конструктор с параметрами (записанными в define до класса)
	{
		set_last_name(last_name);			//Заполнение Фамилии
		set_first_name(first_name);			//Заполнение Имени
		set_age(age);						//Заполнение возраста
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()						//Виртуальный деструктор
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual void info()const				//Виртуальная константная функция вывода в консоль
	{
		cout << last_name << " " << first_name << " " << age << " y/o" << endl;
	}
	virtual std::ostream& info(std::ostream& os)const	//Виртуальная константная функция вывода в консоль через оператор >>
	{
		return os << last_name << " " << first_name << " " << age << " y/o";
	}
	virtual std::ofstream& info(std::ofstream& ofs)const	//Виртуальная константная функция записи в файл
	{
		//width() устанавливает длинну символов записи. left говорит что надо начинать запись с левого символа поля
		ofs.width(HUMAN_TYPE_WIDTH); ofs << left << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":";	//запись имени класса
		ofs.width(LAST_NAME_WIDTH);	ofs << left << last_name;	//запись Фамилии
		ofs.width(FIRS_NAME_WIDTH);	ofs << left << first_name;	//запись Имени
		ofs.width(AGE_WIDTH);		ofs << left << age;			//запись возраста
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)	//виртуальная функция считывания из файла
	{
		read_to_string(ifs, last_name, LAST_NAME_WIDTH);//Функция считывания фамилии в соответствующее поле
		read_to_string(ifs, first_name, FIRS_NAME_WIDTH);//Функция считывания имени в соответствующее поле
		ifs >> age;		//считывание из файла в поле возраст
		return ifs;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj) //Перегруженный оператор вывода в консоль
{
	return obj.info(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj) //перегруженный оператор вывода в файл
{
	return obj.info(ofs);
}
std::ifstream& operator>>(std::ifstream& is, Human& obj) //перегруженный оператор считывания из файла
{
	return obj.read(is);
}


// Для конструкторов класса Student и делигирующих конструкторов классов наследников
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
class Student :public Human
{
	static const int SPECIALITY_WIDTH = 25; //максимальная длинна поля специальность
	static const int GROUP_WIDTH = 8;		//максимальная длинна имени группы 
	static const int RATING_WIDTH = 8;		//максимальная длинна рейтинга
	static const int ATTENDANCE_WIDTH = 8;	//максимальная длинна посещаемости
	std::string speciality;					//поле специальность
	std::string group;						//поле группа
	double rating;							//поле рейтинг
	double attendance;						//поле посещаемость
public:
	const std::string& get_speciality()const	//возврат константной ссылки(работает со string) на поле специальности
	{
		return speciality;
	}
	const std::string& get_group()const			//возврат константной ссылки(работает со string) на поле группа
	{
		return group;
	}
	double get_rating()const					//константная функция возврата поля рейтинг
	{
		return rating;
	}
	double get_attendance()const				//константная функция возврата поля посещаемость
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)	//Заполнение специальности
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)			//заполнение группы
	{
		this->group = group;
	}
	void set_rating(double rating)						//заполнение рейтинга
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)				//заполнение посещаемости
	{
		this->attendance = attendance;
	}

	//				Constructors:
	Student() :Human()		//конструктор по умолчанию делигирующий конструктору класса Human
	{

	}
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS) //конструктор с параметрами
		//делигирующий конструктору класса Human. Параметры храняться в блоке define до класса
	{
		set_speciality(speciality);	//Заполнение специальности
		set_group(group);			//заполнение группы
		set_rating(rating);			//заполнение рейтинга
		set_attendance(attendance);	//заполнение посещаемости
		cout << "SConstructor:\t" << this << endl;
	}
	~Student() //переопределенный деструктор
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//				Methods:
	void info()const override //переопределенная константная функция вывода в консоль
	{
		Human::info(); //Вызов функции info находящейся в классе Human
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
	std::ostream& info(std::ostream& os)const override //переопределенная константная функция вывода в консоль через оператор >>
	{
		return Human::info(os) << " "
			<< speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& info(std::ofstream& ofs)const override //переопределенная константная функция записи в файл
	{
		//width() устанавливает длинну символов записи. left говорит что надо начинать запись с левого символа поля
		Human::info(ofs);// вызов соответствующей функции в классе Human
		ofs.width(SPECIALITY_WIDTH); ofs << speciality; //запись в файл специальности
		ofs.width(GROUP_WIDTH);		ofs << group;		//запись в файл группы
		ofs.width(RATING_WIDTH);	ofs << rating;		//запись в файл рейтинга
		ofs.width(ATTENDANCE_WIDTH); ofs << attendance;	//запись в файл посещаемости
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override //переопределенная функция считывания из файла
	{
		Human::read(ifs);	// вызов соответствующей функции в классе Human
		read_to_string(ifs, speciality, SPECIALITY_WIDTH);	//Функция считывания специальности в соответствующее поле
		read_to_string(ifs, group, GROUP_WIDTH);	//Функция считывания имени группы в соответствующее поле 
		ifs >> rating >> attendance; //считывание рейтинга и посещаемости в соответствующие поля
		return ifs;
	}
};

class Teacher : public Human
{
	static const int SPECIALITY_WIDTH = 25; //максимальная длинна поля специальность 
	static const int EXPERIENCE_WIDTH = 5;	//максимальная длинна опыта работы
	std::string speciality;					//поле специальность
	unsigned int experience;				//поле опыт работы
public:
	const std::string& get_speciality()const	//возврат константной ссылки(работает со string) на поле специальности
	{
		return speciality;
	}
	unsigned int get_experience()const			//константная функция возврата поля опыт работы
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)	//функция заполнения поля специальности
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)	//функция заполнения поля опыт работы
	{
		this->experience = experience;
	}

	//					Constructors:
	Teacher() :Human()	//конструктор по умолчанию делигирующий конструктору класса Human
	{

	}
	Teacher(HUMAN_TAKE_PARAMETERS, const std::string& speciality, unsigned int experience) :
		Human(HUMAN_GIVE_PARAMETERS)//конструктор с параметрами
		//делигирующий конструктору класса Human.
	{
		set_speciality(speciality); //заполнение поля специальность
		set_experience(experience);	//заполнение поля опыт работы
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()	//переопределенный деструктор
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//					Methods:
	void info()const	//переопределенная константная функция вывода в консоль
	{
		Human::info();	//Вызов функции info находящейся в классе Human
		cout << speciality << " " << experience << " years" << endl;
	}
	std::ostream& info(std::ostream& os)const	//переопределенная константная функция вывода в консоль через оператор >>
	{
		return Human::info(os) << " " << speciality << " " << experience << " years";
	}
	std::ofstream& info(std::ofstream& ofs)const override	//переопределенная константная функция записи в файл
	{
		//width() устанавливает длинну символов записи. left говорит что надо начинать запись с левого символа поля
		Human::info(ofs);	// вызов соответствующей функции в классе Human
		ofs.width(SPECIALITY_WIDTH); ofs << speciality; //запись в файл специальности
		ofs.width(EXPERIENCE_WIDTH); ofs << experience;	//запись в файл опыт работы
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override	//переопределенная функция считывания из файла
	{
		Human::read(ifs);	// вызов соответствующей функции в классе Human
		read_to_string(ifs, speciality, SPECIALITY_WIDTH);	//Функция считывания специальности в соответствующее поле
		ifs >> experience; //считывание из фаила опыта работы в соответствующее поле
		return ifs;
	}
};

class Graduate :public Student
{
	static const int SUBJECT_WIDTH = 32;	//максимальная длинна поля предмет
	std::string subject;					//поле предмет
public:
	const std::string& get_subject()const	//возврат константной ссылки(работает со string) на поле предмет
	{
		return subject;
	}
	void set_subject(const std::string& subject)	//функция заполнения поля предмет
	{
		this->subject = subject;
	}

	//				Constructors:
	Graduate() :Student() //конструктор по умолчанию делигирующий конструктору класса Student
	{

	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject) :
		Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS) //конструктор с параметрами
		//делигирующий конструктору класса Student. Параметры храняться в блоке define до класса
	{
		set_subject(subject); //заполнение поля предмет
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate() //переопределенный деструктор
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//				Methods:
	void info()const override	//переопределенная константная функция вывода в консоль
	{
		Student::info();	//Вызов функции info находящейся в классе Human
		cout << subject << endl;
	}
	std::ostream& info(std::ostream& os)const override //переопределенная константная функция вывода в консоль через оператор >>
	{
		return Student::info(os) << " " << subject;
	}
	std::ofstream& info(std::ofstream& ofs)const override	//переопределенная константная функция записи в файл
	{
		//width() устанавливает длинну символов записи. left говорит что надо начинать запись с левого символа поля
		Student::info(ofs);	// вызов соответствующей функции в классе Human
		ofs.width(SUBJECT_WIDTH); ofs << subject; //запись в файл предмета
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override	//переопределенная функция считывания из файла
	{
		Student::read(ifs);	// вызов соответствующей функции в классе Human
		read_to_string(ifs, subject, SUBJECT_WIDTH);	//Функция считывания предмета в соответствующее поле
		return ifs;
	}
};

void Print(Human* group[],const int n) //функция вывода группы на консоль
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++) //цикл до размера группы
	{
		//group[i]->info();
		cout << *group[i] << endl; //вывод объекта группы на консоль через перегруженный оператор<<
		cout << delimiter << endl;
	}
}
void Clear(Human* group[], const int n) //функция удаления объектов группы
{
	for (int i = 0; i <n; i++) //цикл до размара группы
	{
		delete group[i];	//удаление объекта в группе
	}
}
void Save(Human* group[], const int n, const std::string& filename) //функция сохранения объекта в группу
{
	std::ofstream fout(filename); //открытие (создание) файла с указанным именем
	for (int i = 0; i <n; i++)	// цикл до размера группы
	{
		fout << *group[i] << endl; //запись в файл объекта группы через перегруженный оператор <<
	}
	fout.close(); //закрытие файла
	std::string cmd = "notepad " + filename; //переменная с модификатором и именем файла
	system(cmd.c_str());	//выполнение в консольной строке команды на открытие файла
	//c_str() возвращает содержимое объекта std::string в виде обычно C-string (NULL Terminated line)
}
Human* HumanFactory(const std::string& type) //функция создания объекта новой группы при считывании из файла
{
	//сравнивает строку type с "тем что написано" создает объект соответствующего класса и возвращает ссылку на него
	Human* human = nullptr;
	if (type == "Human:")human = new Human("", "", 0);
	if (type == "Student:")human = new Student("", "", 0, "", "", 0, 0);
	if (type == "Teacher:")human = new Teacher("", "", 0, "", 0);
	if (type == "Graduate:")human = new Graduate("", "", 0, "", "", 0, 0, "");
	return human;
}
Human** Load(const std::string& filename,int& n) //функция загрузки из файла
{
	Human** group = nullptr;
	std::ifstream fin(filename); //открытие файла по указанному пути
	if (fin.is_open()) // проверка если файл открыт(Fin.is_open())
	{
		//1) Считаем количество объектов, оно точно соответсвует количеству непустых строк в файле:
		n = 0; //счетчик объектов
		while (!fin.eof()) // работает пока не конец файла (fin.eof() возвращает true когда файл закончился)
		{
			//const int SIZE = 256;
			//char buffer[SIZE]{};	//NULL-Terminated Line
			//fin.getline(buffer, SIZE);	//for NULL-Terminated Lines (C-Strings - char arrays)

			std::string buffer; //буферная переменная для считывания
			std::getline(fin, buffer);		//for std::string global function std::getline(stream, string) used.
			if (buffer.size() < 16)continue; //пропускает все цто ниже в цикле если размер buffer меньше 16
			n++; //увилечения счетчика объектов
		}
		cout << "Количество строк в файле " << n << endl;

		//2) Выделяем память под массив:
		group = new Human * [n] {};

		//3) Возвращаемся в начало файла:
		cout << fin.tellg() << endl; //fin.tellg() возвращает положение позиции считывания в файле, значением int
		fin.clear(); //очищает буфер считывания
		fin.seekg(0);//устанавливает положение позиции считывание в файле на 0 элемент(начало файла)
		cout << fin.tellg() << endl;

		//4) Выпоняем чтение объектов:
		for (int i = 0; i < n; i++) //цикл до количества объектов
		{
			std::string type; //переменная для хранения типа
			fin >> type; //считывание типа через перегруженный оператор >>
			group[i] = HumanFactory(type); //присвоение элементу группы нового объекта созданного в функции HumanFactory() 
			if (group[i])fin >> *group[i]; //если объект создан заполняем его через перегруженный оператор >>
			else continue;
		}
		fin.close(); //закрываем файл
	}
	else //если файл не удалось открыть выводим сообщение
	{
		std::cerr << "Error: File not found" << endl;
	}
	return group; //возвращаем ссылку на новую группу
}
void Human::read_to_string(ifstream& ifs, string& str, const int& size) //функция тения из потока в переменную string
//позволяет убрать лишние пробелы, считать в string фразу с пробелами и символами
{
	int a = ((int)ifs.tellg()) + size; // запоминаем текущее положение позиции считывания и добовляем к нему размер соответствующего поля
	string buuf; //буфер для корректного заполнения строки
	while (true)// условие выхода в самом цикле
	{
		while (ifs.peek() == ' ' && ifs.tellg() < a)// ifs.peek() смотрит какой символ мы считаем возвращает, но не считывает!!
		//сравниваем этот символс " " или выполняем проверку на крайнее положение считывания для данного поля
		{
			ifs.seekg(((int)ifs.tellg() + 1)); //если символ пустой сдвигаем позицию считывания на 1 символ вправо
		}
		//int b = ifs.tellg();
		if (ifs.tellg() >= a) //условие остановки цикла(если достигнут лимит символов считывания)
		{
			break;
		}
		getline(ifs, buuf, ' ');// считываем строку до пробела
		if (str != "") // если заполняемая строка не пуста ложим туда сначала пробел а потом считанное значение
		{
			str += ' ' + buuf;
		}
		else str += buuf;// если заполняемая строка пуста ложим туда значение
	}
}

//#define INHERITANCE_CHECK
//#define POLYMORPHISM

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_CHECK
	Human human("Vercetty", "Tommy", 30);
	human.info();

	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 70, 97);
	student.info();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.info();
#endif // INHERITANCE_CHECK

#ifdef POLYMORPHISM
	/*
Plymorphism (Poly - много, Morphis - форма)
--------------------
AdHoc Polymorphism - Статический полиморфизм.
--------------------
Inclusion Polymorphism
1. Base Class Pointer - Generalization;
2. virtual functions;
	VFPTR - Virtual Functions Pointers (Таблица указателей на виртуальные функции)
*/

//	Generalization:
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 70, 97),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "OBN", 80, 90, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 97, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	Print(group,sizeof(group)/sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
#endif // POLYMORPHISM

	int n = 0;
	Human** group2 = Load("group.txt", n);
	Print(group2, n);

#ifdef POLYMORPHISM
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // POLYMORPHISM

	Clear(group2, n);
}