#include "field.h"
#include <stdio.h>
#include <queue>

// Вывод карты на экран
void Field::print() {
	for (int i = 0; i < this->field.size(); ++ i) {
		for (int j = 0; j < this->field[i].size(); ++ j)
			printf("%d ", this->field[i][j]);
		printf("\n");
	}
}

// Чтение карты из потока ввода
bool Field::read(std::ifstream fin) {
	std::string s;
	int cnt_in = 0, cnt_out = 0;
	//Считывание данных из файла построчно, пока это возможно
	for (int i = 0; std::getline(fin, s); ++ i) {
		this->field.push_back(vi(0));
        //Просмотр каждого сивола считанной строки s
		for (char c : s) {
		    //Если символ 0, 1, 2, 3, то добавляем в field число, преобразованное из символа (c - '0')
			if (c >= '0' && c <= '3') {
				this->field[i].push_back(c - '0');
                //Если символ - цифра 2, то записываем положение точки входа
				if (c == '2') {
					cnt_in ++;
					this->in = pii(i, this->field[i].size() - 1);
				}
				//Если символ - цифра 2, то записываем положение точки выхода
				if (c == '3') {
					cnt_out ++;
					this->out = pii(i, this->field[i].size() - 1);
				}
			}
			//Если встречен недопустимый символ
			else if (c != ' ' && c != '\r' && c != '\n') {
				printf("Unknown symbol\n");
				return false;
			}
		}
		//Если строка оказалась пустой, то её в счёт брать не нужно
		if (this->field[i].empty()) {
			this->field.pop_back();
			-- i;
		}
		//Если длина текущей строки не совпадает с длиной первой строки
		else if (this->field[i].size() != this->field[0].size()) {
			printf("Invalid input\n");
			return false;
		}
	}
	//Если точек входа в лабиринт или точек выхода из лабиринта несколько
	if (cnt_in != 1 || cnt_out != 1) {
		printf("Invalid input\n");
		return false;
	}
	//Если пустой ввод
	if (this->field.empty()) {
		printf("Empty input\n");
		return false;
	}
	return true;
}

// Чтение карты из файла file
bool Field::read(std::string file) {
	return this->read(std::ifstream(file));
}

// Проход по кратчайшему пути из начала в конец (если возможно)
void Field::way() {
	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};
	for (int i = 0; i < this->field.size(); ++ i) {
		this->use.push_back(vi(this->field[0].size(), 0));
	}

	std::queue<pii> que;
	que.push(this->in);
	this->use[this->in.first][this->in.second] = 1;
	int n = this->field.size();
	int m = this->field[0].size();

    //Обход в ширину
	while (!que.empty()) {
        // Извлечение элемента из очереди que
		pii elem = que.front();
		int x = elem.first;
		int y = elem.second;
		que.pop();

		// Если дошли до выхода из лабиринта
		if (x == this->out.first && y == this->out.second)
			break;

        // Просмотр и добавление в очередь всех соседних клеток карты, которые соответствуют условию
		for (int i = 0; i < 4; ++ i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
				if (this->use[nx][ny] == 0 && (this->field[nx][ny] == 1 || this->field[nx][ny] == 3)) {
					this->use[nx][ny] = this->use[x][y] + 1;
					que.push(pii(nx, ny));
				}
			}
		}
	}
}

// Возвращает true, если путь существует
bool Field::is_way() {
	return this->use[this->out.first][this->out.second] != 0;
}

// Возвращает длину кратчайшего пути
int Field::length_way() {
	return this->use[this->out.first][this->out.second] - 1;
}

// Наносит кратчайший путь на карту
void Field::gen_way() {
	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};
	int n = this->field.size();
	int m = this->field[0].size();

	//Вывод кратчайшего пути
	pii cur = this->out;
	while (cur != this->in) {
		int x = cur.first;
		int y = cur.second;
		this->field[x][y] = 4;
		for (int i = 0; i < 4; ++ i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
				if (this->use[nx][ny] == this->use[x][y] - 1)
					cur = pii(nx, ny);
			}
		}
	}
	this->field[this->out.first][this->out.second] = 3;
}
