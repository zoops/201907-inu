// 20190704-lambda.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void foreach2(vector<int>::iterator b, vector<int>::iterator e, function<void(int v)> f) {
	while (b != e)
	{
		f(*b);
		b++;
	}
}

int main()
{
	auto f = []()->void{ std::cout << "Hello World!\n" ; };
	f();

	vector<int> vecs = { 1, 2,3,4,5};
	for_each(vecs.begin(), vecs.end(), [](int v)->void {
		std::cout << v << endl;
	});
	int k = 10;

	foreach2(vecs.begin(), vecs.end(), [k](int v)->void {

		std::cout << k+v << endl;
	});
}