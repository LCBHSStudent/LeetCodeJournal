//
// Created by sword on 2021/7/19.
//

#ifndef LEETCODE_SOLUTION_07_19_HPP
#define LEETCODE_SOLUTION_07_19_HPP

#include "stdc++.h"

class Solution_1838 {
public:
    int maxFrequency(vector<int>& nums, int k) {
        auto size = static_cast<int>(nums.size());
        size_t result = 0;

        std::sort(nums.begin(), nums.end(), std::less<>());

        if (size == 1) {
            return 1;
        }

        size_t left = 0;
        size_t right = 1;

        size_t needs = 0;

        while(right < size) {
            needs += (right - left) * (nums[right] - nums[right - 1]);
            while (needs > k) {
                needs -= nums[right] - nums[left];
                left++;
            }
            result = std::max(result, right - left + 1);
            right++;
        }


        return result;
    }
};

#endif //LEETCODE_SOLUTION_07_19_HPP
