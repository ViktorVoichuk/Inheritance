#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define delimiter "\n------------------------------------\n"

const char* clear(char arr[]);
#define HUMAN_TAKE_PARAMETERS	const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age

class Human
{
	static const int HUMAN_TYPE_WIDTH = 10;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRS_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	const unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//				Constructors:
	Human()
	{

	}
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
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
	virtual std::ofstream& info(std::ofstream& ofs)const
	{
		//ofs << strchr(typeid(*this).name(), ' ')+1 << ":\t" << last_name << " " << first_name << " " << age;
		ofs.width(HUMAN_TYPE_WIDTH); ofs << left << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":";
		ofs.width(LAST_NAME_WIDTH);	ofs << left << last_name;
		ofs.width(FIRS_NAME_WIDTH);	ofs << left << first_name;
		ofs.width(AGE_WIDTH);		ofs << left << age;
		return ofs;
	}
	virtual std::ifstream& info(std::ifstream& ifs)
	{

		ifs.width(LAST_NAME_WIDTH); ifs >> last_name >> right;
		ifs.width(FIRS_NAME_WIDTH); ifs >> first_name >> right;
		ifs.width(AGE_WIDTH);		ifs >> age;
		return ifs;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.info(ofs);
}
std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	return obj.info(ifs);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
class Student :public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
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
	std::ofstream& info(std::ofstream& ofs)const override
	{
		Human::info(ofs);
		ofs.width(SPECIALITY_WIDTH); ofs << speciality;
		ofs.width(GROUP_WIDTH);		ofs << group;
		ofs.width(RATING_WIDTH);	ofs << rating;
		ofs.width(ATTENDANCE_WIDTH); ofs << attendance;
		return ofs;
	}
	std::ifstream& info(std::ifstream& ifs) override
	{
		Human::info(ifs);
		ifs.width(SPECIALITY_WIDTH);	ifs >> speciality >> right;
		ifs.width(GROUP_WIDTH);			ifs >> group >> right;
		ifs.width(RATING_WIDTH);		ifs >> rating;
		ifs.width(ATTENDANCE_WIDTH);	ifs >> attendance;
		return ifs;
	}
};

class Teacher : public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	unsigned int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//					Constructors:
	Teacher() :Human()
	{

	}
	Teacher(HUMAN_TAKE_PARAMETERS, const std::string& speciality, unsigned int experience) :
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
	std::ofstream& info(std::ofstream& ofs)const override
	{
		Human::info(ofs);
		ofs.width(SPECIALITY_WIDTH); ofs << speciality;
		ofs.width(EXPERIENCE_WIDTH); ofs << experience;
		return ofs;
	}
	std::ifstream& info(std::ifstream& ifs) override
	{
		Human::info(ifs);
		char arr[SPECIALITY_WIDTH]{};
		//ifs.width(SPECIALITY_WIDTH);	ifs >> left; 
		ifs.get(arr, SPECIALITY_WIDTH);
		speciality = string(clear(arr));
		ifs.width(EXPERIENCE_WIDTH);	ifs >> experience;
		return ifs;
	}
};

class Graduate :public Student
{
	static const int SUBJECT_WIDTH = 32;
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}

	//				Constructors:
	Graduate() :Student()
	{

	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject) :
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
	std::ofstream& info(std::ofstream& ofs)const override
	{
		Student::info(ofs);
		ofs.width(SUBJECT_WIDTH); ofs << subject;
		return ofs;
	}
	std::ifstream& info(std::ifstream& ifs) override
	{
		Student::info(ifs);
		char arr[SUBJECT_WIDTH]{};
		//ifs.width(SUBJECT_WIDTH);	ifs >> left; 
		ifs.get(arr, SUBJECT_WIDTH);
		subject = string(clear(arr));
		return ifs;
	}

};

void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
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
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string cmd = "notepad " + filename;
	system(cmd.c_str());
	//c_str() возвращает содержимое объекта std::string в виде обычно C-string (NULL Terminated line)
}
void Load(Human* group[], const std::string& filename)
{
	std::ifstream fin(filename);
	string NAME;
	int i = 0;
	while (true)
	{
		NAME = "";
		fin.width(10); fin >> NAME;
		if (NAME == std::string(strchr(typeid(Student).name(), ' ') + 1) + ":")
		{
			group[i] = new Student;
		}
		else if (NAME == std::string(strchr(typeid(Teacher).name(), ' ') + 1) + ":")
		{
			group[i] = new Teacher;
		}
		else if (NAME == std::string(strchr(typeid(Graduate).name(), ' ') + 1) + ":")
		{
			group[i] = new Graduate;
		}
		else
		{
			break;
		}
		fin >> *group[i];
		i++;
	}
	fin.close();
}
const char* clear(char arr[])
{
	for (int i = 0; i < strlen(arr);)
	{
		if (arr[i] == ' ')
		{
			for (int j = 0; j < strlen(arr); j++)
			{
				arr[j] = arr[j + 1];
			}
		}
		else
		{
			break;
		}
	}

	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < strlen(arr); i++)
		{
			if ((arr[i] == ' ' && arr[i + 1] == ' ') || (arr[i] == ' ' && arr[i + 1] == '\0'))
			{
				for (int j = i; j < strlen(arr); j++)
				{
					arr[j] = arr[j + 1];
					flag = true;
				}
				i--;
			}

		}
	}
	return arr;
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
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 97, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Human* group2[5];
	Load(group2, "group.txt");
	Print(group2, sizeof(group) / sizeof(group[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));
}