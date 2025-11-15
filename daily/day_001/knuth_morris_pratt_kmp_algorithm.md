# Knuth-Morris-Pratt (KMP) Algorithm

## 1. Introduction
The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that searches for occurrences of a 'pattern' within a 'text' with linear time complexity. It achieves this efficiency by avoiding re-examining characters of the text that have already been matched, utilizing pre-computed information about the pattern itself to skip unnecessary comparisons. This pre-computation is stored in a 'Longest Proper Prefix which is also Suffix' (LPS) array.

## 2. When is it used?
Text editing software (search and replace), bioinformatics (DNA sequence matching), plagiarism detection, grep-like utilities, data compression, network intrusion detection systems.

## 3. ASCII Diagram

```
Text: A B C A B D A B C A B C A B D
Pattern: A B C A B D

LPS array for Pattern (length 6):
Pattern: A B C A B D
LPS:     [0, 0, 0, 1, 2, 0]

Explanation of LPS:
- A: no proper prefix/suffix (LPS[0]=0)
- AB: no proper prefix/suffix (LPS[1]=0)
- ABC: no proper prefix/suffix (LPS[2]=0)
- ABCA: 'A' is proper prefix/suffix (LPS[3]=1)
- ABCAB: 'AB' is proper prefix/suffix (LPS[4]=2)
- ABCABD: no proper prefix/suffix (LPS[5]=0)

Matching Process (Simplified step):
Text: ... A B C A B D ...
Pat:     A B C A B D
         ^         ^
         Match! (Full pattern matched)

Text: ... A B C A B C A B D ...
Pat:     A B C A B D
                 ^
                 Mismatch at index 5 (D vs C)

Using LPS[4]=2, shift pattern such that suffix 'AB' aligns with prefix 'AB':
Text: ... A B C A B C A B D ...
Pat:             A B C A B D
                 ^ ^
                 No recheck of 'AB', continue matching from 'C'
```

## 4. Approaches

### KMP with LPS Array Construction

The KMP algorithm consists of two main parts: building the LPS (Longest Proper Prefix which is also Suffix) array for the pattern, and then using this array to perform the search. The LPS array stores, for each prefix of the pattern, the length of the longest proper prefix of that prefix that is also a suffix of that prefix. This array guides the shifts of the pattern when a mismatch occurs during the text scanning, preventing redundant character comparisons. When `text[i]` and `pattern[j]` mismatch, if `j > 0`, the pattern is shifted using `lps[j-1]` to align the longest proper prefix of `pattern[0...j-1]` that is also its suffix, effectively aligning a known matching segment of the pattern with itself.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <string>
#include <vector>
#include <iostream>

std::vector<int> computeLPSArray(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> lps(m, 0);
    int length = 0; // Length of the previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

std::vector<int> kmpSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> occurrences;

    if (m == 0) return occurrences; // Empty pattern matches at every position conceptually
    if (n == 0) return occurrences; // No text, no matches

    std::vector<int> lps = computeLPSArray(pattern);

    int i = 0; // index for text
    int j = 0; // index for pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1]; // Found a match, reset j using LPS for next possible match
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return occurrences;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.ArrayList;
import java.util.List;

class KMP {
    private int[] computeLPSArray(String pattern) {
        int m = pattern.length();
        int[] lps = new int[m];
        int length = 0; // Length of the previous longest prefix suffix
        int i = 1;

        while (i < m) {
            if (pattern.charAt(i) == pattern.charAt(length)) {
                length++;
                lps[i] = length;
                i++;
            } else {
                if (length != 0) {
                    length = lps[length - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    public List<Integer> kmpSearch(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();
        List<Integer> occurrences = new ArrayList<>();

        if (m == 0) return occurrences; 
        if (n == 0) return occurrences; 

        int[] lps = computeLPSArray(pattern);

        int i = 0; // index for text
        int j = 0; // index for pattern
        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                i++;
                j++;
            }

            if (j == m) {
                occurrences.add(i - j);
                j = lps[j - 1]; 
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return occurrences;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def compute_lps_array(pattern):
    m = len(pattern)
    lps = [0] * m
    length = 0 # length of the previous longest prefix suffix
    i = 1

    while i < m:
        if pattern[i] == pattern[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1
    return lps

def kmp_search(text, pattern):
    n = len(text)
    m = len(pattern)
    occurrences = []

    if m == 0: return occurrences
    if n == 0: return occurrences

    lps = compute_lps_array(pattern)

    i = 0 # index for text
    j = 0 # index for pattern
    while i < n:
        if pattern[j] == text[i]:
            i += 1
            j += 1

        if j == m:
            occurrences.append(i - j)
            j = lps[j - 1] # Found a match, reset j using LPS for next possible match
        elif i < n and pattern[j] != text[i]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    return occurrences
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N + M), where N is the length of the text and M is the length of the pattern. This is because computing the LPS array takes O(M) time, and the searching phase takes O(N) time. Each character of the text and pattern is visited at most a constant number of times. Space Complexity: O(M) for storing the LPS array.
