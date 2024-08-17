#include "header.h"

/*

630. 课程表 III

这里有 n 门不同的在线课程，按从 1 到 n 编号

给你一个数组 courses，其中 courses[i] = [durationi, lastDayi] 表示第 i 门课将会 持续 上 durationi 天课，并且必须在不晚于 lastDayi 的时候完成

你的学期从第 1 天开始，且不能同时修读两门及两门以上的课程

返回你最多可以修读的课程数目

示例 1：
输入：courses = [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
输出：3
解释：
这里一共有 4 门课程，但是你最多可以修 3 门：
首先，修第 1 门课，耗费 100 天，在第 100 天完成，在第 101 天开始下门课。
第二，修第 3 门课，耗费 1000 天，在第 1100 天完成，在第 1101 天开始下门课程。
第三，修第 2 门课，耗时 200 天，在第 1300 天完成。
第 4 门课现在不能修，因为将会在第 3300 天完成它，这已经超出了关闭日期。

示例 2：
输入：courses = [[1,2]]
输出：1

示例 3：
输入：courses = [[3,2],[4,3]]
输出：0

提示:
1 <= courses.length <= 10^4
1 <= durationi, lastDayi <= 10^4

*/

class Solution1 {
public:
	int scheduleCourse(vector<vector<int>> &courses) {
		sort(courses.begin(), courses.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});
		priority_queue<int> pq;
		int total = 0;
		for (const auto &c : courses) {
			int ti = c[0], di = c[1];
			if (total + ti <= di) {
				total += ti;
				pq.push(ti);
			}
			else if (!pq.empty() && pq.top() > ti) {
				total -= (pq.top() - ti);
				pq.pop();
				pq.push(ti);
			}
		}
		return pq.size();
	}
};


// 转换为01背包动态规划问题
class Solution2 {
private:
	vector<vector<int>> memo;

public:
	int scheduleCourse(vector<vector<int>> &courses) {
		sort(courses.begin(), courses.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});
		int len = courses.size();
		memo.resize(len, vector<int>(courses[len - 1][0] + 1, -1));
		return helper(courses, 0, 0);
	}

private:
	int helper(vector<vector<int>> &courses, int idx, int day) {
		if (idx == courses.size()) return 0;
		if (memo[idx][day] != -1) return memo[idx][day];
		vector<int> c(courses[idx]);
		int taken = 0;
		if (day + c[0] <= c[1]) {
			taken = 1 + helper(courses, idx + 1, day + c[0]);
		}
		int no_taken = helper(courses, idx + 1, day);
		return max(taken, no_taken);
	}
};
// 方法超时，该问题适合贪心
