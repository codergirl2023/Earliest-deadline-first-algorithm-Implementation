#include"Header.h"

void createHighRQ(vector<tasks> j,vector<jobs>& rq,int timer) {
	int cnt, arr_time;
	float rand_no, deadline, wcet;
	for (int i = 0; i < j.size(); i++) {
		if (j[i].criticality == 2) {
			cnt = timer / j[i].period;
			arr_time = j[i].arr_time + cnt * j[i].period;
			if (arr_time <= timer) {
				rand_no = randNo(0.7, 1.0);
				deadline = j[i].arr_time + j[i].deadline;
				wcet = j[i].wcet[1] * rand_no;
				rq.push_back({ j[i].id, j[i].arr_time,deadline,wcet });
			}
		}
	}
}