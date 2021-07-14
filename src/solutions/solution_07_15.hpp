//
// Created by sword on 2021/7/14.
//

#ifndef LEETCODE_SOLUTION_07_15_HPP
#define LEETCODE_SOLUTION_07_15_HPP

#include "stdc++.h"

class Solution_1818 {
    static constexpr auto MOD = 1000000007;
    int binarySearch(vector<int>& array, int target, int size) {
        int left = 0;
        int right = size - 1;
        int mid;

        if (target > array[right]) {
            return array[right];
        } else if (target < array[left]) {
            return array[left];
        }

        while(left <= right) {
            mid = left + (right - left) / 2;
            if (array[mid] == target) {
                return target;
            } else if (array[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        auto absL = abs(array[left] - target);
        auto absR = abs(array[right] - target);
        return absL < absR? array[left]: array[right];
    };
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        auto size = static_cast<int>(nums1.size());

        vector<int> sorted1 = nums1;
        std::sort(sorted1.begin(), sorted1.end(), std::less<>());

        int maxFitVal = INT_MIN;
        int absSum = 0;

        for (int i = 0; i < size; i++) {
            auto& a = nums1[i];
            auto& b = nums2[i];

            auto absSub = abs(a - b);
            absSum += absSub;
            absSum %= MOD;

            auto fitA = binarySearch(sorted1, b, size);
            maxFitVal = std::max(maxFitVal, abs(abs(fitA - b) - absSub));
        }

        auto ans = absSum - maxFitVal;
        while(ans < 0) {
            ans += MOD;
        }
        return ans;
    }
};

class Solution_658 {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto size = static_cast<int>(arr.size());

        int left = 0;
        int right = size - k;

        while (left < right) {
            int mid = left + (right - left) / 2;
            // 如果判断条件写了=，则说明 |a-x| = |b-x| 时 a > b 则a距离近
            if (x - arr[mid] > arr[mid + k] - x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};

#endif //LEETCODE_SOLUTION_07_15_HPP
