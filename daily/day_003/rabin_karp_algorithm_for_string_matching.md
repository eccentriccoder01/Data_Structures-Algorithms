# Rabin-Karp Algorithm for String Matching

## 1. Introduction
The Rabin-Karp algorithm is a string-searching algorithm that uses hashing to find any one of a set of pattern strings in a text. It is particularly effective for multiple pattern matching or when dealing with very long strings, as it can often avoid explicitly comparing every character if hashes do not match.

## 2. When is it used?
Applications include plagiarism detection, bioinformatics (finding DNA sequence patterns), database querying, and network intrusion detection systems where specific packet headers need to be identified within a data stream.

## 3. ASCII Diagram

```
Text:   "ABCCBABCD"
Pattern:"ABC"
Hash of "ABC" = H_p

Slide 1: "ABC"  -> Calculate H_1. If H_1 == H_p, check characters.
Slide 2: "BCC"  -> Calculate H_2 using rolling hash from H_1. If H_2 == H_p, check characters.
Slide 3: "CCB"  -> Calculate H_3 using rolling hash from H_2. ...
...
```

## 4. Approaches

### Rolling Hash

Rabin-Karp computes a hash value for the pattern and for each M-character window of the text (where M is pattern length). Instead of recomputing the hash for each window from scratch, a 'rolling hash' technique is used. This technique efficiently updates the hash value of a window when it slides by one character, by subtracting the contribution of the leading character and adding the contribution of the trailing character. If a hash collision occurs (text window hash matches pattern hash), a full character-by-character comparison is performed to confirm a match and avoid false positives.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// A prime number for modulo operation
const int PRIME = 101;

// Function to calculate hash of a string
long long calculateHash(const std::string& str, int len) {
    long long hash = 0;
    for (int i = 0; i < len; ++i) {
        hash = (hash + str[i] * static_cast<long long>(std::pow(PRIME, i))) % 1000000007; // Modulo to prevent overflow
    }
    return hash;
}

// Function to re-calculate hash for a sliding window
long long reCalculateHash(long long oldHash, char oldChar, char newChar, int patternLen) {
    long long newHash = oldHash - oldChar;
    newHash = newHash / PRIME; // Division is tricky with modulo, better approach is usually precomputing powers and modular inverse
    // For simplicity, here we'll re-implement standard rolling hash without modular inverse for division
    // and use a different prime for multiplication for new character.
    // A more robust rolling hash is typically: hash = (hash - old_char * p_m_minus_1) * base + new_char
    // Let's use the standard form: (hash - S[i-1]*pow(d, m-1)) + S[i+m-1]
    return newHash;
}

// Simpler approach with direct hash recomputation after a window slide for demonstration
// A more typical rolling hash formula:
// hash_new = ( (hash_old - (text[i-1] * power[M-1]) % Q) * base + text[i+M-1] ) % Q
// Need precomputed powers of base and handle negative results of modulo

void rabinKarp(const std::string& text, const std::string& pattern) {
    int N = text.length();
    int M = pattern.length();
    long long Q = 1000000007; // A large prime number for modulo
    long long D = 256;         // Number of characters in the alphabet (ASCII)

    if (M == 0 || M > N) {
        std::cout << "Pattern not found or invalid pattern length." << std::endl;
        return;
    }

    long long h = 1; // D^(M-1) % Q
    for (int i = 0; i < M - 1; ++i) {
        h = (h * D) % Q;
    }

    long long patternHash = 0; // Hash value for pattern
    long long textWindowHash = 0; // Hash value for current text window

    // Calculate the hash value for pattern and first text window
    for (int i = 0; i < M; ++i) {
        patternHash = (patternHash * D + pattern[i]) % Q;
        textWindowHash = (textWindowHash * D + text[i]) % Q;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= N - M; ++i) {
        // If hashes match, then check character by character
        if (patternHash == textWindowHash) {
            bool match = true;
            for (int j = 0; j < M; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                std::cout << "Pattern found at index " << i << std::endl;
            }
        }

        // Calculate hash for next window only if not the last window
        if (i < N - M) {
            textWindowHash = (D * (textWindowHash - text[i] * h) + text[i + M]) % Q;
            // Handle negative results of modulo operation
            if (textWindowHash < 0) {
                textWindowHash = (textWindowHash + Q);
            }
        }
    }
}

int main() {
    std::string text = "ABCCBABCD";
    std::string pattern = "ABC";
    std::cout << "Text: " << text << ", Pattern: " << pattern << std::endl;
    rabinKarp(text, pattern); // Expected: 0, 6

    text = "GEEKSFORGEEKS";
    pattern = "GEEK";
    std::cout << "\nText: " << text << ", Pattern: " << pattern << std::endl;
    rabinKarp(text, pattern); // Expected: 0, 9

    text = "AAAAA";
    pattern = "AAA";
    std::cout << "\nText: " << text << ", Pattern: " << pattern << std::endl;
    rabinKarp(text, pattern); // Expected: 0, 1, 2

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
public class RabinKarp {

    // A large prime number for modulo
    private final long Q = 1000000007;
    // Number of characters in the alphabet (ASCII)
    private final int D = 256;

    public void rabinKarp(String text, String pattern) {
        int N = text.length();
        int M = pattern.length();

        if (M == 0 || M > N) {
            System.out.println("Pattern not found or invalid pattern length.");
            return;
        }

        long h = 1; // D^(M-1) % Q
        for (int i = 0; i < M - 1; i++) {
            h = (h * D) % Q;
        }

        long patternHash = 0; // Hash value for pattern
        long textWindowHash = 0; // Hash value for current text window

        // Calculate the hash value for pattern and first text window
        for (int i = 0; i < M; i++) {
            patternHash = (patternHash * D + pattern.charAt(i)) % Q;
            textWindowHash = (textWindowHash * D + text.charAt(i)) % Q;
        }

        // Slide the pattern over text one by one
        for (int i = 0; i <= N - M; i++) {
            // If hashes match, then check character by character
            if (patternHash == textWindowHash) {
                boolean match = true;
                for (int j = 0; j < M; j++) {
                    if (text.charAt(i + j) != pattern.charAt(j)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    System.out.println("Pattern found at index " + i);
                }
            }

            // Calculate hash for next window only if not the last window
            if (i < N - M) {
                textWindowHash = (D * (textWindowHash - text.charAt(i) * h) + text.charAt(i + M)) % Q;
                // Handle negative results of modulo operation
                if (textWindowHash < 0) {
                    textWindowHash = (textWindowHash + Q);
                }
            }
        }
    }

    public static void main(String[] args) {
        RabinKarp rk = new RabinKarp();

        String text1 = "ABCCBABCD";
        String pattern1 = "ABC";
        System.out.println("Text: " + text1 + ", Pattern: " + pattern1);
        rk.rabinKarp(text1, pattern1); // Expected: 0, 6

        String text2 = "GEEKSFORGEEKS";
        String pattern2 = "GEEK";
        System.out.println("\nText: " + text2 + ", Pattern: " + pattern2);
        rk.rabinKarp(text2, pattern2); // Expected: 0, 9
        
        String text3 = "AAAAA";
        String pattern3 = "AAA";
        System.out.println("\nText: " + text3 + ", Pattern: " + pattern3);
        rk.rabinKarp(text3, pattern3); // Expected: 0, 1, 2
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def rabin_karp(text, pattern):
    N = len(text)
    M = len(pattern)
    Q = 1000000007 # A large prime number for modulo
    D = 256        # Number of characters in the alphabet (ASCII)

    if M == 0 or M > N:
        print("Pattern not found or invalid pattern length.")
        return

    h = 1 # D^(M-1) % Q
    for i in range(M - 1):
        h = (h * D) % Q

    pattern_hash = 0 # Hash value for pattern
    text_window_hash = 0 # Hash value for current text window

    # Calculate the hash value for pattern and first text window
    for i in range(M):
        pattern_hash = (pattern_hash * D + ord(pattern[i])) % Q
        text_window_hash = (text_window_hash * D + ord(text[i])) % Q

    # Slide the pattern over text one by one
    for i in range(N - M + 1):
        # If hashes match, then check character by character
        if pattern_hash == text_window_hash:
            match = True
            for j in range(M):
                if text[i + j] != pattern[j]:
                    match = False
                    break
            if match:
                print(f"Pattern found at index {i}")

        # Calculate hash for next window only if not the last window
        if i < N - M:
            text_window_hash = (D * (text_window_hash - ord(text[i]) * h) + ord(text[i + M])) % Q
            # Handle negative results of modulo operation in Python
            if text_window_hash < 0:
                text_window_hash = (text_window_hash + Q)

if __name__ == "__main__":
    text1 = "ABCCBABCD"
    pattern1 = "ABC"
    print(f"Text: {text1}, Pattern: {pattern1}")
    rabin_karp(text1, pattern1) # Expected: 0, 6

    text2 = "GEEKSFORGEEKS"
    pattern2 = "GEEK"
    print(f"\nText: {text2}, Pattern: {pattern2}")
    rabin_karp(text2, pattern2) # Expected: 0, 9
    
    text3 = "AAAAA"
    pattern3 = "AAA"
    print(f"\nText: {text3}, Pattern: {pattern3}")
    rabin_karp(text3, pattern3) # Expected: 0, 1, 2
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: Average case O(N + M), where N is text length and M is pattern length, due to efficient rolling hash. Worst case O(N * M) occurs rarely when there are many hash collisions requiring character-by-character comparison. Space Complexity: O(1) (excluding input strings).
