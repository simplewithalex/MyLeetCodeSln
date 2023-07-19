#include "header.h"

/*

332. ���°����г�

����һ�ݺ����б�tickets������ tickets[i] = [from_i, to_i] ��ʾ�ɻ������ͽ���Ļ����ص㡣����Ը��г̽������¹滮����

������Щ��Ʊ������һ���� JFK������Ϲ��ʻ��������������������Ը��г̱���� JFK ��ʼ��������ڶ�����Ч���г̣����㰴�ֵ����򷵻���С���г���ϡ�

���磬�г� ["JFK", "LGA"] �� ["JFK", "LGB"] ��Ⱦ͸�С���������ǰ��

�ٶ����л�Ʊ���ٴ���һ�ֺ�����г̡������еĻ�Ʊ ���붼��һ�� �� ֻ����һ�Ρ�

ʾ�� 1��
���룺tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
�����["JFK","MUC","LHR","SFO","SJC"]

ʾ�� 2��
���룺tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
�����["JFK","ATL","JFK","SFO","ATL","SFO"]
���ͣ���һ����Ч���г��� ["JFK","SFO","ATL","JFK","ATL","SFO"] ���������ֵ�������������

��ʾ��
1 <= tickets.length <= 300
tickets[i].length == 2
fromi.length == 3
toi.length == 3
from_i �� to_i �ɴ�дӢ����ĸ���
from_i != to_i

*/

class Solution1 {
private:
	vector<string> res;
	vector<string> path;
	vector<char> used;

public:
	vector<string> findItinerary(vector<vector<string>> &tickets) {
		used.resize(tickets.size(), false);
		sort(tickets.begin(), tickets.end());
		path.push_back("JFK");
		dfs(tickets, "JFK");
		return res;
	}

private:
	void dfs(vector<vector<string>> &tickets, string outset) {
		if (!res.empty()) return;
		if (path.size() == tickets.size() + 1) {
			res = path;
			return;
		}
		for (int i = 0; i < tickets.size(); ++i) {
			if (outset == tickets[i][0] && !used[i]) {
				used[i] = true;
				path.push_back(tickets[i][1]);
				dfs(tickets, tickets[i][1]);
				used[i] = false;
				path.pop_back();
			}
		}
	}
};

// ŷ����·
class Solution2 {
private:
	unordered_map<string, priority_queue<string, vector<string>, greater<string>>> m;
	vector<string> stk;

public:
	vector<string> findItinerary(vector<vector<string>> &tickets) {
		for (const auto &v : tickets) m[v[0]].push(v[1]);
		helper("JFK");
		reverse(stk.begin(), stk.end());
		return stk;
	}

private:
	void helper(const string &str) {
		while (m.count(str) && !m[str].empty()) {
			string tmp = m[str].top();
			m[str].pop();
			helper(tmp);
		}
		stk.push_back(str);
	}
};
// https://leetcode.cn/problems/reconstruct-itinerary/solutions/389885/zhong-xin-an-pai-xing-cheng-by-leetcode-solution/
// @author https://leetcode.cn/u/leetcode-solution/

