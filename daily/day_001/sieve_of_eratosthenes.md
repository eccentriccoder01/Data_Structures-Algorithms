# Sieve of Eratosthenes

## 1. Introduction
The Sieve of Eratosthenes is an ancient and efficient algorithm for finding all prime numbers up to a specified integer limit. It works by iteratively marking as composite (i.e., not prime) the multiples of each prime, starting with the first prime number, 2. Unmarked numbers remaining in the list are prime.

## 2. When is it used?
Finding prime numbers for cryptography, number theory problems in competitive programming, factorization, generating test cases for algorithms involving primes.

## 3. ASCII Diagram

```
Limit N = 30

Initial list (all true/prime candidates):
[F, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T]
(Indices 0, 1 are not prime by definition or convention, 0 and 1 are typically excluded)

1. Mark multiples of 2:
   [F,F,T,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T,F,T]

2. Next unmarked number is 3. Mark multiples of 3 (starting from 3*3=9):
   [F,F,T,T,F,T,F,T,F,F,F,T,F,T,F,F,F,T,F,T,F,F,F,T,F,T,F,F,F,T]
   (e.g., 9, 15, 21, 27 are marked F)

3. Next unmarked number is 5. Mark multiples of 5 (starting from 5*5=25):
   [F,F,T,T,F,T,F,T,F,F,F,T,F,T,F,F,F,T,F,T,F,F,F,T,F,F,F,F,F,T]
   (e.g., 25 is marked F)

4. Next unmarked number is 7. Its square 49 > 30, so all remaining unmarked numbers are prime.

Primes up to 30: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
```

## 4. Approaches

### Basic Sieve of Eratosthenes

The basic Sieve of Eratosthenes uses a boolean array, `isPrime`, of size `limit + 1`, initialized to `true` (assuming all numbers are prime). It iterates from `p = 2` up to `sqrt(limit)`. If `isPrime[p]` is `true`, then `p` is a prime number. For each such prime `p`, all its multiples `(p*p, p*p + p, p*p + 2p, ...)` up to `limit` are marked as `false` (composite). The iteration starts from `p*p` because any multiple smaller than `p*p` (e.g., `k*p` where `k < p`) would have already been marked by a smaller prime factor `k`.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <numeric>

std::vector<bool> sieveOfEratosthenes(int limit) {
    std::vector<bool> isPrime(limit + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    for (int p = 2; p * p <= limit; p++) {
        // If isPrime[p] is true, then it is a prime
        if (isPrime[p]) {
            // Mark all multiples of p as false
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }
    return isPrime;
}

// To get a list of primes:
std::vector<int> getPrimes(int limit) {
    std::vector<bool> isPrime = sieveOfEratosthenes(limit);
    std::vector<int> primes;
    for (int p = 2; p <= limit; p++) {
        if (isPrime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class SieveOfEratosthenes {
    public boolean[] sieveOfEratosthenes(int limit) {
        boolean[] isPrime = new boolean[limit + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = false;
        isPrime[1] = false;

        for (int p = 2; p * p <= limit; p++) {
            if (isPrime[p]) {
                // Mark all multiples of p as false
                for (int i = p * p; i <= limit; i += p)
                    isPrime[i] = false;
            }
        }
        return isPrime;
    }

    // To get a list of primes:
    public List<Integer> getPrimes(int limit) {
        boolean[] isPrime = sieveOfEratosthenes(limit);
        List<Integer> primes = new ArrayList<>();
        for (int p = 2; p <= limit; p++) {
            if (isPrime[p]) {
                primes.add(p);
            }
        }
        return primes;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def sieve_of_eratosthenes(limit):
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False

    p = 2
    while p * p <= limit:
        if is_prime[p]:
            # Mark all multiples of p as false
            for i in range(p * p, limit + 1, p):
                is_prime[i] = False
        p += 1
    return is_prime

# To get a list of primes:
def get_primes(limit):
    is_prime = sieve_of_eratosthenes(limit)
    primes = []
    for p in range(2, limit + 1):
        if is_prime[p]:
            primes.append(p)
    return primes
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N log log N). The outer loop runs up to sqrt(N), and for each prime p, its multiples are marked. The sum of 1/p for primes p up to N is log log N. Space Complexity: O(N) for the boolean array.
