#include"Header.h"

void preProcePhase(float x, int ntasks, vector<tasks> j) {
	for (int i = 0; i < ntasks; i++) {
		if (j[i].criticality == 2)
			j[i].vir_deadline /= x;
	}
}