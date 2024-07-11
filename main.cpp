#include"Header.h"
using namespace std;
int main() {
	srand(time(0));
	vector<float> util(3, 0);
	vector<tasks> jobs;
	float x = 0;
	int ntasks;
	jobs = read_file();					//reading input
	ntasks = jobs.size();
	x = calc_util(util, ntasks, jobs);	//checking if task set is schedulable or not
	preProcePhase(x, ntasks, jobs);		//modifying high critical tasks' virtual deadline
	runningPhase(ntasks, jobs);			//creating schedule
	runningPhaseVD(ntasks, jobs);
	return 0;
}
