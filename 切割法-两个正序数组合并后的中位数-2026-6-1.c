/*
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 

 
提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-100000 <= nums1[i], nums2[i] <= 1000000
*/


#include <stdio.h>
#include <limits.h>

// 辅助函数：返回两个数中的最大值
int max(int a, int b) {
    return a > b ? a : b;
}

// 辅助函数：返回两个数中的最小值
int min(int a, int b) {
    return a < b ? a : b;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // 保证 nums1 是较短的数组，优化二分查找效率
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    
    int m = nums1Size;
    int n = nums2Size;
    
    // 二分查找的左右边界（在较短数组 nums1 上二分）
    // 注意：这里 i 表示 nums1 的切割点，范围是 [0, m]
    int left = 0;
    int right = m;
    
    // 虚拟数组总长度的一半（向上取整）
    // 保证左半边元素个数 >= 右半边
    int halfLen = (m + n + 1) / 2;
    
    while (left <= right) {
        // nums1 的切割点
        int i = left + (right - left) / 2;
        // nums2 的切割点，由 halfLen - i 决定
        int j = halfLen - i;
        
        // 处理边界情况：获取切割点左右的值
        // nums1 切割点左侧的值
        int nums1LeftMax = (i == 0) ? INT_MIN : nums1[i - 1];
        // nums1 切割点右侧的值
        int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
        
        // nums2 切割点左侧的值
        int nums2LeftMax = (j == 0) ? INT_MIN : nums2[j - 1];
        // nums2 切割点右侧的值
        int nums2RightMin = (j == n) ? INT_MAX : nums2[j];
        
        // 判断是否找到正确的切割点
        if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
            // 找到正确的切割点，计算中位数
            if ((m + n) % 2 == 1) {
                // 奇数：中位数是左半边的最大值
                return max(nums1LeftMax, nums2LeftMax);
            } else {
                // 偶数：中位数是 (左半边最大值 + 右半边最小值) / 2
                int leftMax = max(nums1LeftMax, nums2LeftMax);
                int rightMin = min(nums1RightMin, nums2RightMin);
                return (leftMax + rightMin) / 2.0;
            }
        } else if (nums1LeftMax > nums2RightMin) {
            // nums1 的左边太大，切割点需要左移
            right = i - 1;
        } else {
            // nums2LeftMax > nums1RightMin
            // nums1 的左边太小，切割点需要右移
            left = i + 1;
        }
    }
    
    // 理论上不会执行到这里
    return 0.0;
}

