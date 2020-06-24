
#include <iostream>
#include <fstream>

using namespace std;

class listNode {
public:
	string data;
	int count = 0;
	listNode* next;

	//default constructor
	listNode() {
		this->data = "dummy";
		this->count = 0;
		this->next = NULL;
	}

	//constructor to create new nodes
	listNode(string data, int count, listNode* next) {
		this->data = data;
		this->count = count;
		this->next = next;
	}

	static void printNode(listNode* printSpot, ofstream& outFile) {
		outFile << "(" << printSpot->data << ", " << printSpot->count << ", " << printSpot->next->data << ")->";
	}


};


class createhashTable {

public:
	const int bucketSize = 29;
	listNode* hashTableAry[29];

	createhashTable() {
		for (int i = 0; i < bucketSize; i++) {
			listNode* listHead = new listNode();
			hashTableAry[i] = listHead;
		}
	}

	void storeDataIntoHashTable(ifstream& inFile, ofstream& outFile2) {
		if (inFile.is_open())
		{
			string data;
			//iterates through the file to insert data to LL
			while (inFile >> data)
			{
				listNode* newNode = new listNode(data, 1, NULL);
				unsigned int index = doit(data);
				listNode* listHead = hashTableAry[index];
				listInsert(listHead, newNode);
				printList(index, outFile2);

			}
		}
	}

	unsigned int doit(string data) {
		unsigned int val = 1;
		for (unsigned int i = 0; i < data.length(); i++) {
			val = val * 32 + (unsigned int)data[i];
		}
		return val % 29;
	}

	void listInsert(listNode* listHead, listNode* newNode) {
		listNode* spot = findSpot(listHead, newNode);
		if (spot != NULL) {
			newNode->next = spot->next;
			spot->next = newNode;
		}

	}

	listNode* findSpot(listNode* listHead, listNode* newNode) {
		listNode* spot = listHead;
		while (spot->next != NULL && ifSpotsNextLessThanNn(spot, newNode) == true) {
			spot = spot->next;
		}
		if (spot->next != NULL && spot->next->data == newNode->data) {
			spot->next->count++;
			spot = NULL;

		}
		return spot;
	}

	bool ifSpotsNextLessThanNn(listNode* spot, listNode* newNode) {
		if (spot->next->data.compare(newNode->data) < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void printList(unsigned int index, ofstream& outFile) {
		outFile << "hashTable [" << index << "] ->";
		listNode* printSpot = hashTableAry[index];
		while (printSpot->next != NULL) {
			listNode::printNode(printSpot, outFile);
			printSpot = printSpot->next;

		}
		outFile << "(" << printSpot->data << ", " << printSpot->count << ", " << "NULL" << ")" << endl;

	}

	void printHashTable(ofstream& outFile) {
		int index = 0;
		while (index < bucketSize) {
			fixSpecCountError(index);
			printList(index, outFile);
			index++;
		}
	}
			
	void fixSpecCountError(int index) {
		listNode* itterator = hashTableAry[index];
		 
		int count = 0;
		while (itterator != NULL) {
			itterator->count = count;
			itterator = itterator->next;
			count++;
		}

	}
};

int main(int argc, char* argv[])
{
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1, outFile2;
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);

	createhashTable* createHashtableAry = new createhashTable();
	createHashtableAry->storeDataIntoHashTable(inFile, outFile2);
	createHashtableAry->printHashTable(outFile1);


	outFile1.close();
	outFile2.close();
	inFile.close();



}
