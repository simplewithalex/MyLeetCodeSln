#include "header.h"

/*

436. Ѱ��������

����һ���������� intervals ������ intervals[i] = [starti, endi] ����ÿ�� starti �� ��ͬ

���� i �� �Ҳ����� ������ startj >= endi���� startj ��С ������ j��ע�� i ���ܵ��� j

����һ����ÿ������ i ��Ӧ�� �Ҳ����� �±���ɵ����顣���ĳ������ i �����ڶ�Ӧ�� �Ҳ����䣬���±� i ����ֵ��Ϊ -1

ʾ�� 1��
���룺intervals = [[1,2]]
�����[-1]
���ͣ�������ֻ��һ�����䣬�������-1

ʾ�� 2��
���룺intervals = [[3,4],[2,3],[1,2]]
�����[-1,0,1]
���ͣ����� [3,4] ��û�����������ġ��Ҳࡱ����
���� [2,3] ������[3,4]������С�ġ��ҡ����;
���� [1,2] ������[2,3]������С�ġ��ҡ����

ʾ�� 3��
���룺intervals = [[1,4],[2,3],[3,4]]
�����[-1,2,-1]
���ͣ��������� [1,4] �� [3,4] ��û�����������ġ��Ҳࡱ����
���� [2,3] ������ [3,4] ����С�ġ��ҡ����

��ʾ��
1 <= intervals.length <= 2 * 10^4
intervals[i].length == 2
-10^6 <= starti <= endi <= 10^6
ÿ���������㶼 ����ͬ

*/

class Solution1 {
public:
	vector<int> findRightInterval(vector<vector<int>> &intervals) {
		int len = intervals.size();
		vector<pair<int, int>> startIntervals;
		for (int i = 0; i < len; ++i) startIntervals.push_back({ intervals[i][0], i });
		sort(startIntervals.begin(), startIntervals.end());
		vector<int> ans(len);
		for (int i = 0; i < len; ++i) {
			int target = intervals[i][1];
			int lo = 0, hi = len - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo) / 2;
				startIntervals[mi].first < target ? lo = mi + 1 : hi = mi;
			}
			ans[i] = startIntervals[lo].first >= target
				? startIntervals[lo].second : -1;
		}
		return ans;
	}
};

class Solution2 {
public:
	vector<int> findRightInterval(vector<vector<int>> &intervals) {
		vector<pair<int, int>> startIntervals;
		vector<pair<int, int>> endIntervals;
		int len = intervals.size();
		for (int i = 0; i < len; ++i) {
			startIntervals.push_back({ intervals[i][0], i });
			endIntervals.push_back({ intervals[i][1], i });
		}
		sort(startIntervals.begin(), startIntervals.end());
		sort(endIntervals.begin(), endIntervals.end());
		vector<int> ans(len, -1);
		for (int i = 0, j = 0; i < len && j < len; ++i) {
			while (j < len && endIntervals[i].first > startIntervals[j].first) ++j;
			if (j < len) ans[endIntervals[i].second] = startIntervals[j].second;
		}
		return ans;
	}
};

