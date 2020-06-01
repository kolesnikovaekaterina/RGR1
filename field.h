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
	void print(); // ����� ����� �� �����
	bool read(std::ifstream fin); // ������ ����� �� ������ �����
	bool read(std::string file); // ������ ����� �� ����� file
	void way(); // ������ �� ����������� ���� �� ������ � ����� (���� ��������)
	bool is_way(); // ���������� true, ���� ���� ����������
	int length_way(); // ���������� ����� ����
	void gen_way(); // ������� ���������� ���� �� �����
	~Field() {};
};

#endif // FIELD_H_INCLUDED
