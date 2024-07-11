#include"Header.h"


void buildMinHeap(vector<jobs>& rq) {
	int n = rq.size(), heap_size;
	heap_size = n - 1;
	for (int i = n / 2; i >= 0; i--) {
		minHeapify(rq, i, heap_size);
	}
}

void minHeapify(vector<jobs>& rq, int i, int heap_size) {
	
	int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
	jobs temp;
	//cout << "l=" << l << "r=" << r<<"hs="<<heap_size<<endl;
	if ((l <= heap_size) && ((rq[l].arr_time < rq[i].arr_time) || (rq[l].arr_time == rq[i].arr_time && rq[l].abs_deadline < rq[i].abs_deadline)))
		smallest = l;
	if ((r <= heap_size) && ((rq[r].arr_time < rq[smallest].arr_time) || (rq[r].arr_time == rq[smallest].arr_time && rq[r].abs_deadline < rq[smallest].abs_deadline)))
		smallest = r;

	if (smallest != i) {
		temp = rq[i];
		rq[i] = rq[smallest];
		rq[smallest] = temp;
		minHeapify(rq, smallest, heap_size);
	}
}

void extractMin(vector<jobs>& rq) {
	int heap_size = rq.size() - 1;
	if(heap_size>0)
	rq[0] = rq[heap_size];
	auto it = rq.end();
	rq.erase(it - 1);
	heap_size--;
	//cout << "\nheapsize=" << heap_size << endl;
	minHeapify(rq, 0, heap_size);
}

void addJob(vector<jobs>& t, int i) {
	jobs temp;
	while (i > 0 && (t[i].abs_deadline < t[i / 2].abs_deadline)) {
		temp = t[i];
		t[i] = t[i / 2];
		t[i / 2] = temp;
		i = i / 2;
	}
}