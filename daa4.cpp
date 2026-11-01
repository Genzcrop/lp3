#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    double value, weight;
};

// Sort by value/weight ratio, descending
bool cmp(Item a, Item b) {
    return (a.value / a.weight) > (b.value / b.weight);
}

int main() {
    int n;
    double W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++)
        cin >> items[i].value >> items[i].weight;

    cout << "Enter knapsack capacity: ";
    cin >> W;

    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;
    double remaining = W;

    cout << "\nItems taken:\n";
    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].weight <= remaining) {
            // take the whole item
            totalValue += items[i].value;
            remaining -= items[i].weight;
            cout << "Item (v=" << items[i].value << ", w=" << items[i].weight
                 << ") -> full\n";
        } else {
            // take a fraction
            double fraction = remaining / items[i].weight;
            totalValue += items[i].value * fraction;
            cout << "Item (v=" << items[i].value << ", w=" << items[i].weight
                 << ") -> fraction " << fixed << setprecision(2) << fraction << "\n";
            remaining = 0;
        }
    }

    cout << "\nMaximum value = " << fixed << setprecision(2) << totalValue << endl;
    return 0;
}
// Time: O(n log n)   Space: O(1) extra