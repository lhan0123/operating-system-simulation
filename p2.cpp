include <iostream>
include <string>
include <vector>
include <fstream> 
include <algorithm>

using namespace std;



struct PROCESS {
	int id = 0 ;
	int cpuBrust = 0;
	int tmpCpuBrust = 0;
	int arrivalTime = 0 ;
	int priority = 0;
	int executionTime = 0;  
};

struct RESULT {
	int processID = 0;
	int turnaroundTime = 0;
	int waitingTime = 0;
};

vector<PROCESS> inputProcessList;
int MAX_TIME_SLICE;


void ReadFile(int& caseNum, int& timeSlice) {
	ifstream inFile;
	string fileName;
	string str;
	PROCESS p;

	
	do {
		cout << "> Input File Name: ";
		cin >> fileName;

		inFile.open(fileName.c_str(), ifstream::in);

		if (inFile.fail()) {
			cout << "�䤣����ɮסA�Э��s";
		} 

	} while (inFile.fail());

	
	cout << "Read caseNum..." << endl;
	inFile >> caseNum;
	

	
	cout << "Read time slice..." << endl;
	inFile >> timeSlice;
	

	
	
	for (int i = 0; i < 6; i++) {
		inFile >> str;
	} 

	
	while (!inFile.eof()) {
		inFile >> p.id;

		if (inFile.eof()) break;

		inFile >> p.cpuBrust;
		p.tmpCpuBrust = p.cpuBrust;
		inFile >> p.arrivalTime;
		inFile >> p.priority;

		inputProcessList.push_back(p);
	} 

	
	/*
	for (int i = 0; i < inputProcessList.size() ; i++) {
		cout << inputProcessList[i].id << "\t" << inputProcessList[i].cpuBrust << "\t";
		cout << inputProcessList[i].arrivalTime << "\t" << inputProcessList[i].priority << endl;
	} 
	*/

	
	inFile.close();

} 

char ChangeIntToChar(int num) {
	if (num == 0) return '0';
	else if (num == 1) return '1';
	else if (num == 2) return '2';
	else if (num == 3) return '3';
	else if (num == 4) return '4';
	else if (num == 5) return '5';
	else if (num == 6) return '6';
	else if (num == 7) return '7';
	else if (num == 8) return '8';
	else if (num == 9) return '9';
	else if (num == 10) return 'A';
	else if (num == 11) return 'B';
	else if (num == 12) return 'C';
	else if (num == 13) return 'D';
	else if (num == 14) return 'E';
	else if (num == 15) return 'F';
	else if (num == 16) return 'G';
	else if (num == 17) return 'H';
	else if (num == 18) return 'I';
	else if (num == 19) return 'J';
	else if (num == 20) return 'K';
	else if (num == 21) return 'L';
	else if (num == 22) return 'M';
	else if (num == 23) return 'N';
	else if (num == 24) return 'O';
	else if (num == 25) return 'P';
	else if (num == 26) return 'Q';
	else if (num == 27) return 'R';
	else if (num == 28) return 'S';
	else if (num == 29) return 'T';
	else if (num == 30) return 'U';
	else if (num == 31) return 'V';
	else if (num == 32) return 'W';
	else if (num == 33) return 'X';
	else if (num == 34) return 'Y';
	else  return 'Z';
} 


void SortProcessID (vector<RESULT> & resultList) {
	int minID_index = -1;

	for (int i = 0; i < resultList.size()-1; i++) {

		for (int j = 0; j < resultList.size() - i - 1; j++) {
			if (resultList[j].processID > resultList[j+1].processID) {
				swap(resultList[j], resultList[j+1]);
			} 
		} 

	} 
} 


class FCFS
{
public:

	vector<PROCESS> preProcessList;  
	vector<RESULT> resultList; 
	vector<char> ganttChart;      

	
	
	int FindNewProcess(int curTime, vector<PROCESS> processList) {
		int minProcessIndex = -1;

		if (processList.empty()) return -1;

		
		for (int i = 0; i < processList.size(); i++) {
			
			if (processList[i].arrivalTime == curTime) {
				
				if (minProcessIndex == -1) {
					minProcessIndex = i; 
				} 

				
				else {
					
					
					if (processList[minProcessIndex].id > processList[i].id) {
						minProcessIndex = i; 
					} 
				} 
			} 
		} 

		
		
		return minProcessIndex;
	} 

	void ExecuteFCFS() {
		bool isDone = false; 
		bool nowCpuHasExecuteProcess = false; 
		int newProcessIndex = -1; 
		int currentTime = 0;              
		PROCESS nowCpuExecuteProcess;    
		RESULT r;                       
		vector<PROCESS> queue;        

		
		preProcessList = inputProcessList;

		cout << "FCFS Start..." << endl;

		

		while (!isDone) {
			
			if (!preProcessList.empty()) {
				
				newProcessIndex = FindNewProcess(currentTime, preProcessList);

				
				while (newProcessIndex != -1) {

					
					if (nowCpuHasExecuteProcess) {
						
						queue.push_back(preProcessList[newProcessIndex]);

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					else {
						nowCpuHasExecuteProcess = true; 

						
						
						nowCpuExecuteProcess = preProcessList[newProcessIndex];

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					newProcessIndex = FindNewProcess(currentTime, preProcessList);
				} 
			} 

			

			
			if (nowCpuHasExecuteProcess) {
				
				if (nowCpuExecuteProcess.cpuBrust == 0) {
					
					nowCpuExecuteProcess.executionTime = 0;

					
					r.processID = nowCpuExecuteProcess.id;
					r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
					r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
					resultList.push_back(r);

					
					if (!queue.empty()) {
						
						nowCpuExecuteProcess = queue[0];

						
						queue.erase(queue.begin());
					} 

					
					else {
						
						if (!preProcessList.empty()) {
							
							nowCpuHasExecuteProcess = false;
						} 

						
						else {
							
							isDone = true;
						} 
					} 
				} 

				
				else {
					
					
					if (nowCpuExecuteProcess.executionTime == MAX_TIME_SLICE) {
						
						nowCpuExecuteProcess.executionTime = 0;
					} 
				} 
			} 

			
			
			else {
				
				if (preProcessList.empty()) {
					
					isDone = true;
				} 
			} 

			
			if (!isDone) {

				
				if (nowCpuHasExecuteProcess) {
					ganttChart.push_back(ChangeIntToChar(nowCpuExecuteProcess.id)); 
					nowCpuExecuteProcess.cpuBrust = nowCpuExecuteProcess.cpuBrust - 1; 
					nowCpuExecuteProcess.executionTime = nowCpuExecuteProcess.executionTime + 1; 
				} 

				
				else {
					ganttChart.push_back('-'); 
				} 

				currentTime = currentTime + 1; 
			} 
		} 

		cout << "FCFS Finish..." << endl;
	} 

	void OutputFCFS() {
		ofstream outFile;
		string outputFileName = "Output_FCFS.txt";

		SortProcessID(resultList); 

		outFile.open(outputFileName.c_str(), ios::trunc); 

		outFile << "== FCFS == " << endl;  

		
		for (int i = 0; i < ganttChart.size(); i++)
			outFile << ganttChart[i];
		outFile << endl;

		outFile << "============================================" << endl << endl;

		
		outFile << "Waiting Time: " << endl;
		outFile << "ID\tFCFS" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].waitingTime << endl;
		} 

		outFile << "============================================" << endl;
		outFile << endl;

		
		outFile << "Turnaround Time: " << endl;
		outFile << "ID\tFCFS" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].turnaroundTime << endl;
		} 

		outFile << "============================================" << endl;

		outFile.close();

	} 
};

class NSJF
{
public:
	vector<PROCESS> preProcessList;  
	vector<RESULT> resultList; 
	vector<char> ganttChart;      

	
	
	
	int FindNewProcesse(int curTime, vector<PROCESS> processList) {

		int minProcessIndex = -1;

		if (processList.empty()) return -1;

		
		for (int i = 0; i < processList.size(); i++) {

			
			if (processList[i].arrivalTime == curTime) {
				
				if (minProcessIndex == -1) {
					minProcessIndex = i; 
				} 

				
				else {
					
					
					if (processList[minProcessIndex].cpuBrust > processList[i].cpuBrust) {
						minProcessIndex = i; 
					} 

					
					else {
						
						
						if (processList[minProcessIndex].cpuBrust == processList[i].cpuBrust) {

							
							if (processList[minProcessIndex].id > processList[i].id) {
								minProcessIndex = i; 
							} 
						} 
					} 
				} 
			} 
		} 

		
		
		return minProcessIndex;
	} 

	
	
	int FindNewProcessInQueue( vector<PROCESS> queue ) {
		int minCpuBrustTimeProcess = 0;

		for (int i = 0; i < queue.size(); i++) {

			
			if (queue[i].cpuBrust < queue[minCpuBrustTimeProcess].cpuBrust) {
				minCpuBrustTimeProcess = i; 
			} 

			
			else {
				
				if (queue[i].cpuBrust == queue[minCpuBrustTimeProcess].cpuBrust) {

					

					if (queue[i].arrivalTime < queue[minCpuBrustTimeProcess].arrivalTime) {
						minCpuBrustTimeProcess = i; 
					} 

					else {
						if (queue[i].arrivalTime == queue[minCpuBrustTimeProcess].arrivalTime) {
							
							if (queue[minCpuBrustTimeProcess].id > queue[i].id) {
								minCpuBrustTimeProcess = i; 
							}  
						} 
					} 
				} 
			} 
		} 

		return minCpuBrustTimeProcess;

	} 

	void ExecuteNSJF() {
		bool isDone = false; 
		bool nowCpuHasExecuteProcess = false; 
		int newProcessIndex = -1; 
		int nextProcessIndesInQueue = -1; 
		int currentTime = 0;              
		PROCESS nowCpuExecuteProcess;    
		RESULT r;                       
		vector<PROCESS> queue;        

		
		preProcessList = inputProcessList;

		cout << "NSJF Start..." << endl;

		

		while (!isDone) {

			
			if (!preProcessList.empty()) {
				
				newProcessIndex = FindNewProcesse(currentTime, preProcessList);

				
				while (newProcessIndex != -1) {

					
					if (nowCpuHasExecuteProcess) {
						
						queue.push_back(preProcessList[newProcessIndex]);

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					else {
						nowCpuHasExecuteProcess = true; 

						
						
						nowCpuExecuteProcess = preProcessList[newProcessIndex];

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					newProcessIndex = FindNewProcesse(currentTime, preProcessList);
				} 
			} 

			

			
			if (nowCpuHasExecuteProcess) {

				
				if (nowCpuExecuteProcess.cpuBrust == 0) {

					
					nowCpuExecuteProcess.executionTime = 0;

					
					r.processID = nowCpuExecuteProcess.id;
					r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
					r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
					resultList.push_back(r);

					
					if (!queue.empty()) {
						
						nextProcessIndesInQueue = FindNewProcessInQueue(queue);

						
						nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

						
						queue.erase(queue.begin()+ nextProcessIndesInQueue);
					} 

					
					else {
						
						if (!preProcessList.empty()) {
							
							nowCpuHasExecuteProcess = false;
						} 

						
						else {
							
							isDone = true;
						} 
					} 
				} 

				
				else {
					
					
					if (nowCpuExecuteProcess.executionTime == MAX_TIME_SLICE) {
						
						nowCpuExecuteProcess.executionTime = 0;
					} 
				} 
			} 

			
			
			else {
				
				if (preProcessList.empty()) {
					
					isDone = true;
				} 
			} 

			
			if (!isDone) {

				
				if (nowCpuHasExecuteProcess) {
					
					ganttChart.push_back(ChangeIntToChar(nowCpuExecuteProcess.id)); 
					nowCpuExecuteProcess.cpuBrust = nowCpuExecuteProcess.cpuBrust - 1; 
					nowCpuExecuteProcess.executionTime = nowCpuExecuteProcess.executionTime + 1; 
				} 

				
				else {
					
					ganttChart.push_back('-'); 
				} 

				currentTime = currentTime + 1; 
			} 
		} 

		cout << "NSJF Finish..." << endl;
	} 

	void OutputNSJF() {
		ofstream outFile;
		string outputFileName = "Output_NPSJF.txt";

		SortProcessID(resultList); 

		outFile.open(outputFileName.c_str(), ios::trunc); 

		outFile << "== NON-PSJF == " << endl;  

		
		for (int i = 0; i < ganttChart.size(); i++)
			outFile << ganttChart[i];
		outFile << endl;

		outFile << "============================================" << endl << endl;

		
		outFile << "Waiting Time: " << endl;
		outFile << "ID\tNPSJF" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].waitingTime << endl;
		} 

		outFile << "============================================" << endl;
		outFile << endl;

		
		outFile << "Turnaround Time: " << endl;
		outFile << "ID\tNPSJF" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].turnaroundTime << endl;
		} 

		outFile.close();

	} 
};

class PSJF
{
public:
	vector<PROCESS> preProcessList;  
	vector<RESULT> resultList; 
	vector<char> ganttChart;      

	
	
	
	int FindNewProcesse(int curTime, vector<PROCESS> processList) {

		int minProcessIndex = -1;

		if (processList.empty()) return -1;

		
		for (int i = 0; i < processList.size(); i++) {

			
			if (processList[i].arrivalTime == curTime) {
				
				if (minProcessIndex == -1) {
					minProcessIndex = i; 
				} 

				
				else {
					
					
					if (processList[minProcessIndex].cpuBrust > processList[i].cpuBrust) {
						minProcessIndex = i; 
					} 

					
					else {
						
						
						if (processList[minProcessIndex].cpuBrust == processList[i].cpuBrust) {
							if (processList[minProcessIndex].arrivalTime > processList[i].arrivalTime) {
								minProcessIndex = i; 
							} 

							else {
								if (processList[minProcessIndex].arrivalTime == processList[i].arrivalTime) {
									
									if (processList[minProcessIndex].id > processList[i].id) {
										minProcessIndex = i; 
									} 
								} 
							} 
						} 
					} 
				} 
			} 
		} 

		
		

		
		
		return minProcessIndex;
	} 

	
	
	int FindNewProcessInQueue(vector<PROCESS> queue) {
		int minCpuBrustTimeProcess = 0;

		for (int i = 0; i < queue.size(); i++) {

			
			if (queue[i].cpuBrust < queue[minCpuBrustTimeProcess].cpuBrust) {
				minCpuBrustTimeProcess = i;
			} 

			
			else {
				if (queue[i].cpuBrust == queue[minCpuBrustTimeProcess].cpuBrust) {


					
					
					
					
					
					

					
					
					if ((queue[minCpuBrustTimeProcess].cpuBrust == queue[minCpuBrustTimeProcess].tmpCpuBrust) && (queue[i].cpuBrust != queue[i].tmpCpuBrust)) {
						; 
					} 

					
					
					else if ((queue[minCpuBrustTimeProcess].cpuBrust != queue[minCpuBrustTimeProcess].tmpCpuBrust) && (queue[i].cpuBrust == queue[i].tmpCpuBrust)) {
						minCpuBrustTimeProcess = i; 
					} 

					
					
					else {
						

						
						if (queue[minCpuBrustTimeProcess].arrivalTime > queue[i].arrivalTime) {
							minCpuBrustTimeProcess = i; 
						} 

						
						else {
							
							if (queue[minCpuBrustTimeProcess].arrivalTime == queue[i].arrivalTime) {
								
								
								if (queue[minCpuBrustTimeProcess].id > queue[i].id) {
									minCpuBrustTimeProcess = i; 
								} 
							} 
						} 
					} 
				} 
			} 
		} 

		return minCpuBrustTimeProcess;

	} 

	void ExecutePSJF() {
		bool isDone = false; 
		bool nowCpuHasExecuteProcess = false; 
		int newProcessIndex = -1; 
		int nextProcessIndesInQueue = -1; 
		int currentTime = 0;              
		PROCESS nowCpuExecuteProcess;    
		RESULT r;                       
		vector<PROCESS> queue;        

		
		preProcessList = inputProcessList;

		cout << "PSJF Start..." << endl;

		

		while (!isDone) {

			
			if (!preProcessList.empty()) {
				
				newProcessIndex = FindNewProcesse(currentTime, preProcessList);

				
				while (newProcessIndex != -1) {

					

					
					if (nowCpuHasExecuteProcess) {

						
						if (nowCpuExecuteProcess.cpuBrust == 0) {
							
							nowCpuExecuteProcess.executionTime = 0;

							
							r.processID = nowCpuExecuteProcess.id;
							r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
							r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
							resultList.push_back(r);

							
							queue.push_back(preProcessList[newProcessIndex]);

							
							preProcessList.erase(preProcessList.begin() + newProcessIndex);

							
							nextProcessIndesInQueue = FindNewProcessInQueue(queue);

							
							nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

							
							queue.erase(queue.begin() + nextProcessIndesInQueue);
						} 

						
						else {

							
							
							if (nowCpuExecuteProcess.cpuBrust > preProcessList[newProcessIndex].cpuBrust) {
								
								nowCpuExecuteProcess.executionTime = 0;

								
								queue.push_back(nowCpuExecuteProcess);

								
								nowCpuExecuteProcess = preProcessList[newProcessIndex];

								
								preProcessList.erase(preProcessList.begin() + newProcessIndex);
							} 


							
							else {
								queue.push_back(preProcessList[newProcessIndex]);

								
								preProcessList.erase(preProcessList.begin() + newProcessIndex);
							} 
						} 
					} 

					
					else {
						nowCpuHasExecuteProcess = true; 

						
						
						nowCpuExecuteProcess = preProcessList[newProcessIndex];

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					newProcessIndex = FindNewProcesse(currentTime, preProcessList);
				} 
			} 

			

			
			if (nowCpuHasExecuteProcess) {

				
				if (nowCpuExecuteProcess.cpuBrust == 0) {

					
					nowCpuExecuteProcess.executionTime = 0;

					
					r.processID = nowCpuExecuteProcess.id;
					r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
					r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
					resultList.push_back(r);

					
					if (!queue.empty()) {
						
						nextProcessIndesInQueue = FindNewProcessInQueue(queue);

						
						nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

						
						queue.erase(queue.begin() + nextProcessIndesInQueue);
					} 

					
					else {
						
						if (!preProcessList.empty()) {
							
							nowCpuHasExecuteProcess = false;
						} 

						
						else {
							
							isDone = true;
						} 
					} 
				} 

				
				else {
					
					
					if (nowCpuExecuteProcess.executionTime == MAX_TIME_SLICE) {
						
						nowCpuExecuteProcess.executionTime = 0;
					} 

				} 
			} 

			
			
			else {
				
				if (preProcessList.empty()) {
					
					isDone = true;
				} 
			} 

			
			if (!isDone) {

				
				if (nowCpuHasExecuteProcess) {
					
					ganttChart.push_back(ChangeIntToChar(nowCpuExecuteProcess.id)); 
					nowCpuExecuteProcess.cpuBrust = nowCpuExecuteProcess.cpuBrust - 1; 
					nowCpuExecuteProcess.executionTime = nowCpuExecuteProcess.executionTime + 1; 
				} 

				
				else {
					
					ganttChart.push_back('-'); 
				} 

				currentTime = currentTime + 1; 
			} 
		} 

		cout << "PSJF Finish..." << endl;
	} 

	void OutputPSJF() {
		ofstream outFile;
		string outputFileName = "Output_PSJF.txt";

		SortProcessID(resultList); 

		outFile.open(outputFileName.c_str(), ios::trunc); 

		outFile << "== PSJF == " << endl;  

		
		for (int i = 0; i < ganttChart.size(); i++)
			outFile << ganttChart[i];
		outFile << endl;

		outFile << "============================================" << endl << endl;

		
		outFile << "Waiting Time: " << endl;
		outFile << "ID\tPSJF" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].waitingTime << endl;
		} 

		outFile << "============================================" << endl;
		outFile << endl;

		
		outFile << "Turnaround Time: " << endl;
		outFile << "ID\tPSJF" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].turnaroundTime << endl;
		} 

		outFile.close();

	} 
};

class RR
{
public:
	vector<PROCESS> preProcessList;  
	vector<RESULT> resultList; 
	vector<char> ganttChart;      

	
	
	int FindNewProcess(int curTime, vector<PROCESS> processList) {
		int minProcessIndex = -1;

		if (processList.empty()) return -1;

		
		for (int i = 0; i < processList.size(); i++) {
			
			if (processList[i].arrivalTime == curTime) {
				
				if (minProcessIndex == -1) {
					minProcessIndex = i; 
				} 

				
				else {
					
					
					if (processList[minProcessIndex].id > processList[i].id) {
						minProcessIndex = i; 
					} 
				} 
			} 
		} 

		
		
		return minProcessIndex;
	} 

	void ExecuteRR() {
		bool isDone = false; 
		bool nowCpuHasExecuteProcess = false; 
		int newProcessIndex = -1; 
		int currentTime = 0;              
		PROCESS nowCpuExecuteProcess;    
		RESULT r;                       
		vector<PROCESS> queue;        

		
		preProcessList = inputProcessList;

		cout << "RR Start..." << endl;

		

		while (!isDone) {

			
			if (!preProcessList.empty()) {
				
				newProcessIndex = FindNewProcess(currentTime, preProcessList);

				
				while (newProcessIndex != -1) {

					
					
					if (nowCpuHasExecuteProcess) {
						
						queue.push_back(preProcessList[newProcessIndex]);

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					else {
						nowCpuHasExecuteProcess = true; 

						
						
						nowCpuExecuteProcess = preProcessList[newProcessIndex];

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					newProcessIndex = FindNewProcess(currentTime, preProcessList);
				} 
			} 

			

			
			if (nowCpuHasExecuteProcess) {

				
				if (nowCpuExecuteProcess.cpuBrust == 0) {

					
					nowCpuExecuteProcess.executionTime = 0;

					
					r.processID = nowCpuExecuteProcess.id;
					r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
					r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
					resultList.push_back(r);

					
					if (!queue.empty()) {
						
						nowCpuExecuteProcess = queue[0];

						
						queue.erase(queue.begin());
					} 

					
					else {
						
						if (!preProcessList.empty()) {
							
							nowCpuHasExecuteProcess = false;
						} 

						
						else {
							
							isDone = true;
						} 
					} 
				} 

				
				else {
					

					
					
					if (nowCpuExecuteProcess.executionTime == MAX_TIME_SLICE) {

						
						if (!queue.empty()) {
							
							nowCpuExecuteProcess.executionTime = 0;

							
							queue.push_back(nowCpuExecuteProcess);

							
							nowCpuExecuteProcess = queue[0];

							
							queue.erase(queue.begin());

						} 

						
						else {
							
							
							nowCpuExecuteProcess.executionTime = 0;
						} 
					} 
				} 
			} 

			
			
			else {
				
				if (preProcessList.empty()) {
					
					isDone = true;
				} 
			} 

			
			if (!isDone) {

				
				if (nowCpuHasExecuteProcess) {
					ganttChart.push_back(ChangeIntToChar(nowCpuExecuteProcess.id)); 
					nowCpuExecuteProcess.cpuBrust = nowCpuExecuteProcess.cpuBrust - 1; 
					nowCpuExecuteProcess.executionTime = nowCpuExecuteProcess.executionTime + 1; 
				} 

				
				else {
					ganttChart.push_back('-'); 
				} 

				currentTime = currentTime + 1; 
			} 
		} 

		cout << "RR Finish..." << endl;
	} 

	void OutputRR() {
		ofstream outFile;
		string outputFileName = "Output_RR.txt";

		SortProcessID(resultList); 

		outFile.open(outputFileName.c_str(), ios::trunc); 

		outFile << "== RR == " << endl;  

		
		for (int i = 0; i < ganttChart.size(); i++)
			outFile << ganttChart[i];
		outFile << endl;

		outFile << "============================================" << endl << endl;

		
		outFile << "Waiting Time: " << endl;
		outFile << "ID\tRR" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].waitingTime << endl;
		} 

		outFile << "============================================" << endl;
		outFile << endl;

		
		outFile << "Turnaround Time: " << endl;
		outFile << "ID\tRR" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].turnaroundTime << endl;
		} 

		outFile << "============================================" << endl;

		outFile.close();

	} 
};

class PP
{
public:
	vector<PROCESS> preProcessList;  
	vector<RESULT> resultList; 
	vector<char> ganttChart;      

	
	
	
	int FindNewProcesse(int curTime, vector<PROCESS> processList) {

		int minProcessIndex = -1;

		if (processList.empty()) return -1;

		
		for (int i = 0; i < processList.size(); i++) {

			
			if (processList[i].arrivalTime == curTime) {
				
				if (minProcessIndex == -1) {
					minProcessIndex = i; 
				} 

				
				else {
					
					
					if (processList[minProcessIndex].priority > processList[i].priority) {
						minProcessIndex = i; 
					} 

					
					else {
						
						
						if (processList[minProcessIndex].priority == processList[i].priority) {

							
							if (processList[minProcessIndex].id > processList[i].id) {
								minProcessIndex = i; 
							} 
						} 
					} 
				} 
			} 
		} 

		
		
		return minProcessIndex;
	} 

	
	
	
	
	int FindNewProcessInQueue(vector<PROCESS> queue) {
		int minCpuBrustTimeProcess = 0;

		for (int i = 0; i < queue.size(); i++) {
			
			if (queue[i].priority < queue[minCpuBrustTimeProcess].priority) {
				minCpuBrustTimeProcess = i;
			} 

			
			else {
				if (queue[i].priority == queue[minCpuBrustTimeProcess].priority) {

					
					
					
					
					
					
					

					
					
					if ((queue[minCpuBrustTimeProcess].cpuBrust == queue[minCpuBrustTimeProcess].tmpCpuBrust) && (queue[i].cpuBrust != queue[i].tmpCpuBrust)) {
						; 
					} 

					
					
					else if ((queue[minCpuBrustTimeProcess].cpuBrust != queue[minCpuBrustTimeProcess].tmpCpuBrust) && (queue[i].cpuBrust == queue[i].tmpCpuBrust)) {
						minCpuBrustTimeProcess = i; 
					} 

					
					
					else {
						

						
						if (queue[minCpuBrustTimeProcess].arrivalTime > queue[i].arrivalTime) {
							minCpuBrustTimeProcess = i; 
						} 

						
						else {
							
							if (queue[minCpuBrustTimeProcess].arrivalTime == queue[i].arrivalTime) {
								
							    
								if (queue[minCpuBrustTimeProcess].id > queue[i].id) {
									minCpuBrustTimeProcess = i; 
								} 
							} 
						} 
					} 
				} 
			} 
		} 

		return minCpuBrustTimeProcess;

	} 

	void ExecutePP() {
		bool isDone = false; 
		bool nowCpuHasExecuteProcess = false; 
		int newProcessIndex = -1; 
		int nextProcessIndesInQueue = -1; 
		int currentTime = 0;              
		PROCESS nowCpuExecuteProcess;    
		RESULT r;                       
		vector<PROCESS> queue;        

		
		preProcessList = inputProcessList;

		cout << "PP Start..." << endl;

		

		while (!isDone) {

			
			if (!preProcessList.empty()) {
				
				newProcessIndex = FindNewProcesse(currentTime, preProcessList);

				
				while (newProcessIndex != -1) {

					

					
					if (nowCpuHasExecuteProcess) {

						
						if (nowCpuExecuteProcess.cpuBrust == 0) {
							
							nowCpuExecuteProcess.executionTime = 0;

							
							r.processID = nowCpuExecuteProcess.id;
							r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
							r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
							resultList.push_back(r);

							
							queue.push_back(preProcessList[newProcessIndex]);

							
							preProcessList.erase(preProcessList.begin() + newProcessIndex);

							
							nextProcessIndesInQueue = FindNewProcessInQueue(queue);

							
							nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

							
							queue.erase(queue.begin() + nextProcessIndesInQueue);
						} 
						
						
						else {

							
							
							if (nowCpuExecuteProcess.priority > preProcessList[newProcessIndex].priority) {
								
								nowCpuExecuteProcess.executionTime = 0;

								
								queue.push_back(nowCpuExecuteProcess);

								
								nowCpuExecuteProcess = preProcessList[newProcessIndex];

								
								preProcessList.erase(preProcessList.begin() + newProcessIndex);
							} 

							
							else {
								queue.push_back(preProcessList[newProcessIndex]);

								
								preProcessList.erase(preProcessList.begin() + newProcessIndex);
							} 
						} 
					} 

					
					else {
						nowCpuHasExecuteProcess = true; 

						
						
						nowCpuExecuteProcess = preProcessList[newProcessIndex];

						
						preProcessList.erase(preProcessList.begin() + newProcessIndex);
					} 

					
					newProcessIndex = FindNewProcesse(currentTime, preProcessList);
				} 
			} 

			

			
			if (nowCpuHasExecuteProcess) {

				
				if (nowCpuExecuteProcess.cpuBrust == 0) {

					
					nowCpuExecuteProcess.executionTime = 0;

					
					r.processID = nowCpuExecuteProcess.id;
					r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
					r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
					resultList.push_back(r);

					
					if (!queue.empty()) {
						
						nextProcessIndesInQueue = FindNewProcessInQueue(queue);

						
						nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

						
						queue.erase(queue.begin() + nextProcessIndesInQueue);
					} 

					
					else {
						
						if (!preProcessList.empty()) {
							
							nowCpuHasExecuteProcess = false;
						} 

						
						else {
							
							isDone = true;
						} 
					} 
				} 

				
				else {
					
					
					if (nowCpuExecuteProcess.executionTime == MAX_TIME_SLICE) {
						
						nowCpuExecuteProcess.executionTime = 0;
					} 

				} 
			} 

			
			
			else {
				
				if (preProcessList.empty()) {
					
					isDone = true;
				} 
			} 

			
			if (!isDone) {

				
				if (nowCpuHasExecuteProcess) {
					
					ganttChart.push_back(ChangeIntToChar(nowCpuExecuteProcess.id)); 
					nowCpuExecuteProcess.cpuBrust = nowCpuExecuteProcess.cpuBrust - 1; 
					nowCpuExecuteProcess.executionTime = nowCpuExecuteProcess.executionTime + 1; 
				} 

				
				else {
					
					ganttChart.push_back('-'); 
				} 

				currentTime = currentTime + 1; 
			} 
		} 

		cout << "PP Finish..." << endl;
	} 

	void OutputPP() {
		ofstream outFile;
		string outputFileName = "Output_PP.txt";

		SortProcessID(resultList); 

		outFile.open(outputFileName.c_str(), ios::trunc); 

		outFile << "== PP == " << endl;  

		
		for (int i = 0; i < ganttChart.size(); i++)
			outFile << ganttChart[i];
		outFile << endl;

		outFile << "============================================" << endl << endl;

		
		outFile << "Waiting Time: " << endl;
		outFile << "ID\tPP" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].waitingTime << endl;
		} 

		outFile << "============================================" << endl;
		outFile << endl;

		
		outFile << "Turnaround Time: " << endl;
		outFile << "ID\tPP" << endl;
		outFile << "============================================" << endl;

		for (int i = 0; i < resultList.size(); i++) {
			outFile << resultList[i].processID << "\t" << resultList[i].turnaroundTime << endl;
		} 
		outFile << "============================================" << endl;

		outFile.close();

	} 
	
};


void OutputAll(FCFS fcfs, NSJF nsjf, PSJF psjf, RR rr, PP pp) {
	ofstream outFile;
	string outputFileName = "Output_ALL.txt";

	SortProcessID(fcfs.resultList); 
	SortProcessID(nsjf.resultList); 
	SortProcessID(psjf.resultList); 
	SortProcessID(rr.resultList); 
	SortProcessID(pp.resultList); 

	outFile.open(outputFileName.c_str(), ios::trunc); 

	outFile << "== FCFS == " << endl;  

	
	for (int i = 0; i < fcfs.ganttChart.size(); i++)
		outFile << fcfs.ganttChart[i];
	outFile << endl;

	outFile << "== RR == " << endl;  

	
	for (int i = 0; i < rr.ganttChart.size(); i++)
		outFile << rr.ganttChart[i];
	outFile << endl;

	outFile << "== PSJF == " << endl;  

	
	for (int i = 0; i < psjf.ganttChart.size(); i++)
		outFile << psjf.ganttChart[i];
	outFile << endl;

	outFile << "== NON-PSJF == " << endl;  

	
	for (int i = 0; i <nsjf.ganttChart.size(); i++)
		outFile << nsjf.ganttChart[i];
	outFile << endl;

	outFile << "== PP == " << endl;  

	
	for (int i = 0; i < pp.ganttChart.size(); i++)
		outFile << pp.ganttChart[i];
	outFile << endl;

	outFile << "================================================================" << endl << endl;

	
	outFile << "Waiting Time: " << endl;
	outFile << "ID\tFCFS\tRR\tPSJF\tNPSJF\tPriority" << endl;
	outFile << "================================================================" << endl;

	for (int i = 0; i < fcfs.resultList.size(); i++) {
		outFile << fcfs.resultList[i].processID << "\t" << fcfs.resultList[i].waitingTime << "\t" << rr.resultList[i].waitingTime << "\t" << psjf.resultList[i].waitingTime << "\t" << nsjf.resultList[i].waitingTime << "\t" << pp.resultList[i].waitingTime << endl;
	} 

	outFile << "================================================================" << endl;
	outFile << endl;

	
	outFile << "Turnaround Time: " << endl;
	outFile << "ID\tFCFS\tRR\tPSJF\tNPSJF\tPriority" << endl;
	outFile << "================================================================" << endl;

	for (int i = 0; i < fcfs.resultList.size(); i++) {
		outFile << fcfs.resultList[i].processID << "\t" << fcfs.resultList[i].turnaroundTime << "\t" << rr.resultList[i].turnaroundTime << "\t";
		outFile << psjf.resultList[i].turnaroundTime << "\t" << nsjf.resultList[i].turnaroundTime << "\t" << pp.resultList[i].turnaroundTime << endl;
	} 

	outFile << "================================================================" << endl;

	outFile.close();
} 


int main() {
	int caseNum ;
	
	FCFS fcfs;
	NSJF nsjf;
	PSJF psjf;
	RR rr;
	PP pp;

	cout << "--------------PRJOCET 2 --------------" << endl;
	cout << "1. FCFS (First Come First Serve)" << endl;
	cout << "2. RR (Round Robin)" << endl;
	cout << "3. PSJF (Preemptive Shortest Job First)" << endl;
	cout << "4. NSJF (Non-preemptive Shortest Job First)" << endl;
	cout << "5. PP (Preemptive Priority)" << endl;
	cout << "6. ALL" << endl;
	cout << "-------------------------------------" << endl;

	ReadFile(caseNum, MAX_TIME_SLICE); 

	switch (caseNum) {
		case 0: break;

		case 1: 
			fcfs.ExecuteFCFS();
			fcfs.OutputFCFS();
			break;

		case 2: 
			rr.ExecuteRR();
			rr.OutputRR();
			break;
			
		case 3: 
			psjf.ExecutePSJF();
			psjf.OutputPSJF();
			break;

		case 4: 
			nsjf.ExecuteNSJF();
			nsjf.OutputNSJF();
			break;

		case 5: 
		    pp.ExecutePP();
			pp.OutputPP();
			break;

		case 6: 
			fcfs.ExecuteFCFS();
			rr.ExecuteRR();
			psjf.ExecutePSJF();
			nsjf.ExecuteNSJF();
			pp.ExecutePP();
			OutputAll(fcfs, nsjf, psjf, rr, pp);
			break;

		default:
			cout << "COMMANE DOES NOT EXIST!!" << endl;
	} 


	return 0;
} 




						/*
						
						

						
						
						if (nowCpuExecuteProcess.cpuBrust > preProcessList[newProcessIndex].cpuBrust) {
							
							nowCpuExecuteProcess.executionTime = 0;

							
							if (nowCpuExecuteProcess.cpuBrust != 0) {
								
								queue.push_back(nowCpuExecuteProcess);
							} 

							
							else {
								
								r.processID = nowCpuExecuteProcess.id;
								r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
								r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
								resultList.push_back(r);
							} 

							
							nowCpuExecuteProcess = preProcessList[newProcessIndex];

							
							preProcessList.erase(preProcessList.begin() + newProcessIndex);
						} 

						
						else {
							
							if (nowCpuExecuteProcess.cpuBrust == preProcessList[newProcessIndex].cpuBrust) {


								
								
								if (nowCpuExecuteProcess.arrivalTime > preProcessList[newProcessIndex].arrivalTime) {
									
									nowCpuExecuteProcess.executionTime = 0;

									
									if (nowCpuExecuteProcess.cpuBrust != 0) {
										
										queue.push_back(nowCpuExecuteProcess);
									} 

									
									else {
										
										r.processID = nowCpuExecuteProcess.id;
										r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
										r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
										resultList.push_back(r);
									} 

									
									nowCpuExecuteProcess = preProcessList[newProcessIndex];

									
									preProcessList.erase(preProcessList.begin() + newProcessIndex);
								} 

								
								else if (nowCpuExecuteProcess.arrivalTime == preProcessList[newProcessIndex].arrivalTime) {
									
									
									if (nowCpuExecuteProcess.id > preProcessList[newProcessIndex].id) {
										
										nowCpuExecuteProcess.executionTime = 0;

										
										if (nowCpuExecuteProcess.cpuBrust != 0) {
											
											queue.push_back(nowCpuExecuteProcess);
										} 

										
										else {
											
											r.processID = nowCpuExecuteProcess.id;
											r.turnaroundTime = currentTime - nowCpuExecuteProcess.arrivalTime;
											r.waitingTime = r.turnaroundTime - nowCpuExecuteProcess.tmpCpuBrust;
											resultList.push_back(r);
										} 

										
										nowCpuExecuteProcess = preProcessList[newProcessIndex];

										
										preProcessList.erase(preProcessList.begin() + newProcessIndex);
									} 

									
									
									
									else {
										
										queue.push_back(preProcessList[newProcessIndex]);

										
										preProcessList.erase(preProcessList.begin() + newProcessIndex);
									} 
								} 

								
								else {
									
									queue.push_back(preProcessList[newProcessIndex]);

									
									preProcessList.erase(preProcessList.begin() + newProcessIndex);
								} 



								
								

								
								
								
								if (nowCpuExecuteProcess.cpuBrust != nowCpuExecuteProcess.tmpCpuBrust) {

									
									nowCpuExecuteProcess.executionTime = 0;

									
									queue.push_back(nowCpuExecuteProcess);

									
									nowCpuExecuteProcess = preProcessList[newProcessIndex];

									
									preProcessList.erase(preProcessList.begin() + newProcessIndex);
								} 

								
								else {
									

									
									
									if (nowCpuExecuteProcess.arrivalTime > preProcessList[newProcessIndex].arrivalTime) {
										
										nowCpuExecuteProcess.executionTime = 0;

										
										queue.push_back(nowCpuExecuteProcess);

										
										nowCpuExecuteProcess = preProcessList[newProcessIndex];

										
										preProcessList.erase(preProcessList.begin() + newProcessIndex);
									} 

									
									else {
										
										if (nowCpuExecuteProcess.arrivalTime == preProcessList[newProcessIndex].arrivalTime) {
											
											
											
											if (nowCpuExecuteProcess.id > preProcessList[newProcessIndex].id) {
												
												nowCpuExecuteProcess.executionTime = 0;

												
												queue.push_back(nowCpuExecuteProcess);

												
												nowCpuExecuteProcess = preProcessList[newProcessIndex];

												
												preProcessList.erase(preProcessList.begin() + newProcessIndex);
											} 

											
											
											else {
												
												queue.push_back(preProcessList[newProcessIndex]);

												
												preProcessList.erase(preProcessList.begin() + newProcessIndex);
											} 
										} 

										
										
										else {
											
											queue.push_back(preProcessList[newProcessIndex]);

											
											preProcessList.erase(preProcessList.begin() + newProcessIndex);
										} 
									} 
								} 

							} 


							
							else {
								
								queue.push_back(preProcessList[newProcessIndex]);

								
								preProcessList.erase(preProcessList.begin() + newProcessIndex);
							} 
						} 
						*/


						/*
						

						
						
						
						if ((queue[minCpuBrustTimeProcess].cpuBrust == queue[minCpuBrustTimeProcess].tmpCpuBrust) && (queue[i].cpuBrust != queue[i].tmpCpuBrust)) {
							;
						} 

						
						
						
						
						else if ((queue[minCpuBrustTimeProcess].cpuBrust != queue[minCpuBrustTimeProcess].tmpCpuBrust) && (queue[i].cpuBrust == queue[i].tmpCpuBrust)) {
							minCpuBrustTimeProcess = i;
						} 

						
						else {
							

							
							
							if (queue[minCpuBrustTimeProcess].arrivalTime > queue[i].arrivalTime) {
								minCpuBrustTimeProcess = i;
							} 

							
							else {
								
								if (queue[minCpuBrustTimeProcess].arrivalTime == queue[i].arrivalTime) {
									

									
									
									if (queue[minCpuBrustTimeProcess].id > queue[i].id) {
										minCpuBrustTimeProcess = i;
									} 
								} 
							} 
						} 
						*/

						
													/*
													
													
													if ((nowCpuExecuteProcess.cpuBrust == nowCpuExecuteProcess.tmpCpuBrust) && (queue[nextProcessIndesInQueue].cpuBrust != queue[nextProcessIndesInQueue].tmpCpuBrust)) {
														;
													} 

													
													
													else if ((nowCpuExecuteProcess.cpuBrust != nowCpuExecuteProcess.tmpCpuBrust) && (queue[nextProcessIndesInQueue].cpuBrust == queue[nextProcessIndesInQueue].tmpCpuBrust)) {
														
														nowCpuExecuteProcess.executionTime = 0;

														
														queue.push_back(nowCpuExecuteProcess);

														
														nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

														
														queue.erase(queue.begin() + nextProcessIndesInQueue);
													} 

													
													
													else {
														
														
														if (queue[nextProcessIndesInQueue].arrivalTime < nowCpuExecuteProcess.arrivalTime) {
															
															nowCpuExecuteProcess.executionTime = 0;

															
															queue.push_back(nowCpuExecuteProcess);

															
															nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

															
															queue.erase(queue.begin() + nextProcessIndesInQueue);
														} 

														
														
														else if (queue[nextProcessIndesInQueue].arrivalTime == nowCpuExecuteProcess.arrivalTime) {
															
															if (queue[nextProcessIndesInQueue].id < nowCpuExecuteProcess.id) {

																
																nowCpuExecuteProcess.executionTime = 0;

																
																queue.push_back(nowCpuExecuteProcess);

																
																nowCpuExecuteProcess = queue[nextProcessIndesInQueue];

																
																queue.erase(queue.begin() + nextProcessIndesInQueue);
															} 

															
														} 

														
													} 
													*/