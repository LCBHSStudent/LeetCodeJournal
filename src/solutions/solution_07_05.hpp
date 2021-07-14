//
// Created by sword on 2021/7/5.
//

#ifndef LEETCODE_SOLUTION_07_05_HPP
#define LEETCODE_SOLUTION_07_05_HPP

#include "stdc++.h"

class Solution_726 {
    bool isUpperCase(char ch) {
        return ch >= 'A' && ch <= 'Z';
    }
    bool isLowerCase(char ch) {
        return ch >= 'a' && ch <= 'z';
    }
    int isNumber(char ch) {
        if (ch >= '0' && ch <= '9') {
            return ch - '0';
        } else {
            return -1;
        }
    }

public:
    // 败因:  1.没写好方便获取原子名称和数字大小的函数
    //        2. 如果使用hash表而不是vector能很方便的将当前一层的统计结果累加到上一层
    string _countOfAtoms(const string& formula) {
        struct Item {
            Item(int _count, char first, char last = '\0') {
                count = _count;
                atom[0] = first;
                atom[1] = last;
            }
            char    atom[2] = {};
            int     count = 1;
        };
        map<string, int> atomMap = {};
        stack<vector<Item>> layers = {};

        char curAtom[2] = {'\0', '\0'};
        int curCount[4] = {-1, -1, -1, -1};

        vector<Item> curLayer = {};

        for (int i = 0; i < formula.size(); i++) {
            // 添加Item到项目集
            if (curAtom[0] != '\0') {
                int cnt = 0;
                int _pow = 0;
                for (int j = 3; j >= 0; j--) {
                    if (curCount[j] == -1) {
                        continue;
                    }
                    cnt += curCount[j] * static_cast<int>(pow(10, _pow));
                    _pow++;
                }

                if (cnt == 0) {
                    curLayer.emplace_back(Item(1, curAtom[0], curAtom[1]));
                } else {
                    curLayer.emplace_back(Item(cnt, curAtom[0], curAtom[1]));
                }

                // 清空状态
                for (int& c : curCount) {
                    c = -1;
                }
                curAtom[0] = '\0';
                curAtom[1] = '\0';
            }

            // 处理原子符号
            if (isUpperCase(formula[i])) {
                curAtom[0] = formula[i];
                if (isLowerCase(formula[i+1])) {
                    curAtom[1] = formula[++i];
                }
                continue;
            }

            // 处理后缀数字
            int flag = isNumber(formula[i]);
            if (flag != -1) {
                int index = 0;
                while (flag != -1) {
                    curCount[index++] = flag;
                    flag = isNumber(formula[++i]);
                }

                continue;
            }

            if (formula[i] == '(') {
                if (!curLayer.empty()) {
                    layers.push(curLayer);
                    curLayer.clear();
                }
            } else if (formula[i] == ')') {
                if (isNumber(formula[i + 1])) {

                }
            }

        }





        string result;
        for (auto& it: atomMap) {
            result += it.first;

            if (it.second != 1) {
                result += std::to_string(it.second);
            }
        }


        return result;
    }

    string countOfAtoms(string formula) {
        int i = 0, n = formula.length();

        auto parseAtom = [&]() -> string {
            string atom;
            atom += formula[i++]; // 扫描首字母
            while (i < n && islower(formula[i])) {
                atom += formula[i++]; // 扫描首字母后的小写字母
            }
            return atom;
        };

        auto parseNum = [&]() -> int {
            if (i == n || !isdigit(formula[i])) {
                return 1; // 不是数字，视作 1
            }
            int num = 0;
            while (i < n && isdigit(formula[i])) {
                num = num * 10 + int(formula[i++] - '0'); // 扫描数字
            }
            return num;
        };

        stack<unordered_map<string, int>> stk;
        stk.push({});
        while (i < n) {
            char ch = formula[i];
            if (ch == '(') {
                i++;
                stk.push({}); // 将一个空的哈希表压入栈中，准备统计括号内的原子数量
            } else if (ch == ')') {
                i++;
                int num = parseNum(); // 括号右侧数字
                auto atomNum = stk.top();
                stk.pop(); // 弹出括号内的原子数量
                for (auto &[atom, v] : atomNum) {
                    stk.top()[atom] += v * num; // 将括号内的原子数量乘上 num，加到上一层的原子数量中
                }
            } else {
                string atom = parseAtom();
                int num = parseNum();
                stk.top()[atom] += num; // 统计原子数量
            }
        }

        auto &atomNum = stk.top();
        vector<pair<string, int>> pairs;
        for (auto &[atom, v] : atomNum) {
            pairs.emplace_back(atom, v);
        }
        sort(pairs.begin(), pairs.end());

        string ans;
        for (auto &p : pairs) {
            ans += p.first;
            if (p.second > 1) {
                ans += to_string(p.second);
            }
        }
        return ans;
    }
};

class Solution_70 {
public:
    // dp[n] = dp[n - 1](最后爬了一步) + dp[n - 2](最后爬了两步)
    int climbStairs(int n) {
        std::array<int, 3> space = {1, 2, 3};
        int lIdx = 0, mIdx = 1, rIdx = 2;

        if (n <= 3) {
            return space[n - 1];
        } else {
            while (n > 3) {
                rIdx = (rIdx + 1) % 3;
                mIdx = (mIdx + 1) % 3;
                lIdx = (lIdx + 1) % 3;

                space[rIdx] = space[lIdx] + space[mIdx];
                n--;
            }
        }
        return space[rIdx];
    }
};

class Solution_746 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int size = static_cast<int>(cost.size());

        if (size == 1) {
            return cost[0];
        } else if (size == 2) {
            return std::min(cost[0], cost[1]);
        }

        // 不用dp数组，更新每一级阶梯是由n-1还是n-2上来的更省力，并累加cost值
        for (int i = 2; i < size; i++) {
            cost[i] += std::min(cost[i - 1], cost[i - 2]);
        }

        // 最后一级爬到楼顶
        return std::min(cost[size - 2], cost[size - 1]);
    }
};

namespace Solution_offer_04 {
class Solution {
public:
    // 二分查找：错误！无法确定下一步搜索方向
    bool _findNumberIn2DArray(const vector<vector<int>>& matrix, int target) {
        int M = static_cast<int>(matrix.size());        // 行数
        int N = static_cast<int>(matrix[0].size());     // 列数

        int yL = 0, yR = M - 1;

        // 纵向二分
        while (yL <= yR) {
            int yMid = (yL + yR) / 2;
            printf("yMid: %d\n", yMid);
            bool searchLeft = false;

            if (matrix[yMid][0] > target) {
                searchLeft = true;
            } else if (matrix[yMid][N - 1] < target) {
                searchLeft = false;
            } else {
                int xL = 0, xR = N - 1;
                // 横向二分
                while (xL <= xR) {
                    int xMid = (xL + xR) / 2;
                    printf("%d \n", matrix[yMid][xMid]);

                    if (matrix[yMid][xMid] == target) {
                        return true;
                    } else if (matrix[yMid][xMid] > target) {
                        xL = xMid + 1;
                    } else if (matrix[yMid][xMid] < target) {
                        xR = xMid - 1;
                    }
                }
            }

            if (searchLeft) {
                yR = yMid - 1;
            } else {
                yL = yMid + 1;
            }
        }

        return false;
    }

    // 重写：二分查找树
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int M = static_cast<int>(matrix.size());        // 行数
        int N = static_cast<int>(matrix[0].size());     // 列数

        int curX = N - 1;
        int curY = 0;

        while (curX >= 0 && curY < M) {
            printf("%d %d\n", curX, curY);

            int val = matrix[curY][curX];
            if (val == target) {
                return true;
            } else if (target < val) {
                curX--;
            } else if (target > val) {
                curY++;
            }
        }

        return false;
    }
};
};
#endif //LEETCODE_SOLUTION_07_05_HPP
