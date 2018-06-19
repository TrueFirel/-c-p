#include "stdafx.h"


using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a;

	do {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n1.Вход под покупателем\n2.Вход под администрацией\n3.Выход\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
		
		if (!(cin >> a)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			continue;
		}
		
		else {

			switch (a) {
			case 1: {
				system("cls");

				int tryCount = 3;
				bool accessAcception = false;
				Customer someCustomer;

				while (tryCount > 0) {
					
					someCustomer.authorization();

					if (!someCustomer.findAtFile()) {
						tryCount--;
						system("cls");
						cout << "ОШИБКА: Покупатель не найден. У вас осталось "<<tryCount<<" попыток для входа"<<"\n\nНажмите любую кнопку для продолжения" << endl;
						_getch();
						system("cls");
					}

					else {
						cout << "Вы успешно вошли как покупатель\n\nНажмите любую кнопку для продолжения" << endl;
						accessAcception = true;
						_getch();
						system("cls");
						break;
					}
				}

				if (accessAcception == true) {
					someCustomer.service();
				}

				break;
			}
			case 2: {
				system("cls");

				int tryCount = 3;
				Administration somePersonal;
				bool accessAcception = false;

				while (tryCount > 0) {
					somePersonal.authorization();
					if (!somePersonal.findAtFile()) {
						tryCount--;
						system("cls");
						cout << "ОШИБКА: Администратор не найден. У вас осталось " << tryCount << " попыток для входа" << "\n\nНажмите любую кнопку для продолжения" << endl;
						_getch();
						system("cls");
					}

					else {
						cout << "Вы успешно вошли как администратор\n\nНажмите любую кнопку для продолжения" << endl;
						accessAcception = true;
						_getch();
						system("cls");
						break;
					}

				}

				if (accessAcception == true) somePersonal.service();

				break;
			}
			case 3: return 0;
			default: {
				system("cls");
				cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			}

			a = 0;
		}

	} while (a < 1 || a>3);

    return 0;
}

