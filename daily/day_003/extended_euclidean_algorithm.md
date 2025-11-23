# Extended Euclidean Algorithm

## 1. Introduction
The Extended Euclidean Algorithm is an extension of the standard Euclidean algorithm. While the traditional Euclidean algorithm only computes the greatest common divisor (GCD) of two integers 'a' and 'b', the extended version also finds integers 'x' and 'y' such that `ax + by = gcd(a, b)`. This equation is known as Bézout's identity.

## 2. When is it used?
This algorithm is fundamental in number theory and has wide applications in cryptography (e.g., finding modular multiplicative inverses in RSA), solving linear Diophantine equations, and computing inverses in finite fields.

## 3. ASCII Diagram

```
Euclidean Algorithm steps:
_gcd(a, b)_ = _gcd(b, a mod b)_ = ... = _gcd(g, 0)_ = g

Extended Euclidean Algorithm back-substitutes:
_g_ = _a_x + _b_y

Example: gcd(48, 18)
48 = 2 * 18 + 12
18 = 1 * 12 + 6
12 = 2 * 6 + 0
GCD is 6.

Back-substitution for 6:
6 = 18 - 1 * 12
6 = 18 - 1 * (48 - 2 * 18)
6 = 18 - 48 + 2 * 18
6 = 3 * 18 - 1 * 48
So, x = -1, y = 3 (for ax + by = gcd(a,b) where a=48, b=18)
```

## 4. Approaches

### Recursive Approach

The recursive approach directly implements the property `gcd(a, b) = gcd(b, a % b)`. For the base case, when `b` is 0, `gcd(a, 0) = a`, and we can set `x=1, y=0` (since `a*1 + 0*0 = a`). For the recursive step, we call the algorithm for `(b, a % b)`, which returns `gcd`, `x1`, `y1` such that `b*x1 + (a % b)*y1 = gcd`. By substituting `a % b = a - floor(a/b)*b`, we can derive `x` and `y` for `(a, b)`: `x = y1` and `y = x1 - floor(a/b)*y1`.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>

// Structure to return GCD and coefficients x, y
struct Result {
    long long gcd;
    long long x;
    long long y;
};

Result extendedEuclidean(long long a, long long b) {
    if (b == 0) {
        return {a, 1, 0}; // Base case: a*1 + b*0 = a
    }

    Result res = extendedEuclidean(b, a % b);

    // Update x and y using results from recursive call
    long long newX = res.y;
    long long newY = res.x - (a / b) * res.y;

    return {res.gcd, newX, newY};
}

// Function to find modular inverse
// Returns (a^-1) % m if it exists, otherwise -1
long long modInverse(long long a, long long m) {
    Result res = extendedEuclidean(a, m);
    if (res.gcd != 1) {
        return -1; // Modular inverse does not exist
    } else {
        // Ensure x is positive
        // (res.x % m + m) % m handles negative results from extendedEuclidean
        return (res.x % m + m) % m;
    }
}

int main() {
    long long a = 48, b = 18;
    Result res = extendedEuclidean(a, b);
    std::cout << "For a=" << a << ", b=" << b << ":" << std::endl;
    std::cout << "GCD(" << a << ", " << b << ") = " << res.gcd << std::endl;
    std::cout << "x = " << res.x << ", y = " << res.y << std::endl;
    std::cout << a << "*" << res.x << " + " << b << "*" << res.y << " = " << (a * res.x + b * res.y) << std::endl;

    std::cout << "\n-- Modular Inverse Examples --" << std::endl;
    long long num = 3, mod = 11;
    long long inv = modInverse(num, mod);
    if (inv != -1) {
        std::cout << "Modular inverse of " << num << " mod " << mod << " is: " << inv << std::endl; // Expected: 4 (3*4 = 12 = 1 mod 11)
    } else {
        std::cout << "Modular inverse of " << num << " mod " << mod << " does not exist." << std::endl;
    }

    num = 10, mod = 17;
    inv = modInverse(num, mod);
    if (inv != -1) {
        std::cout << "Modular inverse of " << num << " mod " << mod << " is: " << inv << std::endl; // Expected: 12 (10*12 = 120 = 1 mod 17)
    } else {
        std::cout << "Modular inverse of " << num << " mod " << mod << " does not exist." << std::endl;
    }

    num = 4, mod = 6; // gcd(4, 6) = 2 != 1
    inv = modInverse(num, mod);
    if (inv != -1) {
        std::cout << "Modular inverse of " << num << " mod " << mod << " is: " << inv << std::endl;
    } else {
        std::cout << "Modular inverse of " << num << " mod " << mod << " does not exist." << std::endl; // Expected: does not exist
    }

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
public class ExtendedEuclidean {

    static class Result {
        long gcd;
        long x;
        long y;

        Result(long gcd, long x, long y) {
            this.gcd = gcd;
            this.x = x;
            this.y = y;
        }
    }

    public static Result extendedEuclidean(long a, long b) {
        if (b == 0) {
            return new Result(a, 1, 0); // Base case: a*1 + b*0 = a
        }

        Result res = extendedEuclidean(b, a % b);

        // Update x and y using results from recursive call
        long newX = res.y;
        long newY = res.x - (a / b) * res.y;

        return new Result(res.gcd, newX, newY);
    }

    // Function to find modular inverse
    // Returns (a^-1) % m if it exists, otherwise -1
    public static long modInverse(long a, long m) {
        Result res = extendedEuclidean(a, m);
        if (res.gcd != 1) {
            return -1; // Modular inverse does not exist
        } else {
            // Ensure x is positive
            // (res.x % m + m) % m handles negative results from extendedEuclidean
            return (res.x % m + m) % m;
        }
    }

    public static void main(String[] args) {
        long a = 48, b = 18;
        Result res = extendedEuclidean(a, b);
        System.out.println("For a=" + a + ", b=" + b + ":");
        System.out.println("GCD(" + a + ", " + b + ") = " + res.gcd);
        System.out.println("x = " + res.x + ", y = " + res.y);
        System.out.println(a + "*" + res.x + " + " + b + "*" + res.y + " = " + (a * res.x + b * res.y));

        System.out.println("\n-- Modular Inverse Examples --");
        long num = 3, mod = 11;
        long inv = modInverse(num, mod);
        if (inv != -1) {
            System.out.println("Modular inverse of " + num + " mod " + mod + " is: " + inv); // Expected: 4 (3*4 = 12 = 1 mod 11)
        } else {
            System.out.println("Modular inverse of " + num + " mod " + mod + " does not exist.");
        }

        num = 10; mod = 17;
        inv = modInverse(num, mod);
        if (inv != -1) {
            System.out.println("Modular inverse of " + num + " mod " + mod + " is: " + inv); // Expected: 12 (10*12 = 120 = 1 mod 17)
        } else {
            System.out.println("Modular inverse of " + num + " mod " + mod + " does not exist.");
        }

        num = 4; mod = 6; // gcd(4, 6) = 2 != 1
        inv = modInverse(num, mod);
        if (inv != -1) {
            System.out.println("Modular inverse of " + num + " mod " + mod + " is: " + inv);
        } else {
            System.out.println("Modular inverse of " + num + " mod " + mod + " does not exist."); // Expected: does not exist
        }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def extended_euclidean(a, b):
    if b == 0:
        return a, 1, 0 # Base case: a*1 + b*0 = a
    
    gcd, x1, y1 = extended_euclidean(b, a % b)

    # Update x and y using results from recursive call
    x = y1
    y = x1 - (a // b) * y1

    return gcd, x, y

def mod_inverse(a, m):
    gcd, x, y = extended_euclidean(a, m)
    if gcd != 1:
        return -1 # Modular inverse does not exist
    else:
        # Ensure x is positive
        # (x % m + m) % m handles negative results from extended_euclidean
        return (x % m + m) % m

if __name__ == "__main__":
    a, b = 48, 18
    gcd, x, y = extended_euclidean(a, b)
    print(f"For a={a}, b={b}:")
    print(f"GCD({a}, {b}) = {gcd}")
    print(f"x = {x}, y = {y}")
    print(f"{a}*{x} + {b}*{y} = {a * x + b * y}")

    print("\n-- Modular Inverse Examples --")
    num, mod = 3, 11
    inv = mod_inverse(num, mod)
    if inv != -1:
        print(f"Modular inverse of {num} mod {mod} is: {inv}") # Expected: 4 (3*4 = 12 = 1 mod 11)
    else:
        print(f"Modular inverse of {num} mod {mod} does not exist.")

    num, mod = 10, 17
    inv = mod_inverse(num, mod)
    if inv != -1:
        print(f"Modular inverse of {num} mod {mod} is: {inv}") # Expected: 12 (10*12 = 120 = 1 mod 17)
    else:
        print(f"Modular inverse of {num} mod {mod} does not exist.")

    num, mod = 4, 6 # gcd(4, 6) = 2 != 1
    inv = mod_inverse(num, mod)
    if inv != -1:
        print(f"Modular inverse of {num} mod {mod} is: {inv}")
    else:
        print(f"Modular inverse of {num} mod {mod} does not exist.") # Expected: does not exist
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(log(min(a,b))). This is because the Euclidean algorithm reduces the larger number by at least half in two steps, resulting in a logarithmic number of steps. Space Complexity: O(log(min(a,b))) due to the recursion stack.
