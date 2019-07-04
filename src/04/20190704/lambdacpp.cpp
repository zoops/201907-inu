// moLambdaT.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "pch.h"
#include <iostream>
#include <functional>

void testLambda();
void testFunctor();

int main() {
	// �Լ������� ���� 
	// 1. ���¸� ���� �� ����. 
	// 2. ���� ����ȭ�� �� �� ����. 

	testLambda();
	std::cout << "==============" << std::endl;
	testFunctor();

	return 0;
}

void exe(std::function<void(void)> fnLambda) {
	fnLambda();
}

void testLambda() {
	std::cout << "lambda start" << std::endl;
	// �⺻���� : [capture](param) mutable throw() -> int { statements;}  // ���������Ѱ��� ������ �� �ִ�. [] �� {} �� �ȵ�

	int k = 1;
	int z = [](int x, int y) mutable throw() -> int { std::cout << "lambda basic" << std::endl; return x + y; }(10, 20);
	std::cout << z << std::endl;

	// functional 
	std::function<void(void)> fn = [] { std::cout << "lambda with functional" << std::endl; };
	exe(fn);

	// �߷� => ��� ��� ����. 
	auto fn2 = [] {std::cout << "lambda2 with auto" << std::endl; };
	exe(fn2);

	// �Լ� ������ - capture ������ �ȵ�.
	typedef void(*f_type)(void);
	f_type fn3 = []() { std::cout << "lambda2 with function pointer" << std::endl; };
	exe(fn3);

	// capture (closure �Լ�)
	// -[&]() { . . . } �ܺ��� ��� �������� ���۷����� �����´�. (�Լ��� Call - by - reference �� ����)
	// - [=]() { . . . } �ܺ��� ��� �������� ������ �����´�. (�Լ��� Call - by - value �� ����)
	// - [=, &x, &y] { . . . }, [&, x, y] { . . . } �ܺ��� ��� �������� �� / ���۷����� ��������, x �� y �� ���۷��� / ������ �����´�
	// - [x, &y, &z] { . . . } ������ �������� ������ �ٿ� ���� �����´�.

	int m = 0;
	int n = 0;

	auto fc = [&, n](int a) mutable { m = ++n + a;  std::cout << "inner : " << m << ", " << n << std::endl;  };
	fc(4);
	std::cout << m << ", " << n << std::endl;

	n = 10;
	[&](int a) { m = ++n + a; }(4);
	std::cout << m << ", " << n << std::endl;

	// n = 11 , m = 14
	int* p = &n;

	[&m, p](int a) { m = ++(*p) + a; ; }(4);
	std::cout << m << ", " << n << std::endl;
	// m = 16, n = 12

	// n == 2
	fc(4);
	std::cout << "!!!!!" << m << ", " << n << std::endl;

	std::function<int(int)> fact;
	fact = [&fact](int n)->int
	{
		if (n == 0) { return 1; }
		else { return (n *	fact(n - 1)); }
	};
	std::cout << "factorial(4) : " << fact(4) << std::endl;

	std::cout << "lambda end" << std::endl;

	// [capture����](�Ķ����)->����Ÿ��{ �Լ����� }

	// ����
	// 1. �ڵ尡 �������� �� �ִ�. 
	// 2. �Լ������ͳ� �Լ���üó�� �����ڵ带 ������ �Ҵ��ϰų� ������ȭ �ؼ� ���� �� �� �ִ�. (�ϱް�ü)
	// 3. ���� ����ȭ�� ��ȸ�� �ִ�. (�����Ϸ� ����ȭ(�ζ���), ���� �򰡿� ���� ����ȭ)
	// 4. Ŭ������ ���� ���¸� ������ �Լ��� ���� �� ����. 
}

class Functor {
	int m_n;
public:
	Functor(int n) { m_n = n; }
	void operator()() {
		std::cout << "Simple Functor" << std::endl;
	}
};

void exeFunctor(Functor fn) {
	fn();
}

void testFunctor() {
	std::cout << "functor start" << std::endl;

	Functor func(10);
	exeFunctor(func);

	// �Լ������ͷ� �ѱ�� �������� ��Ŀ��� object �� �ѱ�� ������ �����Ϸ��� ���� ����ȭ�� ������.  ���� ����(����) �� ������ �Լ��� ���ķ����� �� �� ����
	// �ڵ尡 �����. �̤� 

	std::cout << "functor end" << std::endl;
}

