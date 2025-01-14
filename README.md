# Word-Composition-Problem

# Overview
This project provides a solution to find the longest and second-longest compound words from a given list of words. A compound word is defined as a word that can be formed by concatenating two or more shorter words from the same list.

The solution uses a Trie data structure for efficient prefix matching and memoization to reduce redundant calculations.

# File
Quality_Analyst.cpp: Main program file containing the implementation.

Input_01.txt and Input_02.txt: Sample input files with word lists.

# Implementation
1.Trie Data Structure: Used to store and search prefixes efficiently.
Supports  complexity for word lookups, where  is the word length.

2.Memoization: Caches results of previously checked words to avoid redundant calculations.

3.Amplified Timing: Repeats processing multiple times for small inputs to get more measurable timings.

