#include <iostream>

using namespace std;

class LinkedListNode
{
public:
	LinkedListNode* nextNode;
	float* data;
	int size;

	LinkedListNode(float* data, int size, LinkedListNode* nextNode = nullptr)
	{
		this->data = data;
		this->nextNode = nextNode;
		this->size = size;
	}
};

class TableRecord
{
public:
	int index;
	LinkedListNode* value;
	TableRecord(int index, LinkedListNode* value)
	{
		this->index = index;
		this->value = value;
	}
};

class IndexedTable
{
public:
	TableRecord* records[5];
	int delta;

	IndexedTable()
	{
		count = 0;
		delta = 1;
	}

	void Add(TableRecord* record)
	{
		if (count < 5)
		{
			records[count] = record;
			count++;
		}
	}

	void InsertAt(TableRecord* record, int index)
	{
		if (count < 5)
		{
			records[index] = record;
			count++;
		}
	}
private:
	int count;
};

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void AddToHead(LinkedListNode* node);
	void AddToTail(LinkedListNode* node);
	void RemoveHead();
	void RemoveTail();
	void InsertAt(LinkedListNode* node, int index);
	void RemoveAt(int index);
	LinkedListNode* GetAt(int index);
	void SetAt(LinkedListNode* node, int index);
	int GetSize() { return size; }
	void Clear();

private:
	int size;
	LinkedListNode* head;
	IndexedTable* indexedTable;
};


LinkedList::LinkedList()
{
	size = 0;
	head = nullptr;
	indexedTable = new IndexedTable();
}


LinkedList::~LinkedList()
{
	Clear();
}


void LinkedList::AddToHead(LinkedListNode* node)
{
	LinkedListNode* currentNode = head;
	node->nextNode = head;
	head = node;
	if (size < 5)
	{
		indexedTable->Add(new TableRecord(5 - size, node));
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			indexedTable->records[i]->index + 1;
		}
	}
	size++;
}

void LinkedList::AddToTail(LinkedListNode* node)
{
	if (head == nullptr)
	{
		head = node;
	}
	else
	{
		LinkedListNode* currentNode = head;

		while (currentNode->nextNode != nullptr)
		{
			currentNode = currentNode->nextNode;
		}
		currentNode->nextNode = node;
	}

	if (size < 5)
	{
		indexedTable->Add(new TableRecord(size, node));
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			indexedTable->records[i]->index + 1;
		}
	}

	size++;
}


void LinkedList::RemoveHead()
{
	LinkedListNode* temp = head;
	head = head->nextNode;
	delete temp;
	size--;
}


void LinkedList::RemoveTail()
{
	RemoveAt(size - 1);
}


void LinkedList::InsertAt(LinkedListNode* node, int index)
{
	if (index == 0)
	{
		AddToHead(node);
	}
	else
	{
		LinkedListNode* previosNode = head;

		for (int i = 0; i < index - 1; i++)
		{
			previosNode = previosNode->nextNode;
		}

		node->nextNode = previosNode->nextNode;
		//LinkedListNode* newNode = new LinkedListNode(data, previosNode->nextNode);
		//previosNode->nextNode = newNode;
		previosNode->nextNode = node;

		size++;
	}
}


void LinkedList::RemoveAt(int index)
{
	if (index == 0)
	{
		RemoveHead();
	}
	else
	{
		LinkedListNode* previosNode = head;

		for (int i = 0; i < index - 1; i++)
		{
			previosNode = previosNode->nextNode;
		}

		LinkedListNode* deleteNode = previosNode->nextNode;
		previosNode->nextNode = deleteNode->nextNode;
		delete deleteNode;

		size--;
	}
}

LinkedListNode* LinkedList::GetAt(int index)
{
	int counter = 0;
	LinkedListNode* currentNode = this->head;

	while (currentNode != nullptr)
	{
		if (counter == index)
		{
			return currentNode;
		}
		currentNode = currentNode->nextNode;
		counter++;
	}
}


void LinkedList::SetAt(LinkedListNode* node, int index)
{
}


void LinkedList::Clear()
{
	while (size)
	{
		RemoveHead();
	}
}

float* GenerateArray(int sizeArray)
{
	//srand(time(NULL));
	//int n = rand() % 10;
	float* ar = new float[sizeArray];
	for (int i = 0; i < sizeArray; i++)
	{
		ar[i] = rand() % 1000;
	}
	return ar;
}


int main()
{
	setlocale(LC_ALL, "ru");

	LinkedList tailList;
	LinkedList headList;

	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int n = rand() % 10;
		float* pArray = GenerateArray(n);
		tailList.AddToTail(new LinkedListNode(pArray, n));
		headList.AddToHead(new LinkedListNode(pArray, n));
	}

	//list.AddToTail(new LinkedListNode(new float[1]{ 1 }, 1));
	//list.AddToTail(new LinkedListNode(new float[2]{ 2, 3 }, 2));
	//list.AddToTail(new LinkedListNode(new float[3]{ 4, 5, 6 }, 3));
	//list.AddToTail(new LinkedListNode(new float[4]{ 7, 8, 9, 10 }, 4));
	//list.AddToTail(new LinkedListNode(new float[5]{ 11, 12, 13, 14, 15 }, 5));

	for (int i = 0; i < tailList.GetSize(); i++)
	{
		LinkedListNode* node = tailList.GetAt(i);
		float* pointer = node->data;
		for (int i = 0; i < node->size; i++)
		{
			printf("%f ", pointer[i]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");

	for (int i = 0; i < headList.GetSize(); i++)
	{
		LinkedListNode* node = headList.GetAt(i);
		float* pointer = node->data;
		for (int i = 0; i < node->size; i++)
		{
			printf("%f ", pointer[i]);
		}
		printf("\n");
	}

	//cout << endl;

	//list.InsertAt(7, 1);

	//for (int i = 0; i < list.GetSize(); i++)
	//{
	//	cout << list[i] << endl;
	//}

	//cout << endl;

	//list.RemoveAt(2);

	//for (int i = 0; i < list.GetSize(); i++)
	//{
	//	cout << list[i] << endl;
	//}
}