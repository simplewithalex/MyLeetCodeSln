#include "header.h"

/*

188. ������Ʊ�����ʱ�� IV

����һ���������� prices �����ĵ� i ��Ԫ�� prices[i] ��һ֧�����Ĺ�Ʊ�ڵ� i ��ļ۸�
���һ���㷨�����������ܻ�ȡ�������������������� k �ʽ��ס�

ע�⣺�㲻��ͬʱ�����ʽ��ף���������ٴι���ǰ���۵�֮ǰ�Ĺ�Ʊ����

ʾ�� 1��
���룺k = 2, prices = [2,4,1]
�����2
���ͣ��ڵ� 1 �� (��Ʊ�۸� = 2) ��ʱ�����룬�ڵ� 2 �� (��Ʊ�۸� = 4) ��ʱ����������ʽ������ܻ������ = 4-2 = 2 

ʾ�� 2��
���룺k = 2, prices = [3,2,6,5,0,3]
�����7
���ͣ��ڵ� 2 �� (��Ʊ�۸� = 2) ��ʱ�����룬�ڵ� 3 �� (��Ʊ�۸� = 6) ��ʱ������, ��ʽ������ܻ������ = 6-2 = 4 
����ڵ� 5 �� (��Ʊ�۸� = 0) ��ʱ�����룬�ڵ� 6 �� (��Ʊ�۸� = 3) ��ʱ������, ��ʽ������ܻ������ = 3-0 = 3 


��ʾ��
0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000

*/

class Solution {
public:
	int maxProfit(int k, vector<int> &prices) {
		int len = prices.size();
		if (len <= 0) return 0;
		if (k > len / 2) return maxProfit_infk(prices);
		vector<vector<vector<int>>> dp(len, vector<vector<int>>(k + 1, vector<int>(2, 0)));
		for (int i = 0; i < len; ++i) {
			for (int j = 1; j <= k; ++j) {
				if (i == 0) {
					// ���ڽ��״���Ϊ0�����ֳ�ʼ״̬��δ���й�Ʊʱ����ʼֵ��ȻΪ0
					// ���й�Ʊ���������δʹ�õ�������û����Խ��״���Ϊ0�ĳ�ʼ״̬�ر����ó�ֵ
					dp[i][j][0] = 0;
					dp[i][j][1] = -prices[i];
					continue;
				}
				dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
				dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
			}
		}
		return dp[len - 1][k][0];
	}

private:
	int maxProfit_infk(vector<int> &prices) {
		int len = prices.size();
		if (len <= 0) return 0;
		vector<vector<int>> dp(len, vector<int>(2, 0));
		for (int i = 0; i < len; ++i) {
			if (i - 1 == -1) {
				dp[i][0] = 0;
				dp[i][1] = -prices[i];
				continue;
			}
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[len - 1][0];
	}
};
