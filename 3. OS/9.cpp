#include <iostream>
using namespace std;

int main()
{
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    // Input Allocation matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> alloc[i][j];
        }
    }

    // Input Maximum matrix
    cout << "\nEnter Maximum Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> max[i][j];
        }
    }

    // Input Available resources
    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; j++)
    {
        cin >> avail[j];
    }

    // Calculate Need matrix = Max - Allocation
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    bool finish[n];
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }

    int safeSeq[n];
    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool possible = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if (possible)
                {
                    // Add allocated resources back
                    for (int j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            cout << "\nSystem is NOT in a safe state (Deadlock possible)\n";
            return 0;
        }
    }

    // Safe state
    cout << "\nSystem is in a SAFE state\nSafe Sequence: ";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << safeSeq[i];
        if (i != n - 1)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}