# Manacher's Algorithm for Longest Palindromic Substring

## 1. Introduction
Manacher's Algorithm is an efficient algorithm to find the longest palindromic substring within a given string in linear time. It cleverly handles both odd-length and even-length palindromes by transforming the string, and avoids redundant computations by exploiting the symmetry of palindromes.

## 2. When is it used?
This algorithm is useful in text processing, bioinformatics (e.g., analyzing palindromic sequences in DNA), pattern recognition, and data compression.

## 3. ASCII Diagram

```
Original String:  "babad"
Transformed String: "#b#a#b#a#d#"
Palindrome Radii (P array):
Idx: 0 1 2 3 4 5 6 7 8 9 10
Char:# b # a # b # a # d #
P:   0 1 0 3 0 1 0 3 0 1 0
(P[i] is the radius of palindrome centered at i, e.g., P[3]=3 for "#a#b#a#" which is "aba")
Longest Palindrome: "bab" (derived from P[3]=3 or P[7]=3)
```

## 4. Approaches

### Linear Time Single Pass

Manacher's Algorithm transforms the input string by inserting a special character (e.g., '#') between every character and at both ends. This converts all palindromes (odd and even length) into odd-length palindromes in the transformed string. It then iterates through the transformed string, calculating the 'palindrome radius' (P array) for each center. When calculating `P[i]`, it leverages the information from `P[j]` (where `j` is the mirror of `i` relative to the current palindrome center `C`) to avoid re-evaluating already known palindromic regions. It expands outward from each `i`, and updates `C` and `R` (the rightmost boundary of the current longest palindrome centered at `C`) as new, larger palindromes are found. This symmetry-driven optimization ensures linear time complexity.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string preprocess(const std::string& s) {
    std::string t = "^"; // Start character
    for (char c : s) {
        t += '#';
        t += c;
    }
    t += '#';
    t += '$'; // End character
    return t;
}

std::string longestPalindrome(const std::string& s) {
    if (s.empty()) return "";

    std::string t = preprocess(s);
    int n = t.length();
    std::vector<int> p(n, 0); // p[i] stores palindrome radius centered at i
    int C = 0, R = 0;        // C = center, R = rightmost boundary of current longest palindrome

    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 1; i < n - 1; ++i) {
        // Mirror index of i relative to C
        int i_mirror = C - (i - C);

        // If i is within R, leverage palindrome information from its mirror
        if (R > i) {
            p[i] = std::min(R - i, p[i_mirror]);
        }

        // Attempt to expand palindrome centered at i
        // t[i + 1 + p[i]] and t[i - 1 - p[i]] are characters outside current palindrome boundary
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
            p[i]++;
        }

        // If palindrome centered at i expands beyond R, update C and R
        if (i + p[i] > R) {
            C = i;
            R = i + p[i];
        }

        // Keep track of the longest palindrome found
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    // Calculate start index and length in original string
    // maxLen is the radius, so actual length is maxLen. E.g., for "#a#b#a#", maxLen=3, original "aba" length 3.
    // The centerIndex in transformed string maps to (centerIndex - maxLen) / 2 in original string.
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    std::cout << "Longest Palindromic Substring of 'babad': " << longestPalindrome("babad") << std::endl; // Expected: bab or aba
    std::cout << "Longest Palindromic Substring of 'cbbd': " << longestPalindrome("cbbd") << std::endl;   // Expected: bb
    std::cout << "Longest Palindromic Substring of 'a': " << longestPalindrome("a") << std::endl;         // Expected: a
    std::cout << "Longest Palindromic Substring of 'racecar': " << longestPalindrome("racecar") << std::endl; // Expected: racecar
    std::cout << "Longest Palindromic Substring of 'forgeeksskeegfor': " << longestPalindrome("forgeeksskeegfor") << std::endl; // Expected: geeksskeeg

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

public class ManacherAlgorithm {

    private String preprocess(String s) {
        StringBuilder t = new StringBuilder("^"); // Start character
        for (char c : s.toCharArray()) {
            t.append('#');
            t.append(c);
        }
        t.append('#');
        t.append('$'); // End character
        return t.toString();
    }

    public String longestPalindrome(String s) {
        if (s == null || s.length() == 0) {
            return "";
        }

        String t = preprocess(s);
        int n = t.length();
        int[] p = new int[n]; // p[i] stores palindrome radius centered at i
        int C = 0, R = 0;    // C = center, R = rightmost boundary of current longest palindrome

        int maxLen = 0;
        int centerIndex = 0;

        for (int i = 1; i < n - 1; i++) {
            // Mirror index of i relative to C
            int i_mirror = C - (i - C);

            // If i is within R, leverage palindrome information from its mirror
            if (R > i) {
                p[i] = Math.min(R - i, p[i_mirror]);
            }

            // Attempt to expand palindrome centered at i
            // t.charAt(i + 1 + p[i]) and t.charAt(i - 1 - p[i]) are characters outside current palindrome boundary
            while (t.charAt(i + 1 + p[i]) == t.charAt(i - 1 - p[i])) {
                p[i]++;
            }

            // If palindrome centered at i expands beyond R, update C and R
            if (i + p[i] > R) {
                C = i;
                R = i + p[i];
            }

            // Keep track of the longest palindrome found
            if (p[i] > maxLen) {
                maxLen = p[i];
                centerIndex = i;
            }
        }

        // Calculate start index and length in original string
        // maxLen is the radius, so actual length is maxLen.
        // The centerIndex in transformed string maps to (centerIndex - maxLen) / 2 in original string.
        int start = (centerIndex - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    public static void main(String[] args) {
        ManacherAlgorithm solver = new ManacherAlgorithm();
        System.out.println("Longest Palindromic Substring of 'babad': " + solver.longestPalindrome("babad")); // Expected: bab or aba
        System.out.println("Longest Palindromic Substring of 'cbbd': " + solver.longestPalindrome("cbbd"));   // Expected: bb
        System.out.println("Longest Palindromic Substring of 'a': " + solver.longestPalindrome("a"));         // Expected: a
        System.out.println("Longest Palindromic Substring of 'racecar': " + solver.longestPalindrome("racecar")); // Expected: racecar
        System.out.println("Longest Palindromic Substring of 'forgeeksskeegfor': " + solver.longestPalindrome("forgeeksskeegfor")); // Expected: geeksskeeg
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def preprocess(s):
    t = "^"
    for char in s:
        t += "#"
        t += char
    t += "#"
    t += "$"
    return t

def longest_palindrome(s):
    if not s: # Equivalent to s is None or len(s) == 0
        return ""

    t = preprocess(s)
    n = len(t)
    p = [0] * n # p[i] stores palindrome radius centered at i
    C, R = 0, 0 # C = center, R = rightmost boundary of current longest palindrome

    max_len = 0
    center_index = 0

    for i in range(1, n - 1):
        # Mirror index of i relative to C
        i_mirror = C - (i - C)

        # If i is within R, leverage palindrome information from its mirror
        if R > i:
            p[i] = min(R - i, p[i_mirror])
        
        # Attempt to expand palindrome centered at i
        # t[i + 1 + p[i]] and t[i - 1 - p[i]] are characters outside current palindrome boundary
        while t[i + 1 + p[i]] == t[i - 1 - p[i]]:
            p[i] += 1
        
        # If palindrome centered at i expands beyond R, update C and R
        if i + p[i] > R:
            C = i
            R = i + p[i]

        # Keep track of the longest palindrome found
        if p[i] > max_len:
            max_len = p[i]
            center_index = i
    
    # Calculate start index and length in original string
    # max_len is the radius, so actual length is max_len.
    # The center_index in transformed string maps to (center_index - max_len) // 2 in original string.
    start = (center_index - max_len) // 2
    return s[start : start + max_len]

if __name__ == "__main__":
    print(f"Longest Palindromic Substring of 'babad': {longest_palindrome('babad')}") # Expected: bab or aba
    print(f"Longest Palindromic Substring of 'cbbd': {longest_palindrome('cbbd')}")   # Expected: bb
    print(f"Longest Palindromic Substring of 'a': {longest_palindrome('a')}")         # Expected: a
    print(f"Longest Palindromic Substring of 'racecar': {longest_palindrome('racecar')}") # Expected: racecar
    print(f"Longest Palindromic Substring of 'forgeeksskeegfor': {longest_palindrome('forgeeksskeegfor')}") # Expected: geeksskeeg
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N), where N is the length of the input string. The preprocessing step creates a string of length 2N+3. Each character is visited a constant number of times (once for processing, and its `p` value potentially contributes to updating `C` and `R`). Space Complexity: O(N) for the preprocessed string and the `p` array.
