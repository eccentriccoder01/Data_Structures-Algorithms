# AVL Tree (Self-Balancing Binary Search Tree)

## 1. Introduction
An AVL tree is a self-balancing binary search tree. It maintains its balance by ensuring that for every node, the difference in height between its left and right subtrees (known as the balance factor) is at most 1. This property guarantees a logarithmic time complexity for search, insertion, and deletion operations.

## 2. When is it used?
AVL trees are widely used in databases for indexing, file systems, symbol tables in compilers, and any application requiring fast lookups and dynamic updates while ensuring worst-case logarithmic performance. They are particularly valuable where guaranteed performance is critical.

## 3. ASCII Diagram

```
     Initial Tree       Insert 50      Rotate Left (node 40 becomes root)
       30                    30                           40
      /  \                  /  \                         /  \
     20  40                20  40                      30  50
         /                     /  \
        35                    35  50
(Unbalanced after 50 -> Balance factor of 30 is -2)

Rotations maintain balance.
```

## 4. Approaches

### Insertion with Rotations

Insertion in an AVL tree begins like a standard BST insertion. After inserting the new node, the path from the inserted node up to the root is checked for balance. If a node becomes unbalanced (balance factor > 1 or < -1), specific rotations are performed to restore balance. There are four types of rotations: Left-Left (LL) and Right-Right (RR) are single rotations, while Left-Right (LR) and Right-Left (RL) are double rotations. LL occurs when a node's left child's left subtree causes imbalance, RR when right child's right subtree causes imbalance. LR is a left rotation on the child followed by a right rotation on the parent. RL is a right rotation on the child followed by a left rotation on the parent.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <algorithm>

class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* insert(AVLNode* node, int key) {
        // 1. Perform standard BST insertion
        if (!node) {
            return new AVLNode(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else { // Duplicate keys not allowed or handled differently
            return node;
        }

        // 2. Update height of current node
        updateHeight(node);

        // 3. Get balance factor and rebalance if necessary
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void printInorder() {
        std::cout << "Inorder Traversal: ";
        inorderTraversal(root);
        std::cout << std::endl;
    }

    // For demonstration, expose root to check structure manually
    AVLNode* getRoot() { return root; }
};

int main() {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.printInorder(); // 10 20 30 (After RR, 20 is root)

    tree.insert(40);
    tree.insert(50);
    tree.printInorder(); // 10 20 30 40 50 (After RR, 40 is root of subtree)

    tree.insert(25);
    tree.printInorder(); // 10 20 25 30 40 50 (After LR, 25 is root of subtree)

    // Manual check on a larger sequence to see balance
    AVLTree tree2;
    std::vector<int> keys = {9, 5, 10, 0, 6, 11, -1, 1, 2};
    for (int key : keys) {
        tree2.insert(key);
    }
    tree2.printInorder(); // Expected sorted: -1 0 1 2 5 6 9 10 11

    // The printed inorder traversal ensures sorted elements. For balance,
    // one would typically inspect heights or balance factors which are internal.

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.ArrayList;
import java.util.List;

class AVLNode {
    int key;
    AVLNode left;
    AVLNode right;
    int height;

    AVLNode(int k) {
        key = k;
        left = null;
        right = null;
        height = 1;
    }
}

public class AVLTree {
    private AVLNode root;

    private int height(AVLNode node) {
        return node == null ? 0 : node.height;
    }

    private int getBalance(AVLNode node) {
        return node == null ? 0 : height(node.left) - height(node.right);
    }

    private void updateHeight(AVLNode node) {
        if (node != null) {
            node.height = 1 + Math.max(height(node.left), height(node.right));
        }
    }

    private AVLNode rightRotate(AVLNode y) {
        AVLNode x = y.left;
        AVLNode T2 = x.right;

        x.right = y;
        y.left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    private AVLNode leftRotate(AVLNode x) {
        AVLNode y = x.right;
        AVLNode T2 = y.left;

        y.left = x;
        x.right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    private AVLNode insert(AVLNode node, int key) {
        // 1. Perform standard BST insertion
        if (node == null) {
            return new AVLNode(key);
        }

        if (key < node.key) {
            node.left = insert(node.left, key);
        } else if (key > node.key) {
            node.right = insert(node.right, key);
        } else { // Duplicate keys not allowed or handled differently
            return node;
        }

        // 2. Update height of current node
        updateHeight(node);

        // 3. Get balance factor and rebalance if necessary
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node.left.key) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && key > node.right.key) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key > node.left.key) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node.right.key) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    public void insert(int key) {
        root = insert(root, key);
    }

    private void inorderTraversal(AVLNode node) {
        if (node != null) {
            inorderTraversal(node.left);
            System.out.print(node.key + " ");
            inorderTraversal(node.right);
        }
    }

    public void printInorder() {
        System.out.print("Inorder Traversal: ");
        inorderTraversal(root);
        System.out.println();
    }

    public static void main(String[] args) {
        AVLTree tree = new AVLTree();

        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.printInorder(); // 10 20 30 (After RR, 20 is root)

        tree.insert(40);
        tree.insert(50);
        tree.printInorder(); // 10 20 30 40 50 (After RR, 40 is root of subtree)

        tree.insert(25);
        tree.printInorder(); // 10 20 25 30 40 50 (After LR, 25 is root of subtree)

        // Manual check on a larger sequence to see balance
        AVLTree tree2 = new AVLTree();
        int[] keys = {9, 5, 10, 0, 6, 11, -1, 1, 2};
        for (int key : keys) {
            tree2.insert(key);
        }
        tree2.printInorder(); // Expected sorted: -1 0 1 2 5 6 9 10 11
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def __init__(self):
        self.root = None

    def _height(self, node):
        return node.height if node else 0

    def _get_balance(self, node):
        return self._height(node.left) - self._height(node.right) if node else 0

    def _update_height(self, node):
        if node:
            node.height = 1 + max(self._height(node.left), self._height(node.right))

    def _right_rotate(self, y):
        x = y.left
        T2 = x.right

        x.right = y
        y.left = T2

        self._update_height(y)
        self._update_height(x)

        return x

    def _left_rotate(self, x):
        y = x.right
        T2 = y.left

        y.left = x
        x.right = T2

        self._update_height(x)
        self._update_height(y)

        return y

    def _insert(self, node, key):
        # 1. Perform standard BST insertion
        if not node:
            return AVLNode(key)

        if key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        else: # Duplicate keys not allowed or handled differently
            return node

        # 2. Update height of current node
        self._update_height(node)

        # 3. Get balance factor and rebalance if necessary
        balance = self._get_balance(node)

        # Left Left Case
        if balance > 1 and key < node.left.key:
            return self._right_rotate(node)

        # Right Right Case
        if balance < -1 and key > node.right.key:
            return self._left_rotate(node)

        # Left Right Case
        if balance > 1 and key > node.left.key:
            node.left = self._left_rotate(node.left)
            return self._right_rotate(node)

        # Right Left Case
        if balance < -1 and key < node.right.key:
            node.right = self._right_rotate(node.right)
            return self._left_rotate(node)

        return node

    def insert(self, key):
        self.root = self._insert(self.root, key)

    def _inorder_traversal(self, node):
        if node:
            self._inorder_traversal(node.left)
            print(node.key, end=" ")
            self._inorder_traversal(node.right)

    def print_inorder(self):
        print("Inorder Traversal: ", end="")
        self._inorder_traversal(self.root)
        print()

if __name__ == "__main__":
    tree = AVLTree()

    tree.insert(10)
    tree.insert(20)
    tree.insert(30)
    tree.print_inorder() # 10 20 30 (After RR, 20 is root)

    tree.insert(40)
    tree.insert(50)
    tree.print_inorder() # 10 20 30 40 50 (After RR, 40 is root of subtree)

    tree.insert(25)
    tree.print_inorder() # 10 20 25 30 40 50 (After LR, 25 is root of subtree)

    # Manual check on a larger sequence to see balance
    tree2 = AVLTree()
    keys = [9, 5, 10, 0, 6, 11, -1, 1, 2]
    for key in keys:
        tree2.insert(key)
    tree2.print_inorder() # Expected sorted: -1 0 1 2 5 6 9 10 11
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(log N) for insertion, deletion, and search operations, where N is the number of nodes. This logarithmic performance is guaranteed due to the self-balancing property. Space Complexity: O(N) for storing the nodes, and O(log N) for the recursion stack during operations.
