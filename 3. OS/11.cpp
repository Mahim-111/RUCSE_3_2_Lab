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

    int frame[frames];
    int front = 0; // points to oldest page (FIFO)

    // Initialize frames with -1 (empty)
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    int hits = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check if page is already in frame (hit)
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = true;
                hits++;
                break;
            }
        }

        // If not found → page fault
        if (!found)
        {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            faults++;
        }

        // Display current frame state
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

    cout << "\nTotal Page Hits = " << hits << endl;
    cout << "Total Page Faults = " << faults << endl;

    return 0;
}