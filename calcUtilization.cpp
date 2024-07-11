#include"Header.h"

float calc_util(vector<float>& vec, int ntasks, vector<tasks> j) {
	int i;
	float x;
	vec.assign(3 * sizeof(int), 0);
	for (i = 0; i < ntasks; i++) {
		if (j[i].criticality == 1)
			vec[0] += j[i].wcet[0] / j[i].period;
		if (j[i].criticality == 2) {
			vec[1] += j[i].wcet[1] / j[i].period;
			vec[2] += j[i].wcet[0] / j[i].period;
		}	}
	x = vec[2] / (1 - vec[0]);
	//x = .5;
	//check two other paramerters for schedulability test
	if ((x * vec[0] + vec[1] > 1) || vec[0] > 1 || vec[1] > 1) {
		printf("\nUnfortunately...Task set is un-schedulable\n");
		exit(0);
	}
	else
		printf("\nCongratulations!!! Task set is schedulable\n");
	cout << "\nx=" << x << endl;
	return x;
}