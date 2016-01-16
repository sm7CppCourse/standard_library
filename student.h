#ifndef _STUDENT_H_ // <- Подобная комбинация директив препроцессора гарантирует, 
#define _STUDENT_H_ // что заголовочный файл будет подключен только один раз

#include <string>
#include <iostream>

struct Student
{
	std::string Name;
	std::string Surname;
	float Average;
};

// Переопределение оператора << класса std::ostream для записи в поток объектов класса Student
std::ostream& operator<<(std::ostream& os, const Student& s);

// Переопределение оператора >> класса std::istream для чтения из потока объектов класса Student
std::istream& operator>>(std::istream& is, Student& s);

#endif //#ifndef _STUDENT_H_
