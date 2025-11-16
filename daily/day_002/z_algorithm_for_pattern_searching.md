# Z-Algorithm for Pattern Searching

## 1. Introduction
The Z-algorithm is a linear-time string matching algorithm used to find all occurrences of a pattern in a text. It constructs a Z-array (or Z-box array) for a given string `S`. The Z-array, `Z[i]`, stores the length of the longest substring starting at `S[i]` that is also a prefix of `S`. This Z-array can then be used to efficiently locate pattern occurrences.

## 2. When is it used?
Pattern searching (finding occurrences of a pattern within a text), string matching, text compression, bioinformatics.

## 3. ASCII Diagram

```
Text S = A A B A A B C A A
Z-array:   [9, 1, 0, 3, 1, 0, 0, 2, 1]
Z[0] = length of S
Z[1] = 1 (A == A)
Z[3] = 3 (AAB == AAB)
```

## 4. Approaches

### Standard Z-Algorithm

The algorithm computes the Z-array for a string `S`. It iterates from `i = 1` to `N-1`. For each `i`, it determines `Z[i]`. It maintains a 'Z-box' defined by `[L, R]`, which is the rightmost segment `S[L...R]` that is also a prefix of `S`. If `i` is outside this `[L, R]` box, `Z[i]` is computed by naive comparison. If `i` is inside `[L, R]`, it leverages previously computed Z-values. Specifically, `S[i...R]` is `S[i-L ... R-L]`, so `Z[i]` is at least `min(Z[i-L], R-i+1)`. If `Z[i]` extends beyond `R`, the Z-box is updated. The pattern searching application concatenates pattern `P`, a unique separator character (e.g., `$`), and text `T` to form `S = P$T`. Then, `Z[i]` values equal to `len(P)` indicate an occurrence of `P` starting at `i - len(P) - 1` in `T`.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> calculateZArray(const std::string& s) {
    int n = s.length();
    std::vector<int> z(n);
    z[0] = n;
    int L = 0, R = 0;
    for (int i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R - L] == s[R]) {
                R++;
            }
            z[i] = R - L;
            R--;
        } else {
            int k = i - L;
            if (z[k] < R - i + 1) {
                z[i] = z[k];
            } else {
                L = i;
                while (R < n && s[R - L] == s[R]) {
                    R++;
                }
                z[i] = R - L;
                R--;
            }
        }
    }
    return z;
}

// To find pattern P in text T:
// std::string S = P + "$" + T;
// std::vector<int> z = calculateZArray(S);
// int pattern_len = P.length();
// for (int i = pattern_len + 1; i < S.length(); ++i) {
//     if (z[i] == pattern_len) {
//         // Pattern found at index i - (pattern_len + 1) in T
//     }
// }
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ZAlgorithm {
    public int[] calculateZArray(String s) {
        int n = s.length();
        int[] z = new int[n];
        z[0] = n;
        int L = 0, R = 0;
        for (int i = 1; i < n; ++i) {
            if (i > R) {
                L = R = i;
                while (R < n && s.charAt(R - L) == s.charAt(R)) {
                    R++;
                }
                z[i] = R - L;
                R--;
            } else {
                int k = i - L;
                if (z[k] < R - i + 1) {
                    z[i] = z[k];
                } else {
                    L = i;
                    while (R < n && s.charAt(R - L) == s.charAt(R)) {
                        R++;
                    }
                    z[i] = R - L;
                    R--;
                }
            }
        }
        return z;
    }

    // To find pattern P in text T:
    // public List<Integer> search(String text, String pattern) {
    //     String S = pattern + "$" + text;
    //     int[] z = calculateZArray(S);
    //     int patternLen = pattern.length();
    //     List<Integer> occurrences = new ArrayList<>();
    //     for (int i = patternLen + 1; i < S.length(); i++) {
    //         if (z[i] == patternLen) {
    //             occurrences.add(i - (patternLen + 1)); // Index in text
    //         }
    //     }
    //     return occurrences;
    // }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def calculate_z_array(s: str) -> list[int]:
    n = len(s)
    z = [0] * n
    z[0] = n
    L, R = 0, 0
    for i in range(1, n):
        if i > R:
            L = R = i
            while R < n and s[R - L] == s[R]:
                R += 1
            z[i] = R - L
            R -= 1
        else:
            k = i - L
            if z[k] < R - i + 1:
                z[i] = z[k]
            else:
                L = i
                while R < n and s[R - L] == s[R]:
                    R += 1
                z[i] = R - L
                R -= 1
    return z

# To find pattern P in text T:
# def find_pattern_z(text: str, pattern: str) -> list[int]:
#     s = pattern + "$" + text # Using '$' as a unique separator
#     z_array = calculate_z_array(s)
#     pattern_len = len(pattern)
#     occurrences = []
#     for i in range(pattern_len + 1, len(s)):
#         if z_array[i] == pattern_len:
#             occurrences.append(i - (pattern_len + 1)) # Index in text
#     return occurrences
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N) where N is the length of the string, as each character is visited and compared a constant number of times. Space Complexity: O(N) for storing the Z-array.
