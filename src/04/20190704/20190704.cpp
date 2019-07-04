// 20190704.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class Car
{
	std::string name;
	string color;


};

int add(int a, int b) {
	return a + b;
}

double add(double a, double b) {
	return a + b;
}

class CShape
{
public:
	void printName() {
		std::cout << "Shape" << std::endl;
	}

	virtual void printRealName() {
		std::cout << "Shape" << std::endl;
	}
};

class CRect : public CShape
{
public:
	void printName() {
		std::cout << "CRect" << std::endl;
	}

	virtual void printRealName() {
		std::cout << "CRect" << std::endl;
	}
};

class CTriangle : public CShape
{
public:
	void printName() {
		std::cout << "CTriangle" << std::endl;
	}

	virtual void printRealName() {
		std::cout << "CTriangle" << std::endl;
	}
};

int main()
{
	CShape s;
	CRect r;
	CTriangle t;

	//s.printName();
	//s.printRealName();

	//r.printName();
	//r.printRealName();

	//t.printName();
	//t.printRealName();

	CShape* pSs[3] = { &s, &r, &t };

	for(CShape* pS : pSs)
	{
		pS->printName();
		pS->printRealName();
	}
}