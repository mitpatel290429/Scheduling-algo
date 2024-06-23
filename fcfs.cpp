#include<bits/stdc++.h>
using namespace std;

class Process{
    public :

    int pid;
    int AT;
    int BT;
    int TAT;
    int WT;
    int CT;

    Process(int pid,int AT,int BT){
        this->pid=pid;
        this->AT=AT;
        this->BT=BT;
    }
};

pair<float,float> fcfs(vector<Process>& processes){
    int n=processes.size();
    sort(processes.begin(),processes.end(),[](const Process& a,const Process& b){
        return a.AT<b.AT;
    });

    int time=0;
    for(int i=0;i<n;i++){
        if(processes[i].AT>time) time=processes[i].AT;
        
        time+=processes[i].BT;
        processes[i].CT=time;
        processes[i].TAT=processes[i].CT-processes[i].AT;
        processes[i].WT=processes[i].TAT-processes[i].BT;
    }

    float avg_TAT=0;
    float avg_WT=0;
    for(int i=0;i<n;i++){
        avg_TAT+=processes[i].TAT;
        avg_WT+=processes[i].WT;
    }
    return {avg_TAT/n,avg_WT/n};
}

int main(){
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    vector<Process> processes;

    for(int i=0;i<n;i++){
        int pid,AT,BT;
        cout<<"Enter Process ID, Arrival Time , Burst Time : ";
        cin>>pid>>AT>>BT;
        processes.push_back(Process(pid,AT,BT));
    }

    pair<float,float> ans=fcfs(processes);
    cout<<"Average Turn Around Time : "<<ans.first<<endl;
    cout<<"Average Waiting Time : "<<ans.second<<endl;
}