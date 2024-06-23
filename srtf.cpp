#include<bits/stdc++.h>
using namespace std;

class Process {
    public: 
        int pid, AT, BT, CT, TAT, WT, remaining_BT;

        Process(int pid, int AT, int BT) {
            this->pid = pid;
            this->AT = AT;
            this->BT = BT;
            this->remaining_BT = BT;
            this->CT = 0;
            this->TAT = 0;
            this->WT = 0;
        }
};

pair<float, float> srtf(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.AT < b.AT;
    });

    int current_time = 0, completed = 0;
    float total_TAT = 0, total_WT = 0;
    vector<bool> is_completed(n, false);

    while (completed != n) {
        int idx = -1;
        int min_remaining_BT = INT_MAX;

        // Find the process with the minimum remaining burst time at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].AT <= current_time && !is_completed[i] && processes[i].remaining_BT < min_remaining_BT) {
                min_remaining_BT = processes[i].remaining_BT;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].remaining_BT--;
            current_time++;

            if (processes[idx].remaining_BT == 0) {
                processes[idx].CT = current_time;
                processes[idx].TAT = processes[idx].CT - processes[idx].AT;
                processes[idx].WT = processes[idx].TAT - processes[idx].BT;

                total_TAT += processes[idx].TAT;
                total_WT += processes[idx].WT;
                is_completed[idx] = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    float avg_TAT = total_TAT / n;
    float avg_WT = total_WT / n;

    return {avg_TAT, avg_WT};
}

int main() {
    cout << "Enter number of processes: ";
    int n;
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int pid, AT, BT;
        cout << "Enter Process ID, Arrival Time, Burst Time: ";
        cin >> pid >> AT >> BT;
        processes.push_back(Process(pid, AT, BT));
    }

    pair<float, float> ans = srtf(processes);
    cout << "Average TAT: " << ans.first << "\n";
    cout << "Average WT: " << ans.second << "\n";
    
    return 0;
}