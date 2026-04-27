#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], wt[n], tat[n];

    // Input burst times
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> bt[i];
    }

    // First process waiting time is 0
    wt[0] = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }

    // Calculate averages
    float total_wt = 0, total_tat = 0;

    cout << "\nProcess\tBT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];

        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time = " << total_wt / n << endl;
    cout << "Average Turnaround Time = " << total_tat / n << endl;

    return 0;
}