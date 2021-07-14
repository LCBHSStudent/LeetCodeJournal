//
// Created by sword on 2021/7/8.
//

#ifndef LEETCODE_SOLUTION_07_08_HPP
#define LEETCODE_SOLUTION_07_08_HPP

#include "stdc++.h"

class Solution_930 {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int result = 0;
        int size = static_cast<int>(nums.size());

        std::vector<int> map(nums.size() + 1, 0);

        int sum = 0;
        for (int i = 0; i < size; i++) {
            map[sum]++;
            sum += nums[i];
            if (sum - goal >= 0) {
                result += map[sum - goal];
            }
        }

        return result;
    }
};

class Solution_724 {
public:
    int pivotIndex(vector<int>& nums) {
        int size = static_cast<int>(nums.size());

        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += nums[i];
        }

        int prefixSum = 0;
        for (int i = 0; i < size; i++) {
            if ((sum - nums[i]) % 2 == 0 && prefixSum == (sum - nums[i]) / 2) {
                return i;
            }
            prefixSum += nums[i];
        }

        return -1;
    }
};

class Solution_560 {
public:
    int subarraySum(vector<int>& nums, int k) {
        auto size = static_cast<int>(nums.size());
        unordered_map<int, int> sumMap = {};

        int sum = 0;
        int result = 0;
        for (int i = 0; i < size; i++) {
            sumMap[sum]++;
            sum += nums[i];
            result += sumMap[sum - k];
        }

        return result;
    }
};

class Solution_1248 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        auto size = static_cast<int>(nums.size());
        unordered_map<int, int> sumMap = {};

        int sum = 0;
        int result = 0;
        for (int i = 0; i < size; i++) {
            sumMap[sum]++;
            if (nums[i] % 2 != 0) {
                sum++;
            }
            result += sumMap[sum - k];
        }

        return result;
    }
};

class Solution_974 {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        auto size = static_cast<int>(nums.size());
        // 和为0的情况
        unordered_map<int, int> sumMap = {{0, 1}};

        int sum = 0;
        int result = 0;

        for (int i = 0; i < size; i++) {
            sum += nums[i];
            int modulus = (sum % k + k) % k;
            ++sumMap[modulus];
        }

        for (auto [x, cx]: sumMap) {
            result += cx * (cx - 1) / 2;
        }

        return result;
    }
};

class Solution_523 {
public:
    // 递增数组
    bool checkSubarraySum(vector<int>& nums, int k) {
        bool result = false;
        auto size = static_cast<int>(nums.size());

        unordered_map<int, int> modMap = {{0, -1}};
        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += nums[i];
            int mod = sum % k;

            auto it = modMap.find(mod);
            if (it != modMap.end()) {
                if (i - it->second >= 2) {
                    result = true;
                    break;
                }
            } else {
                modMap.insert(pair<int, int>(mod, i));
            }
        }

        return result;
    }
};

#endif //LEETCODE_SOLUTION_07_08_HPP
