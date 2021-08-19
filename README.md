# **算法及其设计技术 (:satisfied: Do algorithms for fun :grin:)**

![Github stars](https://img.shields.io/github/stars/Ethanzjp/Algorithms.svg)
![github language](https://img.shields.io/badge/language-C++-green.svg) 
![](https://img.shields.io/github/license/Ethanzjp/Algorithms.svg) 
![](https://img.shields.io/github/forks/Ethanzjp/Algorithms.svg)

## **1. 概述**

包括但不限于以下内容：

* [Basic Data Structure and Algorithms](#lllllaaa)
	* [**heap**](#heap)
	* [**Stack**](#st)
	* [**Queue**](#q)
	* [**Union Find**](#uf)
	* [**Map/Set**](#ms)
	* [**Trees**](#t) 
	* [**Trie**](#trie)
	* [**Linked List**](#ll)
		* [**LRU/LFU**](#lrufu)
	* [**sort**](#s)
	* [**Two Pointers**](#tp)
	* [**Prefix Sum**](#psum)
	* [**Bit Manipulation**](#bm)
	* [**Binary Search**](#bs)
	* [**细节题**](#xijie)
		* [**Big Integer**](#bi)
	* [**经典算法应用**](#jingdian)
		* [Permutation](#jingdianp)
		* [Cycle Detection](#jingdianCD)
		* [KMP](#kmp)
		* [Manacher](#manacher)
	* [**Graph Algorithms**](#ggg)
		* [**DFS & BFS**](#gadfs)
		* [**topology sort**](#gats)
		* [**shorest path**](#gasp)
		* [**minimum spanning tree**](#gamst)
		* [**Network Flow**](#netf)
	* [**Math**](#math)
* [Databases](#db)
	* [SQL Solutions](#dbsql)
	* [Deep Learning for Databases](#dld)
	* Crowdsourcing and NP-hard
* [Concurrency Algoritms](#cal)
* [Design techniques of Algorithms](#dddddddaa)
	* [**Dynamic Programming**](#dp)
		* [Knapsack](#knapsack)
		* [Longest Increasing Subsequence](#lis)
		* [Largest Common Subsequence](#lcs)
		* [Edit Distance](#edd)
		* [Memorization](#mem)
	* [**Greedy Algorithms**](#gd)
		* [Intervals Problems](#interval)
		* [huffman tree](#huft)
	* [**Recursive**](#rec)
	* [**Brute Force Search**](#bf)
		* [**DFS + Backtrack**](#dfs)
		* [**BFS + Branch-and-Bound**](#bfs)
	* **Linear Programming**
	* **Approximation Algorithms**
	* **Random Algorithms**
* [**Analisys of time and space complexity**](#ats)

**在刷题出错时，如何定位错误？两个方法：printf（wrong answer）和删代码（Runtime Error和Segment Fault），如果删掉代码后，不报错RE或者SF，说明删掉的这段代码有问题，重点在删掉的这段代码中排查数组越界、没有读入正确的操作数等错误。**


## **<span id=lllllaaa>2. 算法列表</span>**

* <span id=xijie>细节题</span>
	* [LeetCode2.cpp Add Two Numbers AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode2.cpp)
	* [LeetCode6.cpp ZigZag Conversion AC 等差数列题目](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode6.cpp)
	* [LeetCode12.cpp Integer to Roman AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode12.cpp)
	* [LeetCode14.cpp Longest Common Prefix AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode14.cpp)
	* [LeetCode7.cpp reverse AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode7.cpp)
	* [LeetCode9.cpp isPalindrome  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode9.cpp)
	* [LeetCode29.cpp Divide Two Integers AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode29.cpp)
	* [LeetCode13.cpp romanToInt  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode13.cpp)
	* [LeetCode1351.cpp Count Negative Numbers in a Sorted Matrix AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1351.cpp)
	* [LeetCode8.cpp String to Integer (atoi) AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode8.cpp)
	* [**LeetCode240.cpp Search a 2D Matrix II**  采用二分检索存在TLE，存在一个O(r+c)的线性时间算法](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode240.cpp)
	* [LeetCode54.cpp AC 矩阵搜索，n皇后问题也用到了类似的技巧](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode54.cpp)
	* [LeetCode509.cpp Fibonacci Number AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode509.cpp)
		* [LeetCode80.cpp Remove Duplicates from Sorted Array II AC LeetCode26 follow-up](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode80.cpp)
		* [LeetCode83.cpp Remove Duplicates from Sorted List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode83.cpp)
		* [LeetCode82.cpp Remove Duplicates from Sorted List II AC]()
	* <span id=bi>Big Integer</span>
	    * [LeetCode415.cpp Add to Array-Form of Integer AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode415.cpp)
		* [LeetCode989.cpp Add to Array-Form of Integer AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode989.cpp)
		* [LeetCode67.cpp Add Binary AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode67.cpp)
		* [LeetCode43.cpp Multiply Strings AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode43.cpp)
* <span id=jingdian>经典算法应用</span>
	* <span id=jingdianp>Permutation</span>  **本题是一个Generation in lexicographic order，具体见链接 https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order**
		* [LeetCode31.cpp Next Permutation  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode31.cpp)
		* [LeetCode46.cpp Permutations AC  **调用了LeetCode31.cpp的Next Permutation函数**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode46.cpp)
		* [LeetCode47.cpp Permutations II AC  **和LeetCode46.cpp代码完全一样**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode47.cpp)
		* [LeetCode60.cpp Permutation Sequence  AC  **LeetCode31.cpp变形题**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode60.cpp)
	* <span id=jingdianCD>Cycle Detection Algorithms</span> **本题考查环检测算法，具体见链接 https://en.wikipedia.org/wiki/Cycle_detection**
		* [**LeetCode141.cpp Linked List Cycle AC**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode141.cpp)
		* [**LeetCode142.cpp Linked List Cycle II AC**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode142.cpp)
		* [**LeetCode287.cpp Find the Duplicate Number AC** **数组其实也是一个链表，如果能带着这个观点，这道题目完全和142相同**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode287.cpp)
		* [**LeetCode876.cpp Middle of the Linked List AC**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode876.cpp)
	* <span id=kmp>KMP</span>
	    * [kmp.cpp brute search](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/kmp.cpp)
		* [LeetCode28.cpp Implement strStr() AC KMP](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode28.cpp)
		* [LeetCode459.cpp Repeated Substring Pattern AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode459.cpp)
		* [LeetCode214.cpp Shortest Palindrome AC KMP](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode214.cpp)
		* [POJ3461.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ3461.cpp)
		* [POJ2406.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ2406.cpp)
		* [HDUOJ2087.cpp AC 无重叠子串](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ2087.cpp)
		* [HDUOJ1711.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ1711.cpp)
		* [HDUOJ3746.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ3746.cpp)
		* [HUSTOJ1010.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HUSTOJ1010.cpp)
		* [HDUOJ1358.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ1358.cpp)
		* [POJ2752.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ2752.cpp)
	* <span id=manacher>Manacher</span>
		* [LeetCode5.cpp Longest Palindromic Substring AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode5.cpp)
		* [LeetCode647.cpp Palindromic Substrings AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode647.cpp)
		* [POJ3974.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ3974.cpp)
		* [HDUOJ3068.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ3068.cpp)
		* [HDUOJ4513.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ4513.cpp)
* <span id=bm>Bit Manipulation</span>
    * [LeetCode78.cpp Subsets AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode78.cpp)
	* [LeetCode191.cpp Number of 1 Bits AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode191.cpp)
	* [NowCoder996C.cpp 64位整数乘法](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NowCoder996C.cpp)
* <span id=tp>Two pointers</span>
    * 双指针问题包括（前向型指针(滑动窗口（将O(n^2)算法做成O(n)的算法）和快慢指针两类)、相向型指针（O(n)）、两个数组（典型题目为mergesort中的merge过程）三种大类）
	* [LeetCode167.cpp Two Sum II - Input array is sorted  相向型指针 AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode167.cpp)
	* [LeetCode88.cpp Merge Sorted Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode88.cpp)
	* [LeetCode1.cpp Two Sum AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1.cpp)
	* [LeetCode15.cpp 3Sum  two pointer   AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode15.cpp)
	* [LeetCode16.cpp 3Sum Closest AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode16.cpp)
	* [LeetCode18.cpp 4Sum two pointer AC  相向型指针](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode18.cpp)
	* [LeetCode713.cpp Subarray Product Less Than K AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode713.cpp)
	* [LeetCode3.cpp  Longest Substring Without Repeating Characters O(n) "slide window search" AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/Leetcode3.cpp)
	* [Leetcode209.cpp  Minimum Size Subarray Sum "slide window search"  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode209.cpp)
	* [LeetCode76.cpp Minimum Window Substring   O(256n)  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode76.cpp)
	* [LeetCode628.cpp Maximum Product of Three Numbers AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode628.cpp)
	* [LeetCode21.cpp merge Two Lists AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode21.cpp)
	* [LeetCode4.cpp find Median Sorted Arrays AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode4.cpp)
	* [LeetCode493.cpp Reverse Pairs  AC 相向型指针](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode493.cpp)
	* [LeetCode11.cpp Container With Most Water AC 相向型指针](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode11.cpp)
	* [LeetCode26.cpp Remove Duplicates from Sorted Array AC 前向型指针](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode26.cpp)
	* [LeetCode27.cpp Remove Element AC 前向型指针](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode27.cpp)
* <span id=psum>**prefix sum**</span>
	* **one dimemsion prefix sum**
		* [LeetCode560.cpp Subarray Sum Equals K AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode560.cpp)
		* [LeetCode523.cpp Continuous Subarray Sum AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode523.cpp)
		* [LeetCode974.cpp Subarray Sums Divisible by K TLE](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode974.cpp)
		* [LeetCode303.cpp Range Sum Query - Immutable AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode303.cpp)
		* [LeetCode307.cpp Range Sum Query - Mutable AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode307.cpp)
		* [POJ3468.cpp Range Sum](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ3468.cpp)
	* **two dimension prefix sum**
		* [LeetCode304.cpp Range Sum Query 2D - Immutable AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode304.cpp)
* <span id=s>sort</span>
    * [LeetCode912.cpp Sort an Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode912.cpp)
	    * implement quicksort (最快，最省空间)
		* implement merge sort
			* [LeetCode493.cpp Reverse Pairs  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode493.cpp) 
		* implement heap sort
	* Cyclic Sort
		* [LeetCode268.cpp Missing Number AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode268.cpp)
		* [LeetCode287.cpp Find the Duplicate Number AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode287.cpp)
		* [LeetCode448.cpp Find All Numbers Disappeared in an Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode448.cpp)
		* [LeetCode442.cpp Find All Duplicates in an Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode442.cpp)
	* Counting Sort & Radix Sort
		* [LeetCode287.cpp Find the Duplicate Number AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode287.cpp)
		* [LeetCode75.cpp Sort Colors AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode75.cpp)
		* [LeetCode49.cpp Group Anagrams AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode49.cpp)
	* Intervals
		* [LeetCode56.cpp Merge Intervals AC sort+greedy](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode56.cpp)
		* [LeetCode57.cpp Insert Interval  AC   sort+greedy给出了两种方法，都能AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode57.cpp)
		* [LeetCode986.cpp Interval List Intersections  AC  merge的部分实际上和mergesort中的merge有异曲同工之处](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode986.cpp)
		* [LeetCode435.cpp Non-overlapping Intervals  AC   sort+greedy method](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode435.cpp)
		* [LeetCode452.cpp Minimum Number of Arrows to Burst Balloons  AC sort+greedy求相邻区间的交集](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode452.cpp)
		* [LeetCode1288.cpp Remove Covered Intervals  AC sort+greedy](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1288.cpp)
		* [LeetCode218.cpp The Skyline Problem](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode218.cpp)
	* Line Sweep
		* [LeetCode436.cpp Find Right Interval  AC 解法是利用map，line sweep重点步骤是按照key排序，这里使用map本身的排序特性代替](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode436.cpp)
	* [LeetCode324.cpp Wiggle Sort II AC O(nlogn)](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode324.cpp)
* Data Structure
    * <span id=ms>map and set</span>
        * [LeetCode981.cpp Time Based Key-Value Store  unordered_multimap is time limited, but map is accepted](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode981.cpp)
    	* [LeetCode287.cpp Find the Duplicate Number AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode287.cpp)
    	* [LeetCode414.cpp Third Maximum Number unordered_map + priority_queue  O(n)  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode414.cpp)
    	* [LeetCode1089.cpp Duplicate Zeros AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1089.cpp)
    	* [LeetCode239.cpp Sliding Window Maximum  AC  multiset](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode239.cpp)
    	* [LeetCode480.cpp Sliding Window Median  AC multiset](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode480.cpp)
    	* [LeetCode540.cpp Single Element in a Sorted Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode540.cpp)
    	* [LeetCode350.cpp Intersection of Two Arrays II  Hashtable  O(n)  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode350.cpp)
    	* [LeetCode217.cpp Contains Duplicate AC hash table 去重](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode217.cpp)
    	* [SimulateHashTable.cpp 拉链法解决冲突](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/SimulateHashTable.cpp)
    	* [SimulateHashTable.cpp 开放寻址法解决冲突](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/SimulateHashTable.cpp)
    	* **priority_queue and map/set can exchange at the solving min/max problem.**
    * <span  id=trie>Trie</span>
        * [LeetCode208.cpp  Implement Trie (Prefix Tree) AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode208.cpp)
        * [LeetCode211.cpp Add and Search Word - Data structure design AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode211.cpp)
    	* [HDUOJ1251.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ1251.cpp)
    	* [HDUOJ2072.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ2072.cpp)
    	* [LeetCode421.cpp AC Trie非常好的题目，如何将整数存储在trie中](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode421.cpp)
    * <span id=heap>priority_queue</span>
        * [LeetCode658.cpp Find K Closest Elements AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode658.cpp)
    	* [LeetCode703.cpp Kth Largest Element in a Stream AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode703.cpp)
        * [LeetCode973.cpp K Closest Points to Origin AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode973.cpp)
    	* [LeetCode692.cpp Top K Frequent Words  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode692.cpp)
    	* [LeetCode347.cpp Top K Frequent Elements AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode347.cpp)
    	* [LeetCode451.cpp Sort Characters By Frequency AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode451.cpp)
    	* [LeetCode215.cpp Kth Largest Element in an Array O(n+k*logn)   AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode215.cpp)
    	* [LeetCode414.cpp Third Maximum Number unordered_map + priority_queue  O(n)  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode414.cpp)
    	* [LeetCode378.cpp Kth Smallest Element in a Sorted Matrix   AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode378.cpp)
    	* [LeetCode136.cpp Single Number AC hash table](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode136.cpp)
    	* [LeetCode260.cpp Single Number III AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode260.cpp)
    	* [LeetCode387.cpp First Unique Character in a String AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode387.cpp)
    	* [**LeetCode23.cpp Merge k Sorted Lists O(nlogk)   AC**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode23.cpp)
    	* [LeetCode1046.cpp Last Stone Weight AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1046.cpp)
    	* [dijkstra_heap.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/dijkstra_heap.cpp)
    * <span id=q>queue</span>
    	* [SimulateQueue.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/SimulateQueue.cpp)
    	* [LeetCode102.cpp Binary Tree Level Order Traversal  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode102.cpp)
    	* [LeetCode107.cpp Binary Tree Level Order Traversal II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode107.cpp)
    	* [LeetCode637.cpp Average of Levels in Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode637.cpp)
    	* [LeetCode429.cpp N-ary Tree Level Order Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode429.cpp)
    	* **monotonous queue**
    		* [LeetCode239.cpp Sliding Window Maximum  AC  monotonous stack](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode239.cpp)
    		* [JZ64.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/JZ64.cpp)
    		* [NowCoder1006D.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NowCoder1006D.cpp)
    	* deque
    * <span id=ll>Linked List</span>
        * [SimulateLinkedList.cpp AC  UVa Data Structure](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/SimulateLinkedList.cpp)
        	* [SimulateDoubleLinkedList.cpp AC  UVa Data Structure](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/SimulateDoubleLinkedList.cpp)
        * [LeetCode21.cpp Merge Two Sorted Lists AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode21.cpp) 
        * [LeetCode24.cpp Swap Nodes in Pairs AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode24.cpp)
        * [LeetCode460.cpp Flatten a Multilevel Doubly Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode460.cpp)
        * [LeetCode25.cpp Reverse Nodes in k-Group AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode25.cpp)
        * [LeetCode66.cpp  Plus One AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode66.cpp)
        * [LeetCode61.cpp  Rotate List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode61.cpp)
        * [LeetCode86.cpp Partition List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode86.cpp)
        * [LeetCode206.cpp Reverse Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode206.cpp)
        * [LeetCode92.cpp Reverse Linked List II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode92.cpp)
        * [LeetCode203.cpp Remove Linked List Elements AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode203.cpp)
        * [LeetCode19.cpp Remove Nth Node From End of List O(2n) two pass algorithms   AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode19.cpp)
        * [LeetCode147.cpp Insertion Sort List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode147.cpp)
        * [LeetCode445.cpp Add Two Numbers II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode445.cpp)
        * [LeetCode83.cpp Remove Duplicates from Sorted List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode83.cpp)
            * [LeetCode82.cpp Remove Duplicates from Sorted List II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode82.cpp)
        * [LeetCode707.cpp Design Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode707.cpp)
        * [LeetCode1721.cpp Swapping Nodes in a Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1721.cpp)
        * [LeetCode160.cpp Intersection of Two Linked Lists AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode160.cpp)
		* [LeetCode543.cpp Diameter of Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode543.cpp)
        * <span id=lrufu>LRU/LFU</span>
        	* [LeetCode146.cpp LRU Cache AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode146.cpp)
		* [LeetCode1290.cpp Convert Binary Number in a Linked List to Integer AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1290.cpp)
		* [LeetCode328.cpp Odd Even Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode328.cpp)
    * stack
      * [SimulateStack.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/SimulateStack.cpp)
      * [LeetCode20.cpp Valid Parentheses AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode20.cpp)
      * [LeetCode155.cpp Min Stack AC  数组+两个小顶堆实现](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode155.cpp)
      * <span id=st>monotonous stack</span>
      	* [LeetCode496.cpp Next Greater Element I  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode496.cpp)
      	* [LeetCode503.cpp Next Greater Element II  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode503.cpp)
      	* [LeetCode739.cpp Daily Temperatures AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode739.cpp)
      	* [LeetCode1019.cpp Next Greater Node In Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1019.cpp)
    * <span id=uf>union find</span>
    	* [LeetCode128.cpp Longest Consecutive Sequence  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode128.cpp)
    	* [LeetCodeUnionFind.cpp  LeetCode并查集模板，带路径压缩](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCodeUnionFind.cpp)
    	* [HDUOJ1213.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ1213.cpp)
    	* [POJ1611.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ1611.cpp)
    	* [POJ2236.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ2236.cpp)
* <span id=bs>Binary Search</span>
    * [**LeetCode704.cpp Binary Search AC** ](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode704.cpp)
	* [**LeetCode33.cpp Search in Rotated Sorted Array AC(binary search)**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode33.cpp) 这四道题目其实延伸出很多题目，比如如何在Rotated Sorted Array中找到最小元素的下标并返回？
		* [**LeetCode81.cpp Search in Rotated Sorted Array II AC(binary search)**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode81.cpp)
		* [**LeetCode153.cpp Find Minimum in Rotated Sorted Array AC (binary search)**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode153.cpp)
		* [**LeetCode154.cpp Find Minimum in Rotated Sorted Array II AC(binary search)** (33 81 153 154解法完全一样)](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode154.cpp)
	* [LeetCode69.cpp Sqrt(x) AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode69.cpp)
	* [LeetCode367.cpp Valid Perfect Square  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode367.cpp)
	* [LeetCode278.cpp First Bad Version AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode278.cpp)
	* [LeetCode34.cpp Find First and Last Position of Element in Sorted Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode34.cpp)
	* [LeetCode374.cpp Guess Number Higher or Lower AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode374.cpp)
	* [**LeetCode162.cpp Find Peak Element AC**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode162.cpp)
	* [LeetCode852.cpp Peak Index in a Mountain Array AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode852.cpp)
	* [**LeetCode287.cpp Find the Duplicate Number Binary Search AC  interesting problem**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode287.cpp)
	* [LeetCode35.cpp Search Insert Position AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode35.cpp)
	* [LeetCode744.cpp Find Smallest Letter Greater Than Target AC(binary search)](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode744.cpp)
	* [JZ32.cpp 数字在排序数组中出现的次数 AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/JZ32.cpp)
	* [**LeetCode215.cpp Kth Largest Element in an Array binary search** O(n)时间复杂度 O(1)空间复杂度，比heap更省空间](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode215.cpp)
	* [**LeetCode378.cpp Kth Smallest Element in a Sorted Matrix   AC binary search 思路同LeetCode215.cpp**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode378.cpp)
	* [LeetCode167.cpp Two Sum II - Input array is sorted binary search](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode167.cpp)
	* [LeetCode540.cpp Single Element in a Sorted Array  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode540.cpp)
	* [LeetCode349.cpp Intersection of Two Arrays O(n)  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode349.cpp)
	* [LeetCode74.cpp Search a 2D Matrix  AC nlogn](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode74.cpp)
	* [**LeetCode653.cpp Two Sum IV - Input is a BST AC  binary search** 树形结构二分](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode653.cpp)
	* [LeetCode108.cpp Convert Sorted Array to Binary Search Tree  AC  树形结构二分](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode108.cpp)
		* [LeetCode109.cpp Convert Sorted List to Binary Search Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode109.cpp)
	* [**LeetCode230.cpp Kth Smallest Element in a BST AC (binary search & in-order traversal)**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode230.cpp)
	* [**LeetCode719.cpp Find K-th Smallest Pair Distance   (单纯的使用binary search 或者 heap均 TLE Hard)，其中binary search的方法和leetcode 215思路一致** ](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode719.cpp)
	* [**LeetCode786.cpp K-th Smallest Prime Fraction (单纯的使用binary search 或者 heap均 TLE Hard)**](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode786.cpp)
	* [LeetCode658.cpp Find K Closest Elements AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode658.cpp)
	* [LeetCode1200.cpp Minimum Absolute Difference AC  Binary search](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1200.cpp)
	* [LeetCode275.cpp H-Index II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode275.cpp)
* <span id=t>BFS and DFS of Tree，including Binary Search Tree, Binary Tree and N-ary Tree</span>
	* In-order travel
		* [LeetCode94.cpp Binary Tree Inorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode94.cpp)
		* BST
			* [LeetCode230.cpp Kth Smallest Element in a BST AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode230.cpp)
			* [LeetCode653.cpp Two Sum IV - Input is a BST AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode653.cpp)
			* [LeetCode938.cpp Range Sum of BST AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode938.cpp)
			* [LeetCode173.cpp Binary Search Tree Iterator AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode173.cpp)
			* [LeetCode530.cpp Minimum Absolute Difference in BST  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode530.cpp)
			* [LeetCode783.cpp Minimum Distance Between BST Nodes  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode783.cpp)
	* pre-order travel
		* [LeetCode257.cpp Binary Tree Paths AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode257.cpp)
		* [LeetCode129.cpp Sum Root to Leaf Numbers AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode129.cpp)
		* [LeetCode144.cpp Binary Tree Preorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode144.cpp)
		* [LeetCode589.cpp N-ary Tree Preorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode589.cpp)
		* [LeetCode671.cpp Second Minimum Node In a Binary Tree  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode671.cpp)
		* [LeetCode1022.cpp Sum of Root To Leaf Binary Numbers](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1022.cpp)
		* [LeetCode111.cpp Minimum Depth of Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode111.cpp)
		* [LeetCode112.cpp Path Sum AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode112.cpp)
		* [LeetCode113.cpp Path Sum II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode113.cpp)
	* post-order travel
		* [LeetCode145.cpp Binary Tree Postorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode145.cpp)
		* [LeetCode590.cpp N-ary Tree Postorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode590.cpp)
	* level-order travel
		* [LeetCode102.cpp Binary Tree Level Order Traversal  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode102.cpp)
		* [LeetCode662.cpp Maximum Width of Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode662.cpp)
		* [LeetCode107.cpp Binary Tree Level Order Traversal II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode107.cpp)
		* [LeetCode116.cpp Populating Next Right Pointers in Each Node AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode116.cpp)
		* [LeetCode117.cpp Populating Next Right Pointers in Each Node II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode117.cpp)
		* [LeetCode958.cpp Check Completeness of a Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode958.cpp)
		* [LeetCode637.cpp Average of Levels in Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode637.cpp)
		* [LeetCode429.cpp N-ary Tree Level Order Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode429.cpp)
		* [LeetCode222.cpp Count Complete Tree Nodes AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode222.cpp)
		* [LeetCode1161.cpp Maximum Level Sum of a Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1161.cpp)
		* [LeetCode104.cpp Maximum Depth of Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode104.cpp)
		* [LeetCode559.cpp Maximum Depth of N-ary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode559.cpp)
		* [LeetCode965.cpp Univalued Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode965.cpp)
		* [LeetCode513.cpp Find Bottom Left Tree Value AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode513.cpp)
		* [LeetCode515.cpp Find Largest Value in Each Tree Row AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode515.cpp)
		* [leetCode103.cpp Binary Tree Zigzag Level Order Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode103.cpp)
	* recursion
		* [LeetCode701.cpp Insert into a Binary Search Tree  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode701.cpp)
		* [LeetCode226.cpp Invert Binary Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode226.cpp)
		* [LeetCode404.cpp Sum of Left Leaves AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode404.cpp)
		* [LeetCode1305.cpp All Elements in Two Binary Search Trees AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1305.cpp)
		* [LeetCode1302.cpp Deepest Leaves Sum AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1302.cpp)
		* [LeetCode100.cpp Same Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode100.cpp)
		* [LeetCode114.cpp Flatten Binary Tree to Linked List AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode114.cpp)
		* [LeetCode101.cpp Symmetric Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode101.cpp)
		* [LeetCode872.cpp Leaf-Similar Trees AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode872.cpp)
		* [LeetCode700.cpp Search in a Binary Search Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode700.cpp)
		* [LeetCode110.cpp Balanced Binary Tree  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode110.cpp)
	* Construction Tree
    	* [LeetCode108.cpp Convert Sorted Array to Binary Search Tree  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode108.cpp)
    		* [LeetCode109.cpp Convert Sorted List to Binary Search Tree AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode109.cpp)
    	* [LeetCode1008.cpp Construct Binary Search Tree from Preorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1008.cpp)
        * [LeetCode105.cpp Construct Binary Tree from Preorder and Inorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode105.cpp)
    	* [LeetCode106.cpp Construct Binary Tree from Inorder and Postorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode106.cpp)
    	* [LeetCode889.cpp Construct Binary Tree from Preorder and Postorder Traversal AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode889.cpp)
		* [LeetCode17.cpp Letter Combinations of a Phone Number  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode17.cpp)
    
* <span id=ggg>Graph Algorithms</span>
    * [LeetCodeGraphTraversalTemplate.cpp  图的DFS和BFS模板，保存图时采用了邻接列表的方式，不用邻接矩阵(浪费空间和时间)](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCodeGraphTraversalTemplate.cpp)
	* <span id=gadfs>DFS</span>
		* [POJ1655.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ1655.cpp)
	* <span id=gats>Topology Sort</span>
		* [Topological Sort 拓扑排序模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/topsort.cpp)
		* [LeetCode207.cpp Course Schedule AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode207.cpp)
		* [LeetCode210.cpp Course Schedule II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode210.cpp)
		* [HDUOJ1285.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ1285.cpp)
		* [HDUOJ3342.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ3342.cpp)
	* <span id=gasp>Shortest Path</span>	
		* [Dijkstra](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/Dijkstra.cpp)
			* [Dijkstra.cpp Dijkstra稠密图最短路径模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/Dijkstra.cpp)
			* [POJ2387.cpp 稀疏图无向图单源最短路径](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ2387.cpp)
			* [POJ1724.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ1724.cpp)
			* [LeetCode743.cpp Network Delay Time AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode743.cpp)
		* [bellman-ford bellman-ford模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/bellman_ford.cpp)
			* [LeetCode743.cpp Network Delay Time AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode743.cpp)
			* [LeetCode787.cpp Cheapest Flights Within K Stops AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode787.cpp)
		* [spfa spfa模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/spfa.cpp)
			* [LeetCode743.cpp Network Delay Time AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode743.cpp)
			* [spfa_cycle.cpp  spfa判断负环模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/spfa_cycle.cpp)
			* [POJ1860.cpp]()
			* [POJ3259.cpp]()
		* [floyd](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/floyd.cpp)
			* [LeetCode743.cpp Network Delay Time AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode743.cpp)
	* <span id=gamst>MST</span>
		* [prim prim算法模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/prim.cpp)
		* [kruskal kruskal算法模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/kruskal.cpp)
			* [LeetCode684.cpp Redundant Connection]()
	* <span id=netf>Network Flow</span>
		* bipartite graph
			* [二分图判别（染色法,采用DFS实现，时间复杂度与DFS相同O(m+n)](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/bicolor.cpp)
			* [最大二分匹配 匈牙利算法,最坏情况下时间复杂度为O(mn)，但是一般情况下远小于于O(mn)](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/bimatch.cpp)
		* 最大可行流 (简称最大流，定义参加算法导论中流网络部分)
			* [EK]()
			* [Dinic/ISAP]()

|最短路径类型   | 算法 | 时间复杂度     |算法类型|
| :----------: | :-----------:  | :-----------: |:-----------:|
| 边权均为正，单源最短路径，稠密图     | 朴素dijkstra   | O(n^2)  |贪心|
|边权均为正，单源最短路径，稀疏图|heap+dijkstra|O(mlogn)|贪心|
| 边权存在负值，单源最短路径，限制最短路径<=k     | bellman-ford   | O(nm)  |离散数学、动态规划|
|边权存在负值，单源最短路径, 不限制 |SPFA|平均情况下为O(m)，最坏O(nm)|BFS优化bellman-ford|
|多源(起点)汇(终点)最短路径|floyd|O(n^3)|动态规划|


|最小生成树类型   | 算法 | 时间复杂度     |算法类型|
| :----------: | :-----------:  | :-----------: |:-----------:|
| 稠密图     | 朴素prim   | O(n^2)  |贪心|
| 稀疏图     |heap+prim|O(mlogn)|贪心|
| 稀疏图     | kruskal  | O(mlogm)|贪心|


**注意：如果点数n和边数m在同一个数量级为稀疏图，如果m和n^2在一个数量级，则该图为稠密图。**

* <span id=math>math</span>
	* [质数判定](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/prime.cpp)
		* [LeetCode204.cpp Count Primes AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode204.cpp)
		* [分解质因数模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/factor.cpp)
	* [约数判定](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/get_factor.cpp)
		* [LeetCode507.cpp Perfect Number AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode507.cpp)
		* [LeetCode1492.cpp The kth Factor of n](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1492.cpp)
	* [约数个数和约数之和](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/factor_count.cpp)
	* [最大公约数/欧几里得算法/辗转相除法](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/gcd.cpp)
	* [求欧拉函数的值](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/euler.cpp)
	* [快速幂](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/qmi.cpp)
		* [快速幂求逆元](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/qmin.cpp)
		* [NowCoder996A.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NowCoder996A.cpp)
	* [扩展欧几里得算法](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/exgcd.cpp)
		* [线性同余方程](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/ligcd.cpp)
	* [高斯消元](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/gauss.cpp)
	* 组合计数
		* [求组合数方法一](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/combination1.cpp)
		* [求组合数方法二](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/combination2.cpp)
		* [求组合数方法三](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/combination3.cpp)
		* [求组合数方法四](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/combination4.cpp)
		* [catalan number](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/catalan_num.cpp)
	* [容斥原理](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/in_ex.cpp)
	* [博弈论](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/nim_game.cpp)
		* [LeetCode877.cpp Stone Game](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode877.cpp)
		* [LeetCode292.cpp Nim Game](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode292.cpp)
* <span id=db>Databases</span>
	* <span id=dbsql>SQL solutions</span>
		* [LeetCode175.sql Combine Two Tables  AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode175.sql)
		* find kth elements
			* [LeetCode176.sql Second Highest Salary  AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode176.sql)
			* [LeetCode177.sql Nth Highest Salary AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode177.sql)
			* [LeetCode178.sql Rank Scores  AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode178.sql)
			* [LeetCode180.sql Consecutive Numbers AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode180.sql)
			* [LeetCode184.sql Department Highest Salary AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode184.sql)
			* [LeetCode185.sql Department Top Three Salaries AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode185.sql)
		* [LeetCode196.sql Delete Duplicate Emails AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode196.sql)
		* [LeetCode197.sql Rising Temperature AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode197.sql)
		* [LeetCode620.sql AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode620.sql)
		* [LeetCode626.sql AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode626.sql)
		* [LeetCode595.sql Big Countries AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode595.sql)
		* [LeetCode596.sql Classes More Than 5 Students AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode596.sql)
		* [LeetCode627.sql Swap Salary AC](https://github.com/JunpengCode/Algorithms/blob/master/Databases/LeetCode627.sql)
		* [QS.sql](https://github.com/JunpengCode/Algorithms/blob/master/Databases/QS.sql)
		* 统计参数，其中均值，最大值，最小值，平均值，计数都有内置的聚集函数
			* [Median.sql 中位数](https://github.com/JunpengCode/Algorithms/blob/master/Databases/Median.sql)
			* [ModalNumber.sql 众数](https://github.com/JunpengCode/Algorithms/blob/master/Databases/ModalNumber.sql)
	* <span id=dld>Deep Learning for Databases</span>
		* <span>Neural Network using Numpy</span>
			* [NN_01](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/01_NumpyNN.py)
			* [NN_02](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/02_NumpyTorchNN.py)
		* <span>Neural Network using Pytorch</span>
			* [NN_03](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/03_StandardPytorchNN.py)
			* [NN_04](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/04_StandardNNPytorchAutoGrad.py)
			* [NN_05](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/05_TorchNN.py)
		* <span>Linear Model</span>
			* [Linear_01](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/01_linearModel.py)
			* [Linear_02](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/02_linearModel.py)
			* [Linear_03](https://github.com/JunpengCode/Algorithms/blob/master/MachineLearning4DB/03_linearModel.py)
		* <span>[Deep Learning](https://github.com/EthanDBer/Algorithms/tree/master/ML4DB)</span>
* <span id=cal>Concurrency Algorithms</span>
	* [LeetCode1114.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Concurrency/LeetCodeConcurrencySolution/LeetCode1114.cpp)
	* [LeetCode1115.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Concurrency/LeetCodeConcurrencySolution/LeetCode1115.cpp)
	* [CUDA Programming](https://github.com/JunpengCode/Algorithms/blob/master/Concurrency/CUDA-Programming)
	* [Thread-Parallel-Programming](https://github.com/JunpengCode/Algorithms/blob/master/Concurrency/Thread-Parallel-Programming)

## **<span id=dddddddaa>3. 算法设计技术</span>**

* <span id=dp>Dynamic Programming</span>
	* 坐标型
		* [LeetCode322.cpp Coin Change  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode322.cpp)
		* [LeetCode62.cpp Unique Paths AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode62.cpp)
		* [LeetCode152.cpp Maximum Product Subarray AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode152.cpp)
		* [LeetCode10.cpp Regular Expression Matching AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode10.cpp)
		* [LeetCode55.cpp Jump Game DP(TLE) 存在一个greedy的解](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode55.cpp)
	* <span id=knapsack>背包型</span>
		* **一定要注意背包问题初始化的含义，何时为0，何时为INF，何时为-INF；其次要注意f[i]到含义是<=i还是=i,这与初始化有关**
		* **背包模型参见dd大神的github https://github.com/tianyicui/DP-Book**
	    * 0-1背包问题
			* [01背包最值型裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/knapsack.cpp)
				* [51node1085.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/51node1085.cpp)
				* [POJ3624.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ3624.cpp)
				* [HDUOJ2602.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/HDUOJ2602.cpp)
				* [FZUOJ2214.cpp 超大背包问题，需要做一个等价的转换](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/FZUOJ2214.cpp)
			* [01背包计数型裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/knapsackcnt.cpp)
			    * [NowCoder1042A.cpp 数字组合](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NowCoder1042A.cpp)
		* 完全背包问题
			* [完全背包最值型裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/comknapsack.cpp)
				* [intSplit.cpp 整数划分](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/intSplit.cpp)
			* 完全背包计数型
				* [NowCoder1042B.cpp 自然数拆分](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NowCoder1042B.cpp)
		* 多重背包问题
			* [多重背包最值型裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/mulknapsack1.cpp)
			* [多重背包最值型裸题二进制优化模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/mulknapsack2.cpp)
			* [多重背包最值型单调队列优化模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/mulknapsack3.cpp)
			* [POJ1276.cpp](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ1276.cpp)
		* 混合背包问题
			* [混合背包裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/mixknap.cpp)
		* 分组背包问题
			* [分组背包最值型裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/groupknapsack.cpp)
		* 二维费用的背包问题
			* [二维费用的01背包最值型裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/twoknapsack.cpp)
		* [背包问题求具体方案](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/knapsackways.cpp)
		* [有依赖的背包裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/treeknap.cpp)
	* 线性DP
		* 定义：递推关系存在一个近似的线性关系，我们就称为线性DP，区别于树形DP，不需要严格地将DP分型。
		* [triangleDP.cpp 数字三角形](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/triangleDP.cpp)
		* <span id=lis>最长上升子序列(LIS)</span>
			* 求LIS的长度
				* [POJ2533.cpp 最长上升子序列](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ2533.cpp)
				* [LeetCode300.cpp Longest Increasing Subsequence AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode300.cpp)
				* [maxLISLength.cpp 贪心方法求LIS的长度，适合N很大的情况](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/maxLISLength.cpp)
				* [NOI3532.cpp 最长上升子序列和 AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NOI3532.cpp)
				* [NOI4977.cpp 怪盗基德的滑翔翼 AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NOI4977.cpp)
			* 求一个LIS的解 (同求LIS的长度，只要在其上稍加变形即可)
				* [POJ2533.cpp 最长上升子序列](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ2533.cpp)
				* [LeetCode300.cpp Longest Increasing Subsequence AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode300.cpp)
			* 求LIS的个数
				* [LeetCode673.cpp Number of Longest Increasing Subsequence AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode673.cpp)
	        * 求所有LIS的解
		* <span id=edd>Edit Distance</span>
			* [editDistance.cpp 最短编辑距离](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/editDistance.cpp)
		* <span id=lcs>最长公共子序列 (LCS)</span>
			* [LCS.cpp 最长公共子序列长度](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LCS.cpp)
	* 区间DP
		* [NowCoder1043A.cpp 石子合并 AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/NowCoder1043A.cpp)
	* 计数型
		* [intSplit.cpp 整数划分](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/intSplit.cpp)
	* 数位统计型
	* 状态压缩型
	    * [蒙德里安的梦想 状态压缩的经典应用]
	* 树形DP
		* [有依赖的背包裸题模板](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/treeknap.cpp)
	* 状态机模型
	* DP优化方法
		* 单调队列优化DP
		* 斜率优化DP
	* <span id=mem>记忆化搜索(DP问题递归写法的学名，属于DP的一种实现方法)<span>
	    * [snowing.cpp 滑雪 记忆化搜索](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/snowing.cpp)
	
* <span id=gd>Greedy Algorithms</span>
	* [LeetCode55.cpp Jump Game 存在一个greedy的解  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode55.cpp)
	* [LeetCode452.cpp Minimum Number of Arrows to Burst Balloons  AC sort+greedy求相邻区间的交集](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode452.cpp)
	* [LeetCode11.cpp Container With Most Water AC 相向型指针](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode11.cpp)
	* <span id=interval>区间问题</span>
		* [LeetCode56.cpp Merge Intervals AC sort+greedy](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode56.cpp)
		* [LeetCode57.cpp Insert Interval  AC   sort+greedy给出了两种方法，都能AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode57.cpp)
		* [LeetCode986.cpp Interval List Intersections  AC  merge的部分实际上和mergesort中的merge有异曲同工之处](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode986.cpp)
		* [LeetCode435.cpp Non-overlapping Intervals  AC   sort+greedy method](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode435.cpp)
		* [LeetCode1288.cpp Remove Covered Intervals  AC sort+greedy](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1288.cpp)
		* [interval.cpp 区间选点 AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/interval.cpp)
		* [intervalGroup.cpp 区间分组](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/intervalGroup.cpp)
		* [intervalCover.cpp 区间覆盖](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/intervalCover.cpp)
	* <span id=huft>huffman tree</span>
		* [mergeApple.cpp 合并果子](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/mergeApple.cpp)
	* 排序不等式
		* [sortGreedy.cpp 排队打水](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/sortGreedy.cpp)
	* 绝对值不等式
		* [yardSelection.cpp 货仓选址](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/yardSelection.cpp)
* <span id=bf>Brute Force Search</span>
	* <span id=dfs>**DFS + Backtrack**</span>
		* [LeetCode17.cpp Letter Combinations of a Phone Number  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode17.cpp)
		* [LeetCode39.cpp Combination Sum AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode39.cpp)
		* [LeetCode40. Combination Sum II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode40.cpp)
		* [LeetCode216. Combination Sum III AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode216.cpp)
		* [LeetCode46.cpp Permutations  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode46.cpp)
		* [LeetCode47.cpp Permutations II  AC 先排序去重](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode47.cpp)
		* [POJ1256.cpp AC 先排序去重](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ1256.cpp)
		* [LeetCode78.cpp Subsets AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode78.cpp)
		* [LeetCode90.cpp Subsets II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode90.cpp)
		* [LeetCode77. Combinations  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode77.cpp)
		* [LeetCode79.cpp Word Search AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode79.cpp)
		* [LeetCode60.cpp Permutation Sequence AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode60.cpp)
		* [LeetCode1286.cpp Iterator for Combination  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1286.cpp)
	    * [LeetCode51.cpp N-Queens I AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode51.cpp)
		* [LeetCode52.cpp N-Queens II AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode52.cpp)
		* [LeetCode22.cpp Generate Parentheses AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode22.cpp)
	* <span id=bfs>BFS + Branch-and-Bound</span>
		* [LeetCode17.cpp Letter Combinations of a Phone Number  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode17.cpp)
		* [POJ3984.cpp AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/POJ3984.cpp)
		* [LeetCode1091.cpp AC Shortest Path in Binary Matrix](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode1091.cpp)

|method   | extra space | priorities     |Data Structure|
| :----------: | :-----------:  | :-----------: |:-----------:|
| DFS     | O(h)   |   无   |stack|
| BFS     | O(2^h)   | shortest path(权重必须为1，否则不能找到最短路径)、topology sort  |queue|


* <span id=rec>Recursive</span>
	* [LeetCode493.cpp Reverse Pairs  AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode493.cpp) 
	* [**LeetCode98.cpp Validate Binary Search Tree AC** 简单但不失优雅](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode98.cpp)
	* [LeetCode4.cpp Median of Two Sorted Arrays AC](https://github.com/JunpengCode/Algorithms/blob/master/Traditional-Algorithms/LeetCode4.cpp)

## <span id=ats>**4. 时空复杂度分析**</span>

### **4.1 理论**

```C
 int cal(int n) {
   int sum = 0;
   int i = 1;
   for (; i <= n; ++i) {
     sum = sum + i;
   }
   return sum;
 }
```

如上述代码，在上述代码中，只有for循环中的`sum+=i`被执行了n次，其它代码的执行均与n无关。本例中，我们将算法的时间复杂度表示为O(n)，表示算法的执行时间与n成线性比例。在算法分析中，用大O表示时间复杂度，大O不是算法的真正执行时间，而是表示代码的执行时间随数据规模增长的变化趋势，所有我们也称为渐进时间复杂度。常见的时间复杂度包括：

$O(1) < O(lgn) < O(n) < O(nlogn) < O(n^2) < O(2^n) < O(n!)$ 其中，$O(2^n) < O(n!)$ 被称为$NP$难问题。<font color="red">为使得公式能够真长显示，请在chrome的扩展程序中，打开chrome网上应用店，然后搜索MathJax Plugin for Github，下载该插件，并且启用，就可以让上述公式正常显示。</font>

在时空复杂度分析中，有下面三个法则：

* 只关注循环执行次数最多的一段代码
* 加法法则：总复杂度等于量级最大的那段代码的复杂度，该法则适用于多段平行代码段，总的时间复杂度为最大
* 乘法法则：嵌套代码的复杂度等于嵌套内外代码复杂度的乘积

### 4.2 最好，最坏、平均、时间复杂度分析

3.1节讲了基本的时间复杂度表示方法，本节将重点讲述最好、最坏、平均、均摊时间复杂度分析，这样便有了完整的时间复杂度分析方法。

```C
// n 表示数组 array 的长度
int find(int[] array, int n, int x) {
  int i = 0;
  int pos = -1;
  for (; i < n; ++i) {
    if (array[i] == x) pos = i;
  }
  return pos;
}
```

上述代码的时间复杂度为O(n)，代码性能较差，修改为下面部分：

```C
// n 表示数组 array 的长度
int find(int[] array, int n, int x) {
  int i = 0;
  int pos = -1;
  for (; i < n; ++i) {
    if (array[i] == x) {
       pos = i;
       break;
    }
  }
  return pos;
}
```

如上代码，在**最好情况下：数组的首元素的值与x相等，此时时间复杂度为O(1)，在最坏情况下：遍历整个数组，但是仍然没有找到对应的元素，此时的时间复杂度为O(n)。**至于平均时间复杂度的分析稍微复杂一些，**平均之间复杂度又称为期望时间复杂度或加权时间复杂度。**在本例中，有n个元素，每个元素都有$1/n$的可能性被选中，并且被选中的元素有$1/2$的可能性等于x，因此：

$1 * 1/(2n) + 2 * 1/(2n) + ... + n * 1/(2n) + n * 1/2= (3n+1)/4$ 

上述值就是每个位置可能出现等于x的情况的加权平均值，也叫做期望值，所以平均时间复杂度的全称应该叫做加权平均时间复杂度或者期望时间复杂度。上述值用大O表示为O(n)。另外一种分析方法是，总共有n+1种情况，n种情况下找到该元素，1种情况下元素不在数组中，如下：

$(1+2+...+n+n)/(n+1) = n(n+3)/(2(n+1))$

这种分析方法没有考虑每种情况出现的概率，不可取。

### **4.3 均摊时间复杂度分析**


上述两节之后我们已经初步掌握了时间复杂度的分析方法，本节介绍均摊时间复杂度，均摊时间复杂度对应于算法中的摊还分析(或者叫平摊分析)。相比最好、最差、平均时间复杂度，均摊时间复杂度的使用场景更加特殊、更加有限。

```C
 // array 表示一个长度为 n 的数组
 // 代码中的 array.length 就等于 n
 int[] array = new int[n];
 int count = 0;
 
 void insert(int val) {
    if (count == array.length) {
       int sum = 0;
       for (int i = 0; i < array.length; ++i) {
          sum = sum + array[i];
       }
       array[0] = sum;
       count = 1;
    }

    array[count] = val;
    ++count;
 }
```

这段代码实现了往数组中插入数据的功能。当数组满了之后，也就是代码中 count==array.length时，通过for循环遍历数组求和，并清空数组，将求和之后的sum值放到数组的第一个位置，然后再将心得数据插入。当数组一开始有空闲位置时，则直接将数据插入数组。

**最好情况下时间复杂度**：O(1)，此时数组未满，并且由于count会自动执行加1操作，因此不用遍历找寻空位。

**最坏情况下时间复杂度**：O(n)，此时数组装满，首先需要遍历数组的全部元素执行累加操作，接着将累加后的和放入到数组的0位置上，然后count执行加1操作指向下一个位置，后续操作与最好情况下时间复杂度吻戏类似。

**平均时间复杂度**：假设数组的长度为n，根据插入的位置不同，可以将其分为n中情况，每种情况的时间复杂度都为O(1)，除此之外，还有一种当数组没有空闲位置时的情况，此时的时间复杂度为O(n)，而且这n+1中情况发生的概率一样，都是$1/(n+1)$，所以根据加权平均的计算方法，平均时间复杂度为：

$1 * 1/(n+1) + 1 * 1/(n+1)  ... + n * 1/(n+1)  = O(1)$

到目前位置，最好情况下时间复杂度、最坏情况下时间复杂度、平均情况下时间复杂度的计算，理解起来都没有任何问题。但是这个例子的平均复杂度分析其实并不需要上述那样复杂，不需要引入概率论的知识。这是为什么呢？其实将本例的insert()和前面的find()进行对比，可以知道，find()函数在极端情况下复杂度才为O(1)，但是insert在大部分情况下，时间复杂度都为O(1)，只有当数组没有空闲位置时，采薇O(n)。其次对于insert()，O(1)时间复杂度的插入和O(n)时间复杂度的插入，出现的频率是非常有规律的，而且有一定的前后时序关系，一般都是一个O(n)插入只有，紧跟着$n-1$个O(1)的插入操作，循环往复。所以针对这种特殊的场景，我们引入了一种更加简单的分析方法：摊还分析法，通过摊还分析得到的时间复杂度，本文给其命名为均摊时间复杂度。**那究竟如何使用摊还分析法来分析算法的均摊时间复杂度呢？**

我们还是继续看在数组中插入数据的例子。每一次O(n)的插入操作，都会跟着n-1次O(1)的插入操作，所以把时间耗时多的那次操作均摊到接下来的n-1次耗时少的操作上，均摊下来，这一组连续的操作的均摊时间复杂度就是O(1)，这就是均摊分析的大致思路。均摊时间复杂度和弹摊还分析的应用场景比较复杂，所以我们并不会经常用到。为了方便理解和记忆，本文总结了一下它们的应用场景。如果你以后遇到了，知道是怎么回事就行了。

对一个数据结构进行的操作中，大部分情况下时间复杂度都很低，只有个别情况下时间复杂度比较高，而且这些操作之间存在前后连贯的时序关系，这个时候，我们就可以将这一组操作放在一块儿分析，看是否能够将较高时间复杂度的那次操作的耗时平摊到其它时间复杂度较低的操作上。而且，在能够应用平摊时间复杂度的分析场景中，一般均摊时间复杂度就等于最好情况下的时间复杂度。

尽管许多数据结构和算法书籍都花了很大的力气来区分平均时间复杂度和均摊时间复杂度，但是其实我认为，均摊时间复杂度就是一种特殊的平均时间复杂度，我们没必要花太多的精力去区分它们。我们应该花时间去掌握它的分析方法，摊还分析法。至于分析出来的结果叫平均还是均摊，并不重要。



### **4.4 总结**

之所以引入最好时间复杂度、最坏时间复杂度、平均时间复杂度、均摊时间复杂度这些概念，是因为很多算法，在不同的输入情况下，算法的时间复杂度不一样。在引入这些概念以后，我们能够更加全面的表示算法的时间复杂度。



```C
// 全局变量，大小为 10 的数组 array，长度 len，下标 i。
int array[] = new int[10]; 
int len = 10;
int i = 0;

// 往数组中添加一个元素
void add(int element) {
   if (i >= len) { // 数组空间不够了
     // 重新申请一个 2 倍大小的数组空间
     int new_array[] = new int[len*2];
     // 把原来 array 数组中的数据依次 copy 到 new_array
     for (int j = 0; j < len; ++j) {
       new_array[j] = array[j];
     }
     // new_array 复制给 array，array 现在大小就是 2 倍 len 了
     array = new_array;
     len = 2 * len;
   }
   // 将 element 放到下标为 i 的位置，下标 i 加一
   array[i] = element;
   ++i;
}
/*答案：
最好时间复杂度O(1)，最坏时间复杂度O(n)，平均时间复杂度O(1)，均摊时间复杂度为O(1)
假设数组的长度为n，当数组未满时，每次往数组中添加元素的时间复杂度都为O(1)，当数组满时，需要O(n)的操作进行复制，并且这两个操作具有严格的时序关系，因此可以将复制的操作摊还给前面n-1次操作中，最终得到的时间复杂度仍然为O(1)
平均时间复杂度计算：
1 * 1/(n+1) + 1 * 1/(n+1)  ... + n * 1/(n+1)  = O(1)
*/
```

## **参考文献**

* http://www.cs.cmu.edu/~anupamg/advalgos15/
* http://speech.ee.ntu.edu.tw/~tlkagk/courses_ML20.html
* http://erikdemaine.org/classes/
* SQL练习  https://www.hackerrank.com/domains/sql  (随机写题)  https://sqlzoo.net/ (有针对性地练习SQL的方方面面特性)
* 50道必须会的SQL题目 https://www.techbeamers.com/sql-query-questions-answers-for-practice/
* https://www.techbeamers.com/top-sql-interview-questions-dba-qa/


## 协议

<img src='https://www.gnu.org/graphics/gplv3-127x51.png' width='127' height='51'/>

更多信息参见[协议文件](/LICENSE)。

<img src='https://raw.githubusercontent.com/EyreFree/EFArticles/master/res/cc-by-nc-nd.png' width='145.77' height='51'/>

[署名-非商业性使用-禁止演绎](http://creativecommons.org/licenses/by-nc-nd/3.0/cn/)。

