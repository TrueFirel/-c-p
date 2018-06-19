#include "stdafx.h"

using namespace std;
using namespace myNamespace;
float Account::shopCash = 0;

template <class T>

ostream &operator<<(ostream &out, Customer &someAcc) {
	out << "Логин: " << someAcc.login << "Пароль: " << someAcc.password << endl;
	return out;
}

ostream &operator<<(ostream &out, Administration &someAcc) {
	out << "Логин: " << someAcc.login << "Пароль: " << someAcc.password << endl;
	return out;
}


Account::Account() {
	key = 666;
}

Account::Account(char * log, char * pass) {

	int i = 0;

	for (i; log[i]; i++) {
		login[i] = log[i];
	}

	login[i] = '\0';
	i = 0;

	for (i; pass[i]; i++) {
		password[i] = pass[i];
	}

	key = 666;

	password[i] = '\0';

}

Customer::Customer() {
	cash = 0;
	key = 666;
}

int Account::findAtFile() {

	ifstream readFromFile("Customers.bin", ios_base::in);
	string fieldData;
	int spaceSeen = 0,
		loginFilling = 0,
		passwordFilling = 0,
		counter = 1,
		isFind = 0;
	char log[30],
		pass[30];

	while (getline(readFromFile, fieldData)) {
		for (unsigned int i = 0; i < fieldData.length(); i++) {
			if (fieldData[i] == ' ') {
				spaceSeen++;
				continue;
			}
			if (spaceSeen == 0) {
				log[loginFilling] = fieldData[i];
				loginFilling++;
			}
			else {
				pass[passwordFilling] = fieldData[i];
				passwordFilling++;
			}
		}
		log[loginFilling] = '\0';
		pass[passwordFilling] = '\0';
		spaceSeen = 0;
		loginFilling = 0,
			passwordFilling = 0;
		Administration somePersonal(log, pass);
		somePersonal.codePassword();
		if (strcmp(password, somePersonal.getPassword()) == 0 && strcmp(login, somePersonal.getLogin()) == 0) {
			isFind++;
			break;
		}
		counter++;
	}
	readFromFile.close();
	return isFind;
}

Customer &Customer::operator+=(int a) {
	cash += a;
}

void Account::codePassword() {
	for (int i = 0; i < 15; i++) {
		password[i] = (password[i])^key;
	}
	password[16] = '\0';
}

char * Account::getPassword() {
	return password;
}

char * Account::getLogin() {
	return login;
}

void Account::authorization() {
	
	int mainCounter = 0,
		additionalCounter=0;

		cout << "Введите логин: ";
		cin >> login;
		cout << endl;
		
		while (mainCounter == 0) {
			int i = 0;
			cout << "Введите пароль: ";
			for (i; i < 30; i++) {
				password[i] = _getch();
				if (password[0] == 8) {
					i--;
					continue;
				}
				if ( i < 4 && password[i] == 13) {
					system("cls");
					cout<<"\nОшибка ввода, требуется ввести 4 и более символов, повторите ввод\n\nНажмите любую кнопку для продолжения"<<endl;
					_getch();
					system("cls");
					break;
				}
				if (i > 15 && password[i] == 13) {
					system("cls");
					cout<<"\nОшибка ввода, требуется ввести менее 15 символов, повторите ввод\n\nНажмите любую кнопку для продолжения"<<endl;
					_getch();
					system("cls");
					break;
				}
				if (password[i] == 13) {
					password[i] = '\0';
					mainCounter++;
					break;
				}
				if (password[i] != 8) {
					putchar('*');
				}
				else {
					printf("\b \b");
					i = i - 2;
				}
			}
			
		}
		
		cout << endl;
}

int Account::outputDataInTableForm(Products *prArr, int bufSize) {

	if (prArr == NULL) return 1;

	system("cls");
	cout << setw(120) << setfill('-') << "" << setfill(' ') << endl;
	cout << "|" << setw(15) << "Тип инструмента" << "|" << setw(20) << "Имя инструмента" << "|" << setw(15) << "Материал" << "|" << setw(18) << "Дата производства" << "|" << setw(20) << "Страна" << "|" << setw(12) << "Стоимость $" << "|" << setw(12) << "Количество" << "|" << endl;
	cout << setw(120) << setfill('-') << "" << setfill(' ') << endl;
	for (int i = 0; i<bufSize; i++) {
		cout << "|" << setw(15) << prArr[i].characteristics.instrumentName << "|" << setw(20) << prArr[i].characteristics.instrumentType << "|" << setw(15) << prArr[i].characteristics.material << "|" << setw(18) << prArr[i].characteristics.makingDate << "|" << setw(20) << prArr[i].country << "|" << setw(12) << prArr[i].cost << "|" << setw(12) << prArr[i].count << "|" << endl;
		cout << setw(120) << setfill('-') << "" << setfill(' ') << endl;
	}
	cout << "\n\nНажмите любую кнопку для продолжения" << endl;
	_getch();
	system("cls");

	return 0;
}

int Account::returnNumOfStructures() {
	ifstream in("PRODUCT_DATA.DAT");
	int i = 0;
	Products tmp;
	while (in.read((char*)&tmp, sizeof(Products))) i++;
	in.close();
	return i;
}

#pragma optimize("", off)
Products * Account::readStructFromFile() {
	int size = 0;
	Products *prodArr, tmp;
	ifstream in("PRODUCT_DATA.DAT");


	while (in.read((char*)&tmp, sizeof(Products))) {
		size++;
	}

	if (size == 0) {
		prodArr = NULL;
		return prodArr;
	}

	in.close();
	in.open("PRODUCT_DATA.DAT");
	prodArr = new  Products[size];
	size = 0;

	while (in.read((char*)&tmp, sizeof(Products))) {
		prodArr[size] = tmp;
		size++;
	}

	in.close();
	return prodArr;
}
#pragma optimize("", on)

void Account::rewriteData(Products *prArr, int size) {
	ofstream out("PRODUCT_DATA.DAT");

	for (int i = 0; i < size; i++) {
		out.write((char*)&prArr[i], sizeof(Products));
	}

	out.close();
}

int Account::searchProduct() {

	Products *prArr = readStructFromFile(),
		*outArr,
		tmp;

	if (prArr == NULL) {
		return 0;
	}

	int bufSize = returnNumOfStructures(),
		switchCount,
		breakCycle = 0;

	system("cls");
	while (breakCycle == 0) {
		cout << "\tПоиск\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << "1.По имени товара\n2.По типу товара\n3.По дате производства\n4.По материалу\n5.По стране производства\n6.По стоимости\n7.Выход в предыдущее меню\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		if (!(cin >> switchCount)) {
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			continue;
		}
		switch (switchCount) {
		case 1: {
			int counter = 0;
			system("cls");
			cout << "Введите имя товара: ";
			cin >> tmp.characteristics.instrumentName;
			cout << endl;
			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.instrumentName == prArr[i].characteristics.instrumentName) {
					counter++;
				}
			}

			outArr = new Products[counter];
			int outSize = counter;
			counter = 0;

			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.instrumentName == prArr[i].characteristics.instrumentName) {
					outArr[counter] = prArr[i];
					counter++;
				}
			}

			if (counter != 0) outputDataInTableForm(outArr, outSize);
			else {
				system("cls");
				cout << "Товар не найден\n\nНажмите любую кнопку для продолжения\n" << endl;
				_getch();
			}
			system("cls");
			break;
		}
		case 2: {
			int counter = 0;
			system("cls");
			cout << "Введите тип товара: ";
			cin >> tmp.characteristics.instrumentType;
			cout << endl;
			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.instrumentType == prArr[i].characteristics.instrumentType) {
					counter++;
				}
			}

			outArr = new Products[counter];
			int outSize = counter;
			counter = 0;

			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.instrumentType == prArr[i].characteristics.instrumentType) {
					outArr[counter] = prArr[i];
					counter++;
				}
			}

			if (counter != 0) outputDataInTableForm(outArr, outSize);
			else {
				system("cls");
				cout << "Товар не найден\n\nНажмите любую кнопку для продолжения\n" << endl;
				_getch();
			}
			system("cls");
			break;
		}
		case 3: {
			int counter = 0;
			system("cls");
			cout << "Введите дату производства товара: ";
			cin >> tmp.characteristics.makingDate;
			cout << endl;
			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.makingDate == prArr[i].characteristics.makingDate) {
					counter++;
				}
			}

			outArr = new Products[counter];
			int outSize = counter;
			counter = 0;

			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.makingDate == prArr[i].characteristics.makingDate) {
					outArr[counter] = prArr[i];
					counter++;
				}
			}

			if (counter != 0) outputDataInTableForm(outArr, outSize);
			else {
				system("cls");
				cout << "Товар не найден\n\nНажмите любую кнопку для продолжения\n" << endl;
				_getch();
			}
			system("cls");
			break;
		}
		case 4: {
			int counter = 0;
			system("cls");
			cout << "Введите материал товара: ";
			cin >> tmp.characteristics.material;
			cout << endl;
			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.material == prArr[i].characteristics.material) {
					counter++;
				}
			}

			outArr = new Products[counter];
			int outSize = counter;
			counter = 0;

			for (int i = 0; i < bufSize; i++) {
				if (tmp.characteristics.material == prArr[i].characteristics.material) {
					outArr[counter] = prArr[i];
					counter++;
				}
			}

			if (counter != 0) outputDataInTableForm(outArr, outSize);
			else {
				system("cls");
				cout << "Товар не найден\n\nНажмите любую кнопку для продолжения\n" << endl;
				_getch();
			}
			system("cls");
			break;
		}
		case 5: {
			int counter = 0;
			system("cls");
			cout << "Введите страну производства товара: ";
			cin >> tmp.country;
			cout << endl;
			for (int i = 0; i < bufSize; i++) {
				if (tmp.country == prArr[i].country) {
					counter++;
				}
			}

			outArr = new Products[counter];
			int outSize = counter;
			counter = 0;

			for (int i = 0; i < bufSize; i++) {
				if (tmp.country == prArr[i].country) {
					outArr[counter] = prArr[i];
					counter++;
				}
			}

			if (counter != 0) outputDataInTableForm(outArr, outSize);
			else {
				system("cls");
				cout << "Товар не найден\n\nНажмите любую кнопку для продолжения\n" << endl;
				_getch();
			}
			system("cls");
			break;
		}
		case 6: {
			int counter = 0;
			system("cls");
			cout << "Введите цену товара: $";
			cin >> tmp.cost;
			cout << endl;
			for (int i = 0; i < bufSize; i++) {
				if (tmp.cost == prArr[i].cost) {
					counter++;
				}
			}

			outArr = new Products[counter];
			int outSize = counter;
			counter = 0;

			for (int i = 0; i < bufSize; i++) {
				if (tmp.cost == prArr[i].cost) {
					outArr[counter] = prArr[i];
					counter++;
				}
			}

			if (counter != 0) outputDataInTableForm(outArr, outSize);
			else {
				system("cls");
				cout << "Товар не найден\n\nНажмите любую кнопку для продолжения\n" << endl;
				_getch();
			}
			system("cls");
			break;
		}
		case 7: {
			breakCycle++;
			break;
		}
		default: {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите на любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		}
	}
	system("cls");
	return 1;
}

int Account::filtrateProductsAtCost() {

	Products *prArr = readStructFromFile(),
		*outArr;

	if (prArr == NULL) {
		return 0;
	}

	int leftBorder,
		rightBorder,
		tmpBorder,
		bufSize = returnNumOfStructures(),
		counter = 0;

	system("cls");

	while (true) {
		cout << "Фильтровать от: $";

		if (!(cin >> leftBorder)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			cin.clear();
			while (getchar() != '\n');
			_getch();
			system("cls");
			continue;
		}
		if (leftBorder < 0) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			continue;
		}

		break;
	}

	while (true) {
		cout << "До: $";

		if (!(cin >> rightBorder)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			cin.clear();
			while (getchar() != '\n');
			_getch();
			system("cls");
			continue;
		}
		if (rightBorder < 0) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			continue;
		}

		break;
	}

	if (leftBorder > rightBorder) {
		tmpBorder = leftBorder;
		leftBorder = rightBorder;
		rightBorder = tmpBorder;
	}

	for (int i = 0; i < bufSize; i++) {
		if (prArr[i].cost >= leftBorder && prArr[i].cost <= rightBorder) {
			counter++;
		}
	}

	outArr = new Products[counter];
	counter = 0;

	for (int i = 0; i < bufSize; i++) {
		if (prArr[i].cost >= leftBorder && prArr[i].cost <= rightBorder) {
			outArr[counter] = prArr[i];
			counter++;
		}
	}
	if (counter != 0) {
		outputDataInTableForm(outArr, counter);
		return 1;
	}
	else return -1;
}

int Account::sortProducts() {
	int switchValue,
		breakCycle = 0,
		bufSize = returnNumOfStructures();
	Products *prArr = readStructFromFile();

	if (prArr == NULL) {
		return 0;
	}

	while (breakCycle == 0) {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nСортировка товаров:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n1.По алфовитному порядку\n2.По цене\n3.По количеству товаров на складе\n4.Выход в предыдущее меню\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

		if (!(cin >> switchValue)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			continue;
		}
		system("cls");

		switch (switchValue) {
		case 1: {
			int k = 0;
			Products tmp;

			for (int i = 0; i < bufSize - 1; i++) {
				for (int floatValue = i; floatValue < bufSize; floatValue++) {
					if (strcmp((char*)&prArr[i].characteristics.instrumentName, (char*)&prArr[floatValue].characteristics.instrumentName) > 0) {
						tmp = prArr[i];
						prArr[i] = prArr[floatValue];
						prArr[floatValue] = tmp;
					}
				}
			}
			outputDataInTableForm(prArr, bufSize);
			break;
		}
		case 2: {
			int k = 0;
			Products tmp;

			for (int i = 0; i < bufSize - 1; i++) {
				for (int floatValue = i; floatValue < bufSize; floatValue++) {
					if (prArr[i].cost < prArr[floatValue].cost) {
						tmp = prArr[i];
						prArr[i] = prArr[floatValue];
						prArr[floatValue] = tmp;
					}
				}
			}
			outputDataInTableForm(prArr, bufSize);
			break;
		}
		case 3: {
			int k = 0;
			Products tmp;

			for (int i = 0; i < bufSize - 1; i++) {
				for (int floatValue = i; floatValue < bufSize; floatValue++) {
					if (prArr[i].count < prArr[floatValue].count) {
						tmp = prArr[i];
						prArr[i] = prArr[floatValue];
						prArr[floatValue] = tmp;
					}
				}
			}
			outputDataInTableForm(prArr, bufSize);
			break;
		}
		case 4: {
			breakCycle++;
			break;
		}
		default: {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		}
	}

	return 1;
}

float Customer::getCash() {
	return cash;
}

void Customer::setCash(float someCash) {
	cash += someCash;
}

int Customer::viewProductsUnderCash() {
	Products *prArr = readStructFromFile(),
			 *outArr;

	if (prArr == NULL) {
		return 0;
	}

	int bufSize = returnNumOfStructures(),
		counter=0;

	for (int i = 0; i < bufSize; i++) {
		if (prArr[i].cost <= cash) {
			counter++;
		}
	}

	if (counter == 0) return -1;

	outArr = new Products[counter];
	counter = 0;

	for (int i = 0; i < bufSize; i++) {
		if (prArr[i].cost <= cash) {
			outArr[counter] = prArr[i];
			counter++;
		}
	}

	outputDataInTableForm(outArr, counter);
	return 1;
	
}

void Customer::addCashToShop(float sum) {
	shopCash += sum;
}

#pragma optimize("", off)
int Customer::buySomeProduct(){
	Products *prArr = readStructFromFile(),
		     *outArr;

	if (prArr == NULL) {
		return 0;
	}

	int bufSize = returnNumOfStructures(),
		counter = 0,
		buyId,
		trueCounter = 0,
		numToBuy,
		tmp;

	while (true) {
		system("cls");
		cout << setw(127) << setfill('-') << "" << setfill(' ') << endl;
		cout << "| номер"<< "|" << setw(15) << "Тип инструмента" << "|" << setw(20) << "Имя инструмента" << "|" << setw(15) << "Материал" << "|" << setw(18) << "Дата производства" << "|" << setw(20) << "Страна" << "|" << setw(7) << " Стоимость $" << "|" << setw(12) << "Количество" << "|" << endl;
		cout << setw(127) << setfill('-') << "" << setfill(' ') << endl;
		for (int i = 0; i < bufSize; i++) {
			cout << "| " << setw(5) << i+1 << "|" << setw(15) << prArr[i].characteristics.instrumentName << "|" << setw(20) << prArr[i].characteristics.instrumentType << "|" << setw(15) << prArr[i].characteristics.material << "|" << setw(18) << prArr[i].characteristics.makingDate << "|" << setw(20) << prArr[i].country << "|" << setw(12) << prArr[i].cost << "|" << setw(12) << prArr[i].count << "|" << endl;
			cout << setw(127) << setfill('-') << "" << setfill(' ') << endl;
		}

		cout << "Введите номер товара, который вы желаете купить: ";

		if (!(cin >> buyId)) {
			system("cls");
			cout << "Invalid input\n\nPress any key to try again" << endl;
			cin.clear();
			while (getchar() != '\n');
			_getch();
			system("cls");
			continue;
		}
		cout << endl;
		
		buyId -= 1;

		if (buyId<0 || buyId>bufSize) {
			system("cls");
			cout << "Invalid input\n\nPress any key to try again" << endl;
			_getch();
			system("cls");
			continue;
		}

		cout << "Введите количество товарорв для покупки" << endl;

		if (!(cin >> numToBuy)) {
			system("cls");
			cout << "Ошибка ввода\n\nнажмите любую кнопку для продолжения" << endl;
			cin.clear();
			while (getchar() != '\n');
			_getch();
			system("cls");
			continue;
		}

		if (numToBuy<0 || numToBuy>prArr[buyId].count) {
			int switchValue;
			system("cls");
			cout << "Стольки товаров нет на складе или вы ввели некорректное значение\n\n";
			while (true) {
				cout << "Что вы хотите делать дальше :\n1.Вернуться в меню покупателя\n2.Купить что-нибудь еще" << endl;

				if (!(cin >> switchValue)) {
					system("cls");
					cout << "Ошибка ввода\n\nнажмите любую кнопку для продолжения" << endl;
					cin.clear();
					while (getchar() != '\n');
					_getch();
					system("cls");
					continue;
				}

				switch (switchValue) {
				case 1: {
					switchValue = 0;
					break;
				}
				case 2: {
					switchValue = 1;
					break;
				}
				default: {
					system("cls");
					cout << "Invalid input\n\nPress any key to try again" << endl;
					_getch();
					system("cls");
					continue;
				}
				}
				if (!switchValue) {
					system("cls");
					return -2;
				}
				else break;
			}
			continue;
		}

		if (cash < prArr[buyId].cost * numToBuy) {
			int switchValue;
			system("cls");
			cout << "Этот товар вам не по карману\n\n";
			while (true) {
				cout << "Что вы хотите делать дальше :\n1.Вернуться в меню покупателя\n2.Купить что-нибудь еще" << endl;
				
				if (!(cin >> switchValue)) {
					system("cls");
					cout << "Ошибка ввода\n\nнажмите любую кнопку для продолжения" << endl;
					cin.clear();
					while (getchar() != '\n');
					_getch();
					system("cls");
					continue;
				}

				switch (switchValue) {
				case 1: {
					switchValue = 0;
					break;
				}
				case 2: {
					switchValue = 1;
					break;
				}
				default: {
					system("cls");
					cout << "Invalid input\n\nPress any key to try again" << endl;
					_getch();
					system("cls");
					continue;
				}
				}
				if (!switchValue) {
					system("cls");
					return -2;
				}
				else break;
			}
			continue;
		}
		break;
	}
	cash -= prArr[buyId].cost * numToBuy;
	addCashToShop(prArr[buyId].cost * numToBuy);

	if (prArr[buyId].count == numToBuy) {
		outArr = new Products[bufSize - 1];
		for (int i = 0; i < bufSize; i++) {
			if (i != buyId) {
				outArr[counter] = prArr[i];
				counter++;
			}
			else {
				for (int k = 0; k < buyingArr.size(); k++) {
					if (strcmp((char*)&buyingArr[k].characteristics.instrumentName, (char*)&prArr[i].characteristics.instrumentName) == 0 && strcmp((char*)&buyingArr[k].characteristics.instrumentType, (char*)&prArr[i].characteristics.instrumentType) == 0 && strcmp((char*)&buyingArr[k].characteristics.makingDate, (char*)&prArr[i].characteristics.makingDate) == 0 && strcmp((char*)&buyingArr[k].characteristics.material, (char*)&prArr[i].characteristics.material) == 0 && strcmp((char*)&buyingArr[k].country, (char*)&prArr[i].country) == 0 && buyingArr[k].cost == prArr[i].cost) {
						buyingArr[k].count += prArr[i].count;
						trueCounter++;
					}
				}
				if (trueCounter == 0) buyingArr.insert(buyingArr.end(), prArr[i]);
			}
		}
	}
	else {
		prArr[buyId].count-=numToBuy;
		outArr = new Products[bufSize];
		for (int i = 0; i < bufSize; i++) {
			if (i != buyId) {
				outArr[counter] = prArr[i];
				counter++;
			}
			else {
				outArr[counter] = prArr[i];
				for (int k = 0; k < buyingArr.size(); k++) {
					if (strcmp((char*)&buyingArr[k].characteristics.instrumentName, (char*)&outArr[i].characteristics.instrumentName) == 0 && strcmp((char*)&buyingArr[k].characteristics.instrumentType, (char*)&outArr[i].characteristics.instrumentType) == 0 && strcmp((char*)&buyingArr[k].characteristics.makingDate, (char*)&outArr[i].characteristics.makingDate) == 0 && strcmp((char*)&buyingArr[k].characteristics.material, (char*)&outArr[i].characteristics.material) == 0 && strcmp((char*)&buyingArr[k].country, (char*)&outArr[i].country) == 0 && buyingArr[k].cost == outArr[i].cost) {
						buyingArr[k].count += numToBuy;
						trueCounter++;
					}
				}
				if (trueCounter == 0) {
					tmp = outArr[i].count;
					outArr[i].count = numToBuy;
					buyingArr.insert(buyingArr.end(), outArr[i]);
					outArr[i].count = tmp;
				}
				counter++;
			}
		}
	}

	

	rewriteData(outArr, counter);

	return 1;
}
#pragma optimize("", on)

int Customer::showBuyingList() {

	int size = buyingArr.size();

	if (size == 0) return 0;
	Products *arrToOutput = new Products[size];

	for (int i = 0; i < size; i++) 	arrToOutput[i] = buyingArr[i];

	outputDataInTableForm(arrToOutput, size);
	return 1;
}

void Customer::service() {
	int switchCount,
		breakCycle = 0;
	while (breakCycle==0) {
		cout << "\tМеню Покупателя\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n1.Добавить сумму\n2.Проверить баланс\n3.Посмотреть товары\n4.Поиск по товарам\n5.Фильтрация товаров по цене\n6.Сортировка\n7.Просмотр товаров по карману\n8.Купить товар\n9.Просмотр приобретенных товаров\n10.Выход\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

		if (!(cin >> switchCount)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			continue;
		}

		switch (switchCount)
		{
		case 1: {
			system("cls");

			float moneyToAdd;

			while (true) {

				cout << "Введите количество денег, которые вы хотите добавить: $";

				if (!(cin >> moneyToAdd)) {
					system("cls");
					cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
					_getch();
					system("cls");
					cin.clear();
					while (getchar() != '\n');
					continue;
				}

				if (moneyToAdd < 0) {
					system("cls");
					cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
					_getch();
					system("cls");
					continue;
				}

				else {
					system("cls");
					cout << "Деньги успешно добавлены\n\nНажмите любую кнопку для продолжения" << endl;
					_getch();
					system("cls");
					setCash(moneyToAdd);
					break;
				}
			}
			break;
		}
		case 2: {
			system("cls");
			cout << "Ваш баланс: $" <<  getCash() << endl;
			cout << "\nНажмите на любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		case 3: {
			Products *array = readStructFromFile();
			int arrayBuf = returnNumOfStructures();
			if (outputDataInTableForm(array, arrayBuf) != 0) {
				system("cls");
				cout << "Товаров на складе нет\n\nнажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 4: {
			if (!searchProduct()) {
				system("cls");
				cout << "Товаров на складе нет\n\nнажмите на любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 5: {
			int result = filtrateProductsAtCost();
			if (result == 0) {
				system("cls");
				cout << "Товаров на складе нет\n\nНажмите на любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			
			if (result == -1) {
				system("cls");
				cout << "Can't search such data\n\nPress any key to continue" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 6: {
			system("cls");
			if (!sortProducts()) {
				system("cls");
				cout << "Товаров на складе нет\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			system("cls");
			break;
		}
		case 7: {
			int result = viewProductsUnderCash();
			if (result == 0) {
				system("cls");
				cout << "Товаров на складе нет\n\nНажмите на любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			if (result == -1) {
				system("cls");
				cout << "Нет товаров вам по карману, не расстраивайтесь и приходите в другой раз =)" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 8: {
			int result = buySomeProduct();
			if (result == 1) {
				system("cls");
				cout << "Спасибо за покупку.\n\nНажмите на любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			else {
				system("cls");
				cout << "Товаров на складе нет.\n\nНажмите на любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 9: {
			if (!showBuyingList()) {
				system("cls");
				cout << "Пока вы ничего не купили =(\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 10: {
			system("cls");
			breakCycle++;
			break;
		}
		default: {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		}
	}

}

int Administration::viewAccounts(string filename) {
	ifstream readAccaounts(filename);
	string fieldData;
	int spaceSeen = 0,
		loginFilling = 0,
		passwordFilling = 0,
		counter = 1;
	char log[30],
		 pass[30];

	while (getline(readAccaounts, fieldData)) {
		for (unsigned int i = 0; i < fieldData.length(); i++) {
			if (fieldData[i] == ' ') {
				spaceSeen++;
				continue;
			}
			if (spaceSeen == 0) {
				log[loginFilling] = fieldData[i];
				loginFilling++;
			}
			else {
				pass[passwordFilling] = fieldData[i];
				passwordFilling++;
			}
		}
		log[loginFilling] = '\0';
		pass[passwordFilling] = '\0';
		spaceSeen = 0;
		loginFilling = 0,
		passwordFilling = 0;
		Administration somePersonal(log, pass);
		somePersonal.codePassword();
		cout << counter << ". Логин: " << somePersonal.getLogin() << " Пароль: " << somePersonal.getPassword() << endl;
		counter++;
	}
	readAccaounts.close();
	return counter;
}

int Administration::deleteAccount(string fname) {
	int counter = viewAccounts(fname) - 1,
		placeholder,
		startPoint = 0;
	string dataField;

	if (counter == 0) return 0;

	cout << "Выберите аккаунт для удаления" << endl;

	while (1) {

		if (!(cin >> placeholder)) {
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			cout << "Invalid input\n\nPress any key to continue" << endl;
			_getch();
			system("cls");
			continue;
		}

		if (placeholder<0 || placeholder>counter) {
			system("cls");
			cout << "Invalid input\n\nPress any key to continue" << endl;
			_getch();
			system("cls");
			continue;
		}

		break;
	}

	placeholder--;

	ifstream readFromFile(fname);
	ofstream writeToFile("tmp.bin");

	while (getline(readFromFile, dataField)) {
		if(startPoint!=placeholder) writeToFile << dataField << endl;
		startPoint++;
	}

	system("cls");
	cout << "Аккаунт успешно удален\n\nНажмите любую кнопку для продолжения" << endl;
	_getch();
	system("cls");

	readFromFile.close();
	writeToFile.close();

	remove((char*)&fname);
	rename("tmp.bin", (char*)&fname);

	return 1;
}

int Administration::editAccounts(string fname) {

	int counter = viewAccounts(fname) - 1,
		placeholder,
		startPoint = 0,
		errFlag = 0;
	char log[30],
	     pass[30];	
	string fieldData;

	if (counter == 0) return 0;

	cout << "\nВыберите аккаунт для редактирования: ";

	while (1) {

		if (!(cin >> placeholder)) {
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			cout << "Invalid input\n\nPress any key to continue" << endl;
			_getch();
			system("cls");
			continue;
		}

		if (placeholder<0 || placeholder>counter) {
			system("cls");
			cout << "Invalid input\n\nPress any key to continue" << endl;
			_getch();
			system("cls");
			continue;
		}

		break;
	}
	
	system("cls");
	placeholder--;

	ifstream readFromFile(fname);
	ofstream writeToFile("tmp.bin");
	while (getline(readFromFile, fieldData) && startPoint<counter) {
		if (startPoint != placeholder) writeToFile << fieldData << endl;
		else {
			while (1) {
				cout << "Введите новый логин: ";
				cin >> log;
				cout << endl;
				cout << "Введите новый пароль: ";
				cin >> pass;
				cout << endl;
				ifstream readFromFile(fname, ios_base::in);
				string dataField, loginToFind;

				loginToFind = log;
				
				int cycleIteration = 0;
				char l[30];

				while (readFromFile >> l) {
					if (strcmp(l, log)==0 && cycleIteration != placeholder) {
						system("cls");
						cout << "Этот аккаунт уже зарегистрирован\n\nНажмите на любую кнопку для продолжения" << endl;
						_getch();
						system("cls");
						readFromFile.close();
						errFlag++;
					} 
					cycleIteration++;
					getline(readFromFile, fieldData);
				}

				Administration somePersonal(log, pass);
				somePersonal.codePassword();

				if (errFlag != 0) {
					errFlag = 0;
					continue;
				} 
				readFromFile.close();
				writeToFile << somePersonal.getLogin() << ' ' << somePersonal.getPassword()<< endl;
				system("cls");
				cout << "Аккаунт успешно отредактирован\n\nНажмите на любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
				break;
			}
		}
		startPoint++;
	}
	writeToFile.close();
	readFromFile.close();
	remove((char*)&fname);
	rename("tmp.bin", (char*)&fname);
	return 1;
}

Administration::Administration() {
	login[0] = NULL;
	password[0] = NULL;
}

Administration::Administration(char * log, char * pass) {

	int i = 0;

	for (i; log[i]; i++) {
		login[i] = log[i];
	}

	login[i] = '\0';
	i = 0;

	for (i; pass[i]; i++) {
		password[i] = pass[i];
	}

	password[i] = '\0';

}

int Administration::deleteProducts() {
	Products *prArr = readStructFromFile(),
		*outArr;
	if (prArr == NULL) {
		return 0;
	}

	int bufSize = returnNumOfStructures(),
		counter = 0,
		buyId;

	while (true) {
		system("cls");
		cout << setw(127) << setfill('-') << "" << setfill(' ') << endl;
		cout << "|Номер " << "|" << setw(15) << "Тип инструмента" << "|" << setw(20) << "Имя инструмента" << "|" << setw(15) << "Материал" << "|" << setw(18) << "Дата производства" << "|" << setw(20) << "Страна" << "|" << setw(12) << "Цена $" << "|" << setw(12) << "Количество" << "|" << endl;
		cout << setw(127) << setfill('-') << "" << setfill(' ') << endl;
		for (int i = 0; i < bufSize; i++) {
			cout << "| " << setw(5) << i + 1 << "|" << setw(15) << prArr[i].characteristics.instrumentName << "|" << setw(20) << prArr[i].characteristics.instrumentType << "|" << setw(15) << prArr[i].characteristics.material << "|" << setw(18) << prArr[i].characteristics.makingDate << "|" << setw(20) << prArr[i].country << "|" << setw(12) << prArr[i].cost << "|" << setw(12) << prArr[i].count << "|" << endl;
			cout << setw(127) << setfill('-') << "" << setfill(' ') << endl;
		}

		cout << "Введите номер товара для удаления: ";

		if (!(cin >> buyId)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			cin.clear();
			while (getchar() != '\n');
			_getch();
			system("cls");
			continue;
		}
		cout << endl;

		buyId -= 1;

		if (buyId<0 || buyId>bufSize) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			continue;
		}

		outArr = new Products[bufSize - 1];
		for (int i = 0; i < bufSize; i++) {
			if (i != buyId) {
				outArr[counter] = prArr[i];
				counter++;
			}
		}

		rewriteData(outArr, counter);

		return 1;
	}
}

#pragma optimize("", off)
int Administration::findLoginAtFile(string fname, char *log) {
	ifstream readFromFile(fname, ios_base::in);
	char l[30];
	string someStr;

	while (readFromFile >> l) {
		if (strcmp(l, log) == 0) return 1;
		getline(readFromFile, someStr);
	}
	readFromFile.close();
	return 0;
}
#pragma optimize("", on)

int Administration::findAtFile() {
	ifstream readFromFile("Personal.bin", ios_base::in);
	string fieldData;
	int spaceSeen = 0,
		loginFilling = 0,
		passwordFilling = 0,
		counter = 1,
		isFind = 0;
	char log[30],
		pass[30];

	while (getline(readFromFile, fieldData)) {
		for (unsigned int i = 0; i < fieldData.length(); i++) {
			if (fieldData[i] == ' ') {
				spaceSeen++;
				continue;
			}
			if (spaceSeen == 0) {
				log[loginFilling] = fieldData[i];
				loginFilling++;
			}
			else {
				pass[passwordFilling] = fieldData[i];
				passwordFilling++;
			}
		}
		log[loginFilling] = '\0';
		pass[passwordFilling] = '\0';
		spaceSeen = 0;
		loginFilling = 0,
		passwordFilling = 0;
		Administration somePersonal(log, pass);
		somePersonal.codePassword();
		if (strcmp(password,somePersonal.getPassword()) == 0 && strcmp(login, somePersonal.getLogin()) == 0) {
			isFind++;
			break;
		}
		counter++;
	}
	readFromFile.close();
	return isFind;
}

void Administration::addProductToFile() {
	ofstream out("PRODUCT_DATA.DAT", ios::app);
	Products someProduct;
	cout << "Введите имя музыкального инструмента: ";
	cin >> someProduct.characteristics.instrumentName;
	cout << endl;
	cout << "Введите тип музыкального инструмента: ";
	cin >> someProduct.characteristics.instrumentType;
	cout << endl;
	cout << "Введите материал музыкального инструмента: ";
	cin >> someProduct.characteristics.material;
	cout << endl;
	cout << "Введите дату производства музыкального инструмента: ";
	cin >> someProduct.characteristics.makingDate;
	cout << endl;
	cout << "Введите страну производства музыкального инструмента: ";
	cin >> someProduct.country;
	cout << endl;
	cout << "Введите цену музыкального инструмента: $";
	cin >> someProduct.cost;
	someProduct.cost = costForClient(someProduct.cost, 0.2);
	cout << endl;
	cout << "Введите количество музыкальных инструментов: ";
	cin >> someProduct.count;
	cout << endl;
	out.write((char*)&someProduct, sizeof(Products));
	system("cls");
	cout << "Товар успешно добавлен на склад\n\nНажмите любую кнопку для продолжения" << endl;
	_getch();
	system("cls");
}

int Administration::addAccountToFile(char *log, char *pass, string fname) {

	if (findLoginAtFile(fname, log)) return 0;
	ofstream addFile(fname, ios::app);
	Administration somePersonal(log, pass);
	somePersonal.codePassword();
	addFile << somePersonal.getLogin() << " " << somePersonal.getPassword()<< endl;
	addFile.close();
	return 1;
}

float Administration::getShopCash() {
	return shopCash;
}

void Administration::workWithAccounts() {
	int switchCount,
		breakCycle = 0;

	system("cls");

	while (breakCycle == 0) {

		cout << "\tРабота с аккаунтами:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n1.Добавление нового аккаунта покупателя\n2.Редактирование аккаунта покупателя\n3.Удаление аккаунта покупателя\n4.Посмотреть данные покупателей\n5.Добавление нового администратора\n6.Удаление аккаунта администратора\n7.Редактирования аккаунтов администратора\n8.Посмотреть данные администратора\n9.Вернуться в предыдущее меню\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

		if (!(cin >> switchCount)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			continue;
		}

		system("cls");

		switch (switchCount) {
		case 1: {
			system("cls");
			char log[30], pass[30];
			cout << "Введите логин: ";
			cin >> log;
			cout << endl;
			cout << "Введите пароль: ";
			cin >> pass;
			cout << endl;
			if (addAccountToFile(log, pass, "Customers.bin")) {
				system("cls");
				cout << "Покупатель успешно добавлен\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			else {
				system("cls");
				cout << "Такой аккаунт уже существует\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 2: {
			system("cls");
			if (!editAccounts("Customers.bin")) {
				system("cls");
				cout << "Аккаунтов не найдено\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 3: {
			system("cls");
			if (!deleteAccount("Customers.bin")) {
				system("cls");
				cout << "Аккаунтов не найдено\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 4: {
			system("cls");
			int returnValue = viewAccounts("Customers.bin") - 1;
			if (returnValue == 0) {
				system("cls");
				cout << "Аккаунтов не найдено\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
				break;
			}
			cout << "\n\n Нажмите на любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		case 5: {
			system("cls");
			char log[30], pass[30];
			cout << "Введите логин: ";
			cin >> log;
			cout << endl;
			cout << "Введите пароль: ";
			cin >> pass;
			cout << endl;
			if (addAccountToFile(log, pass, "Personal.bin")) {
				system("cls");
				cout << "Покупатель успешно добавлен\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			else {
				system("cls");
				cout << "Такой аккаунт уже существует\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 6: {
			system("cls");
			if (!deleteAccount("Personal.bin")) {
				system("cls");
				cout << "Аккаунтов не найдено\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 7: {
			system("cls");
			if (!editAccounts("Personal.bin")) {
				system("cls");
				cout << "Аккаунтов не найдено\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 8: {
			system("cls");
			int returnValue = viewAccounts("Personal.bin") - 1;
			if (returnValue == 0) {
				system("cls");
				cout << "Аккаунтов не найдено\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
				break;
			}
			cout << "\n\n Нажмите на любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		case 9: {
			breakCycle++;
			break;
		}
		default: {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		}
	}
}

void Administration::workWithProducts() {
	int switchCount,
		breakCycle = 0;

	system("cls");

	while (breakCycle == 0) {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nРабота с товарами\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n1.Заказ товаров на склад\n2.Удаление товаров со склада\n3.Поиск товара на складе\n4.Фильтрация товаров по цене\n5.Сортировка товаров\n6.Просмотр товаров со склада\n7.Выход в предыдущее меню\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

		if (!(cin >> switchCount)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			continue;
		}

		system("cls");

		switch (switchCount) {
		case 1: {
			system("cls");
			addProductToFile();
			break;
		}
		case 2: {
			system("cls");
			if (!deleteProducts()) {
				system("cls");
				cout << "Товары не были найдены\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			else {
				system("cls");
				cout << "Товары был успешно удален со склада\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			system("cls");
			break;
		}
		case 3: {
			system("cls");
			if (!searchProduct()) {
				system("cls");
				cout << "Товары не были найдены\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 4: {
			system("cls");
			if (!filtrateProductsAtCost()) {
				system("cls");
				cout << "Товары не были найдены\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 5: {
			system("cls");
			if (!sortProducts()) {
				system("cls");
				cout << "Товары не были найдены\n\nНажмите любую кнопку для продолжения" << endl;
				_getch();
				system("cls");
			}
			break;
		}
		case 6: {
			system("cls");
			outputDataInTableForm(readStructFromFile(), returnNumOfStructures());
			break;
		}
		case 7: {
			breakCycle++;
			break;
		}
		}
	}
}

void Administration::service() {
	int switchCount,
		breakCycle = 0;
	while (breakCycle == 0) {
		cout << "\t Меню администрации магазина\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n1.Работа с аккаунтами\n2.Работа с товарами\n3.Выручка магазина\n4.Выход\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

		if (!(cin >> switchCount)) {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			cin.clear();
			while (getchar() != '\n');
			continue;
		}

		switch (switchCount) {
		case 1: {
			workWithAccounts();
			break;
		}
		case 2: {
			workWithProducts();
			break;
		}
		case 3: {
			system("cls");
			cout << "Выручка магазина: $" << getShopCash() << "\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		case 4: {
			system("cls");
			breakCycle++;
			break;
		}
		default: {
			system("cls");
			cout << "ОШИБКА: Некорректный ввод\n\nНажмите любую кнопку для продолжения" << endl;
			_getch();
			system("cls");
			break;
		}
		}
	}
}

