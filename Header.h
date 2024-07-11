#ifndef _EDF_VD_
#define _EDF_VD_

#define _CRT_SECURE_NO_DEPRECATE
#define CRITICALITY_LEVELS 2
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<queue>
#include<math.h>
#include<functional>
#include<time.h>
#include<limits.h>
using namespace std;

struct tasks
{
    int id, arr_time, period, criticality;
    float wcet[CRITICALITY_LEVELS], deadline, vir_deadline;
};
struct jobs {
    int  id, arr_time;
    float abs_deadline, rem_ET;
};

vector<tasks> read_file();
float calc_util(vector<float>& vec, int ntasks, vector<tasks> j);
void preProcePhase(float x, int ntasks, vector<tasks> j);
int calcHyperPeriod(vector<tasks> j);
void schedule(vector<tasks> j, vector<jobs>&,float);
void runningPhase(int ntasks, vector<tasks> j);
void buildMinHeap(vector<jobs>& );
void minHeapify(vector<jobs>&, int, int);
void extractMin(vector<jobs>& );
void addJob(vector<jobs>&, int);
jobs searchWQJob(jobs, vector<tasks>,float,vector<jobs>);
void addJobRQ(vector<tasks> j, vector<jobs>& rq, float timer,jobs);
int searchIDJob(vector<tasks> j, jobs tar);
int searchIDTask(vector<jobs> t, tasks tar);
float randNo(float min, float max);
void runningPhaseVD(int ntasks, vector<tasks> j);
void scheduleVD_low(vector<tasks> j, vector<jobs>& rq, float timer,int);
void addJobRQVD(vector<tasks> j, vector<jobs>& rq, float timer,jobs,int);
jobs searchWQJobVD(jobs tar, vector<tasks> j, float timer, vector<jobs> rq);
void scheduleVD_high(vector<tasks> j, vector<jobs>& rq, float timer,int,int);
void createHighRQ(vector<tasks> j, vector<jobs>& rq, int timer);
jobs searchWQJobVD_high(jobs tar, vector<tasks> j, float timer, vector<jobs> rq,int);
void addJobRQVD_high(vector<tasks> j, vector<jobs>& rq, float timer, jobs tar,int);
int jobExistsinRQ(vector<jobs> rq, int id);
//void heapSort(vector<jobs>&);
#endif
