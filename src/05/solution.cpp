#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>

using namespace std;

// ����ū�� 
string solution42746(vector<int> numbers) {
	string answer = "";

	vector<string> unit;
	for (int v : numbers) unit.push_back(std::to_string(v));

	std::sort(unit.begin(), unit.end(), [](const string &a, const string &b) { return (a + b).compare(b + a) > 0; });
	if (unit.size() > 0 && unit[0].compare("0") == 0)	answer = "0";
	else for (string s : unit) answer += s;

    return answer;
}


// 43162 : ��Ʈ��ũ
// n : ��ǻ�� �� 
// computers : ���� ����  ( computers[i][j] = 1 �̸� i��°�� j��°�� ����Ǿ� ����, computers[i][i] �� �׻� 1)
// ret : ��Ʈ�� �� ���� (� �׷����� �����°�?)
// dfs �� bfs 
// dfs : depth first search ������ ���� ����� ������ Ž��
// bfs : Breadth first search �Է¼����� ���� ����� ������ Ž�� (queue �̿�)
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


// 43164 - ������
//��� ������ ���ĺ� �빮�� 3���ڷ� �̷�����ϴ�.
//�־��� ���� ���� 3�� �̻� 10, 000�� �����Դϴ�.
//tickets�� �� ��[a, b]�� a ���׿��� b �������� ���� �װ����� �ִٴ� �ǹ��Դϴ�.
//�־��� �װ����� ��� ����ؾ� �մϴ�.
//���� ������ ��ΰ� 2�� �̻��� ��� ���ĺ� ������ �ռ��� ��θ� return �մϴ�.
//��� ���ø� �湮�� �� ���� ���� �־����� �ʽ��ϴ�.
// [[ICN, SFO], [ICN, ATL], [SFO, ATL], [ATL, ICN], [ATL,SFO]]	[ICN, ATL, ICN, SFO, ATL, SFO]
vector<string> solution43164(vector<vector<string>> tickets) {
	vector<string> answer;

	// �׷����� ���� ��ȸ�Ѵ�. 
	// �湮�ߴ����� �ٽ� �湮�� �� �ִ�. (��ȯ �׷��� �����ϴ�.)
	// ���, ���� �� �ڷᱸ�� 
	// ��忡�� ������ ������ �����ϸ鼭 dfs �� ��ȸ�Ѵ�. 

    // ��絵�ø� �湮�� �� ���� ���� ���ٴ� �̾߱�� �Ѻױ׸����� �����ȴ�. 
	// �����, �������� ���ٴ� ������ ���� ���Ϸ� ��(Euler walk) �Ǵ� ���Ϸ� Ʈ����(Euler trail)
	// �׷��� G���� ���Ϸ� Ʈ������ ������ ���� �ʿ����������
	// 		1) �׷��� G�� ����׷��� �̰�
	// 		2) �׷��� G�� Ȧ�� ���� �������� ���� 0 �Ǵ� 2�̴�.
    // ���ĺ������� ��η� ��� Ƽ���� �� ����� �� ������ ���� ���ĺ� ������ �ٽ� ã�ƾ� �Ѵ�. 
    
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