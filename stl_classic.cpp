#include <vector>     // std::vector
#include <list>       // std::list
#include <algorithm>  // std::sort, std::transform, std::find и др.
#include <numeric>    // std::accumulate
#include <functional> // std::binary_function, std::unary_function
#include "student.h"

using namespace std;


class AverageSorter : public binary_function<Student, Student, bool>
{
public:
	bool operator () (const Student& i, const Student& j) const
	{
		return i.Average > j.Average;
	}
};

class SurnameSorter : public binary_function<Student, Student, bool>
{
public:
	bool operator () (const Student& i, const Student& j) const
	{
		return i.Surname < j.Surname;
	}
};

class GetDescription : public unary_function<Student, std::string>
{
public:
	std::string operator () (const Student& i) const
	{
		return i.Name + "_" + i.Surname;;
	}
};

class SumAverage : public binary_function<float, Student, float>
{
	float k_;

public:

	SumAverage(float k = 1.0) : k_(k)
	{
	}

	float operator () (float i, const Student& j) const
	{
		return i + j.Average * k_;
	}
};

class FindAverageLessThan : public unary_function<Student, bool>
{
	float average_threshold_;

public:

	FindAverageLessThan(float average_threshold) : 
		average_threshold_(average_threshold)
	{
	}

	float operator () (const Student& j) const
	{
		return j.Average < average_threshold_;
	}
};
		

void testSTL_CppClassic()
{
	vector<Student> group_sm7_17;

	Student x = {"Petr", "Ivanov", 3.0};
	Student y = {"Ivan", "Petrov", 4.0};
	Student z = {"Semen", "Sidorov", 5.0};

    //-- Добавляем студентов в конец коллекции
	group_sm7_17.push_back(x);
	group_sm7_17.push_back(y);
	group_sm7_17.push_back(z);
	
	//-- Добавляем студента во вторую позицию
	// метод insert принимает итератор, указывающий на позицию вставки
	// и значение элемента
    group_sm7_17.insert(begin(group_sm7_17) + 1, {"Anna", "Fedorova", 5.0});	

    //-- Выводим на экран
	cout << "Students:" << std::endl;
	vector<Student>::iterator it;
	for(it = group_sm7_17.begin(); it != group_sm7_17.end(); ++it)
	{
		cout << *it;
	}

    //-- Сортируем студентов по убыванию баллов
	sort(group_sm7_17.begin(), group_sm7_17.end(), AverageSorter());

	cout << "Students sorted by average:" << std::endl;
	for(it = group_sm7_17.begin(); it != group_sm7_17.end(); ++it)
	{
		cout << *it;
	}

    //-- Сортируем студентов по фамилии в алфавитном порядке
	sort(group_sm7_17.begin(), group_sm7_17.end(), SurnameSorter());

	cout << "Students sorted by surname:" << std::endl;
	for(it = group_sm7_17.begin(); it != group_sm7_17.end(); ++it)
	{
		cout << *it;
	}

	//-- Рассчитываем средний балл в группе
	float average = accumulate(group_sm7_17.begin(), group_sm7_17.end(), 
		0.f, SumAverage(1.f / group_sm7_17.size()));

	cout << "Group average: " << average << endl;

	//-- Удаляем из списка студентов с низким средним баллом
	
	// начинаем с начала коллекции
	it = group_sm7_17.begin();
	
	// объявляем функциональный объект, реализующую критерий поиска
	FindAverageLessThan looser(4.0);	
	
	// ищем следующего студента, удовлетворяющего критерию
	while((it = find_if(it, group_sm7_17.end(), looser)) != group_sm7_17.end())
	{
		// удаляем его из коллекции
		// функция erase принимает итератор, указывающий на элемент, который
		// необходимо удалить и возвращает итератор на последующий элемент
		it = group_sm7_17.erase(it);
	}

	//-- Копируем фамилии студентов в новый список и выводим на экран
	list<string> surnames(group_sm7_17.size());

	transform(group_sm7_17.begin(), group_sm7_17.end(), 
		surnames.begin(), GetDescription());

	cout << "\nStudents after session:";

	list<std::string>::iterator at;
	for(at = surnames.begin(); at != surnames.end(); ++at)
	{
		cout << ' ' << *at;
	}
	cout << std::endl;
}
