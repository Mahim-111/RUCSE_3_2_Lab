#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], pr[n];
    int ct[n], wt[n], tat[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> at[i];

        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];

        cout << "Enter Priority for P" << i + 1 << ": ";
        cin >> pr[i];

        rt[i] = bt[i]; // remaining time
    }

    int completed = 0, time = 0;

    while (completed < n)
    {
        int highest = -1;
        int bestPriority = INT_MAX;

        // Find highest priority process (lowest number)
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] > 0)
            {
                if (pr[i] < bestPriority)
                {
                    bestPriority = pr[i];
                    highest = i;
                }
            }
        }

        if (highest == -1)
        {
            time++; // CPU idle
            continue;
        }

        // Execute for 1 unit time
        rt[highest]--;
        time++;

        // If process finishes
        if (rt[highest] == 0)
        {
            completed++;

            ct[highest] = time;
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];
        }
    }

    // Display results
    cout << "\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}