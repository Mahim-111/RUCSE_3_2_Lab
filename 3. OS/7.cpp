#include <iostream>
using namespace std;

int main() {
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], rt[n], wt[n], tat[n], ct[n];

    // Input burst times
    for (int i = 0; i < n; i++) {
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];
        rt[i] = bt[i]; // remaining time
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int time = 0, done;

    cout << "\nGantt Chart:\n| ";

    do {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;

                cout << "P" << i + 1 << " | ";

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;
                }
            }
        }

    } while (!done);

    // Calculate WT and TAT
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i];         // since arrival time = 0
        wt[i] = tat[i] - bt[i];
    }

    // Display time line
    cout << "\n0 ";
    int tempTime = 0;
    for (int i = 0; i < n; i++) {
        tempTime += bt[i];
        cout << tempTime << " ";
    }

    // Display table
    cout << "\n\nProcess\tBT\tCT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}