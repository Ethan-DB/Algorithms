// O(n)空间复杂度
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        int position = len - (k % len);
        vector<int>ans;
        
        //先放后半部分
        for(int i = position; i < len; i++){
            ans.push_back(nums[i]);
        }
        
        for(int i = 0; i < position; i++){
            ans.push_back(nums[i]);
        }
        nums = ans;
    }
    
};