#include "header.h"

/*

2558. 从数量最多的堆取走礼物

给你一个整数数组gifts，表示各堆礼物的数量。每一秒，你需要执行以下操作：

选择礼物数量最多的那一堆
如果不止一堆都符合礼物数量最多，从中选择任一堆即可
选中的那一堆留下平方根数量的礼物（向下取整），取走其他的礼物

返回在 k 秒后剩下的礼物数量


示例 1：
输入：gifts = [25,64,9,4,100], k = 4
输出：29
解释：
按下述方式取走礼物：
- 在第一秒，选中最后一堆，剩下 10 个礼物
- 接着第二秒选中第二堆礼物，剩下 8 个礼物
- 然后选中第一堆礼物，剩下 5 个礼物
- 最后，再次选中最后一堆礼物，剩下 3 个礼物
最后剩下的礼物数量分别是 [5,8,9,4,3] ，所以，剩下礼物的总数量是 29

示例 2：
输入：gifts = [1,1,1,1], k = 4
输出：4
解释：
在本例中，不管选中哪一堆礼物，都必须剩下 1 个礼物
也就是说，你无法获取任一堆中的礼物
所以，剩下礼物的总数量是 4

提示：
1 <= gifts.length <= 10^3
1 <= gifts[i] <= 10^9
1 <= k <= 10^3

*/

// 手写堆实现
class MyHeap {
public:
	vector<int> v;
	int sz;

public:
	MyHeap(const vector<int> &nums) {
		v.resize(1);
		for (const int &num : nums) v.push_back(-num);
		sz = v.size() - 1;
		for (int i = sz / 2; i >= 1; --i) down(i);
	}
	void add(int x) {
		v.push_back(x);
		++sz;
		up(sz);
	}
	int peek() { return v[1]; }
	int poll() {
		int res = peek();
		v[1] = v.back();
		v.pop_back();
		--sz;
		down(1);
		return res;
	}

private:
	void up(int u) {
		int fa = u / 2;
		while (fa && v[fa] > v[u]) {
			swap(v[fa], v[u]);
			u = fa;
			fa = u / 2;
		}
	}
	void down(int d) {
		int realfa = d;
		do {
			d = realfa;
			int l = d * 2, r = d * 2 + 1;
			// 开始 realfa 与 d 相等, l 与 d 比较 
			if (l <= sz && v[l] < v[d]) realfa = l;
			// realfa 相当于记录 l 与 d 的小者, r 与小者比较
			if (r <= sz && v[r] < v[realfa]) realfa = r;
			swap(v[realfa], v[d]);
		} while (realfa != d);
	}
};

class Solution {
public:
	long long pickGifts(vector<int> &gifts, int k) {
		MyHeap heap(gifts);
		while (k--) heap.add(-sqrt(-heap.poll()));
		long long ans = 0;
		for (const auto n : heap.v) ans += n;
		return -ans;
	}
};

