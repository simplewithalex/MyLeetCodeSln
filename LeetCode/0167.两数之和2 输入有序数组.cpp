#include "header.h"

// 二分查找
class Solution1 {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		int len = numbers.size();
		for (int lo = 0; lo < len - 1; ++lo) {
			int hi = binarySearch(numbers, lo + 1, len - 1, target - numbers[lo]);
			if (hi != -1) return{ lo + 1,hi + 1 };
		}
		return {};
	}
private:
	int binarySearch(vector<int> &numbers, int lo, int hi, int target) {
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			if (numbers[mi] < target) lo = mi + 1;
			else hi = mi;
		}
		if (numbers[lo] == target) return lo;
		else return -1;
	}
};

// 双指针
class Solution2 {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		int len = numbers.size();
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int sum = numbers[lo] + numbers[hi];
			if (sum == target) return{ lo + 1,hi + 1 };
			else if (sum < target) ++lo;
			else --hi;
		}
		return {};
	}
};