#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>

using namespace std;

// 가장큰수 
string solution42746(vector<int> numbers) {
	string answer = "";

	vector<string> unit;
	for (int v : numbers) unit.push_back(std::to_string(v));

	std::sort(unit.begin(), unit.end(), [](const string &a, const string &b) { return (a + b).compare(b + a) > 0; });
	if (unit.size() > 0 && unit[0].compare("0") == 0)	answer = "0";
	else for (string s : unit) answer += s;

    return answer;
}


// 43162 : 네트워크
// n : 컴퓨터 수 
// computers : 연결 정보  ( computers[i][j] = 1 이면 i번째와 j번째가 연결되어 있음, computers[i][i] 는 항상 1)
// ret : 네트웍 수 리턴 (몇개 그래프가 나오는가?)
// dfs 와 bfs 
// dfs : depth first search 마지막 노드와 연결된 노드부터 탐색
// bfs : Breadth first search 입력순서의 노드와 연결된 노드부터 탐색 (queue 이용)
void dfs(int start, vector<vector<int>>& computers, int n, vector<bool>& isVisitVec) {
	isVisitVec[start] = true;
	for (int i = 0; i < n; i++) {
		if (isVisitVec[i] == false && computers[start][i] == 1) 
			dfs(i, computers, n, isVisitVec);
	}
}

int solution43162(const int n, vector<vector<int>> computers) {
	int answer = 0;
	vector<bool> isVisitVec(n, false);

	for (int i = 0; i < n; i++) {
		if (isVisitVec[i] == false) {
			answer++;
			dfs(i, computers, n, isVisitVec);
		}
	}

	return answer;
}


// 43164 - 여행경로
//모든 공항은 알파벳 대문자 3글자로 이루어집니다.
//주어진 공항 수는 3개 이상 10, 000개 이하입니다.
//tickets의 각 행[a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
//주어진 항공권은 모두 사용해야 합니다.
//만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
//모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.
// [[ICN, SFO], [ICN, ATL], [SFO, ATL], [ATL, ICN], [ATL,SFO]]	[ICN, ATL, ICN, SFO, ATL, SFO]
vector<string> solution43164(vector<vector<string>> tickets) {
	vector<string> answer;

	// 그래프로 보고 순회한다. 
	// 방문했던곳을 다시 방문할 수 있다. (순환 그래프 가능하다.)
	// 노드, 간선 의 자료구조 
	// 노드에서 지나간 간선을 삭제하면서 dfs 로 순회한다. 

    // 모든도시를 방문할 수 없는 경우는 없다는 이야기는 한붓그리기라고 생각된다. 
	// 출발점, 도착점이 같다는 조건이 없는 오일러 길(Euler walk) 또는 오일러 트레일(Euler trail)
	// 그래프 G에서 오일러 트레일을 가지기 위한 필요충분조건은
	// 		1) 그래프 G가 연결그래프 이고
	// 		2) 그래프 G의 홀수 차수 꼭짓점의 수가 0 또는 2이다.
    // 알파벳순서의 경로로 모든 티켓을 다 사용할 수 없으면 다음 알파벳 순서로 다시 찾아야 한다. 
    
	class Ticket {
	public:
		string dAirport;
		vector<string> aAirports;

		Ticket(string d) {
			dAirport = d;
		}
		Ticket() {

		}

		static vector<string> dfs(map<string, Ticket>& nodes, int ticketCnt, string depature, string arrive, vector<string> ans, int arriveIdx)
		{
			map<string, Ticket> nodeMap = nodes;
			vector<string> answer;

			vector<string> &aAirports = nodeMap[depature].aAirports;
			if (depature != "") 
				aAirports.erase(aAirports.begin() + arriveIdx);

			ans.push_back(arrive);

			if (nodeMap[arrive].aAirports.empty() == true)
				return ans;

			depature = arrive;
			for (int i = 0; i < nodeMap[depature].aAirports.size(); i++)
			{
				arrive = nodeMap[depature].aAirports[i];
				
				answer = dfs(nodeMap, ticketCnt, depature, arrive, ans, i);
				if (answer.size() == (ticketCnt + 1))
					return answer;
			}
			return answer;
		};

	};

	std::map<string, Ticket> nodeMap;
	for (vector<string> v : tickets) {
		
		string d = v[0];
		string a = v[1];
		if (nodeMap.find(d) == nodeMap.end())
			nodeMap[d] = Ticket(d);
	
		nodeMap[v[0]].aAirports.push_back(a);

		if (nodeMap.find(a) == nodeMap.end())
			nodeMap[a] = Ticket(a);
	}

	std::map<string, Ticket>::iterator iter;
	for (iter = nodeMap.begin(); iter != nodeMap.end(); ++iter)
		sort((iter->second.aAirports).begin(), (iter->second.aAirports).end());

	answer = Ticket::dfs(nodeMap, tickets.size(), "", "ICN", answer, 0);

	return answer;
}