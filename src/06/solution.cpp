#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

// 입국심사
long long solution43238(int n, vector<int> times) {
    long long answer = 0;
    int max_times = *max_element(times.begin(), times.end()); // 가장 늦게 심사하는 심사관
    unsigned long long left = 0, right = max_times * n; // 가장 늦게 심사하는 심사관이 모두 심사한다고 했을때 right
    while(left <= right)  
    {
        unsigned long long total = 0;
        unsigned long long mid = (right + left )/2;
        
        for(int i=0; i<times.size(); i++)
            total = total + (mid/times[i]);
        
        if(total >= n) right = mid - 1;  
        else left = mid + 1;   
    }
    answer = left;
    return answer;
}

// 숫자야구
int solution42841(vector<vector<int>> baseball) {
	int answer = 0;

	string num1 = "";
	string num2 = "";

	vector<int> nums;

	for (int i = 123; i <= 987; i++) {
		num1 = std::to_string(i);

		if (num1[0] == num1[1] || num1[0] == num1[2] || num1[1] == num1[2])
			continue;
		else if (num1[0] == '0' || num1[1] == '0' || num1[2] == '0')
			continue;

		int flag = true;
		for (int j = 0; j < baseball.size(); j++) {
			int cntStrike = 0;
			int cntBall = 0;
			num2 = to_string(baseball[j][0]);

			for (int a = 0; a < num1.length(); a++) {
				for (int b = 0; b < num2.length(); b++) {

					if (a == b && num1[a] == num2[b])
					{
						cntStrike++;
						continue;
					}
					if (a != b && num1[a] == num2[b]) {
						cntBall++;
						continue;
					}
				}
			}

			if (cntStrike != baseball[j][1] || cntBall != baseball[j][2]) {
				flag = false;
				break;
			}
		}

		if (flag == true) {
            cout << i << endl;
            nums.push_back(i);
        }
	}
	return nums.size();
}


// 모의고사
vector<int> solution42840(vector<int> answers) {
	vector<int> answer;
	vector<vector<int>> aa = {
		{1,2,3,4,5},			// 1번 12345 순서 
		{2,1,2,3,2,4,2,5},		// 2번 21232425 순서 
		{3,3,1,1,2,2,4,4,5,5}	// 3번 3311224455 순서 
	};
	
	vector<pair<int,int>> acnt(aa.size(), make_pair(0,0));
	for (int j = 0; j < (int)answers.size(); j++) {
		for (int i = 0; i < (int)aa.size(); i++) {
			acnt[i].first = i + 1;
			int idx = j % aa[i].size();
			if (answers[j] == aa[i][idx])
				acnt[i].second++;
		}
	}
		
	int max = 0;
	std::sort(acnt.begin(), acnt.end(), [](const pair<int, int> &a, const pair<int, int> &b)->bool{return a.second == b.second ? a.first < b.first : a.second > b.second;});
	for (int i = 0; i < (int)acnt.size(); i++) {		
		if (answer.empty() == true) {
			answer.push_back(acnt[i].first);
			max = acnt[i].second;
		}
		else {
			if (acnt[i].second == max)  answer.push_back(acnt[i].first);
			else        				break;
		}
	}
	return answer;
}

// 조이스틱
int solution42860(string name) {
    int answer = 0;

	char ALPHA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int alen = std::strlen(ALPHA);
	int ahalfLen = alen / 2;

	int len = name.length();	
	// 오른쪽으로 이동하는게 좋은지... 왼쪽으로 이동하는게 좋은지... 판단.
	// A 가 어느쪽에 더 많이 **붙어** 있는지 
	int maxa = 0;
	for (int i = 1; i < len; i++) {
		char c = name.at(i);
		if (c == 'A')	maxa++;
		else break;
	}

	int maxra = 0;
	for (int i = len-1; i <= 0; i--) {
		char c = name.at(i);
		if (c == 'A')	maxra++;
		else break;
	}
	maxa = std::max(maxa, maxra);

	// 알파벳을 위로 이동할지 아래로 이동할지 결정하면 됨. 	
	for (int i = 0; i < len; i++) {
		char c = name.at(i);
		int offset = c - 'A';
		if (offset > ahalfLen)
			offset = alen - ahalfLen - (offset - ahalfLen);

		// 알파벳이동
		answer += offset;
	}

	// 자리이동
	answer += len - maxa - 1;
	return answer;
}

// 큰수만들기
string solution42883(string number, int k) {
    string answer = "";
	vector<int> v;
	for (char c : number)
		v.push_back(c - '0');

	
	int idx = 0;
	while (idx < v.size() && k < (v.size() - idx) ) {
		int max = 0;
		if (k > 0) {
			// 최소한 (K + 1) 개 숫자가 있으니 개중에 가장 큰 숫자가 앞으로 나가야 한다. 			
			for (int i = 0; i <= std::min(k, ((int)v.size()-idx-1)); i++)
				max = std::max(max, v[idx+i]);

			while (true) {
				int n = v[idx++];

				if (n == max) {
					// max 값이 나오면 결과에 포함시킨다. 
					answer += (char)'0' + n;
					break;
				}
				else {
					// max 값이 나올때까지 버리고 k 감소시킨다. 
					k--;
				}
			}
		}
		else {
			int n = v[idx++];
			answer += (char)'0' + n;
		}
	}
    return answer;
}

// 구명보트
int solution42885(vector<int> people, int limit) {
    int answer = 0;
	/*
	가장무게가 무거운 사람과 같이 탈 수 있는 가장 무게가 작은 사람 찾아서 같이 보내면 됨.
	*/
	std::sort(people.begin(), people.end());
	deque<int> dp;
	for (int w : people) dp.push_back(w);

	while (dp.size() > 0) {
		int max = dp.back(); dp.pop_back();

		if (dp.size() > 0) {
			int min = dp.front();
			if ((min + max) <= limit)
				dp.pop_front();
		}
		
		answer++;
	}
    
    return answer;
}

// 피보나치
int solution12945(int n) {
	int answer = 0;
	vector<int> v(n+1);
	v[0] = 0;
	v[1] = 1;
	for (int i = 2; i <= n; i++) v[i] = (v[i-2] + v[i-1]) % 1234567;
	
	answer = v[n];
	return answer;
}
