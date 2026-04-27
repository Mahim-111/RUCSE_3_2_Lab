#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], ct[n], wt[n], tat[n];

    // Input Arrival Time and Burst Time
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];
        rt[i] = bt[i]; // remaining time initially = burst time
    }

    int completed = 0, currentTime = 0;

    while (completed < n)
    {
        int shortest = -1;
        int minTime = INT_MAX;

        // Find process with minimum remaining time
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currentTime && rt[i] > 0 && rt[i] < minTime)
            {
                minTime = rt[i];
                shortest = i;
            }
        }

        if (shortest == -1)
        {
            currentTime++; // no process available
            continue;
        }

        // Execute process for 1 unit time
        rt[shortest]--;
        currentTime++;

        // If process is completed
        if (rt[shortest] == 0)
        {
            completed++;

            ct[shortest] = currentTime;

            tat[shortest] = ct[shortest] - at[shortest];

            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    // Display results
    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}