#pragma once

template <class T>
struct CycleList
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

	CycleList() {}
	CycleList(CycleList& other) = delete;
	CycleList& operator=(CycleList& other) = delete;

	~CycleList()
	{
		Clear();
	}

	void PushBack(const T& value)
	{
		if (head == nullptr)
		{
			// Initialise list
			head = new Node(value);
			head->next = head;
			head->prev = head;
		}
		else
		{
			InsertAfter(value, head->prev);
		}
	}

	void InsertAfter(const T& value, Node* indexNode)
	{
		Node* newNode = new Node(value);
		Node* afterIndex = indexNode->next;

		ConnectNodes(indexNode, newNode);
		ConnectNodes(newNode, afterIndex);
	}

	void ConnectNodes(Node* before, Node* after)
	{
		before->next = after;
		after->prev = before;
	}

	void RemoveNode(Node* target)
	{
		if (target->next == target)
		{
			delete target;
			head = nullptr;
		}
		else
		{
			if (target == head)
			{
				head = target->next;
			}

			ConnectNodes(target->prev, target->next);
			delete target;
		}
	}

	void Clear()
	{
		if (head == nullptr)
		{
			return;
		}

		Node* current = head;
		do
		{
			Node* next = current->next;
			delete current;
			current = next;
		} while (current != head);

		head = nullptr;
	}
};