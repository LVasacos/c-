
/*这里讲二分查找的方法，还有更巧妙的方法，见"切割法-两个正序数组合并后的中位数-2026-6-1.c"*/

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


/*
思路：即找出合并数组的第（m+n）/2个数或者第（m+n）/2个数和第（m+n）/2+1个数的平均值。一个个遍历显然太慢，怎么在不创建一个新数组遍历的情况下找出中位数呢？采用二分查找：
     假设我们要找第k个元素，则从m和n中各取前k/2个元素，比较两个片段尾项的大小（即第k/2个元素），值更小的那个数组的前 k/2 个元素一定不包含第 k 小的元素，可以全部排除。不妨从合并数组和原数组中去掉较小片段的k/2个元素，那么我们就从找第k个元素变成了找第k/2个元素，更新k=k-k/2。重复以上的工作，只用比较每个片段的尾项，当k=1时，则两个数组中较小的第一个数就是所
     找的数。
*/
#include <stdio.h>
#include <limits.h>

// 找两个有序数组中第 k 小的元素
int findKth(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    // 保证 nums1 是较短的那个数组，简化边界处理
    if (nums1Size > nums2Size) {
        return findKth(nums2, nums2Size, nums1, nums1Size, k);
    }
    
    // 边界情况1：较短的数组为空
    if (nums1Size == 0) {
        return nums2[k - 1];
    }
    
    // 边界情况2：找第1小的元素
    if (k == 1) {
        return nums1[0] < nums2[0] ? nums1[0] : nums2[0];
    }
    
    // 正常情况：各取 k/2 个元素比较
    // 注意处理数组长度不足 k/2 的情况
    int i = (nums1Size < k/2) ? nums1Size : k/2;
    int j = (nums2Size < k/2) ? nums2Size : k/2;
    
    if (nums1[i - 1] < nums2[j - 1]) {
        // 排除 nums1 的前 i 个元素
        return findKth(nums1 + i, nums1Size - i, nums2, nums2Size, k - i);
    } else {
        // 排除 nums2 的前 j 个元素
        return findKth(nums1, nums1Size, nums2 + j, nums2Size - j, k - j);
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total = nums1Size + nums2Size;
    
    if (total % 2 == 1) {
        // 奇数：找第 (total/2 + 1) 个元素
        return findKth(nums1, nums1Size, nums2, nums2Size, total/2 + 1);
    } else {
        // 偶数：找第 (total/2) 和 第 (total/2 + 1) 个元素的平均值
        int left = findKth(nums1, nums1Size, nums2, nums2Size, total/2);
        int right = findKth(nums1, nums1Size, nums2, nums2Size, total/2 + 1);
        return (left + right) / 2.0;
    }
}

