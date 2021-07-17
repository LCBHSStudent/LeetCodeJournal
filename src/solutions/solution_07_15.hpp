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

class Solution_1846 {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int size = static_cast<int>(arr.size());

        std::sort(arr.begin(), arr.end(), std::less<>());
        if (arr[0] != 1) {
            arr[0] = 1;
        }
        for (int i = 1; i < size; i++) {
            if (arr[i] - arr[i - 1] > 1) {
                arr[i] = arr[i - 1] + 1;
            }
        }

        return arr[size - 1];
    }
};

class Solution_42 {
public:
    int trap(vector<int>& height) {
        int size = static_cast<int>(height.size());

        vector<int> dpL(size, 0);
        vector<int> dpR(size, 0);

        int result = 0;

        for (int i = size - 2; i >= 1; i--) {
            dpR[i] = std::max(dpR[i + 1], height[i + 1]);
        }

        for (int i = 1; i <= size - 2; i++) {
            dpL[i] = std::max(dpL[i - 1], height[i - 1]);
            result += std::max(0, std::min(dpL[i], dpR[i]) - height[i]);
        }

        return result;
    }
};

class Solution_413 {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        auto size = static_cast<int>(nums.size());
        vector<int> dp(size, 0);

        int maxLength = 0;
        for (int i = 2; i < size; i++) {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                maxLength++;
                dp[i] = dp[i - 1] + maxLength;
            } else {
                dp[i] = dp[i - 1];
                maxLength = 0;
            }
        }

        return dp[size - 1];
    }
};

class Solution_446 {
public:
    static int numberOfArithmeticSlices(vector<int>& nums) {
        auto size = static_cast<int>(nums.size());
        vector<vector<int>> dp(size, vector<int>{});


    }
};

class Solution_118 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result(numRows);
        result[0] = {1};
        for (int i = 1; i < numRows; i++) {
            vector<int> row(i + 1, 0);
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    row[j] = 1;
                } else {
                    row[j] = result[i - 1][j - 1] + result[i - 1][j];
                }
            }
            result[i] = row;
        }

        return result;
    }
};

class Solution_119 {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1, 0);
        row[0] = 1;
        for (int i = 1; i <= rowIndex; i++) {
            for (int j = i; j >= 1; j--) {
                row[j] = row[j - 1] + row[j];
            }
        }

        return row;
    }
};

class Solution_91 {
public:
    int numDecodings(string s) {
        int size = static_cast<int>(s.size());
        vector<int> dp(size + 1, 0);
        dp[0] = 1;
        dp[1] = s[0] == '0'? 0: 1;

        for (int i = 1; i < size; i++) {
            int idx = i + 1;
            if (s[i] == '0') {
                if (s[i - 1] == '1' || s[i - 1] == '2') {
                    dp[idx] = dp[idx - 2];
                } else {
                    return 0;
                }
            } else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6')) {
                dp[idx] = dp[idx - 1] + dp[idx - 2];
            } else {
                dp[idx] = dp[idx - 1];
            }
        }

        return dp[size];
    }
};

#endif //LEETCODE_SOLUTION_07_15_HPP
