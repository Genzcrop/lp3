#include <iostream>
#include <vector>
using namespace std;

// Non-recursive: Time O(n), Space O(1)
long long fibIter(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Recursive: Time O(2^n), Space O(n) (call stack)
long long fibRec(int n) {
    if (n <= 1) return n;
    return fibRec(n - 1) + fibRec(n - 2);
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    cout << "\nFibonacci series (iterative): ";
    for (int i = 0; i < n; i++) cout << fibIter(i) << " ";

    cout << "\nFibonacci series (recursive): ";
    for (int i = 0; i < n; i++) cout << fibRec(i) << " ";

    
    return 0;
}