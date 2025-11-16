# Trie (Prefix Tree)

## 1. Introduction
A Trie, also known as a prefix tree, is a tree-like data structure used to store a dynamic set of strings where the nodes store characters. Each node represents a prefix, and all descendants of a node share that prefix. Tries are highly efficient for operations involving prefixes, such as searching for words with a common prefix or autocomplete functionalities.

## 2. When is it used?
Autocomplete and spell checkers, dictionary implementations, IP routing, T9 predictive text, DNA matching.

## 3. ASCII Diagram

```
   (root)
   / | \
  c  d  a
  |  |  |
  a  o  n
  |  |  |
  t  g  d
  |     |
  (word) (word)
'cat', 'dog', 'and'
```

## 4. Approaches

### Standard Trie Implementation

A Trie is composed of nodes, where each node can have child nodes representing the next character in a sequence. Typically, a node contains a map or array of pointers to its children and a boolean flag indicating if it marks the end of a word. To insert a word, traverse the Trie, creating new nodes for characters not present. To search, traverse based on the characters of the target string. If the path ends at a node marked as a word end, the word is found. Prefix search involves traversing the Trie for the prefix; if the traversal is successful, the prefix exists.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <map>
#include <string>
#include <vector>

class TrieNode {
public:
    std::map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}

    ~TrieNode() {
        for (auto const& [key, val] : children) {
            delete val;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return true;
    }
};
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.HashMap;
import java.util.Map;

class TrieNode {
    Map<Character, TrieNode> children;
    boolean isEndOfWord;

    public TrieNode() {
        children = new HashMap<>();
        isEndOfWord = false;
    }
}

public class Trie {
    private TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    public void insert(String word) {
        TrieNode current = root;
        for (char ch : word.toCharArray()) {
            current.children.putIfAbsent(ch, new TrieNode());
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode current = root;
        for (char ch : prefix.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return true;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        current = self.root
        for char in word:
            if char not in current.children:
                current.children[char] = TrieNode()
            current = current.children[char]
        current.is_end_of_word = True

    def search(self, word: str) -> bool:
        current = self.root
        for char in word:
            if char not in current.children:
                return False
            current = current.children[char]
        return current.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        current = self.root
        for char in prefix:
            if char not in current.children:
                return False
            current = current.children[char]
        return True
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: Insertion/Search/Prefix Search O(L) where L is the length of the key. Space Complexity: O(Total characters in all words) in the worst case, but often much less due to shared prefixes.
