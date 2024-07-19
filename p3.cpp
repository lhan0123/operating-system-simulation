include <iostream>
include <string>
include <vector>
include <fstream> 
include <algorithm>
include <stdio.h>

using namespace std;

int PAGE_FRAME_TOTAL;
vector<int> gInputPageList;

struct PAGEFRAME {
	int curPage = -1;
	int ref = 0;
	int counter = 0;
	int timestamp = -1;
	vector<int> shiftReg;  
};

struct RESUTL {
	int enterPage = -1;
	vector<int> accessPageList;
	bool isPageFault = false;
};


void ReadFile(int& pageFrame) {
	ifstream inFile;
	string fileName;
	string pageReference;

	
	do {
		cout << "> Input File Name: ";
		cin >> fileName;

		inFile.open(fileName.c_str(), ifstream::in);

		if (inFile.fail()) {
			cout << "�䤣����ɮסA�Э��s";
		} 

	} while (inFile.fail());

	
	cout << "Read page frame..." << endl;
	inFile >> pageFrame;
	cout << "page frame: " << pageFrame << endl;

	
	inFile >> pageReference;

	for (int i = 0; i < pageReference.size(); i++) {
		gInputPageList.push_back((int)pageReference[i] - 48);
	} 

	
	/*
	for (int i = 0; i < inputProcessList.size() ; i++) {
		cout << inputProcessList[i];
	} 
	cout << endl;
	*/

	
	inFile.close();

} 


class FIFO {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;


	
	void InitPageFrame() {
		PAGEFRAME p;
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	void ExecuteFIFO() {

		int index = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					
					index = FindPageInPageFrameList(pageFrameAccessList[lastPageIndexInAccessList]);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + lastPageIndexInAccessList);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			else {
				;
			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;
		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;

		*/
	} 
};

class LRU {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;

	
	void InitPageFrame() {
		PAGEFRAME p;
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	void ExecuteLRU() {

		int index = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					
					index = FindPageInPageFrameList(pageFrameAccessList[lastPageIndexInAccessList]);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + lastPageIndexInAccessList);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {

				
				index = FindPageInPageFrameAccessList(inputPageList[i]);

				
				pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

				
				
				pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;
		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/
		
	} 
};

class Additional_Reference_Bits {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;

	
	void InitPageFrame() {
		PAGEFRAME p;

		
		for (int i = 0; i < 16; i++) {
			p.shiftReg.push_back(0);
		} 

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	
	
	
	void ShiftAllRegAndInit() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList[i].shiftReg.erase(pageFrameList[i].shiftReg.begin() + 15);
			pageFrameList[i].shiftReg.insert(pageFrameList[i].shiftReg.begin(), pageFrameList[i].ref);
			pageFrameList[i].ref = 0;
		} 

	} 

	
	int CountShiftReg( vector<int> shiftReg) {
		int twoNum = 32768 ;
		int sum = 0;

		for (int i = 0; i < 16; i++) {
			sum = sum + shiftReg[i] * twoNum;
			twoNum = twoNum / 2;
		} 

		return sum;
	} 

	int FindCurAccessPageInPageList(int page, int curEnter) {

		for (int i = curEnter - 1; i >= 0; i--) {
			if (inputPageList[i] == page) return i;
		} 

		return -1;

	} 

	
	
	
	
	
	int ReturnReplacePageNumInPageFrame(int curEnter) {
		int pageInPageFrameIndex;
		int minIndex = - 1;      
		int tmp1Index = -1;
		int tmp2Index = -1;

		
		for (int i = PAGE_FRAME_TOTAL - 1 ; i >= 0 ; i--) {
			
			pageInPageFrameIndex = FindPageInPageFrameList(pageFrameAccessList[i]);

			if (minIndex == -1) {
				minIndex = pageInPageFrameIndex;
			} 

			else {
				
				if (CountShiftReg(pageFrameList[minIndex].shiftReg) > CountShiftReg(pageFrameList[pageInPageFrameIndex].shiftReg)) {
					minIndex = pageInPageFrameIndex;
				} 

				else if (CountShiftReg(pageFrameList[minIndex].shiftReg) == CountShiftReg(pageFrameList[pageInPageFrameIndex].shiftReg)) {
					tmp1Index = FindCurAccessPageInPageList(pageFrameList[minIndex].curPage, curEnter);
					tmp2Index = FindCurAccessPageInPageList(pageFrameList[pageInPageFrameIndex].curPage, curEnter);
					if (tmp2Index < tmp1Index) {
						minIndex = pageInPageFrameIndex;
					} 
				} 
			} 
		} 

		
		return pageFrameList[minIndex].curPage;
	} 

	void ExecuteARB() {

		int index = -1;
		int removePageNum = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			/*
			cout << "print current shift reg: " << endl;
			for (int k = 0; k < PAGE_FRAME_TOTAL; k++) {
				cout << "page " << k << " (" << pageFrameList[k].curPage << ")" << endl;
				for (int j = 0; j < pageFrameList[k].shiftReg.size(); j++)
					cout << pageFrameList[k].shiftReg[j];
				cout << endl;
			} 
			*/

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].ref = 1;

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					removePageNum = ReturnReplacePageNumInPageFrame(i);

					
					index = FindPageInPageFrameList(removePageNum);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					for (int j = 0; j < 16; j++) {
						pageFrameList[index].shiftReg[j] = 0;
					} 

					
					pageFrameList[index].ref = 1;

					
					index = FindPageInPageFrameAccessList(removePageNum);

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {

				
				index = FindPageInPageFrameList(inputPageList[i]);

				
				pageFrameList[index].ref = 1;
			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;

			
			ShiftAllRegAndInit();
		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/

	} 
};


class Least_Frequently_Used_Page_Replacement {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;

	
	void InitPageFrame() {
		PAGEFRAME p;

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	
	int FindCurAccessPageInPageList( int page, int curEnter) {

		for (int i = curEnter-1 ; i >= 0; i--) {
			if (inputPageList[i] == page) return i;
		} 

		return -1;

	} 

	int ReturnReplacePageNumInPageFrame( int  curEnter ) {
		int pageInPageFrameIndex;
		int minIndex = -1;      
		int tmp1Index = -1;
		int tmp2Index = -1;

		
		for (int i = PAGE_FRAME_TOTAL - 1; i >= 0; i--) {

			
			pageInPageFrameIndex = FindPageInPageFrameList(pageFrameAccessList[i]);

			if (minIndex == -1) {
				minIndex = pageInPageFrameIndex;
			} 

			else {
				
				if (pageFrameList[minIndex].counter > pageFrameList[pageInPageFrameIndex].counter) {
					minIndex = pageInPageFrameIndex;
				} 

				
				else if (pageFrameList[minIndex].counter == pageFrameList[pageInPageFrameIndex].counter) {
					tmp1Index = FindCurAccessPageInPageList(pageFrameList[minIndex].curPage, curEnter);
					tmp2Index = FindCurAccessPageInPageList(pageFrameList[pageInPageFrameIndex].curPage, curEnter);
					if (tmp2Index < tmp1Index) {
						minIndex = pageInPageFrameIndex;
					} 
				} 

			} 
		} 

		
		return pageFrameList[minIndex].curPage;

	} 


	void ExecuteLFU() {

		int index = -1;
		int removePageNum = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			/*
			cout << "enter page: " <<  inputPageList[i] << endl;
			for (int k = 0; k < PAGE_FRAME_TOTAL; k++) {
				cout << "page " << k << " (" << pageFrameList[k].curPage << ")" << endl;
				cout << "counter: " << pageFrameList[k].counter << endl;
			} 
			*/

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter++ ;

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					removePageNum = ReturnReplacePageNumInPageFrame(i);

					
					index = FindPageInPageFrameList(removePageNum);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter = 0 ;

					
					pageFrameList[index].counter++;

					
					index = FindPageInPageFrameAccessList(removePageNum);

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {
				
				index = FindPageInPageFrameList(inputPageList[i]);

				
				pageFrameList[index].counter++;

			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;


		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/

	} 
};

class Least_Frequently_Used_Page_Replacement_2 {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;
	vector<int> timeStampList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;

	
	void InitPageFrame() {
		PAGEFRAME p;

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	
	int FindCurAccessPageInPageList(int page, int curEnter) {

		for (int i = curEnter - 1; i >= 0; i--) {
			if (inputPageList[i] == page) return i;
		} 

		return -1;

	} 

	int ReturnReplacePageNumInPageFrame(int  curEnter) {
		int pageInPageFrameIndex;
		int minIndex = -1;      
		int tmp1Index = -1;
		int tmp2Index = -1;

		
		for (int i = PAGE_FRAME_TOTAL - 1; i >= 0; i--) {

			
			pageInPageFrameIndex = FindPageInPageFrameList(pageFrameAccessList[i]);

			if (minIndex == -1) {
				minIndex = pageInPageFrameIndex;
			} 

			else {
				
				if (pageFrameList[minIndex].counter > pageFrameList[pageInPageFrameIndex].counter) {
					minIndex = pageInPageFrameIndex;
				} 

				
				else if (pageFrameList[minIndex].counter == pageFrameList[pageInPageFrameIndex].counter) {
					tmp1Index = FindPageInPageFrameAccessList(pageFrameList[minIndex].curPage);
					tmp2Index = FindPageInPageFrameAccessList(pageFrameList[pageInPageFrameIndex].curPage);
					if (tmp2Index > tmp1Index) {
						minIndex = pageInPageFrameIndex;
					} 
				} 

			} 
		} 

		
		return pageFrameList[minIndex].curPage;

	} 


	void ExecuteLFU() {

		int index = -1;
		int removePageNum = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter++;

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);

					
					timeStampList.insert(timeStampList.begin() + 0, inputPageList[i] );
				} 

				
				else {
					countPageReplace++; 

					
					removePageNum = ReturnReplacePageNumInPageFrame(i);

					
					index = FindPageInPageFrameList(removePageNum);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter = 0;

					
					pageFrameList[index].counter++;

					
					index = FindPageInPageFrameAccessList(removePageNum);

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {
				
				index = FindPageInPageFrameList(inputPageList[i]);

				
				pageFrameList[index].counter++;

			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;


		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/

	} 
};

class Most_Frequently_Used_Page_Replacement {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;

	
	void InitPageFrame() {
		PAGEFRAME p;

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	
	int FindCurAccessPageInPageList(int page, int curEnter) {

		for (int i = curEnter - 1; i >= 0; i--) {
			if (inputPageList[i] == page) return i;
		} 

		return -1;

	} 

	int ReturnReplacePageNumInPageFrame(int  curEnter) {
		int pageInPageFrameIndex;
		int minIndex = -1;      
		int tmp1Index = -1;
		int tmp2Index = -1;

		
		for (int i = PAGE_FRAME_TOTAL - 1; i >= 0; i--) {

			
			pageInPageFrameIndex = FindPageInPageFrameList(pageFrameAccessList[i]);

			if (minIndex == -1) {
				minIndex = pageInPageFrameIndex;
			} 

			else {
				
				if (pageFrameList[minIndex].counter <  pageFrameList[pageInPageFrameIndex].counter) {
					minIndex = pageInPageFrameIndex;
				} 

				
				else if (pageFrameList[minIndex].counter == pageFrameList[pageInPageFrameIndex].counter) {
					tmp1Index = FindCurAccessPageInPageList(pageFrameList[minIndex].curPage, curEnter);
					tmp2Index = FindCurAccessPageInPageList(pageFrameList[pageInPageFrameIndex].curPage, curEnter);
					if (tmp2Index < tmp1Index) {
						minIndex = pageInPageFrameIndex;
					} 
				} 

			} 
		} 

		
		return pageFrameList[minIndex].curPage;

	} 


	void ExecuteMFU() {

		int index = -1;
		int removePageNum = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			/*
			cout << "enter page: " <<  inputPageList[i] << endl;
			for (int k = 0; k < PAGE_FRAME_TOTAL; k++) {
				cout << "page " << k << " (" << pageFrameList[k].curPage << ")" << endl;
				cout << "counter: " << pageFrameList[k].counter << endl;
			} 
			*/

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter++;

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					removePageNum = ReturnReplacePageNumInPageFrame(i);

					
					index = FindPageInPageFrameList(removePageNum);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter = 0;

					
					pageFrameList[index].counter++;

					
					index = FindPageInPageFrameAccessList(removePageNum);

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {
				
				index = FindPageInPageFrameList(inputPageList[i]);

				
				pageFrameList[index].counter++;

			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;


		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/

	} 


};

class Most_Frequently_Used_Page_Replacement_2 {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;

	
	void InitPageFrame() {
		PAGEFRAME p;

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	
	int FindCurAccessPageInPageList(int page, int curEnter) {

		for (int i = curEnter - 1; i >= 0; i--) {
			if (inputPageList[i] == page) return i;
		} 

		return -1;

	} 

	int ReturnReplacePageNumInPageFrame(int  curEnter) {
		int pageInPageFrameIndex;
		int minIndex = -1;      
		int tmp1Index = -1;
		int tmp2Index = -1;

		
		for (int i = PAGE_FRAME_TOTAL - 1; i >= 0; i--) {

			
			pageInPageFrameIndex = FindPageInPageFrameList(pageFrameAccessList[i]);

			if (minIndex == -1) {
				minIndex = pageInPageFrameIndex;
			} 

			else {
				
				if (pageFrameList[minIndex].counter < pageFrameList[pageInPageFrameIndex].counter) {
					minIndex = pageInPageFrameIndex;
				} 

				
				else if (pageFrameList[minIndex].counter == pageFrameList[pageInPageFrameIndex].counter) {
					tmp1Index = FindCurAccessPageInPageList(pageFrameList[minIndex].curPage, curEnter);
					tmp2Index = FindCurAccessPageInPageList(pageFrameList[pageInPageFrameIndex].curPage, curEnter);
					if (tmp2Index > tmp1Index) {
						minIndex = pageInPageFrameIndex;
					} 
				} 

			} 
		} 

		
		return pageFrameList[minIndex].curPage;

	} 


	void ExecuteMFU() {

		int index = -1;
		int removePageNum = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			/*
			cout << "enter page: " <<  inputPageList[i] << endl;
			for (int k = 0; k < PAGE_FRAME_TOTAL; k++) {
				cout << "page " << k << " (" << pageFrameList[k].curPage << ")" << endl;
				cout << "counter: " << pageFrameList[k].counter << endl;
			} 
			*/

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter++;

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					removePageNum = ReturnReplacePageNumInPageFrame(i);

					
					index = FindPageInPageFrameList(removePageNum);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].counter = 0;

					
					pageFrameList[index].counter++;

					
					index = FindPageInPageFrameAccessList(removePageNum);

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {
				
				index = FindPageInPageFrameList(inputPageList[i]);

				
				pageFrameList[index].counter++;

			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;


		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/

	} 



};

class Second_Change_Page_Replacement {
public:
	vector<PAGEFRAME> pageFrameList; 
	vector<int> pageFrameAccessList; 
	vector<RESUTL> resultList;
	vector<int> inputPageList;

	bool isCurPageFault = false;

	int countPageFault = 0;
	int countPageReplace = 0;
	int curTime = -1;

	
	void InitPageFrame() {
		PAGEFRAME p;

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			pageFrameList.push_back(p);
		} 
	} 

	
	
	int ReturnAvailabelPageFrame() {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == -1)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameList(int page) {

		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameList[i].curPage == page)
				return i;
		} 

		return -1;
	} 

	
	int FindPageInPageFrameAccessList(int page) {
		for (int i = 0; i < PAGE_FRAME_TOTAL; i++) {
			if (pageFrameAccessList[i] == page)
				return i;
		} 

		return -1;
	} 

	int ReturnReplacePageNumInPageFrame() {
		int index = -1;
		bool isDone = false;
		int page = -1;

		while (!isDone) {

			
			
			index = FindPageInPageFrameList(pageFrameAccessList[PAGE_FRAME_TOTAL-1]); 

			
			if (pageFrameList[index].ref == 0) {
				
				isDone = true;
			} 

			
			
			else {
				pageFrameList[index].ref = 0;

				
				page = pageFrameList[index].curPage;
				pageFrameAccessList.erase(pageFrameAccessList.begin() + PAGE_FRAME_TOTAL - 1);
				pageFrameAccessList.insert(pageFrameAccessList.begin(), page);

				
			} 
		} 
		
		return pageFrameList[index].curPage;

	} 


	void ExecuteSCPR() {

		int index = -1;
		int removePageNum = -1;
		int lastPageIndexInAccessList = PAGE_FRAME_TOTAL - 1;
		int curTime = -1;
		int page = -1;
		RESUTL result;

		InitPageFrame();

		inputPageList = gInputPageList;

		for (int i = 0; i < inputPageList.size(); i++) {

			curTime = i;

			/*
			cout << "enter page: " <<  inputPageList[i] << endl;
			for (int k = 0; k < PAGE_FRAME_TOTAL; k++) {
				cout << "page " << k << " (" << pageFrameList[k].curPage << ")" << endl;
				cout << "counter: " << pageFrameList[k].counter << endl;
			} 
			*/

			
			
			index = FindPageInPageFrameList(inputPageList[i]);

			
			if (index == -1) {

				countPageFault++; 
				isCurPageFault = true;

				
				index = ReturnAvailabelPageFrame();

				
				if (index != -1) {
					
					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].ref = 1;

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 

				
				else {
					countPageReplace++; 

					
					removePageNum = ReturnReplacePageNumInPageFrame();

					
					index = FindPageInPageFrameList(removePageNum);

					
					pageFrameList[index].curPage = inputPageList[i];

					
					pageFrameList[index].ref = 1;

					
					index = FindPageInPageFrameAccessList(removePageNum);

					
					pageFrameAccessList.erase(pageFrameAccessList.begin() + index);

					
					pageFrameAccessList.insert(pageFrameAccessList.begin(), inputPageList[i]);
				} 
			} 

			
			
			
			else {
				
				index = FindPageInPageFrameList(inputPageList[i]);

				
				pageFrameList[index].ref = 1;

			} 

			
			result.enterPage = inputPageList[i];
			result.accessPageList = pageFrameAccessList;
			
			
			result.isPageFault = isCurPageFault;
			resultList.push_back(result);

			
			isCurPageFault = false;


		} 

		/*
		for (int i = 0; i < resultList.size(); i++) {
			cout << resultList[i].enterPage << "\t";
			for (int j = 0; j < resultList[i].accessPageList.size(); j++) {
				cout << resultList[i].accessPageList[j];
			} 
			cout << "\t";

			if (resultList[i].isPageFault) cout << "F";
			cout << endl;
		} 

		cout << "Page Fault: " << countPageFault << endl;
		cout << "Page Replacement: " << countPageReplace << endl;
		*/

	} 

};


void OutputAll(FIFO fifo, LRU lru, Additional_Reference_Bits arb, Least_Frequently_Used_Page_Replacement lfu, Most_Frequently_Used_Page_Replacement mfu, Second_Change_Page_Replacement scpr) {
	ofstream outFile;
	string outputFileName = "Output_ALL.txt";

	outFile.open(outputFileName.c_str(), ios::trunc); 

	outFile << "--------------- FIFO --------------- " << endl;  

	
	for (int i = 0; i < fifo.resultList.size(); i++) {
		outFile << fifo.resultList[i].enterPage << "\t";
		for (int j = 0; j < fifo.resultList[i].accessPageList.size(); j++) {
			outFile << fifo.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (fifo.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 
	
	outFile << "Page Fault = " << fifo.countPageFault << "  Page Replaces = " << fifo.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl ;

	outFile << "---------------  LRU --------------- " << endl;  

	
	for (int i = 0; i < lru.resultList.size(); i++) {
		outFile << lru.resultList[i].enterPage << "\t";
		for (int j = 0; j < lru.resultList[i].accessPageList.size(); j++) {
			outFile << lru.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (lru.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << lru.countPageFault << "  Page Replaces = " << lru.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl ;

	outFile << "--------------- Additional_Reference_Bits --------------- " << endl;  

	
	for (int i = 0; i < arb.resultList.size(); i++) {
		outFile << arb.resultList[i].enterPage << "\t";
		for (int j = 0; j < arb.resultList[i].accessPageList.size(); j++) {
			outFile << arb.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (arb.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << arb.countPageFault << "  Page Replaces = " << arb.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl ;

	outFile << "--------------- Second chance Page --------------- " << endl;  

	
	for (int i = 0; i < scpr.resultList.size(); i++) {
		outFile << scpr.resultList[i].enterPage << "\t";
		for (int j = 0; j < scpr.resultList[i].accessPageList.size(); j++) {
			outFile << scpr.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (scpr.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << scpr.countPageFault << "  Page Replaces = " << scpr.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl ;

	outFile << "--------------- Least Frequently Used Page Replacement --------------- " << endl;  

	
	for (int i = 0; i < lfu.resultList.size(); i++) {
		outFile << lfu.resultList[i].enterPage << "\t";
		for (int j = 0; j < lfu.resultList[i].accessPageList.size(); j++) {
			outFile << lfu.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (lfu.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << lfu.countPageFault << "  Page Replaces = " << lfu.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl ;


	outFile << "--------------- Most Frequently Used Page Replacement --------------- " << endl;  

	
	for (int i = 0; i < mfu.resultList.size(); i++) {
		outFile << mfu.resultList[i].enterPage << "\t";
		for (int j = 0; j < mfu.resultList[i].accessPageList.size(); j++) {
			outFile << mfu.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (mfu.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << mfu.countPageFault << "  Page Replaces = " << mfu.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl ;

	
	outFile.close();
} 

void OutputAll_2(Least_Frequently_Used_Page_Replacement_2 lfu) {
	ofstream outFile;
	string outputFileName = "Output_ALL_2.txt";

	outFile.open(outputFileName.c_str(), ios::trunc); 


	outFile << "--------------- Least Frequently Used Page Replacement --------------- " << endl;  

	
	for (int i = 0; i < lfu.resultList.size(); i++) {
		outFile << lfu.resultList[i].enterPage << "\t";
		for (int j = 0; j < lfu.resultList[i].accessPageList.size(); j++) {
			outFile << lfu.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (lfu.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << lfu.countPageFault << "  Page Replaces = " << lfu.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl;


	outFile.close();
} 


void OutputAll_3(Most_Frequently_Used_Page_Replacement_2 mfu) {
	ofstream outFile;
	string outputFileName = "Output_ALL_3.txt";

	outFile.open(outputFileName.c_str(), ios::trunc); 


	outFile << "--------------- Most Frequently Used Page Replacement --------------- " << endl;  

	
	for (int i = 0; i < mfu.resultList.size(); i++) {
		outFile << mfu.resultList[i].enterPage << "\t";
		for (int j = mfu.resultList[i].accessPageList.size()-1 ; j >= 0 ; j--) {
			outFile << mfu.resultList[i].accessPageList[j];
		} 
		outFile << "\t";

		if (mfu.resultList[i].isPageFault) outFile << "F";
		outFile << endl;
	} 

	outFile << "Page Fault = " << mfu.countPageFault << "  Page Replaces = " << mfu.countPageReplace << "  Page Frames = " << PAGE_FRAME_TOTAL << endl << endl;


	outFile.close();
} 


int main() {
	FIFO fifo;
	LRU lru;
	Additional_Reference_Bits arb;
	Least_Frequently_Used_Page_Replacement lfu;
	Least_Frequently_Used_Page_Replacement_2 lfu2;
	Most_Frequently_Used_Page_Replacement mfu;
	Most_Frequently_Used_Page_Replacement_2 mfu2;
	Second_Change_Page_Replacement scpr;
	
	ReadFile(PAGE_FRAME_TOTAL); 

	
	/*
	fifo.ExecuteFIFO();
	lru.ExecuteLRU();
	arb.ExecuteARB();
	scpr.ExecuteSCPR();
	lfu.ExecuteLFU();
	mfu.ExecuteMFU();

	OutputAll(fifo, lru, arb, lfu, mfu, scpr);
	*/

	
	/*
	lfu2.ExecuteLFU();
	OutputAll_2(lfu2);
	*/

	

	mfu2.ExecuteMFU();
	OutputAll_3(mfu2);
	


} 