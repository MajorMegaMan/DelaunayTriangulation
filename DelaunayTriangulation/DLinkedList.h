#pragma once

// this is a Bidirectional Linked List of edges
template <class T>
struct DLinkedList
{
	struct Node
	{
		T value;
		Node* prev = nullptr;
		Node* next = nullptr;

		Node(const T& value)
		{
			this->value = value;
		}

		~Node()
		{
			prev = nullptr;
			next = nullptr;
		}
	};

	Node* head = nullptr;
	Node* tail = nullptr;

	DLinkedList() {}
	DLinkedList(DLinkedList& other) = delete;
	DLinkedList& operator=(DLinkedList& other) = delete;

	~DLinkedList()
	{
		Clear();
	}

	T* PushBack(const T& value)
	{
		if (tail == nullptr)
		{
			// Initialise list
			tail = new Node(value);
			head = tail;
		}
		else
		{
			Node* oldTail = tail;
			tail = new Node(value);

			ConnectNodes(oldTail, tail);
		}
		return &tail->value;
	}

	T* InsertAfter(const T& value, Node* indexNode)
	{
		if (indexNode == tail)
		{
			return PushBack(value);
		}
		else
		{
			Node* newNode = new Node(value);
			Node* afterIndex = indexNode->next;

			ConnectNodes(indexNode, newNode);
			ConnectNodes(newNode, afterIndex);

			return &newNode->value;
		}
	}

	void ConnectNodes(Node* before, Node* after)
	{
		before->next = after;
		after->prev = before;
	}

	void RemoveNode(Node* target)
	{
		if (target == head && target == tail)
		{
			delete target;
			head = nullptr;
			tail = nullptr;
		}
		else if (target == head)
		{
			Node* oldHead = head;
			head = head->next;
			head->prev = nullptr;
			delete oldHead;
		}
		else if (target == tail)
		{
			Node* oldTail = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete oldTail;
		}
		else
		{
			Node* before = target->prev;
			Node* after = target->next;

			ConnectNodes(before, after);
			delete target;
		}
	}

	void Clear()
	{
		Node* current = head;
		while (current != nullptr)
		{
			Node* next = current->next;
			delete current;
			current = next;
		}

		head = nullptr;
		tail = nullptr;
	}
};