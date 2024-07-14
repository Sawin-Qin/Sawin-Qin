

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <variant>
#include <array>
#include <algorithm> //for std::sort

//本文件为针对  leetcode上的刷题记录保存的代码，以供后续参考

//第一题
/*给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
你可以按任意顺序返回答案。

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
*/

class Solution1 {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            //it->first为（target-nums[i]）的键,it->second为值
            
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
            //查找不到键值，则储备数据以方便后续查找配对
        }
        return {};
    }
};


//第49题
/*
给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
字母异位词 是由重新排列源单词的所有字母得到的一个新单词。

示例 1:
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

本质需求为对比两个哈希表
*/

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& str){
    //本处的作用为定义一个哈希表数组，该哈希表数组的作用为将  
    /*
    1. 将所有的字符串进行重新排序，并将排序后的数据放进数组中
    */

    std::unordered_map<std::string,std::vector<std::string>> map_filter;
    for (std::vector<std::string>::const_iterator it = str.begin();it!=str.end();++it){
        std::string key_value = *it;
        std::sort(key_value.begin(),key_value.end());
        map_filter[key_value].emplace_back(*it);

    } 

    std::vector<std::vector<std::string>> result;
    for (auto it = map_filter.begin();it != map_filter.end();++it){
        result.emplace_back(it->second);
 
    }
    return result;    

}



/*
128题
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4
*/

class Solution128 {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = std::max(longestStreak, currentStreak);   //max函数在algorithm库中
            }
        }

        return longestStreak;           
    }
};


int main(){
    //验证第1 题
    std::vector<int> nums = {3,2,4,1,0};
    std::vector<std::string> strs_for_49 = {"eat","tea","tan","ate","nat","bat"};
    std::vector<int> nums_for_128  = {1,32,45,2,3,4,5};
    int target_1 = 6;
    std::vector<int> the_result_1;
    std::vector<std::vector<std::string>> the_result_2;
    int the_result_3;

    Solution1 two_num_for_target;
    Solution128 for_longest_stack;

    the_result_1 = two_num_for_target.twoSum(nums,target_1);
    std::cout << "第一题的输出结果为：" << std::endl;
    for (std::vector<int>::iterator it = the_result_1.begin();it != the_result_1.end();++it){
        std::cout << *it << "";
    }
    


    //验证第49题

    std::cout << "第49题的输出结果为：" << std::endl;
    the_result_2 = groupAnagrams(strs_for_49);
    for (std::vector<std::vector<std::string>>::iterator it = the_result_2.begin();it != the_result_2.end();++it){
        
        std::cout << "[" << " ";
        for (auto &ele : *it){
            std::cout << ele << " ";
        }

 
        std::cout << "]" << " ";
         


    }
    


    //验证第128题
    the_result_3 = for_longest_stack.longestConsecutive(nums_for_128);
     std::cout << the_result_3 << std::endl;

    return 0;
}