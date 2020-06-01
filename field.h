#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <vector>
#include <fstream>
#include <string>
#include <utility>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, int> pii;

class Field {
private:
	vvi field, use;
	pii in, out;
public:
	Field() {};
	void print(); // Вывод карты на экран
	bool read(std::ifstream fin); // Чтение карты из потока ввода
	bool read(std::string file); // Чтение карты из файла file
	void way(); // Проход по кратчайшему пути из начала в конец (если возможно)
	bool is_way(); // Возвращает true, если путь существует
	int length_way(); // Возвращает длину пути
	void gen_way(); // Наносит кратчайший путь на карту
	~Field() {};
};

#endif // FIELD_H_INCLUDED
