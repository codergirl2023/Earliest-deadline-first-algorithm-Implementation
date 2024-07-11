#include"Header.h"
/*#include"calcUtilization.cpp"
#include"heap.cpp"
#include"hyperPeriod.cpp"
#include"preProcessPhase.cpp"
#include"randNo.cpp"
#include"readFile.cpp"
#include"searchID.cpp"
#include"createHighRQ.cpp"
*/
jobs searchWQJobVD(jobs tar, vector<tasks> j, float timer, vector<jobs> rq) {
	int cnt, arr_time;
	float deadline, temp = INT_MAX;
	jobs wq;
	wq.arr_time = -1;
	for (int i = 0; i < j.size(); i++) {
		cnt = ceil(timer / j[i].period);
		arr_time = j[i].arr_time + cnt * j[i].period;
		deadline = j[i].deadline + arr_time;
		if (tar.id != j[i].id && timer < arr_time && deadline < temp && deadline < tar.abs_deadline && arr_time < tar.rem_ET + timer && (jobExistsinRQ(rq, j[i].id) == -1)) {
			temp = deadline;
			wq.abs_deadline = deadline;
			wq.arr_time = arr_time;
			wq.id = j[i].id;
			wq.rem_ET = j[i].wcet[1];
		}
	}
	return wq;
}

void addJobRQVD(vector<tasks> j, vector<jobs>& rq, float timer, jobs tar,int cri) {
	int cnt, arr_time, k;
	float deadline, temp = INT_MAX, wcet, rand_no;
	for (int i = 0; i < j.size(); i++) {
		cnt = (timer / j[i].period);
		arr_time = j[i].arr_time + cnt * j[i].period;
		rand_no = randNo(0.7, 1.0);
		if (j[i].criticality == cri) {
			deadline = arr_time + j[i].deadline;
			wcet = j[i].wcet[0] * rand_no;
		}
		else {
			deadline = arr_time + j[i].vir_deadline;
			wcet = j[i].wcet[1] * rand_no;
		}
		if (arr_time <= timer && searchIDTask(rq, j[i]) == -1 && ((tar.arr_time < arr_time && deadline < tar.abs_deadline) || tar.arr_time < arr_time)) {
			rq.push_back({ j[i].id,arr_time,deadline,wcet });
			addJob(rq, rq.size() - 1);
		}
	}
}

void scheduleVD_low(vector<tasks> j, vector<jobs>& rq, float timer,int cri) {
	int i = 0, k, hyperPeriod = calcHyperPeriod(j),cnt;
	vector<int> count(j.size(), 0);
	float diff, rand_no;
	jobs temp, wq;
	wq.arr_time = -1, temp.arr_time = -1;
	cout << "\n****************************SCHEDULE:******************************************\n\n";
	while (timer < hyperPeriod)
	{
		/*cout << "\n waiting queue:\n";
		for (int i = 0; i < wq.size(); i++)
			cout << "arr=" << wq[i].arr_time << " exe=" << wq[i].rem_ET << " id= " << wq[i].id << " deadline=" << wq[i].abs_deadline << endl;
		cout << "ready queue:\n";
		for (int i = 0; i < rq.size(); i++)
			cout << "arr=" << rq[i].arr_time << " exe=" << rq[i].rem_ET << " id= " << rq[i].id << " deadline=" << rq[i].abs_deadline << endl;
		*/
		if (!rq.empty()) {
			wq = searchWQJobVD(rq[0], j, timer, rq);
			cnt = rq[0].id;
		}
		if (wq.arr_time != -1 && !rq.empty()) {
			temp = rq[0];
			diff = wq.arr_time - timer;
			rq[0].rem_ET -= diff;
			//cout << "diff=" << diff << endl;
			if (timer + diff < hyperPeriod) {
				cout << "Next job selected:T" << rq[0].id << "(" << timer << "-" << timer + diff << ")" << endl;
				timer = timer + diff;
			}
		}
		else if (!rq.empty() && rq[0].arr_time <= timer && (count[cnt]!=(floor(timer/j[cnt].period)+1)) ){
			int k= searchIDJob(j, rq[0]);
			if (rq[0].rem_ET < j[k].wcet[0]) {
				temp = rq[0];
				extractMin(rq);
				cout << "Next job selected: T" << temp.id << "(" << timer << "-" << timer + temp.rem_ET << ")" << endl;
				timer += temp.rem_ET;
				count[cnt]++;
			}
			else {
				//cout << "\nET=" << rq[0].rem_ET << endl;
				scheduleVD_high(j,rq,timer,hyperPeriod,cri);
				break;
			}
		}
		else {
			timer += .01;
			timer = (ceilf(timer * 100) / 100);
		}				
		addJobRQVD(j, rq, timer, temp,cri);
		//cout << "\ntimer=" << timer << "\n\n";
	}
}

jobs searchWQJobVD_high(jobs tar, vector<tasks> j, float timer, vector<jobs> rq,int cri) {
	int cnt, arr_time;
	float deadline, temp = INT_MAX;
	jobs wq;
	wq.arr_time = -1;
	for (int i = 0; i < j.size(); i++) {
		if (cri<j[i].criticality ) {
			cnt = ceil(timer / j[i].period);
			arr_time = j[i].arr_time + cnt * j[i].period;
			deadline = j[i].deadline + arr_time;
			if (tar.id != j[i].id && timer < arr_time && deadline < temp && deadline < tar.abs_deadline && arr_time < tar.rem_ET + timer && (jobExistsinRQ(rq, j[i].id) == -1)) {
				temp = deadline;
				wq.abs_deadline = deadline;
				wq.arr_time = arr_time;
				wq.id = j[i].id;
				wq.rem_ET = j[i].wcet[1];
			}
		}
	}
	return wq;
}

void addJobRQVD_high(vector<tasks> j, vector<jobs>& rq, float timer, jobs tar,int cri) {
	int cnt, arr_time, k;
	float deadline, temp = INT_MAX, wcet, rand_no;
	for (int i = 0; i < j.size(); i++) {
		if(cri<j[i].criticality){
			cnt = (timer / j[i].period);
			arr_time = j[i].arr_time + cnt * j[i].period;
			rand_no = randNo(0.1,1.0);
			deadline = arr_time + j[i].deadline;
			wcet = j[i].wcet[1] * rand_no;
			if (arr_time <= timer && searchIDTask(rq, j[i]) == -1 && ((tar.arr_time < arr_time && deadline < tar.abs_deadline) || tar.arr_time < arr_time)) {
				rq.push_back({ j[i].id,arr_time,deadline,wcet });
				addJob(rq, rq.size() - 1);
			}
		}
	}
}

void scheduleVD_high(vector<tasks> j, vector<jobs>& rq, float timer,int hyperPeriod,int cri) {
	jobs wq,temp;
	vector<int> count(j.size(), 0);
	int diff,cnt=0;
	rq.clear();
	createHighRQ(j, rq, timer);
	wq.arr_time = -1, temp.arr_time = -1;
	cout << "\nMODE SWITCHED FROM LOW TO HIGH\n";
	while (timer < hyperPeriod)
	{
		//wq.arr_time = -1, temp.arr_time = -1;
		/*cout << "\n waiting queue:\n";
		for (int i = 0; i < wq.size(); i++)
			cout << "arr=" << wq[i].arr_time << " exe=" << wq[i].rem_ET << " id= " << wq[i].id << " deadline=" << wq[i].abs_deadline << endl;
		cout << "ready queue:\n";
		for (int i = 0; i < rq.size(); i++)
			cout << "arr=" << rq[i].arr_time << " exe=" << rq[i].rem_ET << " id= " << rq[i].id << " deadline=" << rq[i].abs_deadline << endl;
		*/
		if (!rq.empty()) {
			cnt = rq[0].id;
			wq = searchWQJobVD_high(rq[0], j, timer, rq, cri);
		}
		if (wq.arr_time != -1 && !rq.empty()) {
			temp = rq[0];
			diff = wq.arr_time - rq[0].arr_time;
			rq[0].rem_ET -= diff;
			if (timer + diff < hyperPeriod) {
				cout << "Next job selected:T" << rq[0].id << "(" << timer << "-" << timer + diff << ")" << endl;
				timer = timer + diff;
			}
		}
		else if (!rq.empty() && rq[0].arr_time <= timer && count[cnt]!=(floor(timer/j[cnt].period)+1)) {
				temp = rq[0];
				extractMin(rq);
				cout << "Next job selected: T" << temp.id << "(" << timer << "-" << timer + temp.rem_ET << ")" << endl;
				timer += temp.rem_ET;
				count[cnt]++;
		}
		else {
			timer += .01;
			timer = (ceilf(timer * 100) / 100);
		}
			addJobRQVD_high(j, rq, timer, temp,cri);
		//cout << "\ntimer=" << timer << "\n\n";
	}
}

void runningPhaseVD(int ntasks, vector<tasks> j) {
	vector<jobs> ready_queue;
	int temp,cri=1;
	float wcet, deadline, rand_no = 1, timer = j[0].arr_time;
	vector<tasks>  highCriticalityTasks;
	for (int i = 0; i < ntasks; i++) {
		if (j[i].arr_time <= timer) {
			rand_no = randNo(0.7, 1.0);
			if (j[i].criticality == cri) {
				deadline = j[i].arr_time + j[i].deadline;
				wcet = j[i].wcet[0] * rand_no;
			}
			else {
				deadline = j[i].arr_time + j[i].vir_deadline;
				wcet = j[i].wcet[1] * rand_no;
			}
			ready_queue.push_back({ j[i].id, j[i].arr_time,deadline,wcet });
		}

	}
	buildMinHeap(ready_queue);
	scheduleVD_low(j, ready_queue, timer,cri);
}
