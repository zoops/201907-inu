// 20190408-01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <stack>

using namespace std;

template<typename T> void printVector(vector<T> vecs, int ppc = 4) {
	for (int i = 0; i < vecs.size(); i++) {
		std::cout << vecs[i] << ", ";
		if (i > 0 && (i % ppc) == 0)
			std::cout << endl;
	}
	std::cout << endl;
}

// 라면공장
int solution42629(int stock, vector<int> dates, vector<int> supplies, int k) {
    int answer = 0;
	int didx = 0;
	priority_queue< int, vector<int>, less<int> > pq;
	for (int i = 0; i < k; i++) {
		if (dates[didx] == i) pq.push(supplies[didx++]);
		
		if (stock == 0) {
            if (pq.size() > 0) {
			    stock += pq.top();	pq.pop();
			    answer++;
            }
		}
		if (stock > 0)
            stock--;
	}    
    return answer;
}

// 더맵게
int solution42626(vector<int> scoville, int K) {
    int answer = 0;
    
	priority_queue< int, vector<int>, greater<int> > pq;
	for (int i : scoville)
		pq.push(i);

	while (!pq.empty()) {
		int s1 = pq.top();
		if (s1 >= K)
			break;

		if (pq.size() < 2)
			return -1;

		pq.pop();
		int s2 = pq.top(); pq.pop();
		pq.push(s1 + s2 * 2);

		answer++;
	}
    
    return answer;
}

// k 번째 수
vector<int> solution42748(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
	for (vector<int> command : commands) {
		vector<int> arr(command[1] - command[0] + 1);

		std::copy(array.begin() + (command[0] - 1), array.begin() + (command[1]), arr.begin());

		std::sort(arr.begin(), arr.end());
		answer.push_back(arr[command[2]-1]);
	}
    
    return answer;
}

int main()
{
	return 0;
}
