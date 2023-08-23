#include <iostream>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include <cmath>

// структура объект списка
struct MyStruct
{
	int kolvo;
	float prise;
	MyStruct* next;
};

//Прототипы
//Операция по закупке 
MyStruct* _PurchaseOperation(MyStruct* head, bool &flag);
//Операция по продаже  
MyStruct* _SaleOperation(MyStruct* head);
//Отрисовка графики
void _Graphics();
//Анимация
void switchColor();
//Запись о поступлениях на склад 
void warehouse(MyStruct* head);
//Меню записи торговых операций
void _menu(MyStruct* head);


void _Graphics() {
	std::cout << "________________________________________________________" << std::endl;
	std::cout << "                _      ____    _____                   " << std::endl;
	std::cout << "               / \\    |    \\  |     \\                  " << std::endl;
	std::cout << "              /   \\   |____/  |                        " << std::endl;
	std::cout << "             /-----\\  |    \\  |                        " << std::endl;
	std::cout << "            /       \\ |____/  |_____/                  " << std::endl;
	std::cout << "________________________________________________________" << std::endl;

}

void switchColor() {
	while (true)
	{
		system("color 2");
		Sleep(100);
		system("color D");
		Sleep(100);
		system("color 4");
	}
}

MyStruct* _PurchaseOperation(MyStruct* head, bool &flag) {
	MyStruct* end = head;
	flag = true;
	std::cout << "Сколько партий планируете принять? Введите целочисл. зн.: ";
	int j(0);
	std::cin >> j;
	for (int i = 0; i < j; i++) {
		std::cout << "Введите кол-во: ";
		end->next = new MyStruct;
		end = end->next;
		std::cin >> end->kolvo;
		std::cout << "Введите цену за единицу продукции: ";
		std::cin >> end->prise;
		std::cout << "______________________________________\n\n";
	}
	end->next = NULL;
	end = head;
	std::cout << "Результат:\n";
	std::cout << " ________________________________________________________" << std::endl;
	std::cout << "| Количество продукции | Цена за шт. | Общая Цена\n";
	std::cout << "|--------------------------------------------------------\n";
	for (int i = 0; i < j; i++) {
		end = end->next;
		std::cout << "|           " << end->kolvo << "                 " << end->prise << "$          " << end->prise * end->kolvo << '$' << std::endl;
		std::cout << "|________________________________________________________" << std::endl;
	}

	return head;
}

MyStruct* _SaleOperation(MyStruct* head) {
	MyStruct* end = head;
	end = end->next;
	int tovar(0), total_tovar(0), ptr(0);
	float total_сost(0);
	std::cout << "Введите количество товара для продажи :\n";
	std::cin >> tovar;
	while (end)
	{
		total_tovar = total_tovar + end->kolvo;
		end = end->next;
	}
	end = head;
	end = end->next;
	std::cout << "Результат:\n";
	std::cout << " _________________________________________________________" << std::endl;
	std::cout << "| Количество продукции | Цена за шт. | Цена за товар + 20%\n";
	std::cout << "|---------------------------------------------------------\n";
	while (end) {
		
		ptr = end->kolvo;
		if (tovar > 0) {
			if (tovar < end->kolvo) {
				total_сost = ((end->prise + end->prise * 0.20) * tovar) + total_сost;
			}
			else
			{
				total_сost = ((end->prise + end->prise * 0.20) * (tovar - (tovar - end->kolvo))) + total_сost;
			}
				end->kolvo = end->kolvo - tovar;
				tovar = tovar - ptr;
				if (end->kolvo < 0) { end->kolvo = 0; }
		}
		std::cout << "|         S " << end->kolvo << "                 " << end->prise + end->prise * 0.20 << "$          " << (end->prise+end->prise*0.20) * end->kolvo << '$' << std::endl ;
		std::cout << "|________________________________________________________" << std::endl;
		
		end = end->next;
	}

	std::cout << "\n Общая сумма с продаж: " << total_сost << '$' <<std::endl;
	
	if (tovar > total_tovar) {
		std::cout <<' ' << tovar - total_tovar << " Единиц товара отсутствует на складе!" << std::endl;
	}

	return head;
}

void warehouse(MyStruct* head) {
	MyStruct* end = head;
	end = end->next;
	std::cout << "\nРезультат:\n";
	std::cout << " ________________________________________________________" << std::endl;
	std::cout << "| Количество продукции | Цена за шт. | Общая Цена\n";
	std::cout << "|--------------------------------------------------------\n";
	while (end) {
		std::cout << "|           " << end->kolvo << "                 " << end->prise << "$          " << end->prise * end->kolvo << '$' << std::endl;
		std::cout << "|________________________________________________________" << std::endl;
		end = end->next;
	}
}

void _menu(MyStruct* head) {

	int key(0);
	bool flag(false);
	std::cout << "\n1.Операция по закупке." << std::endl;
	std::cout << "2.На складе хранится:" << std::endl;
	std::cout << "3.Операция по продаже." << std::endl;

	while (true)
	{
		switch (key = _getch())
		{
		case 0x31:
			head = _PurchaseOperation(head, flag);
			break;

		case 0x32:
			if (flag == true) {
				warehouse(head);
			}
			else std::cout << "Ни одно звено списка не создано!!!\n";
			break;

		case 0x33:
			if (flag == true) {
				head = _SaleOperation(head);
			}
			else std:: cout << "Ни одно звено списка не создано!!!\n";
			break;

		case 0x1B:
			exit(0);
			break;

		default:
			std::cout << "Нет такой команды!!!" << std::endl;
			break;
		}
	}
}


int main() {

	setlocale(LC_ALL, "Rus");
	_Graphics();
	//Выделяем поток
	std::thread th1(switchColor);
	th1.detach();
	MyStruct* head = NULL;
	head = new MyStruct;
	_menu(head);

	return 0;
}