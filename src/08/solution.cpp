#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <iostream>
#include <cstring>

#pragma warning(disable:4996)

using namespace std;

class CLog{
public:
	CLog(string cmd, string uid) {
		sCmd = cmd;
		sUid = uid;
	}
	string sCmd;
	string sUid;
};

vector<string> tok(string s, string delimiter) {
	vector<string> res;
	char *str = const_cast<char *>(s.c_str());
	char *tok;
	tok = std::strtok(str, delimiter.c_str());
	while (tok != NULL) {
		res.push_back(tok);
		tok = std::strtok(NULL, delimiter.c_str());
	}
	return res;	
}

// ����ä�ù�
vector<string> solution42888(vector<string> record) {
	vector<string> answer;
	// record => Enter uid nick or Leave uid or Change uid nick
	// ��ҹ��� ����, 1~10 ����
	// input (record 10���� ����) : ["Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan"]
	// result (answer) : ["Prodo���� ���Խ��ϴ�.", "Ryan���� ���Խ��ϴ�.", "Prodo���� �������ϴ�.", "Prodo���� ���Խ��ϴ�."]

	map<string, string>  nickMap;
	vector<CLog> logs;
	for( string var : record) {		
		vector<string> cmd = tok(var, " ");
		if (cmd.size() > 2) nickMap[cmd[1]] = cmd[2];
		if (cmd[0].compare("Change") != 0) logs.push_back(CLog(cmd[0], cmd[1]));
	}

	for( CLog log : logs) {
		if (log.sCmd.compare("Enter") == 0) answer.push_back(nickMap[log.sUid] + "���� ���Խ��ϴ�.");
		else if (log.sCmd.compare("Leave") == 0) answer.push_back(nickMap[log.sUid] + "���� �������ϴ�.");
	}
	return answer;
}

// =============================================================================================

class CStageFailRate {
public:
	CStageFailRate(int stage, double failRate) {
		nStage = stage;
		fFailRate = failRate;
	}
	int nStage = 0;
	double fFailRate = 0.0;

	bool operator<(CStageFailRate& sf) const {
		return this->fFailRate == sf.fFailRate ?  this->nStage < sf.nStage : this->fFailRate > sf.fFailRate;
	}
};

// ������
vector<int> solution42889(int N, vector<int> stages) {
	// input : ���������� N , �� ����ڰ� �ӹ��� �ִ� �������� �迭
	// output : �������� ���� �������������� �������� �迭 (������ ����������ȣ�� ������)
	// ������� : 
	//		������: ���������� ���������� ���� Ŭ�������� ���� �÷��̾��� �� / ���������� ������ �÷��̾� ��
	//		���������� ���� N�� 1 �̻� 500 ������ �ڿ����̴�.
	//		stages�� ���̴� 1 �̻� 200, 000 �����̴�.
	//		stages���� 1 �̻� N + 1 ������ �ڿ����� ����ִ�.
	//		�� �ڿ����� ����ڰ� ���� ���� ���� ���������� ��ȣ�� ��Ÿ����.
	//		��, N + 1 �� ������ ��������(N ��° ��������) ���� Ŭ���� �� ����ڸ� ��Ÿ����.
	//		���� �������� ���� ���������� �ִٸ� ���� ��ȣ�� ���������� ���� ������ �ϸ� �ȴ�.
	//		���������� ������ ������ ���� ��� �ش� ���������� �������� 0 ���� �����Ѵ�.

	vector<int> answer;	
	vector<int> stageUserCnts(N+2);
	vector<CStageFailRate> stageFailRates;

	for (int stage : stages) stageUserCnts[stage]++;

	int upToUserCnt = stages.size();
	for (int i = 1; i <= N; i++) {
		if (upToUserCnt <= 0)	stageFailRates.push_back(CStageFailRate(i, 0));
		else					stageFailRates.push_back(CStageFailRate(i, (double)stageUserCnts[i] / (double)upToUserCnt));
		upToUserCnt -= stageUserCnts[i];
	}

	sort(stageFailRates.begin(), stageFailRates.end());
	for (CStageFailRate sf : stageFailRates) 
		answer.push_back(sf.nStage);

	return answer;
}


// =============================================================================================

typedef long long INT64;

class CFoodInfo {
public:
	INT64 no = 0;
	INT64 amount = 0;
	CFoodInfo() {}
	CFoodInfo(INT64 n, INT64 a) {
		no = n;
		amount = a;
	}
	bool operator <(const CFoodInfo &n) const {
		return this->amount == n.amount ? this->no < n.no : this->amount < n.amount;
	}
};

bool comp(const CFoodInfo &a, const CFoodInfo &b) {
	return a.no < b.no;
}

// ������ �Թ� ���̺�
int solution42891(vector<int> food_times, INT64 k) {
	INT64 sum = 0;

	vector< CFoodInfo> foods;
	for (int i = 0; i < food_times.size(); i++) {
		foods.push_back(CFoodInfo(i+1, food_times[i]));
		sum += food_times[i];
	}
	if (sum <= k) return -1;

	std::sort(foods.begin(), foods.end());

	for (int i = 0; i < food_times.size(); i++) {
		INT64 time = 0;
		if (i == 0) time = foods[i].amount * (food_times.size() - i);
		else time = (foods[i].amount - foods[i - 1].amount) * (food_times.size() - i);

		if (k <= time) {
			sort(foods.begin() + i, foods.end(), comp);
			k %= (food_times.size() - i);
			k += i;
			return foods[k].no;
		}
		k -= time;
	}
	return -1;
}


// =============================================================================================

class Node {
public:
	int no;
	int level;
	int pos;

	int parent;
	int left;
	int right;
	Node() {}
	Node(int l, int p, int n) { level = l, pos = p; no = n; left = right = parent = -1; }
	bool operator < (const Node &n) const { return level == n.level ? pos < n.pos : level > n.level; }
};

bool isValid(const vector<Node>& nodes, int target, int source) {
	int p = nodes[target].parent;
	if (p == -1) return true;
	if (nodes[p].left == target) if (nodes[p].pos < nodes[source].pos) return false;
	if (nodes[p].right == target) if (nodes[p].pos > nodes[source].pos) return false;
	return isValid(nodes, p, source);
}

void preorder(const vector<Node>& nodes, int idx, vector<int> &ans) {
	ans.push_back(nodes[idx].no);
	if (nodes[idx].left > 0) preorder(nodes, nodes[idx].left, ans);
	if (nodes[idx].right > 0) preorder(nodes, nodes[idx].right, ans);
}

void postorder(const vector<Node>& nodes, int idx, vector<int> &ans) {
	if (nodes[idx].left > 0) postorder(nodes, nodes[idx].left, ans);
	if (nodes[idx].right > 0) postorder(nodes, nodes[idx].right, ans);
	ans.push_back(nodes[idx].no);
}

vector<Node> makeTree(const vector<vector<int>> nodeinfo) {
	vector<Node> nodes;
	int no = 1;
	for (vector<int> elem : nodeinfo) nodes.push_back(Node(elem[1], elem[0], no++));
	std::sort(nodes.begin(), nodes.end());

	queue<int> tree;
	tree.push(0);
	for (int i = 1; i < nodes.size(); i++) {
		int idx = tree.front();
		if (nodes[idx].left != -1 && nodes[idx].right != -1) tree.pop(), idx = tree.front();
		if (nodes[idx].left == -1) {
			if (nodes[idx].pos > nodes[i].pos && isValid(nodes, idx, i)) {
				nodes[idx].left = i, nodes[i].parent = idx;
				tree.push(i);
				continue;
			}
			else nodes[idx].left = -2;
		}
		if (nodes[idx].right == -1) {
			if (nodes[idx].pos < nodes[i].pos && isValid(nodes, idx, i)) {
				nodes[idx].right = i, nodes[i].parent = idx;
				tree.push(i);
				continue;
			}
			else nodes[idx].right = -2;
		}
		tree.pop(), i--;    //Retry node
	}
	return nodes;
}

// ��ã��
vector<vector<int>> solution42892(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2);
	
	vector<Node> nodes = makeTree(nodeinfo);
	preorder(nodes, 0, answer[0]);
	postorder(nodes, 0, answer[1]);

	return answer;
}