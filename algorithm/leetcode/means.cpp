/**
 * 细节实现题
 * 不用特定的算法，考察代码的熟练度
 */
class Solution {
public:
	/**
     * 7. Reverse Integer
     * Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output:  321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range. 
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
     */
    //考虑 1. 负数的情况 2. 溢出的情况 (正溢出 && 负移除 x = -2147483648(即-2^31) )
	int reverse(int x) {
        long long r=0;
        long long t=x;
        t = t>0?t:-t;

        for(;t;t/=10)
        	r= r*10 + t%10;

        bool sign = x>0?false:true;
        if(r > 2147483647 || (sign && r>2147483648)){
        	return 0;
        }else{
        	if(sign)
        		return -r;
        	else
        		return r;
        }
	}

  /**
   * 9. Palindrome Number
   * Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:
Input: 121
Output: true

Example 2:
Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Follow up:
Coud you solve it without converting the integer to a string?
   */
	//不断地区第一位和最后一位进行比较，相等则取第二位和倒数第二位，知道完成比较或者找到了不一致的位
	bool isPalindrome(int x) {
		if(x<0)
			return false;

		int d=1;
		while(x/d >= 10)
			d *=10;

		while(x>0){
			int q = x/d;
			int r = x%10;
			if(q != r)
				return false;
			x = x%d/10;
			d /= 100;
		}

		return true;
	}

	/**
	 * 78. Subsets
	 * Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
	 */
	vector<vector<int>> subsets(vector<int>& nums) {
        sort (nums.begin(), nums.end());
        int elem_num = nums.size();
        int subset_num = pow (2, elem_num);
        vector<vector<int> > subset_set (subset_num, vector<int>());
        for (int i = 0; i < elem_num; i++)
            for (int j = 0; j < subset_num; j++)
                if ((j >> i) & 1)
                    subset_set[j].push_back (nums[i]);
        return subset_set;
    }

	/**
	 * 50. Pow(x, n)
	 * Implement pow(x, n).

Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100
	 */
	//二分法，$x^n = x^{n/2} * x^{n/2} * x^{n\%2}$
    double myPow(double x, int n) {
        if(n<0)
        	return 1.0/power(x,-n);
        else 
        	return power(x,n);
    }
    double power(double x,int n){
    	if(n==0)
    		return 1;
    	double v = power(x,n/2);
    	if(n%2==0)
    		return v*v;
    	else
    		return v*v*x;
    }

    /**
     * 119. Pascal's Triangle II
     * Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?
     */
    //滚动数组
    vector<int> getRow(int rowIndex) {
        vector<int> array;
        for(int i=0;i<=rowIndex;i++){
        	for(int j=i-1;j>0;j--)
        		array[j] = array[j-1] + array[j];
        	array.push_back(1);
        }

        return array;
    }

    /**
     * 152. Maximum Product Subarray
     * Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
     */
	int maxProduct(vector<int>& nums) {
		int n = nums.size();

	    if(n==1) 
	    	return nums[0];
	    int pMax=0, nMax=0, m = 0;

	    for(int i=0; i<n; i++){
	        if(nums[i]<0) swap(pMax, nMax);
	        pMax = max(pMax*nums[i], nums[i]);
	        nMax = min(nMax*nums[i], nums[i]);
	        m = max(m, pMax);
	    }
	    return m;
    }	
}