#include "header.h"

/*

����һ����άƽ�棬ƽ������ n ���㣬������ж��ٸ�����ͬһ��ֱ���ϡ�

����: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
���: 4

*/

struct Point 
{
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	int maxPoints(vector<Point> &points)
	{
		int len = points.size();
		if (len <= 2) return len;
		unordered_map<int, unordered_map<int, int>> m;
		int res = 0;
		for (int i = 0; i < len; ++i)
		{
			m.clear();
			int overlap = 0, maxCnt = 0;
			for (int j = i + 1; j < len; ++j)
			{
				int x = points[j].x - points[i].x;
				int y = points[j].y - points[i].y;
				if (x == 0 && y == 0)
				{
					++overlap;
					continue;
				}
				int gcd = generateGcd(x, y);
				if (gcd != 0)
				{
					x /= gcd;
					y /= gcd;
				}
				++m[x][y];
				maxCnt = max(maxCnt, m[x][y]);
			}
			res = max(res, maxCnt + overlap + 1);
		}
		return res;
	}
	int generateGcd(int x, int y)
	{
		if (y == 0) return x;
		else
			return generateGcd(y, x%y);
	}
};

//https://leetcode.com/problems/max-points-on-a-line/discuss/47113/A-java-solution-with-notes