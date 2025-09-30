/*The Safety Algorithm

    This algorithm determines if the system is in a safe state.

Initialization:

    Calculate the Need matrix where Need[i][j] = Max[i][j] - Allocation[i][j].

    Create a Work vector, which is a copy of the Available resources.

    Create a boolean Finish vector (size equal to the number of processes), and initialize all its elements to false.

Find a Safe Process:

    Search for a process i that satisfies both of the following conditions:

    Finish[i] is false.

    Need[i] <= Work. (The process's needs are less than or equal to the available resources).

Update and Progress:

    If you find such a process in Step 2:

    Update the Work vector by adding the resources allocated to that process: Work = Work + Allocation[i]. This simulates releasing the resources.

    Mark the process as finished: Finish[i] = true.

    Add this process to the safe sequence.

    Go back to Step 2 to find the next process.

    If no such process can be found, proceed to Step 4.

Determine Safety:

    After the loop finishes, check if all elements in the Finish vector are true.

    If all are true, the system is in a safe state, and you have found a valid safe sequence.

    If any element is false, the system is in an unsafe state.*/

#include <iostream>
#include <vector>

using namespace std;

// Define the number of processes and resources
const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Function to check if the system is in a safe state
void checkSafeState(
    vector<int>& processes,
    vector<int>& available,
    vector<vector<int>>& max,
    vector<vector<int>>& allocation) {

    // 1. Calculate the Need matrix and initialize Work & Finish
    vector<vector<int>> need(P, vector<int>(R));
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    vector<int> work = available;
    vector<bool> finish(P, false);
    vector<int> safeSequence;

    // 2. & 3. Find a safe process and update
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            // Check if process p is not finished yet
            if (finish[p] == false) {
                // Check if its needs can be met with current work
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break; // Not enough resources
                    }
                }

                // If all needs were met (loop completed)
                if (j == R) {
                    // Release the resources allocated to this process
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }

                    // Add process to safe sequence and mark as finished
                    safeSequence.push_back(p);
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        // If no process was found, the system is unsafe
        if (found == false) {
            cout << "System is in an UNSAFE STATE." << endl;
            return;
        }
    }

    // 4. If all processes finished, the system is safe
    cout << "System is in a SAFE STATE." << endl;
    cout << "Safe Sequence: ";
    for (int i = 0; i < P; i++) {
        cout << "P" << safeSequence[i] << (i == P - 1 ? "" : " -> ");
    }
    cout << endl;
}

int main() {
    // Process IDs
    vector<int> processes = {0, 1, 2, 3, 4};

    // Available instances of resources
    vector<int> available = {3, 3, 2};

    // Maximum R that can be allocated to processes
    vector<vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};

    // Resources currently allocated to processes
    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};

    // Check if the system is in a safe state
    checkSafeState(processes, available, max, allocation);

    return 0;
}