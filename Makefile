# this target will compile all files
all:
	g++ main.cpp  calcUtilization.cpp createHighRQ.cpp edf.cpp edf-vd.cpp heap.cpp hyperPeriod.cpp preProcessPhase.cpp randNo.cpp readFile.cpp searchID.cpp -lm -o a

clean:
	rm -rf *o a
