#include "header.h"

/*

324. �ڶ����� II

����һ����������nums�������������г� nums[0] < nums[1] > nums[2] < nums[3]... ��˳��

����Լ��������������鶼���Եõ�������ĿҪ��Ľ��

ʾ�� 1��
���룺nums = [1,5,1,1,6,4]
�����[1,6,1,5,1,4]
���ͣ�[1,4,1,5,1,6] ͬ���Ƿ�����ĿҪ��Ľ�������Ա����������ܡ�

ʾ�� 2��
���룺nums = [1,3,2,2,3,1]
�����[2,3,1,3,1,2]

��ʾ��
1 <= nums.length <= 5 * 10^4
0 <= nums[i] <= 5000
��Ŀ���ݱ�֤�����ڸ���������nums �����ܲ���������ĿҪ��Ľ��

���ף������� O(n) ʱ�临�ӶȺ� / ��ԭ�� O(1) ����ռ���ʵ����

*/

// O(nlogn)
class Solution1 {
public:
	void wiggleSort(vector<int> &nums) {
		vector<int> tmp(nums);
		sort(tmp.begin(), tmp.end());
		int len = nums.size();
		int lo = (len - 1) / 2, hi = len - 1;
		for (int i = 0; i < len; ++i) {
			nums[i] = i & 1 ? tmp[hi--] : tmp[lo--];
		}
	}
};

// O(n)
class Solution2 {
public:
	void wiggleSort(vector<int> &nums) {
		vector<int> buckets(5001);
		for (const int n : nums) ++buckets[n];
		int hi = 5000;
		for (int i = 1; i < nums.size(); i += 2) {
			while (!buckets[hi]) --hi;
			nums[i] = hi;
			--buckets[hi];
		}
		for (int i = 0; i < nums.size(); i += 2) {
			while (!buckets[hi]) --hi;
			nums[i] = hi;
			--buckets[hi];
		}
	}
};


// O(n) + �ռ��Ż�
// ���ٻ��� + �����з�
class Solution3 {
private:
	int len;
	int mid;

public:
	void wiggleSort(vector<int> &nums) {
		len = nums.size();
		mid = len / 2;
		quickSelect(nums, 0, len - 1, mid);
		int midNum = nums[mid];
		// ��ӵ�����ת���������з��㷨
		// ��Ȼ����ԭʼ������С�������У������ս���൱��
		// �Ѵ��������1 3 5 7��С��������2 4 6 8
		int lo = 0, hi = len - 1, k = 0;
		while (k <= hi) {
			if (nums[getIdx(k)] > midNum) {
				swap(nums[getIdx(k++)], nums[getIdx(lo++)]);
			} else if (nums[getIdx(k)] < midNum) {
				swap(nums[getIdx(k)], nums[getIdx(hi--)]);
			} else {
				++k;
			}
		}
	}

private:
	void quickSelect(vector<int> &nums, int lo, int hi, int mi) {
		int index = partition(nums, lo, hi);
		while (index != mi) {
			if (index > mi) {
				hi = index - 1;
				index = partition(nums, lo, hi);
			}
			else {
				lo = index + 1;
				index = partition(nums, lo, hi);
			}
		}
	}
	int partition(vector<int> &nums, int lo, int hi) {
		swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
		int pivot = nums[lo];
		while (lo < hi) {
			while (lo < hi) {
				if (pivot < nums[hi]) --hi;
				else {
					nums[lo++] = nums[hi];
					break;
				}
			}
			while (lo < hi) {
				if (pivot > nums[lo]) ++lo;
				else {
					nums[hi--] = nums[lo];
					break;
				}
			}
		}
		nums[lo] = pivot;
		return lo;
	}
	int getIdx(int x) { return (2 * x + 1) % (len | 1); }
};
