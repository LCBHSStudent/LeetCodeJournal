//
// Created by sword on 2021/7/11.
//

#ifndef LEETCODE_SOLUTION_07_11_HPP
#define LEETCODE_SOLUTION_07_11_HPP

#include "stdc++.h"

class Solution_152 {
public:
    int maxProduct(vector<int>& nums) {
        int size = static_cast<int>(nums.size());

        if (size == 0) {
            return 0;
        }

        int minProd, maxProd, result;
        minProd = maxProd = result = nums[0];

        for (int i = 1; i < size; i++) {
            if (nums[i] < 0) {
                std::swap(maxProd, minProd);
            }
            maxProd = std::max(nums[i], nums[i] * maxProd);
            minProd = std::min(nums[i], nums[i] * minProd);

            result = std::max(maxProd, result);
        }

        return result;
    }
};

// 维护最大负、最大正乘积数组长度的两种情况变量，dp解决
class Solution_1567 {
public:
    int getMaxLen(vector<int>& nums) {
        int size = static_cast<int>(nums.size());

        int length = 0;
        int positive = 0;
        int negative = 0;
        for (auto& num: nums) {
            if (num == 0) {
                positive = negative = 0;
            } else if (num > 0) {
                positive++;
                if (negative > 0) negative++;
                length = std::max(length, positive);
            } else {
                std::swap(positive, negative);
                negative++;
                if (positive > 0) positive++;
                length = std::max(length, positive);
            }
        }

        return length;
    }
};

class Solution_275 {
public:
    int hIndex(vector<int>& citations) {
        int size = static_cast<int>(citations.size());



        int result = 0;

        int left = 0, right = size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            int refCnt = size - mid;
            if (citations[mid] >= refCnt) {
                result = refCnt;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return result;
    }
};

class Solution_274 {
public:
    int hIndex(vector<int>& citations) {
        int size = static_cast<int>(citations.size());
        std::sort(citations.begin(), citations.end(), std::less<>());
        int result = 0;

        int left = 0, right = size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            int refCnt = size - mid;
            if (citations[mid] >= refCnt) {
                result = refCnt;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return result;
    }
};

#endif //LEETCODE_SOLUTION_07_11_HPP
