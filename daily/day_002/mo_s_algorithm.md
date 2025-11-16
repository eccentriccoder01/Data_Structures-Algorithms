# Mo's Algorithm

## 1. Introduction
Mo's Algorithm is an offline query processing algorithm used for answering range queries on an array efficiently. It works by reordering queries in a specific way that allows for efficient 'sliding window' updates between consecutive queries. This reordering is based on square root decomposition of the array.

## 2. When is it used?
Range sum query with distinct elements, range frequency queries, other range queries where updates can be done in O(1) or O(log N) after sorting. Popular in competitive programming for problems that are too slow with segment trees or Fenwick trees alone.

## 3. ASCII Diagram

```
Original Array: [1, 5, 2, 4, 3, 6, 7, 8]
Queries: (0, 3), (2, 5), (1, 4), (0, 7)

Mo's reorders queries, then uses a sliding window (L, R) to efficiently move from one query's range to the next.
```

## 4. Approaches

### Square Root Decomposition with Sliding Window

Mo's algorithm partitions the array into blocks of size `sqrt(N)`. Queries `(L, R)` are sorted first by their block index (`L / sqrt(N)`), and then by their `R` value. If two queries are in the same block, they are sorted by `R`. For alternating blocks, one might sort `R` in ascending, the other in descending order to minimize movement. After sorting, the algorithm processes queries by maintaining a sliding window `[currentL, currentR]`. When moving from one query `(L_prev, R_prev)` to `(L_curr, R_curr)`, the window `[currentL, currentR]` is expanded or shrunk by one element at a time, and the answer for the current query is updated incrementally in O(1) per element added/removed. The specific sorting order ensures that the total movement of `L` and `R` pointers across all queries is minimized, leading to the overall time complexity.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>
#include <cmath>

// Structure to store queries
struct Query {
    int l, r, idx, block;
};

// Comparison function for sorting queries
bool compareQueries(const Query& a, const Query& b) {
    if (a.block != b.block) {
        return a.block < b.block;
    }
    // For queries in the same block, sort R in alternating order
    // to minimize head movement (optional optimization but good practice)
    if (a.block % 2 == 0) {
        return a.r < b.r;
    }
    return a.r > b.r;
}

// Example: Range Sum Query for elements, add/remove functions are O(1)
// Note: This is a placeholder for `add` and `remove` functions.
// Actual implementation depends on specific problem (e.g., count distinct, sum of squares).
int current_sum = 0;
std::vector<int> freq; // Placeholder, actual size depends on max value in array

void add(const std::vector<int>& arr, int idx) {
    // For range sum, current_sum += arr[idx];
    // For distinct count, if freq[arr[idx]] == 0, count++; freq[arr[idx]]++;
    current_sum += arr[idx]; // Example for sum
}

void remove(const std::vector<int>& arr, int idx) {
    // For range sum, current_sum -= arr[idx];
    // For distinct count, freq[arr[idx]]--; if freq[arr[idx]] == 0, count--;
    current_sum -= arr[idx]; // Example for sum
}

std::vector<int> mosAlgorithm(const std::vector<int>& arr, std::vector<Query>& queries) {
    int n = arr.size();
    int q = queries.size();
    int block_size = static_cast<int>(std::sqrt(n));

    for (int i = 0; i < q; ++i) {
        queries[i].idx = i;
        queries[i].block = queries[i].l / block_size;
    }

    std::sort(queries.begin(), queries.end(), compareQueries);

    std::vector<int> results(q);
    // freq.assign(MAX_VAL + 1, 0); // Initialize frequency array based on max value in arr
    // Reset current_sum if mosAlgorithm is called multiple times without clearing global state
    current_sum = 0; 

    int current_l = 0;
    int current_r = -1;

    for (const auto& query : queries) {
        int L = query.l;
        int R = query.r;

        while (current_l > L) {
            current_l--;
            add(arr, current_l);
        }
        while (current_r < R) {
            current_r++;
            add(arr, current_r);
        }
        while (current_l < L) {
            remove(arr, current_l);
            current_l++;
        }
        while (current_r > R) {
            remove(arr, current_r);
            current_r--;
        }
        results[query.idx] = current_sum; // Store current_sum or other query result
    }
    return results;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

class Query {
    int l, r, idx, block;

    public Query(int l, int r, int idx) {
        this.l = l;
        this.r = r;
        this.idx = idx;
        this.block = -1;
    }
}

public class MoAlgorithm {
    private int currentSum = 0; 
    private int[] freq; // Max element value + 1, e.g., new int[100001];

    // `add` and `remove` methods depend on the specific query type.
    // Example for range sum:
    private void add(int[] arr, int idx) {
        currentSum += arr[idx];
        // If counting distinct elements: if (freq[arr[idx]] == 0) distinctCount++; freq[arr[idx]]++;
    }

    private void remove(int[] arr, int idx) {
        currentSum -= arr[idx];
        // If counting distinct elements: freq[arr[idx]]--; if (freq[arr[idx]] == 0) distinctCount--;
    }

    public int[] mosAlgorithm(int[] arr, List<Query> queries) {
        int n = arr.length;
        int blockSize = (int) Math.sqrt(n);

        // Initialize frequency array based on problem constraints
        // For this example, assuming array elements are within a small range (e.g., 0-100000)
        int maxVal = 0; // Determine max value to size freq array
        for(int x : arr) maxVal = Math.max(maxVal, x);
        freq = new int[maxVal + 1]; 
        Arrays.fill(freq, 0);
        currentSum = 0; // Reset sum for each call

        for (int i = 0; i < queries.size(); i++) {
            queries.get(i).block = queries.get(i).l / blockSize;
            queries.get(i).idx = i;
        }

        Collections.sort(queries, (a, b) -> {
            if (a.block != b.block) {
                return Integer.compare(a.block, b.block);
            }
            // Alternating sort for R to optimize
            if (a.block % 2 == 0) {
                return Integer.compare(a.r, b.r);
            } else {
                return Integer.compare(b.r, a.r);
            }
        });

        int[] results = new int[queries.size()];
        int currentL = 0;
        int currentR = -1;

        for (Query query : queries) {
            int L = query.l;
            int R = query.r;

            while (currentL > L) {
                currentL--;
                add(arr, currentL);
            }
            while (currentR < R) {
                currentR++;
                add(arr, currentR);
            }
            while (currentL < L) {
                remove(arr, currentL);
                currentL++;
            }
            while (currentR > R) {
                remove(arr, currentR);
                currentR--;
            }
            results[query.idx] = currentSum; // Store currentSum or other query result
        }
        return results;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
import math
from functools import cmp_to_key

class Query:
    def __init__(self, l, r, idx):
        self.l = l
        self.r = r
        self.idx = idx
        self.block = -1 # Will be assigned later

# Global state for `add` and `remove` functions, depends on problem
_current_sum = 0
_freq = [] # Placeholder, actual size depends on max value in array

def _add_mo(arr, idx):
    global _current_sum, _freq
    _current_sum += arr[idx] # Example for sum
    # if _freq[arr[idx]] == 0: distinct_count += 1; _freq[arr[idx]] += 1

def _remove_mo(arr, idx):
    global _current_sum, _freq
    _current_sum -= arr[idx] # Example for sum
    # _freq[arr[idx]] -= 1; if _freq[arr[idx]] == 0: distinct_count -= 1

def mos_algorithm(arr: list[int], queries: list[Query]) -> list[int]:
    n = len(arr)
    block_size = int(math.sqrt(n))

    global _freq, _current_sum
    # Initialize freq array based on max value in arr or problem constraints
    max_val = max(arr) if arr else 0
    _freq = [0] * (max_val + 1)
    _current_sum = 0 # Reset sum for each call to mos_algorithm

    for query in queries:
        query.block = query.l // block_size
    
    def compare_queries(q1, q2):
        if q1.block != q2.block:
            return q1.block - q2.block
        # Alternating sort for R to optimize
        if q1.block % 2 == 0:
            return q1.r - q2.r
        else:
            return q2.r - q1.r

    queries.sort(key=cmp_to_key(compare_queries))

    results = [0] * len(queries)
    current_l = 0
    current_r = -1 # Window is initially empty

    for query in queries:
        L, R, idx = query.l, query.r, query.idx

        while current_l > L:
            current_l -= 1
            _add_mo(arr, current_l)
        while current_r < R:
            current_r += 1
            _add_mo(arr, current_r)
        while current_l < L:
            _remove_mo(arr, current_l)
            current_l += 1
        while current_r > R:
            _remove_mo(arr, current_r);
            current_r -= 1
        
        results[idx] = _current_sum # Store the result for this query
    
    return results
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O((N + Q) * sqrt(N)) if `add` and `remove` operations take O(1) time, where N is array size and Q is number of queries. If `add`/`remove` take O(log N) (e.g., using a balanced BST or `std::map`), it becomes O((N + Q) * sqrt(N) * log N). Space Complexity: O(N + Q) for storing array, queries, and frequency map.
