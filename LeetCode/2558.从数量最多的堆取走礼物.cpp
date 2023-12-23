#include "header.h"

/*

2558. ���������Ķ�ȡ������

����һ����������gifts����ʾ���������������ÿһ�룬����Ҫִ�����²�����

ѡ����������������һ��
�����ֹһ�Ѷ���������������࣬����ѡ����һ�Ѽ���
ѡ�е���һ������ƽ�����������������ȡ������ȡ������������

������ k ���ʣ�µ���������


ʾ�� 1��
���룺gifts = [25,64,9,4,100], k = 4
�����29
���ͣ�
��������ʽȡ�����
- �ڵ�һ�룬ѡ�����һ�ѣ�ʣ�� 10 ������
- ���ŵڶ���ѡ�еڶ������ʣ�� 8 ������
- Ȼ��ѡ�е�һ�����ʣ�� 5 ������
- ����ٴ�ѡ�����һ�����ʣ�� 3 ������
���ʣ�µ����������ֱ��� [5,8,9,4,3] �����ԣ�ʣ��������������� 29

ʾ�� 2��
���룺gifts = [1,1,1,1], k = 4
�����4
���ͣ�
�ڱ����У�����ѡ����һ�����������ʣ�� 1 ������
Ҳ����˵�����޷���ȡ��һ���е�����
���ԣ�ʣ��������������� 4

��ʾ��
1 <= gifts.length <= 10^3
1 <= gifts[i] <= 10^9
1 <= k <= 10^3

*/

// ��д��ʵ��
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
			// ��ʼ realfa �� d ���, l �� d �Ƚ� 
			if (l <= sz && v[l] < v[d]) realfa = l;
			// realfa �൱�ڼ�¼ l �� d ��С��, r ��С�߱Ƚ�
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

