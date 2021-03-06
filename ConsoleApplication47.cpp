// ConsoleApplication47.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include<fstream>
#include <string>

using namespace std;

template<class T>
T vvod() {
	for (;;) {
		try {
			T n = NULL;
			if (!(cin >> n)) throw 1;
			return n;
		}
		catch (int) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка! Введено не целое число!" << endl;
		}
	}
}

template<class T>
T vvod(T i, T j) {
	for (;;) {
		try {
			T n = vvod <int>();
			if (n < i || n > j) throw 1.5;
			return n;
		}
		catch (double) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка! Число должно быть в диапозоне от " << i << " до " << j << endl;
		}
	}
}

class Products {
private:
	char Name[100];
	int Count;
	int Number;
public:
	Products() {};
	void in(char NAME[100], int COUNT, int NUMBER);
	friend ostream& operator<< (ostream &out, const Products &prod);
	bool operator <(Products &prod);
	bool operator >(Products &prod);
	void operator =(Products &prod);
	bool operator ==(char* &gr);
	char* getName();
	int getCount();
	int getNumber();;
};

void Products::in(char NAME[100], int COUNT, int NUMBER)
{
	strcpy_s(this->Name, NAME);
	this->Count = COUNT;
	this->Number = NUMBER;
}
char* Products::getName() 
{
	return Name;
}

int Products::getCount() 
{
	return Count;
}

int Products::getNumber() 
{
	return Number;
}

bool Products::operator<(Products &pr) 
{
	char f[100];
	strcpy_s(f, pr.getName());
	if ((int)Name[0] < (int)f[0])
		return true;
	else return false;
}

bool Products::operator>(Products &pr) 
{
	char f[100];
	strcpy_s(f, pr.getName());
	if ((int)Name[0] > (int)f[0])
		return true;
	else return false;
}

void Products::operator=(Products &pr) 
{
	strcpy_s(this->Name, pr.getName());
	this->Count = pr.getCount();
	this->Number = pr.getNumber();
}

bool Products::operator==(char* &gr)
{
	if (strcmp(Name, gr) == 0)
		return true;
	else return false;
}

ostream& operator<< (ostream &out, const Products &prod)
{
	out << "Наименование:" << endl;
	out << prod.Name << endl;
	out << "Количество:" << endl;
	out << prod.Count << endl;
	out << "Номер цеха:" << endl;
	out << prod.Number << " ";
	return out;
}

template<class T>
class vector {
	template<class T>
	friend class vect_iterator;
	template<class T>
	friend class rev_iterator;
	int size;
public:
	T * vect;
	vector()
	{
		size = 0;
		vect = NULL;
	}
	vector(int n);
	int getSize();
	void setSize(int s) { size = s; }
	~vector();
};

template<class T>
vector<T>::vector(int n) {
	size = n;
	try {
		vect = new T[n];
	}
	catch (bad_alloc& ba)
	{
		cerr << ba.what() << endl;
	}
}

template<class T>
int vector<T>::getSize() {
	return size;
}

template<class T>
vector<T>::~vector() {

	delete[]vect;
}

// шаблон класса vect_iterator
template <class T>
class vect_iterator
{
	vector<T> *pv;
	int ind; // текущий индекс в массиве
public:
	vect_iterator(vector<T>  &v)
	{
		ind = 0;
		pv = &v;
	}
	vect_iterator()
	{
		ind = 0;
		pv = NULL;
	}
	T& operator *();
	T& operator [](int i);
	int begin();
	int end();
	void setSize(int s) { pv->setSize(s); }
};

template <class T>
T& vect_iterator<T>::operator *()
{
	if (ind >= pv->size)
		return pv->vect[(ind = 0)++];
	else
		return pv->vect[ind++];
}

template <class T>
T& vect_iterator<T>::operator [](int i)
{
	if (i >= pv->size)
	{
		cout << "Выход за пределы массива. Возвращается первый элемент." << endl;
		return pv->vect[0];
	}
	else
		return pv->vect[i];
}

template <class T>
int vect_iterator<T>::begin()
{
	return 0;
}

template <class T>
int vect_iterator<T>::end()
{
	return pv->getSize() - 1;
}

// шаблон класса rev_iterator
template <class T>
class rev_iterator
{
	vector<T> *pv;
	int ind; // текущий индекс в массиве
public:
	rev_iterator(vector<T>  &v)
	{
		pv = &v;
		ind = pv->size - 1;
	}
	rev_iterator()
	{
		ind = 0;
		pv = NULL;
	}
	T& operator *();
	int end();
};

template <class T>
T& rev_iterator<T>::operator *()
{
	if (ind == -1)
		return pv->vect[(ind = pv->size - 1)--];
	else
		return pv->vect[ind--];
}

template <class T>
int rev_iterator<T>::end()
{
	return pv->getSize() - 1;
}



class Algoritm
{
public:
	Algoritm();
	~Algoritm();
	//Алгоритм: быстрая сортировка
	template <class T>
	void quickSort(int left, int right, vect_iterator<T> &itr) {
		int l = left, r = right;
		T mid = itr[(r + l) / 2], help;
		while (l < r) {
			while (itr[l] < mid)
			{
				l++;
			}
			while (itr[r] > mid)
			{
				r--;
			}
			if (l <= r) {
				help = itr[l];
				itr[l] = itr[r];
				itr[r] = help;
				l++; r--;
			}
		}
		if (left < r)
			quickSort(left, r, itr);
		if (l < right)
			quickSort(l, right, itr);
	}

	//Алгоритм: функция нахождения первого элемента, который
	//удовлетворяет заданным критериям.
	template <class T>
	T& find(vect_iterator<T> &itr, char* group) {
		for (int i = 0; i <= itr.end(); i++) {
			if (itr[i] == group)
			{
				return itr[i];
			}
		}
		throw 1;
	}

	//Алгоритм: функция, которая удаляет элементы,
	//удовлетворяющие условию.
	template <class T>
	void del(vect_iterator<T> &itr, char* group) {
		for (int i = 0; i <= itr.end(); i++) {
			if (itr[i] == group)
			{
				for (int j = i; j < itr.end(); j++) {
					itr[j] = itr[j + 1];
				}
				itr.setSize(itr.end());
			}
		}
	}
};

Algoritm::Algoritm()
{
}

Algoritm::~Algoritm()
{
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество Продукции:" << endl;
	int n = vvod<int>();
	vector <Products> a(n);
	vect_iterator <Products> itr(a);
	rev_iterator <Products> r_itr(a);
	Algoritm al;
	char Name[100];
	int Count;
	int Number;
	for (int i = 0; i < n; i++) {
		cout << "Введите наименование: " << endl;
		cin.ignore();
		cin.getline(Name, 100);
		cout << "Введите количество: " << endl;
		Count = vvod<int>();
		cout << "Введите номер цеха: " << endl;
		Number = vvod<int>();
		a.vect[i].in(Name, Count, Number);
	}
	int ch = 0;
	while (ch != 7)
	{
		cout << "1. Вывести список продукции" << endl;
		cout << "2. Вывести список продукции в обратном порядке" << endl;
		cout << "3. Сортировать список продукции" << endl;
		cout << "4. Просмотреть информацию о продукции" << endl;
		cout << "5. Найти продукцию" << endl;
		cout << "6. Удалить продукцию" << endl;
		cout << "7. Выход" << endl;
		cout << "Выбор меню:" << endl;
		ch = vvod<int>(1, 7);
		switch (ch)
		{
		case 1:
		{
			for (int i = 0; i <= itr.end(); i++) {
				cout << *itr << endl;
			}
		}
		break;
		case 2:
		{
			for (int i = 0; i <= r_itr.end(); i++) {
				cout << *r_itr << endl;
			}
		}
		break;
		case 3:
		{
			al.quickSort(0, a.getSize() - 1, itr);
			cout << "   Отсортировано!" << endl;
		}
		break;
		case 4:
		{
			cout << "Введите порядковый номер продукции:" << endl;
			int num = vvod<int>() - 1;
			cout << itr[num] << endl;
		}
		break;
		case 5:
		{
			cout << "  Демонстракия алгоритма find. Поиск Продукцию по наименованию" << endl;
			try
			{
				cout << "Введите наименование: " << endl;
				cin.ignore();
				cin.getline(Name, 100);
				cout << al.find(itr, Name) << endl;
			}
			catch (int)
			{
				cout << "Совпадений не найдено" << endl;
			}
		}
		case 6:
		{
			cout << "  Демонстракия алгоритма del. Удаление продукции по наименованию" << endl;
			cout << "Введите наименование: " << endl;
			cin.ignore();
			cin.getline(Name, 100);
			al.del(itr, Name);
			cout << "  Сделано!" << endl;
		}
		case 7:
			break;
		default:
			cout << "Неккоректный ввод" << endl;
			break;
		}
	}
	return 0;
}
