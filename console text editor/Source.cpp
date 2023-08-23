#pragma warning(disable : 4996)

#include <iostream>

#include <iomanip>

#include <conio.h>

#include <windows.h>

#include <string>

#include <fstream>

using namespace std;

struct chr {

	char S;

	chr* next;
};

struct text {

	chr* Start;

	chr* Cur;

	int n, posX, posY;
};


text* createText()
{
	text* out = new text;

	out->Cur = NULL;

	out->Start = NULL;

	out->n = 0;

	out->posX = 0;

	out->posY = 0;

	return out;
}

// ���� ������

void enterText(text* t, char c)
{
	chr* tmp = new chr;

	tmp->S = c;

	tmp->next = t->Cur;

	if (t->n) {

		chr* prev = t->Start;

		if (prev != t->Cur) {

			while (prev->next != t->Cur)
				prev = prev->next;

			prev->next = tmp;
		}
		else
		{
			t->Start = tmp;
			tmp->next = t->Cur;
		}
	}
	else
	{
		t->Start = tmp;
	}
	if (c == 13)
	{
		tmp->S = '\n';
		t->posX = 0;
		t->posY++;
	}
	else
	{
		t->posX++;
	}
	t->n++;
}
// ........................................................................................................................................................................

// ���������� Backspace

void backspaceText(text* t)
{
	if (t->Cur != t->Start)
	{
		if (t->Start->next == t->Cur)
		{
			delete t->Start;
			t->Start = t->Cur;
			t->n--;
			t->posX = 0;
			t->posY = 0;
			return;
		}
		int u = 1, v = 0;
		chr* prev = t->Start, * tmp;
		while (prev->next->next != t->Cur)
		{
			if (prev->next->S == '\n')
				u = 0, v++;
			else
				u++;
			prev = prev->next;
		}
		tmp = prev->next;
		prev->next = prev->next->next;
		delete tmp;
		t->n--;
		t->posY = v;
		t->posX = u;
	}
}
// ........................................................................................................................................................................

// ����������� ������� ������

void moveRight(text* t)
{
	if (!t->Cur)
		return;
	if (t->Cur->S == '\n')
	{
		t->posX = 0;
		t->posY++;
	}
	else
		t->posX++;
	t->Cur = t->Cur->next;
}
// ........................................................................................................................................................................

// ����������� ������� �����

void moveLeft(text* t)
{
	if (t->Cur != t->Start)
	{
		int u = 0, v = 0;
		chr* prev = t->Start;
		while (prev->next != t->Cur)
		{
			if (prev->S == '\n')
				u = 0, v++;
			else
				u++;
			prev = prev->next;
		}
		t->Cur = prev;
		t->posX = u;
		t->posY = v;
	}
}
// ........................................................................................................................................................................

// ����������� ������� �����

void moveUp(text* t)
{
	if (t->posY > 0)
	{
		t->posY--;
		int u = 0, v = 0;
		chr* prev = t->Start;
		while (true)
		{
			if (t->posX == u && t->posY == v)
				break;
			if (prev->S == '\n') {
				if (t->posY == v)
					break;
				else
					u = 0, v++;
			}
			else
				u++;
			prev = prev->next;
		}
		t->Cur = prev;
		t->posX = u;
		t->posY = v;
	}
}
// ........................................................................................................................................................................

// ����������� ������� ����

void moveDown(text* t)
{
	int u = t->posX, v = t->posY++;
	chr* pred = t->Cur;
	while (true)
	{
		if (!pred)
			if (v < t->posY)
			{
				t->posY--;
				return;
			}
			else
			{
				t->posX = u;
				break;
			}

		if (u == t->posX && v == t->posY)
			break;
		if (pred->S == '\n')
			if (v < t->posY)
				v++, u = 0;
			else
			{
				t->posX = u;
				break;
			}
		else
			u++;
		pred = pred->next;
	}
	t->Cur = pred;
}
// ........................................................................................................................................................................

// ����� ������

void output(text* t)
{
	chr* tu = t->Start;
	while (tu)
	{
		cout << tu->S;
		tu = tu->next;
	}
}
// ........................................................................................................................................................................

// ������� ������

void DoneText(text* t)
{
	t->Cur = t->Start;
	while (t->Cur)
	{
		chr* tmp = t->Cur;
		t->Cur = t->Cur->next;
		delete tmp;
	}
	delete t;
}
// ........................................................................................................................................................................

// �������

void oform() {

	cout << "_______________________________________________________________________________________________________________";
	cout << "\n                                                                                                              /\n ��������� �������� EMPTY_WORD                                                                               /" << endl;
	cout << "____________________________________________________________________________________________________________/" << endl << endl << endl << endl;

}

void graf_func() {

	oform();

	cout << "\n ����:\n" << endl;

	cout << " 1. ����� ������� ��������� �������� ������� 1" << endl;

	cout << " 2. ����� ������� ��������� �������� ��� �������������� 2" << endl;

	cout << " 3. ��� ������ ������� Esc " << endl;

}

void graf_funk_2() {

	cout << "\n _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl << endl;

	cout << " ������ ������:\n" << endl << endl;
}

// ......................................................................................................................................................................

// ��������� ����

void save_as_odn_sp(string name, text* head) {

	bool b(0);

	cout << "\n ��� ����� �� ����� ��������� ��������� ������ � ����: ? / : * < > | AUX COM1 COM2 PRN NUL \n" << endl;

	while (b == 0) {

		cout << " ������� ��� �����: ";

		cin >> name;

		ofstream f;

		f.open(name);

		if (f.is_open()) {

			b = 1;

			chr* pred = head->Start;

			while (pred)
			{
				f << pred->S;

				pred = pred->next;
			}

			f.close();
		}
		else { cout << "\n ���� �� ��������, ������� ������������ ���\n" << endl; b = 0; }
	}
}

// .........................................................................................................................................................................

// ������ Esc

void Esc(int& key, string& name, text* head) {

	system("cls");

	oform();

	cout << " ������ �� �� ��������� ���� (�� = 1; ��� - ����� ������)?" << endl;

	key = getch();

	if (key == 49) {

		save_as_odn_sp(name, head);

		cout << " ���� ��������" << endl;

	}

	else cout << " ���� �� ��������" << endl;
}

//.......................................................................................................................................................................


// ����������

void functional(int& key, HANDLE hConsole, COORD position, text* head) {

	if (key == 8)
		backspaceText(head);
	else if (key != 77 && key != 80 && key != 72 && key != 75 && key != 27 && key != 224)
		enterText(head, key);

	system("cls");

	graf_func();

	graf_funk_2();

	output(head);

	position.X = head->posX, position.Y = head->posY + 19;

	SetConsoleCursorPosition(hConsole, position);
}

// ........................................................................................................................................................................


// ���������� �������� 

void control(int& key, text* head, string& name) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD position;

	position.X = head->posX, position.Y = head->posY + 19;

	while (key != 27) {

		key = getch();
		switch (key) {

		case 75:

			moveLeft(head);

			break;

		case 77:

			moveRight(head);

			break;

		case 72:

			moveUp(head);

			break;

		case 80:

			moveDown(head);

			position.X = head->posX, position.Y = head->posY + 19;

			break;

		}

		functional(key, hConsole, position, head);
	}

	Esc(key, name, head);

	cout << " ������� ����� ������� ��� ���������� ������ " << endl;

	key = getch();

	DoneText(head);

	exit('1');

}

// .................................................................................................................................................................................


// ������� ����

void create_file(int& key, text* head, string& name) {

	graf_funk_2();

	control(key, head, name);

}

// ..........................................................................................................................................................................


// ������� ����

void open_file(string& name, int& key, text* head) {

	cout << "\n _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ";

	fstream f;

	char str_1;

	cout << " \n\n������� ��� �����: ";

	cin >> name;

	f.open(name);

	name = "";

	if (f) {

		cout << "\n\n�� ������� ������� ��������� ��������.\n" << endl;

		cout << "��� ������ � ��� ������� Enter . . . " << endl;

		while (key != 13) {

			key = getch();

		}

		system("cls");

		graf_func();

		cout << "\n _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n\n";

		cout << " ������ ������:" << endl << endl;

		while (!f.eof()) {

			f.get(str_1);

			enterText(head, str_1);
		}

		cout << endl;

		output(head);

		control(key, head, name);
	}

	else cout << "\n\n���� �� ������." << endl;
}

// ..............................................................................................................................................................................


// �������� ���� 

void menu(int& key, string& name, text* head) {

	graf_func();

	key = getch();

	while (1) {

		switch (key)
		{
		case 27:

			cout << " ������� ����� ������� ��� ���������� ������ " << endl;

			key = getch();

			DoneText(head);

			exit('1');

			break;

		case 49:

			create_file(key, head, name);

			break;

		case 50:

			open_file(name, key, head);

			break;

		default: cout << " ��� ������ ������!!! ���������� ��� ���!!!" << endl; key = getch();

		}
	}
}

// .....................................................................................................................................................................


// ������� �������

int main() {

	system("color 03");

	string name;

	text* head = createText();

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	int key(0);

	oform();

	cout << "\n\t\t\t\t\t\t����� ����������!!!" << endl << endl;

	cout << "\t\t\t\t\t��� ����������� ������� Enter . . . " << endl;

	while (key != 13) {

		key = getch();

	}

	system("cls");

	menu(key, name, head);

	return 0;
}
