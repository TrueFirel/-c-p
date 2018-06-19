#pragma once

#include <iostream>
#include <vector>

using namespace std;

class InstrumentCharacteristics {
public:
	string material,
		instrumentType,
		makingDate,
		instrumentName;
};

class Products {
public:
	InstrumentCharacteristics characteristics;
	string country;
	float cost;
	int count;
};

class Account {
protected:
	char login[30];
	char password[30];
	int key;
	static float shopCash;
public:
	virtual void authorization();
	Account();
	Account(char*, char*);
	Products * readStructFromFile();
	int returnNumOfStructures();
	int outputDataInTableForm(Products *, int);
	int searchProduct();
	int filtrateProductsAtCost();
	int sortProducts();
	virtual void service() = 0;
	void rewriteData(Products *, int size);
	virtual int findAtFile();
	void codePassword();
	char * getLogin();
	char * getPassword();
};

class Customer :public Account {
private:
	float cash;
	vector <Products> buyingArr;
	friend ostream &operator<<(ostream &, Customer &);
public:
	Customer();
	Customer &operator+=(int);
	float getCash();
	void setCash(float);
	void service();
	int showBuyingList();
	static void addCashToShop(float);
	int viewProductsUnderCash();
	int buySomeProduct();
};

class Administration :public Account {
private:
	friend ostream &operator<<(ostream &, Administration &);
public:
	Administration();
	Administration(char*, char*);
	int findAtFile();
	int editAccounts(string);
	int addAccountToFile(char*, char*, string);
	static float getShopCash();
	int viewAccounts(string);
	int deleteAccount(string);
	void service();
	void workWithAccounts();
	void workWithProducts();
	int deleteProducts();
	void addProductToFile();
	int findLoginAtFile(string, char*);
};
