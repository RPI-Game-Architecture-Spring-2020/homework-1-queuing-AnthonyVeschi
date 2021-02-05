#pragma once
/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/

#include <mutex>

class ga_queue
{
public:
	struct Node
	{
		Node* next;
		void* val;

		/*~Node()
		{
			if (val) { free(val); }
			if (next)
			{
				next->~Node();
				free(next);
			}
		}*/
	};

	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;

private:
	Node* head;
	Node* tail;

	std::mutex headLock;
	std::mutex tailLock;
};
