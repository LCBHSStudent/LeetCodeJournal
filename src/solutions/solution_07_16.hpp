//
// Created by sword on 2021/7/16.
//

#ifndef LEETCODE_SOLUTION_07_16_HPP
#define LEETCODE_SOLUTION_07_16_HPP

#include "stdc++.h"

namespace offer {

class Solution_53_I {
public:
    int search(vector<int>& nums, int target) {
        auto size = static_cast<int>(nums.size());

        int result = 0;

        int left = 0;
        int right = size - 1;
        int mid = -1;

        while (left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                result++;
                break;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid;
            }
        }

        for (int i = mid + 1; i < size; i++) {
            if (nums[i] == target) {
                result++;
            } else {
                break;
            }
        }
        for (int i = mid - 1; i >= 0; i--) {
            if (nums[i] == target) {
                result++;
            } else {
                break;
            }
        }

        return result;
    }
};

};

class Solution_34 {
public:
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int leftIdx = binarySearch(nums, target, true);
        int rightIdx = binarySearch(nums, target, false) - 1;
        if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
            return vector<int>{leftIdx, rightIdx};
        }
        return vector<int>{-1, -1};
    }
};

class Solution_264 {
public:
    int nthUglyNumber(int n) {
        static const auto factors = {2, 3, 5};

        vector<int> dp(n, 0);
        dp[0] = 1;

        int pos2 = 0;
        int pos3 = 0;
        int pos5 = 0;

        for (int i = 1; i < n; i++) {
            int mul2 = dp[pos2] * 2;
            int mul3 = dp[pos3] * 3;
            int mul5 = dp[pos5] * 5;
            int min = std::min(mul2, std::min(mul3, mul5));

            dp[i] = min;
            if (min == mul2) {
                pos2++;
            }
            if (min == mul3) {
                pos3++;
            }
            if (min == mul5) {
                pos5++;
            }
        }

        return dp[n - 1];
    }
};

class Solution_96 {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }

        return dp[n];
    }
};

#endif //LEETCODE_SOLUTION_07_16_HPP
