//
// Created by sword on 2021/7/17.
//

#ifndef LEETCODE_SOLUTION_07_17_HPP
#define LEETCODE_SOLUTION_07_17_HPP

#include "stdc++.h"

namespace offer {

class Solution_42 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        if (size == 0) {
            return 0;
        }
        int dp = nums[0];
        int max = dp;

        for (int i = 1; i < size; i++) {
            dp = std::max(dp + nums[i], nums[i]);
            if (dp > max) {
                max = dp;
            }
        }

        return max;
    }
};

};

#endif //LEETCODE_SOLUTION_07_17_HPP
