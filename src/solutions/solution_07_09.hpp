//
// Created by sword on 2021/7/9.
//

#ifndef LEETCODE_SOLUTION_07_09_HPP
#define LEETCODE_SOLUTION_07_09_HPP

#include "stdc++.h"

class Solution_17_10 {
public:
    int majorityElement(vector<int>& nums) {
        auto size = static_cast<int>(nums.size());

        int candidate = -1;
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (count == 0) {
                candidate = nums[i];
            }
            if (nums[i] == candidate) {
                count++;
            } else {
                count--;
            }
        }

        count = 0;

        for (int i = 0; i < size; i++) {
            if (nums[i] == candidate) {
                count++;
            }
        }

        return count > size / 2? candidate: -1;
    }
};

class Solution_53 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        if (size == 0) {
            return 0;
        }
        vector<int> dp(size, 0);

        dp[0] = nums[0];
        for (int i = 1; i < size; i++) {
            dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);
        }

        return *std::max_element(dp.begin(), dp.end());
    }
};

class Solution_918 {
    // 分类讨论 + 连通数组两端项目单独处理
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        if (size == 0) {
            return 0;
        }

        int sum;
        int dpMax, dpMin, maxSum, minSum;
        dpMax = maxSum = sum = nums[0];
        dpMin = minSum = 0;

        for(int i = 1; i < size; i++) {
            // 处理最大子数组和
            dpMax  = std::max(nums[i], dpMax + nums[i]);
            maxSum = std::max(maxSum, dpMax);

            // 处理[1:-2]最小子数组和
            if (i < size - 1) {
                dpMin = std::min(nums[i], dpMin + nums[i]);
                minSum = std::min(minSum, dpMin);
            }
            sum += nums[i];
        }

        return std::max(maxSum, sum - minSum);
    }
};

#endif //LEETCODE_SOLUTION_07_09_HPP
