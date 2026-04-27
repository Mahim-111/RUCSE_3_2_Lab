#include <iostream>
using namespace std;

int main()
{
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[n][m], request[n][m], avail[m];

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> alloc[i][j];
        }
    }

    // Input Request Matrix
    cout << "\nEnter Request Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> request[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; j++)
    {
        cin >> avail[j];
    }

    bool finish[n];

    // Initialize finish array
    for (int i = 0; i < n; i++)
    {
        bool zeroAlloc = true;

        for (int j = 0; j < m; j++)
        {
            if (alloc[i][j] != 0)
            {
                zeroAlloc = false;
                break;
            }
        }

        if (zeroAlloc)
            finish[i] = true;
        else
            finish[i] = false;
    }

    // Deadlock detection
    bool found;
    do
    {
        found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool possible = true;

                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > avail[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if (possible)
                {
                    // Release resources
                    for (int j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    finish[i] = true;
                    found = true;
                }
            }
        }

    } while (found);

    // Check deadlock
    bool deadlock = false;

    cout << "\nDeadlocked Processes: ";
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            cout << "P" << i << " ";
            deadlock = true;
        }
    }

    if (!deadlock)
        cout << "None (No Deadlock)";

    cout << endl;

    return 0;
}