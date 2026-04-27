#include <iostream>
using namespace std;

int main()
{
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    int pages[n];
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    int frame[frames], time[frames];

    // Initialize
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }

    int faults = 0, counter = 0;

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check for hit
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = true;
                counter++;
                time[j] = counter; // update last used time
                break;
            }
        }

        // If page fault
        if (!found)
        {
            int lruIndex = 0;

            // Find least recently used page
            for (int j = 1; j < frames; j++)
            {
                if (time[j] < time[lruIndex])
                {
                    lruIndex = j;
                }
            }

            counter++;
            frame[lruIndex] = pages[i];
            time[lruIndex] = counter;
            faults++;
        }

        // Display frame status
        cout << "Frames: ";
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == -1)
                cout << "- ";
            else
                cout << frame[j] << " ";
        }
        cout << endl;
    }

    cout << "\nTotal Page Faults = " << faults << endl;

    return 0;
}