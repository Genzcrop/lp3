#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    char id;
    int deadline;
    int profit;
};

// Sort by profit, descending (greedy choice)
bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    cout << "Enter job id, deadline, profit for each job:\n";
    for (int i = 0; i < n; i++)
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;

    sort(jobs.begin(), jobs.end(), cmp);

    int maxDeadline = 0;
    for (auto &j : jobs) maxDeadline = max(maxDeadline, j.deadline);

    vector<char> slot(maxDeadline + 1, '-');   // slots 1..maxDeadline
    vector<bool> filled(maxDeadline + 1, false);
    int totalProfit = 0, count = 0;

    for (int i = 0; i < n; i++) {
        // Find the latest free slot on or before the deadline
        for (int t = jobs[i].deadline; t >= 1; t--) {
            if (!filled[t]) {
                filled[t] = true;
                slot[t] = jobs[i].id;
                totalProfit += jobs[i].profit;
                count++;
                break;
            }
        }
    }

    cout << "\nJob sequence: ";
    for (int t = 1; t <= maxDeadline; t++)
        if (filled[t]) cout << slot[t] << " ";

    cout << "\nJobs scheduled: " << count;
    cout << "\nTotal profit: " << totalProfit << endl;
    return 0;
}
// Time: O(n log n) for sorting + O(n * d) for slot search = O(n^2) worst case
// Space: O(d)