// codeInterview-1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string reverseStr(string input) {
	std::reverse(input.begin(), input.end());
	return input;
}

char* strReverse(char* input) {
	char *ret = input;

	char *left = input;
	while (*input++);

	char tmp;
	input = input - 2;
	while (left < input) {
		tmp = *left;
		*left++ = *input;
		*input-- = tmp;
	}
	return ret;
}

void swap1(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void swap2(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	/*
    string input = "Hello world!"; 
	std::cout << input << endl;
	string output = reverseStr(input);
	std::cout << input << ", " << output << endl;

	char input2[] = "www.moberan.com";
	std::cout << input2 << endl;
	char* output2 = strReverse(input2);
	std::cout << input2 << ", " << output2 << endl;

	std::cout << endl;
	*/
	int a = 10;
	int b = 20;
	std::cout << a << ", " << b << endl;
	std::swap(a, b);
	std::cout << a << ", " << b << endl;
	swap1(a, b);
	std::cout << a << ", " << b << endl;
	swap2(&a, &b);
	std::cout << a << ", " << b << endl;

}

