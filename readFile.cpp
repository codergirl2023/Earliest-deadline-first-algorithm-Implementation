#include"Header.h"

vector<tasks> read_file() {
	int i;
	char ch;
	int ntsks = 0;
	char file_name[80];
	FILE* f;
	cout << "Enter file name: ";
	cin >> file_name;
	f = fopen(file_name, "r");

	if (f == NULL) {
		printf("Error opening file\n");
		exit(0);
	}
	ch = fgetc(f);
	/*while ((ch = fgetc(f)) != '\n'){                    //if no of tasks are more than or equal to 10	
		cout<<"ch="<<(int)(ch-48)<<"n="<<ntsks<<endl;		
		ntsks = ntsks * 10 + (int)(ch-48);
	}*/
	ntsks = ntsks * 10 + (int)(ch-48);
	//cout<<"n="<<ntsks<<endl;
	cout << "+++++++++++++++++++++++++++++BELOW IS THE TASK SET++++++++++++++++++++++++++++++++" << endl;
	cout << "ID  A.T  T.P.    Critical\tWCETLOW\t\tWCETHI\tDeadline " << endl;
	vector<tasks> j(ntsks);
	for (i = 0; i < ntsks; i++) 
	{
		j[i].id = i;
		int k=fscanf(f, "%d %d %d %f %f %f", &j[i].arr_time, &j[i].criticality, &j[i].period, &j[i].wcet[0], &j[i].wcet[1], &j[i].deadline);
		if (k != 6)
			cout << "\nError\n";
		cout << j[i].id << "   " << j[i].arr_time << "    " << j[i].period << "\t\t" << j[i].criticality << "\t" << j[i].wcet[0] << " \t\t" << j[i].wcet[1] <<"\t"<<j[i].deadline<< endl;
		j[i].vir_deadline = j[i].deadline;
	}
	fclose(f);
	return j;
}
