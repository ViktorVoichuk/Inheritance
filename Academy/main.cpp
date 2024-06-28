#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define delimiter "\n------------------------------------\n"

enum Human_type { tTeacher, tStudent, tGraduate };
#define HUMAN_TAKE_PARAMETERS	const char last_name[], const char first_name[], unsigned int age
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age

class Human
{
	char last_name[100]{};
	char first_name[100]{};
	unsigned int age;
	static int counter;

public:
	const char get_last_name()const
	{
		return *last_name;
	}
	const char get_first_name()const
	{
		return *first_name;
	}
	const unsigned int get_age()const
	{
		return age;
	}
	static int get_counter()
	{
		return counter;
	}
	static void set_counter(int a)
	{
		counter = a;
	}
	void set_last_name(const char last_name[])
	{
		memcpy(this->last_name, last_name, strlen(last_name));
	}
	void set_first_name(const char first_name[])
	{
		memcpy(this->first_name, first_name, strlen(first_name));
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//				Constructors:
	Human()
	{

		counter++;
	}
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
		counter++;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << " y/o" << endl;
	}
	virtual std::ostream& info(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age << " y/o";
	}
	virtual Human_type get_tipe();
};
int Human::counter;

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}

#define STUDENT_TAKE_PARAMETERS const char speciality[], const char group[], double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
class Student :public Human
{
	char speciality[100]{};
	char group[100]{};
	double rating;
	double attendance;
public:
	const char get_speciality()const
	{
		return *speciality;
	}
	const char get_group()const
	{
		return *group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const char speciality[])
	{
		memcpy(this->speciality, speciality, strlen(speciality));
	}
	void set_group(const char group[])
	{
		memcpy(this->group, group, strlen(group));
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//				Constructors:
	Student() :Human()
	{

	}
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//				Methods:
	void info()const override //переопределить
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
	std::ostream& info(std::ostream& os)const override //переопределить
	{
		return Human::info(os) << " "
			<< speciality << " " << group << " " << rating << " " << attendance;
	}

};

class Teacher : public Human
{
	char speciality[100]{};
	unsigned int experience;
public:
	const char get_speciality()const
	{
		return *speciality;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const char speciality[])
	{
		memcpy(this->speciality, speciality, strlen(speciality));
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//					Constructors:
	Teacher() :Human()
	{

	}
	Teacher(HUMAN_TAKE_PARAMETERS, const char speciality[], unsigned int experience) :
		Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//					Methods:
	void info()const
	{
		Human::info();
		cout << speciality << " " << experience << " years" << endl;
	}
	std::ostream& info(std::ostream& os)const
	{
		return Human::info(os) << " " << speciality << " " << experience << " years";
	}

};

class Graduate :public Student
{
	char subject[100]{};
public:
	const char& get_subject()const
	{
		return *subject;
	}
	void set_subject(const char subject[])
	{
		memcpy(this->subject, subject, strlen(subject));
	}

	//				Constructors:
	Graduate() :Student()
	{

	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const char subject[]) :
		Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//				Methods:
	void info()const override
	{
		Student::info();
		cout << subject << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		return Student::info(os) << " " << subject;
	}

};

Human_type Human::get_tipe()
{
	if (typeid(*this) == typeid(Teacher)) return tTeacher;
	else if (typeid(*this) == typeid(Student)) return tStudent;
	else if (typeid(*this) == typeid(Graduate)) return tGraduate;
}

void Print(Human* group[])
{
	cout << delimiter << endl;
	for (int i = 0; i < Human::get_counter(); i++)
	{
		group[i]->info();
		//cout << *group[i] << endl;
		cout << delimiter << endl;
	}
}
void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}
void Save(Human* group[], const int n, const std::string& filename)
{
	int size;
	ofstream fout;
	Human_type human;

	fout.open(filename, ios::binary);
	if (!fout)
	{
		cout << "\nError opening file!\n";
	}
	for (int j = 0; j < n; j++)
	{
		human = group[j]->get_tipe();
		fout.write((char*)&human, sizeof(human));
		switch (human)
		{
		case tTeacher:size = sizeof(Teacher); break;
		case tStudent:size = sizeof(Student); break;
		case tGraduate:size = sizeof(Graduate); break;
		default:
			break;
		}
		//fout.write((char*)(group[j]), size);
		fout.write((char*)(group[j]) + sizeof(void*), size - sizeof(void*));
	}
	fout.close();
}
void Load(Human* group[], const std::string& filename)
{
	int size;
	std::ifstream fin;
	Human_type human;

	fin.open(filename, ios::binary);
	if (!fin)
	{
		cout << "\nError opening file!\n"; return;
	}
	Human::set_counter(0);
	int n = 0;
	while (true)
	{
		fin.read((char*)&human, sizeof(human));
		if (fin.eof())
			break;

		switch (human)
		{
		case tStudent:
			group[n] = new Student;
			size = sizeof(Student);
			break;
		case tGraduate:
			group[n] = new Graduate;
			size = sizeof(Graduate);
			break;
		case tTeacher:
			group[n] = new Teacher;
			size = sizeof(Teacher);
			break;
		default: return;
		}

		//fin.read((char*)group[n], size);
		fin.read((char*)(group[n]) + sizeof(void*), size - sizeof(void*));
		n++;
	}
	Human::set_counter(n);
	fin.close();
	cout << "Read from file " << n << " people\n";
}

//#define INHERITANCE_CHECK

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
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 97, 98)
	};



	Print(group);
	cout << delimiter;

	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Human* group2[10];
	Load(group2, "group.txt");

	Print(group2);
	Clear(group, sizeof(group) / sizeof(group[0]));
	Clear(group2, Human::get_counter());
}