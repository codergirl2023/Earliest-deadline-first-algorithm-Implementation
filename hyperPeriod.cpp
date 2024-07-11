#include"Header.h"

int gcd(int a, int b) {
	if (a == b)     return a;
	else if (a > b) return gcd(a - b, b);
	else 	        return gcd(a, b - a);
}

int calcHyperPeriod(vector<tasks> j) {
	int hcf, lcm, a, b;
	lcm = j[0].period;
	for (int i = 1; i < j.size(); i++) {
		a = lcm;
		b = j[i].period;
		hcf = gcd(a, b);
		lcm = (a * b) / hcf;
	}
	printf("\nHyperperiod=%d\n", lcm);
	return lcm;
}