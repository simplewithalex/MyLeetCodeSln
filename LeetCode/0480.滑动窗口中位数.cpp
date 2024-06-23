#include "header.h"

/*

480. ����������λ��

��λ���������������м���Ǹ�����������еĳ�����ż������û�����м��������ʱ��λ�������м����������ƽ������

���磺
[2,3,4]����λ���� 3
[2,3]����λ���� (2 + 3) / 2 = 2.5
����һ������ nums����һ������Ϊ k �Ĵ��ڴ�����˻��������Ҷˡ��������� k ������ÿ�δ��������ƶ� 1 λ��
����������ҳ�ÿ�δ����ƶ���õ����´�����Ԫ�ص���λ�����������������ɵ����顣

ʾ����
���� nums = [1,3,-1,-3,5,3,6,7]���Լ� k = 3

����λ��                      ��λ��
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7      -1
 1  3 [-1  -3  5] 3  6  7      -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
��ˣ����ظû������ڵ���λ������ [1,-1,-1,3,5,6]

��ʾ��
����Լ��� k ʼ����Ч������k ʼ��С�ڵ�������ķǿ������Ԫ�ظ���
����ʵֵ����� 10^-5 ���ڵĴ𰸽���������ȷ��

*/

class Solution {
private:
	priority_queue<int> small;
	priority_queue<int, vector<int>, greater<int>> big;
	unordered_map<int, int> del;

public:
	vector<double> medianSlidingWindow(vector<int> &nums, int k) {
		for (int i = 0; i < k; ++i) small.push(nums[i]);
		for (int i = 0; i < k / 2; ++i) {
			big.push(small.top());
			small.pop();
		}
		vector<double> res{ getMid(k) };
		for (int i = k; i < nums.size(); ++i) {
			int lo = nums[i - k], hi = nums[i];
			++del[lo];
			if (lo <= small.top()) {
				big.push(hi);
				small.push(big.top());
				big.pop();
			} else {
				small.push(hi);
				big.push(small.top());
				small.pop();
			}
			// �����ظ�Ԫ�أ������ɾ��small�����
			while (!small.empty() && del.count(small.top())) {
				--del[small.top()];
				if (!del[small.top()]) del.erase(small.top());
				small.pop();
			}
			while (!big.empty() && del.count(big.top())) {
				--del[big.top()];
				if (!del[big.top()]) del.erase(big.top());
				big.pop();
			}
			res.push_back(getMid(k));
		}
		return res;
	}

private:
	double getMid(int k) {
		if (k & 1) return small.top();
		else return ((long long)(small.top()) + big.top()) / 2.0;
	}
};
