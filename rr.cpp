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

pair<float, float> rr(vector<Process>& processes, int tc) {
    int n = processes.size();
    queue<int> q;
    int time = 0;
    int completed = 0;
    float total_TAT = 0, total_WT = 0;

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.AT < b.AT;
    });

    // Initial process entry into the queue
    q.push(0);
    vector<bool> in_queue(n, false);
    in_queue[0] = true;
    time = processes[0].AT;

    while (completed != n) {
        if (q.empty()) {
            // If the queue is empty, find the next available process
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && processes[i].AT > time) {
                    q.push(i);
                    in_queue[i] = true;
                    time = processes[i].AT;
                    break;
                }
            }
        }

        int front = q.front();
        q.pop();
        if (processes[front].remaining_BT > tc) {
            processes[front].remaining_BT -= tc;
            time += tc;
        } else {
            time += processes[front].remaining_BT;
            processes[front].remaining_BT = 0;
            processes[front].CT = time;
            processes[front].TAT = processes[front].CT - processes[front].AT;
            processes[front].WT = processes[front].TAT - processes[front].BT;
            total_TAT += processes[front].TAT;
            total_WT += processes[front].WT;
            completed++;
        }

        // Add all processes that have arrived by the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].AT <= time && processes[i].remaining_BT > 0 && !in_queue[i]) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        // If the process has remaining burst time, push it back into the queue
        if (processes[front].remaining_BT > 0) {
            q.push(front);
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
    cout << "Enter time quantum: ";
    int tc;
    cin >> tc;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int pid, AT, BT;
        cout << "Enter Process ID, Arrival Time, Burst Time: ";
        cin >> pid >> AT >> BT;
        processes.push_back(Process(pid, AT, BT));
    }

    pair<float, float> ans = rr(processes, tc);
    cout << "Average TAT: " << ans.first << "\n";
    cout << "Average WT: " << ans.second << "\n";

    for (const auto& p : processes) {
        cout << "Process ID: " << p.pid << ", AT: " << p.AT << ", BT: " << p.BT
             << ", CT: " << p.CT << ", TAT: " << p.TAT << ", WT: " << p.WT << "\n";
    }

    return 0;
}