//解法一，i表示开始处的指针，j表示后面一个指针
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,bool> hash;
        int len = s.size();
        int i = 0, j = 0, ans = 0;
        for(;i < len; i++){
            while (j < len && hash[s[j]] == false){
                hash[s[j]] = true;
                ans = max(ans, j-i+1);
                j++;
            }
            hash[s[i]] = false;
        }
        return ans;
    }
};


// 解法二
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int map[256] = {0};
        int len = s.size();
        int i = 0, j = 0, ans = 0;
        for(;i < len; i++){
            while (j < len && map[s[j]] == 0 ){
                map[s[j]] = 1;
                ans = max(ans, j-i+1);
                j++;
            }
            map[s[i]] = 0;
        }
        return ans;
    }
};

//解法三： 最为精炼，其中i表示后一个指针，j表示前一个指针
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int>m;
        int res = 0;
        for(int i = 0, j = 0; i < s.size(); i++){
            m[s[i]]++;
            while(m[s[i]] > 1) m[s[j++]]--;
            res = max(res, i -j + 1);
        }
        return res;
    }
};


//解法四 双指针经典模板
