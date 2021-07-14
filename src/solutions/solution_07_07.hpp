//
// Created by sword on 2021/7/7.
//

#ifndef LEETCODE_SOLUTION_07_07_HPP
#define LEETCODE_SOLUTION_07_07_HPP

#include "stdc++.h"

class Solution_1711 {
    inline static const auto MOD = 1000000007;
public:
    int countPairs(vector<int>& deliciousness) {
        uint64_t result = 0;

        if (deliciousness.empty()) {
            return 0;
        }

        std::vector<int> countMap((2 << 20) + 4, 0);

        int maxVal = -1;
        for (const auto& val: deliciousness) {
            maxVal = std::max(val, maxVal);
            countMap[val]++;
        }

        int maxSum = maxVal * 2;


        for (int i = 0; i <= maxVal; i++) {
            decltype(countMap)::value_type thisCount = countMap[i];
            if (thisCount > 0) {
                for (int sum = 1; sum <= maxSum; sum = sum << 1) {
                    if (sum - i < 0) {
                        continue;
                    }
                    if (sum - i == i) {
                        result += static_cast<uint64_t>(thisCount) * static_cast<uint64_t>(thisCount - 1);
                        continue;
                    }
                    int count = countMap[sum - i];
                    if (count > 0) {
                        result += static_cast<uint64_t>(count) * static_cast<uint64_t>(thisCount);
                    }
                }
            }
        }

        return static_cast<int>(result / 2 % MOD);
    }
};

class Solution_55 {
public:
    bool canJump(vector<int>& nums) {
        auto size = nums.size();
        if (size <= 1) {
            return true;
        }

        std::vector<int> dp(size, 0);
        dp[0] = nums[0];

        for (int i = 1; i < size; i++) {
            if (i > dp[i - 1]) {
                break;
            }
            dp[i] = std::max(i + nums[i], dp[i - 1]);
        }

        return dp[size - 1] >= size - 1;
    }
};

class Solution_45 {
public:
    int jump(vector<int>& nums) {

        int maxPos      = 0;
        int endPoint    = 0;
        int result      = 0;
        auto size = nums.size();

        for (int i = 0; i < size - 1; i++) {
            if (maxPos >= i) {
                maxPos = std::max(maxPos, i + nums[i]);
                if (i == endPoint) {
                    endPoint = maxPos;
                    result++;
                }
            }
        }

        return result;
    }
};

namespace offer {

class Solution_10 {
public:
    int numWays(int n) {
        int lIdx = 0, mIdx = 1, rIdx = 2;
        std::vector<int> space = {1, 2, 0};
        if (n == 0) return 1;
        if (n == 1) return space[0];
        if (n == 2) return space[1];

        for (int i = 2; i < n; i++) {
            space[rIdx] = space[mIdx] % 1000000007 + space[lIdx] % 1000000007;
            if (i == n - 1) {
                return space[rIdx] % 1000000007;
            } else {
                lIdx = (lIdx + 1) % 3;
                mIdx = (mIdx + 1) % 3;
                rIdx = (rIdx + 1) % 3;
            }
        }

        return space[rIdx] % 1000000007;
    }
};

class Solution_11 {
    bool judge(int l, int m, int r) {
        return (m <= l && m <= r) && (m != r || m != l);
    }
public:
    int minArray(vector<int>& numbers) {
        int low = 0;
        int high = static_cast<int>(numbers.size()) - 1;

        while (low < high) {
            int pivot = low + (high - low) / 2;
            if (numbers[pivot] < numbers[high]) {
                high = pivot;
            }
            else if (numbers[pivot] > numbers[high]) {
                low = pivot + 1;
            }
            else {
                high -= 1;
            }
        }
        return numbers[low];
    }
};

};

#endif //LEETCODE_SOLUTION_07_07_HPP
