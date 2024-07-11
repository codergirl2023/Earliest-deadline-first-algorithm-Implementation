#ifndef _EDF_VD_
#define _EDF_VD_

#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<queue>
using namespace std;

struct tasks
{
    int id, arr_time, period, criticality, wcet_low, wcet_hi, rel_deadline, rel_virtual_deadline;
};
struct ex_time {
    int abs_deadline, id, rem_ET, arr_time;
};

vector<tasks> read_file();
float calc_util(vector<float>& vec, int ntasks, vector<tasks> j);
void preProcePhase(float x, int ntasks, vector<tasks> j);
int calcHyperPeriod(vector<tasks> j);
bool compare(ex_time t1, ex_time t2);
int findNextJobToRun(vector<ex_time> rq, int* timer);
void addNewJob(vector<ex_time>& rq, int k, vector<tasks> j);
void displayReadyQueue(vector<ex_time>rq);
void schedule(vector<tasks> j, vector<ex_time> rq);
void runningPhase(int ntasks, vector<tasks> j);
#endif