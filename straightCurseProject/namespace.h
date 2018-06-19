#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace myNamespace {

	template <typename T>
	class MyStack
	{
	private:
		T *stackPtr; 
		int size; 
		T top; 
	public:
		MyStack(int = 10);
		~MyStack(); 
		int push(T);
		T pop();
		void printStack();
	};

	template <typename T>
	MyStack<T>::MyStack(int s)
	{
		if (size < 0) s = 10;
		stackPtr = new T[size]; 
		top = -1; 
	}

	template <typename T>
	MyStack<T>::~MyStack()
	{
		delete[] stackPtr;
	}

	template <typename T>
	int MyStack<T>::push(T value)
	{
		if (top == size - 1)
			return 0;

		top++;
		stackPtr[top] = value;

		return 1;
	}

	template <typename T>
	T MyStack<T>::pop()
	{
		if (top == -1)
			return 0; 

		T tmp = stackPtr[top];
		stackPtr[top] = 0;
		top--;

		return tmp;
	}

	template <typename T>
	void MyStack<T>::printStack()
	{
		for (int i = size - 1; i >= 0; i--)
			cout << stackPtr[i] << endl;
	}

	template <class T>
	T & costForClient(T shopCost, float persent) {
		shopCost += shopCost*persent;
		return shopCost;
	}
}