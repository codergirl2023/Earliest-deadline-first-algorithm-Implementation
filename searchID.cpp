#include"Header.h"


int searchIDTask(vector<jobs> t, tasks tar) {
	int i;
	for (i = 0; i < t.size(); i++)
		if (t[i].id == tar.id)
			return i;
	return -1;
}

int searchIDJob(vector<tasks> t, jobs tar) {
	int i;
	for (i = 0; i < t.size(); i++)
		if (t[i].id == tar.id)
			return i;
	return -1;
}

int jobExistsinRQ(vector<jobs> rq, int id) {
	for (int i = 0; i < rq.size(); i++) {
		if (rq[i].id == id)
			return 1;
	}
	return -1;
}