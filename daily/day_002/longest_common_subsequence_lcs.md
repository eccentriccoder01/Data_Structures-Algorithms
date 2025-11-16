# Longest Common Subsequence (LCS)

## 1. Introduction
The Longest Common Subsequence (LCS) problem involves finding the longest subsequence common to two or more sequences. A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements. Unlike a substring, the elements of a subsequence do not need to occupy consecutive positions.

## 2. When is it used?
File comparison (diff utility), bioinformatics (comparing DNA sequences), plagiarism detection, version control systems.

## 3. ASCII Diagram

```
Sequence 1: A G G T A B
Sequence 2: G X T Y A Z B

Common Subsequences: G T A B, G T B, G A B, ...
LCS: G T A B (Length 4)
```

## 4. Approaches

### Dynamic Programming (Iterative)

This approach uses a 2D table `dp[i][j]` to store the length of the LCS of the first `i` characters of `text1` and the first `j` characters of `text2`. If `text1[i-1] == text2[j-1]`, then `dp[i][j] = 1 + dp[i-1][j-1]`. Otherwise, `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`. The table is filled in a bottom-up manner. After filling the table, the length of the LCS is `dp[m][n]`. The actual subsequence can be reconstructed by backtracking through the `dp` table.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <string>
#include <vector>
#include <algorithm>

int longestCommonSubsequence(const std::string& text1, const std::string& text2) {
    int m = text1.length();
    int n = text2.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
public class LongestCommonSubsequence {
    public int longestCommonSubsequence(String text1, String text2) {
        int m = text1.length();
        int n = text2.length();

        int[][] dp = new int[m + 1][n + 1];

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1.charAt(i - 1) == text2.charAt(j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def longest_common_subsequence(text1: str, text2: str) -> int:
    m = len(text1)
    n = len(text2)

    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i - 1] == text2[j - 1]:
                dp[i][j] = 1 + dp[i - 1][j - 1]
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    return dp[m][n]
```

</details>

---

### Dynamic Programming (Memoization)

This approach is a top-down, recursive solution with memoization. A recursive function is defined that computes the LCS length for substrings. To avoid redundant computations, a 2D `memo` table stores results of subproblems. Before computing `LCS(i, j)`, check if `memo[i][j]` is already computed. If `text1[i-1] == text2[j-1]`, then `LCS(i, j) = 1 + LCS(i-1, j-1)`. Otherwise, `LCS(i, j) = max(LCS(i-1, j), LCS(i, j-1))`. Base cases are when either `i` or `j` is 0, returning 0.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> memo;

int lcsMemoization(const std::string& text1, const std::string& text2, int i, int j) {
    if (i == 0 || j == 0) {
        return 0;
    }
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    if (text1[i - 1] == text2[j - 1]) {
        return memo[i][j] = 1 + lcsMemoization(text1, text2, i - 1, j - 1);
    } else {
        return memo[i][j] = std::max(lcsMemoization(text1, text2, i - 1, j),
                                    lcsMemoization(text1, text2, i, j - 1));
    }
}

int longestCommonSubsequenceMemoized(const std::string& text1, const std::string& text2) {
    int m = text1.length();
    int n = text2.length();
    memo.assign(m + 1, std::vector<int>(n + 1, -1)); // Initialize memo table with -1
    return lcsMemoization(text1, text2, m, n);
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

public class LongestCommonSubsequenceMemoized {
    private int[][] memo;

    public int longestCommonSubsequence(String text1, String text2) {
        int m = text1.length();
        int n = text2.length();
        memo = new int[m + 1][n + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        return lcsMemoization(text1, text2, m, n);
    }

    private int lcsMemoization(String text1, String text2, int i, int j) {
        if (i == 0 || j == 0) {
            return 0;
        }
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        if (text1.charAt(i - 1) == text2.charAt(j - 1)) {
            return memo[i][j] = 1 + lcsMemoization(text1, text2, i - 1, j - 1);
        } else {
            return memo[i][j] = Math.max(lcsMemoization(text1, text2, i - 1, j),
                                        lcsMemoization(text1, text2, i, j - 1));
        }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def longest_common_subsequence_memoized(text1: str, text2: str) -> int:
    m = len(text1)
    n = len(text2)
    memo = {} # Dictionary to store results of subproblems

    def solve(i, j):
        if i == 0 or j == 0:
            return 0
        if (i, j) in memo:
            return memo[(i, j)]

        if text1[i - 1] == text2[j - 1]:
            memo[(i, j)] = 1 + solve(i - 1, j - 1)
        else:
            memo[(i, j)] = max(solve(i - 1, j), solve(i, j - 1))
        return memo[(i, j)]

    return solve(m, n)
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(M * N) where M and N are the lengths of the two strings, as each state in the DP table (or memoization table) is computed once. Space Complexity: O(M * N) for the DP table/memoization table.
