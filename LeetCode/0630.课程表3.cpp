#include "header.h"

/*

630. �γ̱� III

������ n �Ų�ͬ�����߿γ̣����� 1 �� n ���

����һ������ courses������ courses[i] = [durationi, lastDayi] ��ʾ�� i �ſν��� ���� �� durationi ��Σ����ұ����ڲ����� lastDayi ��ʱ�����

���ѧ�ڴӵ� 1 �쿪ʼ���Ҳ���ͬʱ�޶����ż��������ϵĿγ�

�������������޶��Ŀγ���Ŀ

ʾ�� 1��
���룺courses = [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
�����3
���ͣ�
����һ���� 4 �ſγ̣��������������� 3 �ţ�
���ȣ��޵� 1 �ſΣ��ķ� 100 �죬�ڵ� 100 ����ɣ��ڵ� 101 �쿪ʼ���ſΡ�
�ڶ����޵� 3 �ſΣ��ķ� 1000 �죬�ڵ� 1100 ����ɣ��ڵ� 1101 �쿪ʼ���ſγ̡�
�������޵� 2 �ſΣ���ʱ 200 �죬�ڵ� 1300 ����ɡ�
�� 4 �ſ����ڲ����ޣ���Ϊ�����ڵ� 3300 ������������Ѿ������˹ر����ڡ�

ʾ�� 2��
���룺courses = [[1,2]]
�����1

ʾ�� 3��
���룺courses = [[3,2],[4,3]]
�����0

��ʾ:
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


// ת��Ϊ01������̬�滮����
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
// ������ʱ���������ʺ�̰��
