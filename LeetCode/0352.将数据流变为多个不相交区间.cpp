#include "header.h"

/*

352. ����������Ϊ������ཻ����

����һ���ɷǸ����� a1, a2, ..., an ��ɵ����������룬���㽫��ĿǰΪֹ�����������ܽ�Ϊ���ཻ�������б�

ʵ�� SummaryRanges �ࣺ
SummaryRanges() ʹ��һ������������ʼ������
void addNum(int val) ���������м������� val
int[][] getIntervals() �Բ��ཻ���� [start_i, end_i] ���б���ʽ���ض����������������ܽ�

ʾ����
���룺
["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
[[], [1], [], [3], [], [7], [], [2], [], [6], []]
�����
[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
���ͣ�
SummaryRanges summaryRanges = new SummaryRanges();
summaryRanges.addNum(1);      // arr = [1]
summaryRanges.getIntervals(); // ���� [[1, 1]]
summaryRanges.addNum(3);      // arr = [1, 3]
summaryRanges.getIntervals(); // ���� [[1, 1], [3, 3]]
summaryRanges.addNum(7);      // arr = [1, 3, 7]
summaryRanges.getIntervals(); // ���� [[1, 1], [3, 3], [7, 7]]
summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
summaryRanges.getIntervals(); // ���� [[1, 3], [7, 7]]
summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
summaryRanges.getIntervals(); // ���� [[1, 3], [6, 7]]

��ʾ��
0 <= val <= 10^4
������ addNum �� getIntervals ���� 3 * 10^4 ��

���ף�������ڴ����ϲ����������������Ĵ�С��ȣ����ཻ�����������С������ô��?

*/

class SummaryRanges1 {
private:
	set<int> values;

public:
	SummaryRanges1() {}

	void addNum(int value) { values.insert(value); }

	vector<vector<int>> getIntervals() {
		if (values.empty()) return{};
		vector<vector<int>> intervals;
		int left = -1, right = -1;
		for (int val : values) {
			if (left < 0) {
				left = right = val;
			} else if (val == right + 1) {
				right = val;
			} else {
				intervals.push_back({ left, right });
				left = right = val;
			}
		}
		intervals.push_back({ left, right });
		return intervals;
	}
};

// ��������ĸ�����⣺
// ǿ���������󣬺ϲ�����࣬��˼Ӧ����ָ����ά�����䣬�����Ǳ���ÿ��Ԫ�أ��ɼ��ٿռ�ռ��
class SummaryRanges2 {
private:
	vector<vector<int>> nums;
	vector<int> head{ -10, -10 };
	vector<int> tail{ 10010, 10010 };

public:
	SummaryRanges2() {
		nums.push_back(head);
		nums.push_back(tail);
	}

	void addNum(int value) {
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int mi = lo + (hi - lo + 1) / 2;
			if (nums[mi][0] > value) hi = mi - 1;
			else lo = mi;
		}

		vector<int> cur{ value, value };
		vector<int> &pre(nums[lo]);
		vector<int> &next(nums[lo + 1]);
		if (pre[0] <= value && value <= pre[1]) {
			// pass
		} else if (pre[1] + 1 == value && value == next[0] - 1) {
			pre[1] = next[1];
			nums.erase(nums.begin() + lo + 1);
		} else if (pre[1] + 1 == value) {
			pre[1] = value;
		} else if (value == next[0] - 1) {
			next[0] = value;
		} else {
			nums.insert(nums.begin() + lo + 1, cur);
		}
	}

	vector<vector<int>> getIntervals() {
		int len = nums.size();
		vector<vector<int>> ans;
		for (int i = 1; i < len - 1; ++i) ans.push_back(nums[i]);
		return ans;
	}
};


// ʹ�����������Ż�
class SummaryRanges3 {
private:
	set<vector<int>> nums;
	vector<int> head{ -10, -10 };
	vector<int> tail{ 10010, 10010 };

public:
	SummaryRanges3() {
		nums.insert(head);
		nums.insert(tail);
	}

	void addNum(int value) {
		vector<int> cur{ value, value };
		auto iter = nums.lower_bound(cur);
		auto lower = (*iter)[0] == value ? iter : --iter;
		auto upper = ++iter;
		// set��������������ʧЧ
		if ((*lower)[0] <= value && value <= (*lower)[1]) {
			// pass
		} else if ((*lower)[1] + 1 == value && (*upper)[0] - 1 == value) {
			nums.insert({ (*lower)[0], (*upper)[1] });
			nums.erase(lower);
			nums.erase(upper);
		} else if ((*lower)[1] + 1 == value) {
			nums.insert({ (*lower)[0], value });
			nums.erase(lower);
		} else if (value == (*upper)[0] - 1) {
			nums.insert({ value, (*upper)[1] });
			nums.erase(upper);
		} else {
			nums.insert({ value, value });
		}
	}

	vector<vector<int>> getIntervals() {
		int len = nums.size();
		vector<vector<int>> ans;
		for (auto it = ++nums.begin(); it != --nums.end(); ++it) {
			ans.push_back(*it);
		}
		return ans;
	}
};

// https://leetcode.cn/problems/data-stream-as-disjoint-intervals/solutions/1037331/gong-shui-san-xie-yi-ti-shuang-jie-er-fe-afrk/
// @author https://leetcode.cn/u/ac_oier/

/**
* Your SummaryRanges object will be instantiated and called as such:
* SummaryRanges* obj = new SummaryRanges();
* obj->addNum(value);
* vector<vector<int>> param_2 = obj->getIntervals();
*/

