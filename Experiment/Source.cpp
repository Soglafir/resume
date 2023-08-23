#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <TlHelp32.h>

HWND handle;
POINT cursor;

void Paint() {
	std::cout << "___________________________________________" << std::endl;
	std::cout << "                                          /" << std::endl;
	std::cout << "      ______      ______   ________      /" << std::endl;
	std::cout << "     |      \\    /      \\     |         /" << std::endl;
	std::cout << "     |______/   /        \\    |        /" << std::endl;
	std::cout << "     |      \\   \\        /    |       /" << std::endl;
	std::cout << "     |______/    \\______/     |      /" << std::endl;
	std::cout << "                                    /" << std::endl;
	std::cout << "                                   /" << std::endl;
	std::cout << "__________________________________/" << std::endl;

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

void MoveCursor() {
	SetCursorPos(450, 350);
	//зажать левую кнопку мыши
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	for (int i = 0; i < 25; i++) {
		//Получаем текущую позицию курсора
		GetCursorPos(&cursor);
		Sleep(20);
		//Отдаем позицию курсора (т.е. перемещаем его)
		SetCursorPos(cursor.x + i, cursor.y);
	}
	for (int i = 0; i < 25; i++) {
		GetCursorPos(&cursor);
		Sleep(20);
		SetCursorPos(cursor.x, cursor.y + i);
	}
	for (int i = 0; i < 25; i++) {
		GetCursorPos(&cursor);
		Sleep(20);
		SetCursorPos(cursor.x - i, cursor.y);
	}
	for (int i = 0; i < 25; i++) {
		GetCursorPos(&cursor);
		Sleep(20);
		SetCursorPos(cursor.x, cursor.y - i);
	}
	//отпустить левую кнопку мыши
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void ClickMouse() {
	//Отслеживаем нажатие кнопок мыши по окну 
	while (true) {
		if (GetAsyncKeyState(VK_RBUTTON)) {
			std::cout << "Нажата правая кнопка мыши!!!" << std::endl;
			Sleep(50);
		}
		if (GetAsyncKeyState(VK_LBUTTON)) {
			std::cout << "Нажата левая кнопка мыши!!!" << std::endl;
			Sleep(50);
		}
	}
}

void AutoClick (int &a) {
	SetCursorPos(880, 560);
	for (int i = 0; i < a*2; i++) {
		Sleep(400);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
}

void DestroyTask() {
	while (true)
	{
		handle = FindWindowA("TaskManagerWindow", "Диспетчер задач");
		SendMessage(handle, WM_SYSCOMMAND, SC_CLOSE, 0);
	}
}

void DestroyTaskActivity() {
	std::thread th2(DestroyTask);
	th2.detach();
}

int main() {
	setlocale(LC_ALL, "Rus");
	int num(0), a(0);
	//Рисуем 
	Paint();
	//Меняем цвет
	std::thread th1(switchColor);
	//std::thread th2(ClickMouse);
	th1.detach();
	//th2.detach();
	std::cout << "\n\n";
	std::cout << "Вы хотите:\n\n";
	std::cout << "1. Нарисовать прямоугольник в Paint." << std::endl;
	std::cout << "2. Запустить Google Chrome" << std::endl;
	std::cout << "3. Сломать Шиндовс" << std::endl;
	std::cout << "4. Блокировать диспетчер задач" << std::endl;
	std::cout << "5. Автоклик на подписки" << std::endl;
	std::cout << "6. Выход" << std::endl;
	std::cout << "___________________________________________" << std::endl;

	while (true) {
		std::cin >> num;
		switch (num)
		{
		case 1:
			std::cout << "Выбран 1 пункт:" << std::endl;
			system("Start mspaint.exe");
			Sleep(1000);
			MoveCursor();
			system("taskkill /IM mspaint.exe");
			SetCursorPos(950, 535);
			Sleep(300);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			break;
		case 2:
			std::cout << "Выбран 2 пункт:" << std::endl;
			//Запускаем Google Chrome 
			ShellExecuteA(handle, "open", "chrome.exe", NULL, NULL, SW_RESTORE);
			break;
		case 3:
			std::cout << "Выбран 3 пункт:" << std::endl;
			while (true) {
				//Получаем текущее окно
				handle = GetForegroundWindow();
				// - окна 
				SendMessage(handle, WM_DESTROY, 0, 0);
			}
			break;
		case 4:
			std::cout << "Выбран пункт 4:" << std::endl;
			DestroyTaskActivity();
			break;
		case 5:
			std::cout << "Выбран пункт 5:" << std::endl;
			//std::string str = "";
			//std::cout << "Вставьте ссылку на профиль: " <<std::endl;
			//std::cin >> str;
			std::cout << "Введите количество итераций: ";
			//std::cin >> a;
			//ShellExecuteA(handle, "open", "chrome.exe", NULL, NULL, SW_RESTORE);
			AutoClick(a);
			break;
		case 6:
			std::cout << "Приходите еще))" << std::endl;
			exit(0);
			break;
		default:
			std::cout << "Нет такой команды!!!" << std::endl;
			break;
		}
	}

	return 0;
}