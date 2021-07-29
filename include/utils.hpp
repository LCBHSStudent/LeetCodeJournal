//
// Created by sword on 2021/7/3.
//

#ifndef LEETCODE_UTILS_HPP
#define LEETCODE_UTILS_HPP

#include <iostream>
#include <iterator>
#include <chrono>

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

/**------------------------------------------------------------------------------
 * @brief LeetCode 输入解析器
 * @author DFW
 * @date 2021-07-06
 * @example auto input = InputParser<std::string>().getVecInVec("./1418_53.ipt");
 * -------------------------------------------------------------------------------
 */

#include <fstream>
#include <sstream>
#include <type_traits>

template<typename T>
concept IsInteger = std::is_integral_v<T>;

template<typename T>
class InputParser {
public:
    InputParser() = default;
    InputParser(char _lRegionSym, char _rRegionSym, char _splitter)
            : lRegionSym(_lRegionSym)
            , rRegionSym(_rRegionSym)
            , splitter(_splitter) {}

    template<typename DataType = T>
    DataType parseData(const std::string& file, int& index) {
        static_assert(false, "Unsupportable data type to extract.");
    }

    template<>
    T parseData<T>(const std::string& file, int& index) requires IsInteger<T> {
        char* pStart = const_cast<char*>(file.data()) + index;
        char* pEnd = pStart;

        static constexpr auto getVal = [](char* _p1, char** _p2) -> T {
            switch(sizeof(T)) {
            case 2:
                return static_cast<unsigned char> (strtol(_p1, _p2, 10));
            case 4:
                return strtol(_p1, _p2, 10);
            case 8:
                return strtoll(_p1, _p2, 10);
            default:
                return strtol(_p1, _p2, 10);
            }
        };

        auto val = getVal(pStart, &pEnd);
        index += static_cast<int>(pEnd - pStart) - 1;

        return val;
    }

    template<>
    std::string parseData<std::string>(const std::string& file, int& index) {
        while(file[index] == '\"') {
            index++;
        }
        int backupIdx = index;

        for (index; index < file.size(); index++) {
            if (file[index] == '\"') {
                break;
            }
        }

        return file.substr(backupIdx, index - backupIdx);
    }


    std::vector<T> getVec(const char* inputPath) {
        std::vector<T> data;
        auto&& file = readFile2Str(inputPath);

        int depth = 0;
        for (int i = 0; i < file.size(); i++) {
            if (file[i] == lRegionSym) {
                if (depth >= 1) {
                    break;
                } else {
                    depth = 1;
                }
                continue;
            } else if (file[i] == rRegionSym) {
                depth--;
                if (depth == 0) {
                    break;
                }
            } else if (file[i] == splitter) {
                continue;
            } else {
                auto val = parseData<T>(file, i);
                data.emplace_back(val);
            }
        }

        return data;
    }

    std::vector<std::vector<T>> getVecInVec(const char* inputPath) {
        std::vector<std::vector<T>> data;
        auto&& file = readFile2Str(inputPath);

        int depth = 0;

        std::vector<T> row = {};
        for (int i = 0; i < file.size(); i++) {
            if (file[i] == lRegionSym) {
                if (depth >= 1) {
                    depth++;
                    row.clear();
                } else {
                    depth = 1;
                }
                continue;
            } else if (file[i] == rRegionSym) {
                depth--;
                if (depth == 0) {
                    break;
                } else {
                    data.emplace_back(row);
                    continue;
                }
            } else if (file[i] == splitter) {
                continue;
            } else {
                auto val = parseData<T>(file, i);
                row.emplace_back(val);
            }
        }
        return data;
    }

protected:
    std::string readFile2Str(const char* inputPath) {
        std::ifstream fin(inputPath);
        if (!fin.is_open()) {
            throw std::runtime_error(
                    string("failed to open local file at: ") + inputPath
            );
        }

        std::ostringstream tmp;
        tmp << fin.rdbuf();

        // fin.close();

        return tmp.str();
    }

private:
    char lRegionSym = '[', rRegionSym = ']', splitter = ',';
};

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define LOG_DEBUG_TIME() RAIITimer __block_timer(__FUNCSIG__)
#else
#define LOG_DEBUG_TIME() RAIITimer __block_timer(__PRETTY_FUNCTION__)
#endif

class RAIITimer {
    using Clock = std::chrono::high_resolution_clock;
    using DurationType = std::chrono::microseconds;
    using TimePoint = Clock::time_point;
public:
    explicit RAIITimer(const std::string& msg)
        : m_msg(msg)
    {
        m_begin = Clock::now();
    }

    virtual ~RAIITimer() {
        auto cur = Clock::now();
        auto cost = std::chrono::duration_cast<DurationType>(cur - m_begin);

        std::cout << "<" << m_msg << "> " << cost /* << typeid(DurationType).name() */ << std::endl;
    }

private:
    TimePoint m_begin;
    std::string m_msg;
};

template<class T>
class NullNodeValue {
public:
    static constexpr auto NULL_NODE = "";
};

template<>
class NullNodeValue<int> {
public:
    static constexpr auto NULL_NODE = INT_MAX;
};


template<class T>
class BTreeGenerator {
public:
    const static auto NULL_NODE = NullNodeValue<T>::NULL_NODE;

    struct TreeNode {
        T val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    static vector<TreeNode> genFromArray(const T* begin, size_t length) {
        auto it = begin;

        vector<TreeNode> list(length, TreeNode());

        for (auto i = 0; i < length; i++) {
            list[i].val = *(begin + i);

            // has right
            if (i * 2 + 2 < length && *(begin + (i * 2 + 2)) != NULL_NODE) {
                list[i].right = list.data() + (i * 2 + 2);
                // has left
                if (i * 2 + 1 < length && *(begin + (i * 2 + 1)) != NULL_NODE) {
                    list[i].left = list.data() + (i * 2 + 1);
                } else {
                    list[i].left = nullptr;
                }
            } else {
                list[i].right = nullptr;
            }
        }

        return list;
    }
};

#endif //LEETCODE_UTILS_HPP
