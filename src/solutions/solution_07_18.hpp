//
// Created by sword on 2021/7/18.
//

#ifndef LEETCODE_SOLUTION_07_18_HPP
#define LEETCODE_SOLUTION_07_18_HPP

#include "stdc++.h"
#include "utils.hpp"

class Solution10_02 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int size = static_cast<int>(strs.size());
        // lambda 不靠谱
        struct _hash {
            size_t operator()(const array<int, 26>& arr) const {
                size_t hash = 0;
                for (int i = 25; i >= 0; i--) {
                    hash += hash * 31 + arr[i];
                }
                return hash;
            }
        };

        unordered_map<array<int, 26>, int, _hash> situations;


        vector<vector<int>> indices(size + 1, vector<int>{});

        int situationCnt = 0;

        for (int i = 0; i < size; i++) {
            const auto& str = strs.at(i);
            array<int, 26> situation = {};
            for (auto& ch: str) {
                situation[ch - 'a']++;
            }

            auto it = situations.find(situation);
            if (it == situations.end()) {
                situationCnt++;
                indices[situationCnt].emplace_back(i);
                situations.insert(pair<array<int, 26>, int>(situation, situationCnt));
            } else {
                int situationNum = it->second;
                indices[situationNum].emplace_back(i);
            }
        }

        vector<vector<string>> result(situationCnt, vector<string>{});

        const auto _cmp = [&strs](int a, int b) {
            return strs[a] < strs[b];
        };
        for (int i = 1; i <= situationCnt; i++) {
            auto& index = indices.at(i);
            if (!index.empty()) {
                std::sort(index.begin(), index.end(), _cmp);
                for (auto& idx: index) {
                    result[i - 1].emplace_back(strs[idx]);
                }
            }
        }

        return result;
    }
};

class FooBar {
private:
    int n;

    // 保证 [Foo在Bar执行后, 程序开始执行] 这两个时间点能够运行的promise
    promise<void> promiseFoo = {};
    // 保证 [Bar在Foo执行后] 这个时间点能够运行的promise
    promise<void> promiseBar = {};

public:
    explicit FooBar(int _n): n(_n) {
        promiseFoo.set_value();				// 设置promise的值，使得能够从future端get得到
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            promiseFoo.get_future().get();
            promiseFoo = promise<void> {};	// 相当于清除了promiseFoo的状态，当然只是权宜之计
            // printFoo();
            promiseBar.set_value();			// 设置promiseBar的值
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            promiseBar.get_future().get();
            promiseBar = promise<void> {};	// 重置promiseBar
            // printBar();
            promiseFoo.set_value();			// 设置promiseFoo的值
        }
    }

    template<class FB>
    static void TestFooBar(FB& fooBar) {
        LOG_DEBUG_TIME();

        thread t1(&FB::bar, std::addressof(fooBar), []() { printf("bar"); });
        thread t2(&FB::foo, std::addressof(fooBar), []() { printf("foo"); });

        t1.join();
        t2.join();
    }
};


class FooBar2 {
private:
    int n;
    atomic<bool> foo_done = false;

public:
    FooBar2(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {

        for (int i = 0; i < n; i++) {
            while (foo_done) std::this_thread::yield();
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            foo_done = true;
        }
    }

    void bar(function<void()> printBar) {

        for (int i = 0; i < n; i++) {
            while (!foo_done) std::this_thread::yield();
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            foo_done = false;
        }
    }
};


#define ZERO 0
#define ODD  1
#define EVEN 2

class ZeroEvenOdd {
private:
    int n = 0;
    atomic<int> curState;

public:
    explicit ZeroEvenOdd(int _n): n(_n) {
        curState.store(ZERO, std::memory_order_release);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n; i++) {
            while (curState.load(std::memory_order_acquire) != ZERO) {
                std::this_thread::yield();
            }
            printNumber(0);
            if (i % 2 == 0) {
                curState.store(ODD, std::memory_order_release);
            } else {
                curState.store(EVEN, std::memory_order_release);
            }
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            while (curState.load(std::memory_order_acquire) != EVEN) {
                std::this_thread::yield();
            }
            printNumber(i);
            curState.store(ZERO, std::memory_order_release);
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            while (curState.load(std::memory_order_acquire) != ODD) {
                std::this_thread::yield();
            }
            printNumber(i);
            curState.store(ZERO, std::memory_order_release);
        }
    }

    template<class T>
    static void TestZeroEvenOdd(T& zeo) {
        static const auto printNumber = [](int num) {
            printf("%d ", num);
        };
        thread te(&T::even, &zeo, printNumber);
        thread to(&T::odd, &zeo, printNumber);
        thread tz(&T::zero, &zeo, printNumber);

        tz.join(); te.join(); to.join();
    }
};

#undef ZERO
#undef ODD
#undef EVEN

#endif //LEETCODE_SOLUTION_07_18_HPP
