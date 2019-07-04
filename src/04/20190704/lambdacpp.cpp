// moLambdaT.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include <iostream>
#include <functional>

void testLambda();
void testFunctor();

int main() {
	// 함수포인터 단점 
	// 1. 상태를 가질 수 없다. 
	// 2. 성능 최적화를 할 수 없다. 

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
	// 기본문법 : [capture](param) mutable throw() -> int { statements;}  // 생략가능한것은 생략할 수 있다. [] 와 {} 은 안됨

	int k = 1;
	int z = [](int x, int y) mutable throw() -> int { std::cout << "lambda basic" << std::endl; return x + y; }(10, 20);
	std::cout << z << std::endl;

	// functional 
	std::function<void(void)> fn = [] { std::cout << "lambda with functional" << std::endl; };
	exe(fn);

	// 추론 => 재귀 사용 못함. 
	auto fn2 = [] {std::cout << "lambda2 with auto" << std::endl; };
	exe(fn2);

	// 함수 포인터 - capture 있으면 안됨.
	typedef void(*f_type)(void);
	f_type fn3 = []() { std::cout << "lambda2 with function pointer" << std::endl; };
	exe(fn3);

	// capture (closure 함수)
	// -[&]() { . . . } 외부의 모든 변수들을 레퍼런스로 가져온다. (함수의 Call - by - reference 를 생각)
	// - [=]() { . . . } 외부의 모든 변수들을 값으로 가져온다. (함수의 Call - by - value 를 생각)
	// - [=, &x, &y] { . . . }, [&, x, y] { . . . } 외부의 모든 변수들을 값 / 레퍼런스로 가져오되, x 와 y 만 레퍼런스 / 값으로 가져온다
	// - [x, &y, &z] { . . . } 지정한 변수들을 지정한 바에 따라 가져온다.

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

	// [capture변수](파라메터)->리턴타입{ 함수내용 }

	// 장점
	// 1. 코드가 간단해질 수 있다. 
	// 2. 함수포인터나 함수객체처럼 실행코드를 변수에 할당하거나 데이터화 해서 전달 할 수 있다. (일급객체)
	// 3. 성능 최적화의 기회가 있다. (컴파일러 최적화(인라인), 늦은 평가에 의한 최적화)
	// 4. 클로저에 의해 상태를 가지는 함수를 만들 수 있음. 
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

	// 함수포인터로 넘기는 고전적인 방식에서 object 을 넘기기 때문에 컴파일러에 의한 최적화가 가능함.  또한 상태(변수) 를 가지는 함수를 에뮬레이팅 할 수 있음
	// 코드가 길어짐. ㅜㅜ 

	std::cout << "functor end" << std::endl;
}

