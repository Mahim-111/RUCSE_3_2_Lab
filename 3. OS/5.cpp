#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], wt[n], tat[n], pid[n];

    // Input burst times
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter Burst Time for Process " << pid[i] << ": ";
        cin >> bt[i];
    }

    // Sort by burst time (SJF)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                swap(bt[i], bt[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    // Calculate waiting time
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n| ";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << " | ";
    }

    cout << "\n0 ";
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        time += bt[i];
        cout << time << " ";
    }

    // Display table
    cout << "\n\nProcess\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}