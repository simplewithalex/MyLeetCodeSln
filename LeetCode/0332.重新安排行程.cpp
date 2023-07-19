#include "header.h"

/*

332. 重新安排行程

给你一份航线列表tickets，其中 tickets[i] = [from_i, to_i] 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。

所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。

例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。

假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。

示例 1：
输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
输出：["JFK","MUC","LHR","SFO","SJC"]

示例 2：
输入：tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
输出：["JFK","ATL","JFK","SFO","ATL","SFO"]
解释：另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"] ，但是它字典排序更大更靠后。

提示：
1 <= tickets.length <= 300
tickets[i].length == 2
fromi.length == 3
toi.length == 3
from_i 和 to_i 由大写英文字母组成
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

// 欧拉回路
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

