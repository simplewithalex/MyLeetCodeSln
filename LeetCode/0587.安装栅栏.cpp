#include "header.h"

/*

587. ��װդ��

����һ������ trees������ trees[i] = [xi, yi] ��ʾ���ڻ�԰�е�λ��

�㱻Ҫ������̳��ȵ����Ӱ�������԰Χ��������Ϊ���Ӻܹ�ֻ�а� ���е�����Χ��������԰��Χ�úܺ�

����ǡ��λ��Χ���ܱߵ���ľ������

ʾ�� 1:
����: points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
���: [[1,1],[2,0],[3,3],[2,4],[4,2]]

ʾ�� 2:
����: points = [[1,2],[2,2],[4,2]]
���: [[4,2],[2,2],[1,2]]

ע��:
1 <= points.length <= 3000
points[i].length == 2
0 <= xi, yi <= 100
���и����ĵ㶼�� Ψһ ��

*/

class Solution {
public:
	vector<vector<int>> outerTrees(vector<vector<int>> &trees) {
		sort(trees.begin(), trees.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1];
		});
		int len = trees.size(), sp = 0;
		vector<int> st(len + 5);
		vector<char> vis(len + 5);
		st[++sp] = 0;
		for (int i = 1; i < len; ++i) {
			vector<int> c = trees[i];
			while (sp >= 2) {
				vector<int> a = trees[st[sp - 1]], b = trees[st[sp]];
				if (getArea(a, b, c) > 0) vis[st[sp--]] = false;
				else break;
			}
			st[++sp] = i;
			vis[i] = true;
		}
		int curSize = sp;
		for (int i = len - 1; i >= 0; --i) {
			if (vis[i]) continue;
			vector<int> c = trees[i];
			while (sp > curSize) {
				vector<int> a = trees[st[sp - 1]], b = trees[st[sp]];
				if (getArea(a, b, c) > 0) --sp;
				else break;
			}
			st[++sp] = i;
		}
		vector<vector<int>> ans;
		for (int i = 1; i < sp; ++i) ans.push_back(trees[st[i]]);
		return ans;
	}

private:
	vector<int> subtraction(const vector<int> &a, const vector<int> &b) {
		return { a[0] - b[0], a[1] - b[1] };
	}
	int cross(const vector<int> &a, const vector<int> &b) {
		return a[0] * b[1] - a[1] * b[0];
	}
	int getArea(vector<int> &a, vector<int> &b, vector<int> &c) {
		return cross(subtraction(b, a), subtraction(c, a));
	}
};
// https://leetcode.cn/problems/erect-the-fence/solutions/1442258/by-ac_oier-4xuu/
// @author https://leetcode.cn/u/ac_oier/

