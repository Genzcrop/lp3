#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> wt(n + 1), val(n + 1);
    cout << "Enter weight and value of each item:\n";
    for (int i = 1; i <= n; i++)
        cin >> wt[i] >> val[i];

    cout << "Enter knapsack capacity: ";
    cin >> W;

    // dp[i][w] = max value using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i] <= w)
                dp[i][w] = max(dp[i - 1][w],                      // exclude
                               val[i] + dp[i - 1][w - wt[i]]);    // include
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "\nMaximum value = " << dp[n][W] << endl;

    // Trace back to find the selected items
    cout << "Items selected (item numbers): ";
    int w = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {   // item i was included
            cout << i << " ";
            w -= wt[i];
        }
    }
    cout << endl;
    return 0;
}
// Time: O(n * W)   Space: O(n * W)  (can be reduced to O(W) with a 1D array)