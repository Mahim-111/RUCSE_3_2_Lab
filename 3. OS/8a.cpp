#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], wt[n], tat[n], ct[n], pr[n], pid[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter Burst Time for P" << pid[i] << ": ";
        cin >> bt[i];
        cout << "Enter Priority for P" << pid[i] << ": ";
        cin >> pr[i];
    }

    // Sort by priority (lower value = higher priority)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (pr[i] > pr[j])
            {
               swap(pr[i], pr[j]);
               swap(bt[i], bt[j]);
               swap(pid[i], pid[j]);
            }
        }
    }

    // Calculate Waiting Time
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate Turnaround Time and Completion Time
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        ct[i] = tat[i]; // since AT = 0
    }

    // Display results
    cout << "\nProcess\tBT\tPriority\tCT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}