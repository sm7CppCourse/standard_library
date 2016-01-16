#include "student.h"

// Переопределение оператора << класса std::ostream для записи в поток объектов класса Student
std::ostream& operator<<(std::ostream& os, const Student& s)
{
	return os << s.Name << ' ' <<  s.Surname << ' ' << s.Average << std::endl;
}

// Переопределение оператора >> класса std::istream для чтения из потока объектов класса Student
std::istream& operator>>(std::istream& is, Student& s)
{
	return is >> s.Name >> s.Surname >> s.Average;
}
