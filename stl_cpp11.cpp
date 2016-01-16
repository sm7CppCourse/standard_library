#include <vector>     // std::vector
#include <list>       // std::list
#include <algorithm>  // std::sort, std::transform, std::find и др.
#include <numeric>    // std::accumulate
#include "student.h"

using namespace std;

void testSTL_Cpp11()
{
    //-- Использование списков инициализации в C++11
	vector<Student> group_sm7_17 = {
	    {"Petr", "Ivanov", 4.0}, 
	    {"Ivan", "Sidorov", 3.0}, 
	    {"Semen", "Petrov", 5.0} };
	    
	//-- Добавляем студента во вторую позицию
	// метод insert принимает итератор, указывающий на позицию вставки
	// и значение элемента
    group_sm7_17.insert(begin(group_sm7_17) + 1, {"Anna", "Fedorova", 5.0});

    //-- Выводим на экран
	cout << "Students:" << std::endl;
	// новый вид цикла for специально для коллекций
	for(auto student : group_sm7_17)
	{
		cout << student;
	}

    //-- Сортируем студентов по убыванию баллов
	sort(begin(group_sm7_17), end(group_sm7_17), 
		[](Student& i, Student& j) { return i.Average > j.Average; });

	cout << "\nStudents sorted by average:" << std::endl;
	for(auto student : group_sm7_17) cout << student;

    //-- Сортируем студентов по фамилии в алфавитном порядке
	sort(begin(group_sm7_17), end(group_sm7_17), 
		[](Student& i, Student& j) { return i.Surname < j.Surname; });

	cout << "\nStudents sorted by surname:" << std::endl;
	for(auto student : group_sm7_17) cout << student;

	//-- Рассчитываем средний балл в группе
	float sum = accumulate(begin(group_sm7_17), end(group_sm7_17), 
		0.f, [](float sum, Student& s) { return sum + s.Average; } );

    // выводим сумму баллов, деленную на количество студентов
	cout << "\nGroup average: " << sum / group_sm7_17.size()  << endl;

	//-- Удаляем из списка студентов с низким средним баллом
	
	// начинаем с начала коллекции
	auto it = begin(group_sm7_17);
	
	// объявляем объект - лямбда функцию, реализующую критерий поиска
	auto looser = [](Student& s) { return s.Average < 4.0; };	
	
	// ищем следующего студента, удовлетворяющего критерию
	while((it = find_if(it, end(group_sm7_17), looser)) != end(group_sm7_17))
	{
		// удаляем его из коллекции
		// функция erase принимает итератор, указывающий на элемент, который
		// необходимо удалить и возвращает итератор на последующий элемент
		it = group_sm7_17.erase(it);
	}

	//-- Копируем фамилии студентов в новый список и выводим на экран
	list<string> surnames(group_sm7_17.size());
	transform(begin(group_sm7_17), end(group_sm7_17), begin(surnames),
		 [](Student& s) { return s.Name + "_" + s.Surname; });

	cout << "\nStudents after session:";
	for(auto surname : surnames) cout << ' ' << surname;
	cout << std::endl;
}
