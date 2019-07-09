#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

// 소수찾기
int primes[1000000+1];
int solution12921(int N) {
	int answer = 0;

	if (N < 2 || N > 10000000)
		return 0;

                 int sq = std::sqrt(N);
	for (int p = 2; p <= sq; p++) {
		if (primes[p] == 0) {
			for (int i = p+p; i <= N; i=i+p) 
			                primes[i] = 1;
		}
	}

	for (int i = 2; i <= N; i++) {
		if (primes[i] == 0)
			answer++;
	}
	return answer;
}

// 두 정수 사이의 합
long long solution12912(int a, int b) {
    long long answer = 0;
      long long temp=0;
    int tmp=0;
      if(a > b){
          tmp = a;
          a = b;
          b = tmp;
      }
      else if(a==b){
          return a;
      }
/*      
      for(int i=a; i<=b; i++){
          temp += i;
      }
      
      answer = temp;
*/
    answer = ((long long)(a+b))*((long long)(b-a+1))/2;
    return answer;
}


int gcd_recursion(int u, int v){
    if (v == 0) return u;
    else return gcd_recursion(v, u%v);
}

// 최대공약수 최소공배수
vector<int> solution12940(int n, int m) {
    vector<int> answer;
    
    int GCD = gcd_recursion(n, m);
    answer.push_back(GCD);
    int LCM = GCD * (m / GCD) * (n / GCD);
    answer.push_back(LCM);
    return answer;
}

// 압축
vector<int> solution17684(string msg) {
    vector<int> answer;
    
    int idx = 1;
	std::map<string, int> dic;

	string d = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(char c : d) {		
		string v(1, c);		
		dic[v] = idx++;
	}

	string v = "";
	string prev = "";

	for (char c : msg) {

		v.append(1, c);
		if (dic[v] != 0) {
			prev = v;
		}
		else {
			answer.push_back(dic[prev]);

			dic[v] = idx++;
			v = "";
			v.append(1, c);
			prev = v;
		}
	}

	if (prev.empty() == false)
		answer.push_back(dic[prev]);
    
    return answer;
}

