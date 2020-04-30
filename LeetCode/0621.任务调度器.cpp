#include "header.h"

/*

给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。
任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。
CPU 在任何一个单位时间内都可以执行一个任务，或者在待命状态。
然而，两个相同种类的任务之间必须有长度为 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。
你需要计算完成所有任务所需要的最短时间。

示例 1：
输入: tasks = ["A","A","A","B","B","B"], n = 2
输出: 8
执行顺序: A -> B -> (待命) -> A -> B -> (待命) -> A -> B.

注：
任务的总个数为 [1, 10000]。
n 的取值范围为 [0, 100]。

*/

//优先级队列
class Solution1 {
public:
	int leastInterval(vector<char> &tasks, int n)
	{
		vector<int> m(26, 0);
		for (char c : tasks) ++m[c - 'A'];
		priority_queue<int> q;
		for (int i : m) if (i > 0) q.push(i);
		int times = 0;
		while (!q.empty())
		{
			int i = 0;
			vector<int> temp;
			while (i <= n)
			{
				if (!q.empty())
				{
					if (q.top() > 1)
					{
						temp.push_back(q.top() - 1);
						q.pop();
					}
					else
					{
						q.pop();
					}
				}
				++times;
				if (q.empty() && temp.empty()) break;
				++i;
			}
			for (int i : temp) q.push(i);
		}
		return times;
	}
};
//https://leetcode-cn.com/problems/task-scheduler/solution/ren-wu-diao-du-qi-by-leetcode/

//统计空闲时间槽法(技巧性)
class Solution2 {
public:
	int leastInterval(vector<char> &tasks, int n)
	{
		vector<int> m(26, 0);
		int len = tasks.size();
		for (char c : tasks) ++m[c - 'A'];
		sort(m.begin(), m.end());
		int maxVal = m[25] - 1, idel = maxVal*n;
		for (int i = 24; i >= 0 && m[i] > 0; --i)
		{
			idel -= min(m[i], maxVal);
		}
		return idel > 0 ? idel + len : len;
	}
};
//https://leetcode-cn.com/problems/task-scheduler/solution/ren-wu-diao-du-qi-by-leetcode/