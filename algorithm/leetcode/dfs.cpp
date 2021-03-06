class Solution {
public:
	/**
	 * 37. Sudoku Solver
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
1. Each of the digits 1-9 must occur exactly once in each row.
2. Each of the digits 1-9 must occur exactly once in each column.
3. Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

Empty cells are indicated by the character '.'.

A sudoku puzzle...

...and its solution numbers marked in red.

Note:
The given board contain only digits 1-9 and the character '.'.
You may assume that the given Sudoku puzzle will have a single unique solution.
The given board size is always 9x9.

problem:
https://leetcode.com/problems/sudoku-solver/description/
	 */
	void solveSudoku(vector<vector<char>>& board) {
		for(int i=0; i<9; ++i)
			for(int j=0; j<9; ++j){
				if(board[i][j] == '.'){
					for(int k=0; k<9; ++k){
						board[i][j] = '1'+k;
						if(isValid(board, i, j) && solveSudoku(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}				
			}

		return true;
	}
	bool isValid(const vector<vector<char>> &board, int x, int y){
		int i,j;
		for(i=0; i<9; i++) //检查y列
			if(i != x && board[i][y] == board[x][y])
				return false;

		for(int j=0; j<9; j++) //检查x行
			if(j!=y && board[x][j] == board[x][y])
				return false;

		for(i=3*(x/3); i<3*(x/3+1); i++)
			for(j=3*(y/3); j<3*(y/3+1); j++)
				if((i != x || j !=y) && board[i][j]==board[x][y])
					return false;

		return true;
	}

	/**
	 * 40. Combination Sum II
Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]

problem:
https://leetcode.com/problems/combination-sum-ii/description/
	 */
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());

		vector<vector<int>> result;
		vector<int> path;
		dfs(candidates, path, result, target, 0);

		return result;
	}
	void dfs(const vector<int> &candidates, vector<int> &path, 
		vector<vector<int>> &result, int gap, int start){
		if(gap == 0){ //找到一个合法解
			result.push_back(path);
			return;
		}

		int previous = -1;
		for(size_t i=start; i<candidates.size(); ++i){
			//candidates[i]最多只用一次
			if(previous == candidates[i]) continue;

			if(gap < candidates[i]) return; //剪枝

			previous = candidates[i];

			path.push_back(candidates[i]);
			dfs(candidates, path, result, gap-candidates[i], i+1);
			path.pop_back(); //恢复环境
		}
	}

	/**
	 * 51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that 
no two queens attack each other.


Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, 
where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:
Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
	 */
	//设置一个数组vector<int> C(n,0), C[i]表示第i行皇后所在的列编号，即在位置(i,C[i])上放了一个皇后，
	//这样放了一个皇后，这样用一个以为数组，就能记录整个棋盘。
	//深搜+剪枝
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> result;
		vector<int> C(n, -1); //C[i]表示第i行皇后所在的列编号
		dfs(C, result, 0);
		return result;
	}
	void dfs(vector<int> &C, vector<vector<string>> &result, int row){
		const int N=C.size();
		if(row == N){ //终止条件，找到一个可行解
			vector<string> solution;
			for(int i=0; i<N; ++i){
				string s(N, '.');
				for(int j=0; j<N; ++j){
					if(j == C[i]) s[j] = 'Q';
				}
				solution.push_back(s);
			}
			result.push_back(solution);
			return ;
		}

		for(int j=0; j<N; ++j){ //扩展状态，一列一列的试
			const bool ok = isValid(C, row, j);
			if(!ok) continue; //剪枝，如果非法，继续尝试下一列
			//执行扩展动作
			C[row] = j;
			dfs(C, result, row+1);
			//撤销动作
			//C[row] = -1;
		}
	}
	bool isValid(const vector<int> &C, int row, int col){
		for(int i=0; i<row; ++i){
			//在同一列
			if(C[i] == col) return false;
			//在同一对角线上
			if(abs(i-row) == abs(C[i]-col)) return false;
		}
		return true;
	}
	//深搜+剪枝
	//三个变量用于剪枝
	vector<bool> columns; //表示已经放置的皇后占据了那些列
	vector<bool> main_diag; //占据了哪些主对角线
	vector<bool> anti_diag; //占据了哪些副对角线
	vector<vector<string>> solveNQueens(int n){
		this->columns = vector<bool>(n, false);
		this->main_diag = vector<bool>(2*n-1, false);
		this->anti_diag = vector<bool>(2*n-1, false);

		vector<vector<string>> result;
		vector<int> C(n, -1);
		dfs(C, result, 0);
		return result;
	}
	void dfs(vector<int> &C, vector<vector<string>> &result, int row){
		const int N = C.size();
		if(row == N){
			vector<string> solution;
			for(int i=0; i<N; ++i){
				string s(N, '.');
				for(int j=0; j<N; ++j){
					if(j == C[i]) s[j] = 'Q';
				}
				solution.push_back(s);
			}
			result.push_back(solution);
			return;
		}

		for(int j=0; j<N; ++j){
			const bool ok = !columns[j] && !main_diag[row-j+N-1] && !anti_diag[row+j];
			if(!ok) continue; //剪枝，如果非法，继续尝试下一列
			//执行扩展动作
			C[row] = j;
			columns[j] = main_diag[row-j+N-1] = anti_diag[row+j] = true;
			dfs(C, result, row+1);
			columns[j] = main_diag[row-j+N-1] = anti_diag[row+j] = false;
		}
	}

	/**
	 * 52. N-Queens II
The n-queens puzzle is the problem of placing n queens on an n×n chessboard 
such that no two queens attack each other.



Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Example:
Input: 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
	 */
	//深搜+剪枝
	int totalNQueens(int n) {
		this->count = 0;

		vector<int> C(n, 0);
		dfs(C, 0);
		return this->count;
	}
	int count;
	void dfs(vector<int> &C, int row){
		const int N = C.size();
		if(row == N){
			++this->count;
			return;
		}

		for(int j=0; j<N; ++j){
			const bool ok = isValid(C, row, j);
			if(!ok) continue; //剪枝
			C[row] = j;
			dfs(C, row+1);
		}
	}
	bool isValid(const vector<int> &C, int row, int col){
		for(int i=0; i<row; ++i){
			//在同一列
			if(C[i] == col) return false;
			//在同一对角线上
			if(abs(i-row) == abs(C[i]-col)) return false;
		}

		return true;
	}
	//深搜+剪枝
	int totalNQueens(int n){
		this->count = 0;
		this->columns = vector<bool>(n, false);
		this->main_diag = vector<bool>(2*n-1, false);
		this->anti_diag = vector<bool>(2*n-1, false);

		vector<int> C(n,0);
		dfs(C,0);
		return this->count;
	}
	int count;
	vector<bool> columns;
	vector<bool> main_diag;
	vector<bool> anti_diag;
	void dfs(vector<int> &C, int row){
		const int N = C.size();
		if(row == N){
			++this->count;
			return;
		}

		for(int j=0; j<N; ++j){
			const bool ok = !columns[j] && !main_diag[row-j+N] && !anti_diag[row+j];
			if(!ok) continue;
			C[row] = j;
			columns[j] = main_diag[row-j+N] = anti_diag[row+j] = true;
			dfs(C, row+1);
			columns[j] = main_diag[row-j+N] = anti_diag[row+j] = false;
		}
	}

	/**
	 * 62. Unique Paths
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. 
The robot is trying to reach the bottom-right corner of the grid 
(marked 'Finish' in the diagram below).

How many possible unique paths are there?

Above is a 7 x 3 grid. How many possible unique paths are there?

Note: m and n will be at most 100.

Example 1:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:
Input: m = 7, n = 3
Output: 28

problem:
https://leetcode.com/problems/unique-paths/description/
	 */
	//深搜,小集合可以过，大集合超时
	int uniquePaths(int m, int n) {
		if(m < 1 || n<1) return 0; //终止条件

		if(m==1 && n==1) return 1; //收敛条件

		return uniquePaths(m-1, n) + uniquePaths(m, n-1);
    }

    //备忘录法，对前面的深搜加缓存
    int uniquePaths(int m, int n){
    	f = vector<vector<int>> (m, vector<int>(n, 0)); //f[x][y]表示从(0,0)到(x,y)的路径条数
    	f[0][0] = 1;
    	return dfs(m-1, n-1);
    }
    vector<vector<int>> f; //缓存
    int dfs(int x, int y){
    	if(x<0 || y<0) return 0;

    	if(x==0 && y==0) return f[0][0]; 

    	if(f[x][y] > 0){
    		return f[x][y];
    	}else{
    		return f[x][y] = dfs(x-1,y) + dfs(x,y-1);
    	}
    }
    //动规
    int uniquePaths(int m, int n){
    	vector<int> f(n, 0);
    	f[0] = 1;

    	for(int i=0; i<m; i++){
    		for(int j=0; j<n; j++){
    			//左边的f[j]，表示更新后的f[j]，与公式中的f[i][j]对应
    			//右边的f[j]，表示老的f[j]，与公式中的f[i-1][j]对应
    			f[j] = f[j] + f[j-1];
    		}
    	}

    	return f[n-1];
    }

    /**
     * 63. Unique Paths II
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. 
The robot is trying to reach the bottom-right corner of the grid 
(marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: m and n will be at most 100.

Example 1:
Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
     */
    //备忘录法，深搜+缓存
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		const int m = obstacleGrid.size();
		const int n = obstacleGrid[0].size();

		if(obstacleGrid[0][0] || obstacleGrid[m-1][n-1]) return 0;

		f = vector<vector<int>> (m, vector<int>(n,0));
		f[0][0] = obstacleGrid[0][0] ? 0 : 1;

		return dfs(obstacleGrid, m-1, n-1);
	}
	vector<vector<int>> f;
	int dfs(const vector<vector<int>> &obstacleGrid, int x, int y){
		if(x<0 || y<0) return 0;

		//(x,y)是障碍
		if(obstacleGrid[x][y]) return 0;

		if(x==0 && y==0) return f[0][0];

		if(f[x][y] > 0){
			return f[x][y];
		}else{
			return f[x][y] = dfs(obstacleGrid, x-1, y) + dfs(obstacleGrid, x, y-1);
		}
	}
	//动规
	int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid){
		const int m = obstacleGrid.size();
		const int n = obstacleGrid[0].size();
		if(obstacleGrid[0][0] || obstacleGrid[m-1][n-1]) return 0;

		vector<int> f(n, 0);
		f[0] = obstacleGrid[0][0] ? 0 : 1;

		for(int i=0; i<m; i++){
			f[0] = f[0] == 0 ? 0:(obstacleGrid[i][0]?0:1);
			for(int j=1; j<n; j++)
				f[j] = obstacleGrid[i][j] ? 0:(f[j]+f[j-1]);
		}

		return f[n-1];
	}

	/**
	 * 79. Word Search
	 * Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, 
where "adjacent" cells are those horizontally or vertically neighboring. 
The same letter cell may not be used more than once.

Example:

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
	 */
	bool exist(vector<vector<char>>& board, string word) {
		const int m = board.size();
		const int n = board[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(dfs(board, word, 0, i, j, visited))
					return true;

		return false;
	}
	static bool dfs(const vector<vector<char>> &board, const string &word,
		int index, int x, int y, vector<vector<bool>> &visited){
		if(index == word.size())
			return true;

		if(x<0 || y<0 || x>=board.size() || y>=board[0].size())
			return false;

		if(visited[x][y]) return false;

		if(board[x][y] != word[index]) return false;

		visited[x][y]=true;
		bool ret = dfs(board, word, index+1, x-1, y, visited) || //上
					dfs(board, word, index+1, x+1, y, visited) || //下
					dfs(board, word, index+1, x, y-1, visited) || //左
					dfs(board, word, index+1, x, y+1, visited); //右

		visited[x][y] = false;

		return ret;
	}

	/**
	 * 93. Restore IP Addresses
Given a string containing only digits, restore it by returning all possible valid 
IP address combinations.

Example:
Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]

problem:
https://leetcode.com/problems/restore-ip-addresses/description/
	 */
	vector<string> restoreIpAddresses(string s) {
		vector<string> result;
		vector<string> ip;
		dfs(s, ip, result, 0);
		return result;
	}
	void dfs(string s, vector<string>& ip, vector<string>& result, size_t start){
		if(ip.size() == 4 && start==s.size()){
			result.push_back(ip[0] + '.' + ip[1] + '.' + ip[2] + '.' +ip[3]);
			return;
		}

		if(s.size() - start > (4-ip.size()) * 3)
			return; //剪枝
		if(s.size() - start < (4-ip.size()))
			return; //剪枝

		int num=0;
		for(size_t i=start; i<start+3; i++){
			num = num*10 + (s[i] - '0');

			if(num < 0 || num>255) continue; //剪枝

			ip.push_back(s.substr(start, i-start+1));
			dfs(s, ip, result, i+1);
			ip.pop_back();

			if(num == 0) break;
		}
	}

	/**
	 * 131. Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

Example:
Input: "aab"
Output:
[
  ["aa","b"],
  ["a","a","b"]
]

problem:
https://leetcode.com/problems/palindrome-partitioning/description/

solution:
https://leetcode.com/problems/palindrome-partitioning/discuss/41964/Clean-C++-backtracking-solution
	 */
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        if(s.empty()) return res;

        vector<string> path; //一种partition方案
        dfs(0, s, path, res);

        return res;
    }
    void dfs(int index, string &s, vector<string>& path, vector<vector<string>> &res){
    	if(index == s.size()){
    		res.push_back(path);
    		return;
    	}
    	for(int i=index; i<s.size(); ++i){
    		if(isPalindrome(s, index, i)){
    			path.push_back(s.substr(index, i-index+1));
    			dfs(i+1, s, path, res); //继续往下搜索
    			path.pop_back(); //撤销上上行
    		}
    	}
    }
    bool isPalindrome(const string& s, int start, int end){
    	while(start <= end){
    		if(s[start++] != s[end--])
    			return false;
    	}

    	return true;
    }

    /**
     * 200. Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
An island is surrounded by water and is formed by connecting adjacent lands 
horizontally or vertically. You may assume all four edges of the grid are all 
surrounded by water.

Example 1:
Input:
11110
11010
11000
00000
Output: 1

Example 2:
Input:
11000
11000
00100
00011
Output: 3

problem:
https://leetcode.com/problems/number-of-islands/description/
     */
    int m,n;
	int numIslands(vector<vector<char>>& grid) {
		int count = 0;
		n = grid.size();
		if(n == 0) return 0;
		m = grid[0].size();

		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(grid[i][j] == '1'){
					dfs(grid, i, j);
					++count;
				}
			}
		}

		return count;
	}
	void dfs(vector<vector<char>> &grid, int i, int j){
		if(i<0 || j<0 || i>=n || j>=m || grid[i][j] != '1') return;

		grid[i][j] = '0';
		dfs(grid, i+1, j);
		dfs(grid, i-1, j);
		dfs(grid, i, j+1);
		dfs(grid, i, j-1);
	}

	/**
	 * 207. Course Schedule
There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have 
to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, 
is it possible for you to finish all courses?

Example 1:
Input: 2, [[1,0]] 
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. 
Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
	 */
	//BFS
    bool canFinish(int numCourses, vector<pair<int,int>> &prerequisites){
    	vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
    	vector<int> degrees = compute_indegree(graph);
    	for(int i=0; i<numCourses; i++){
    		int j=0;
    		for(; j<numCourses; j++)
    			if(!degrees[j]) break;
    		if(j == numCourses) return false;
    		degrees[j] = -1;
    		for(int neigh : graph[j])
    			degrees[neigh]--;
    	}

    	return true;
    }
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>> &prerequisites){
    	vector<unordered_set<int>> graph(numCourses);
    	for(auto pre : prerequisites)
    		graph[pre.second].insert(pre.first);
    	return graph;
    }
    vector<int> compute_indegree(vector<unordered_set<int>>& graph){
    	vector<int> degrees(graph.size(), 0);
    	for(auto neighbors: graph)
    		for(int neigh : neighbors)
    			degrees[neigh]++;

    	return degrees;
    }
	//DFS
	vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites){
		vector<unordered_set<int>> graph(numCourses);
		for(auto pre : prerequisites)
			graph[pre.second].insert(pre.first);

		return graph;
	}
	bool dfs_cycle(vector<unordered_set<int>>& graph, int node, vector<bool>& onpath, vector<bool>& visited){
		if(visited[node]) return false;
		onpath[node] = visited[node] = true;
		for(int neigh : graph[node])
			if(onpath[neigh] || dfs_cycle(graph, neigh, onpath, visited))
				return true;

		return onpath[node] = false;
	}
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites){
		vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
		vector<bool> onpath(numCourses, false), visited(numCourses, false);
		for(int i=0; i<numCourses; i++){
			if(!visited[i] && dfs_cycle(graph, i, onpath, visited))
				return false;
		}

		return true;
	}
};
