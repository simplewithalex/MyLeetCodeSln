#include "header.h"

/*

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。

示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5

*/

class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) 
	{
		if (m > n) return findMedianSortedArrays(B, n, A, m);
		int i = 0, j = 0;
		int minIndex = 0, maxIndex = m;
		//i + j == m - i + n - j(m + n为偶数) 或 m - i + n - j + 1(m + n为奇数)
		//2(i + j) == m + n 或 m + n + 1，所以 i + j == (m + n + 1) >> 1
		int half = (m + n + 1) >> 1;
		while (minIndex <= maxIndex)
		{
			i = (minIndex + maxIndex) >> 1;
			j = half - i;
			if (i > 0 && j < n && A[i - 1] > B[j])
				maxIndex = i - 1;
			else if (j > 0 && i < m && B[j - 1] > A[i])
				minIndex = i + 1;
			else
			{
				int left = 0, right = 0;
				if (i == 0)
					left = B[j - 1];
				else if (j == 0)
					left = A[i - 1];
				else
					left = max(A[i - 1], B[j - 1]);
				//如果长度为奇数，则不用考虑右半部分。
				if ((m + n) & 1) return left;

				//如果长度为偶数，需要考虑右边部分。
				if (i == m)
					right = B[j];
				else if (j == n)
					right = A[i];
				else
					right = min(A[i], B[j]);
				return (left + right) / 2.0;
			}
		}
		return 0.0;
	}
};


/*
要解决这个问题，我们需要了解“中位数有什么用”。在统计中，中值用于将集合划分为两个相等长度的子集，
一个子集总是大于另一个子集。如果我们使用中位数来划分，就会非常接近答案。

首先让我们在随机位置将A切成两部分：

left_A | right_A

A[0]，A[1]，...，A[i - 1] | A[i]，A[i + 1]，...，A[m - 1]
由于A有m个元素，所以有m + 1种切割（i = 0~m）。
我们知道：len（left_A） = i，len（right_A） = m - i。注意：当i = 0时，left_A为空，而当i = m时，right_A为空。

以同样的方式，在随机位置j将B切成两部分：

left_B | right_B

B[0]，B[1]，...，B[j - 1] | B[j]，B[j + 1]，...，B[n - 1]
将left_A和left_B放入一组，并将right_A和right_B放入另一组。我们将它们命名为left_part和right_part：

left_part | right_part

A[0]，A[1]，...，A[i - 1] | A[i]，A[i + 1]，...，A[m - 1]
B[0]，B[1]，...，B[j - 1] | B[j]，B[j + 1]，...，B[n - 1]

如果我们能确保：
1）len（left_part） == len（right_part）
2）max（left_part） <= min（right_part）
然后我们将{ A，B }中的所有元素分成两个长度相等的部分，一部分总是大于另一部分。然后中位数 median = （max（left_part） + min（right_part）） / 2。

为了确保这两个条件，我们只需要确保：

(1) i + j == m - i + n - j(m + n为偶数) 或 m - i + n - j + 1(m + n为奇数)
如果n > = m，我们只需要设置：i = 0~m，j = (m + n + 1) / 2 - i
(2) B[j - 1] <= A[i]和A[i - 1] <= B[j]
ps.1 为简单起见，我推测A[i - 1]，B[j - 1]，A[i]，B[j]总是有效，即使i = 0 / i = m / j = 0 / j = n。后面讨论如何处理这些边缘值。

ps.2 为什么n >= m,因为我必须确保j是非负的，因为0 <= i <= m且j = （m + n + 1）/ 2 - i。如果n < m，则j可能是负的，这将导致错误的结果。

所以，我们需要做的就是：

在[0，m]中搜索i,使得B[j - 1] <= A[i]和A[i - 1] <= B[j]，（其中j = （m + n + 1） / 2 - i）
我们可以按照下面描述的步骤进行二进制搜索：

<1>设置imin = 0，imax = m，然后开始在[imin，imax]中搜索

<2>设置i = （imin + imax） / 2，j =（m + n + 1）/ 2 - i

<3>现在我们有len（left_part） == len（right_part）。而且只有3种情况
我们可能会遇到：
<a> B[j - 1] <= A[i]和A[i - 1] <= B[j]
意味着我们找到了对象i，所以停止搜索。
<b> B[j - 1]> A[i]
意味着A[i]太小了。我们必须增加i得到B[j - 1] <= A[i]。也就是说，我们必须调整搜索范围为[i + 1，imax].
设置imin = i + 1，然后转到<2>。
<c> A[i - 1]> B[j]
意味着A[i - 1]太大了。我们必须减少i得到A [i-1] <= B [j]。也就是说，我们必须将搜索范围调整为[imin，i - 1]。
设置imax = i - 1，并转到<2>。

当找到对象i时，中位数是：
max(A[i - 1]，B[j - 1])（当m + n为奇数时）或（max（A[i - 1]，B[j - 1]）+ min（A[i]，B[j]））/ 2（当m + n为偶数时）

现在让我们考虑边缘值i = 0，i = m，j = 0，j = n其中A [i-1]，B [j-1]，A [i]，B [j]可能不存在。实际上这种情况要容易。

我们需要做的是确保max（left_part）<= min（right_part）。
因此，如果i和j不是边值（意味着A [i-1]，B [j-1]，A [i]，B [j]都存在），
那么我们必须检查两个B [j-1] <= A [i]和A [i-1] <= B [j]。
但是如果A [i-1]，B [j-1]，A [i]，B [j]中的某些不存在，那么我们不需要检查这两个条件中的一个（或两个）。
例如，如果i = 0，则A [i-1]不存在，那么我们不需要检查A [i-1] <= B [j]。

总结起来我们需要做的是：在[0，m]中搜索i：
（j == 0或i == m或B [j-1] <= A [i]）和（i == 0或j == n或A [i-1] <= B [j]）其中j =（m + n + 1）/ 2 - i
在搜索循环中，我们只会遇到三种情况：

<a>（j == 0或i == m或B [j-1] <= A [i]）和（i == 0或j == n或A [i-1] <= B [j]）
意味着i是完美的，我们可以停止搜索。

<b> j> 0且i <m且B [j - 1]> A [i]
意味着i太小了，我们必须增加它。

<c> i> 0且j <n且A [i - 1]> B [j]
意味着i太大了，我们必须减少它。

*/