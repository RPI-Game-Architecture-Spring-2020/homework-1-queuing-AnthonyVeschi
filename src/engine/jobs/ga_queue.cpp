/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	//Initialize Queue

	head = (Node*)malloc(sizeof(Node));
	tail = (Node*)malloc(sizeof(Node));
	//Node* node = (Node*)malloc(sizeof(Node));
	Node* node = new Node;

	node->next = NULL;
	node->val = NULL;
	head = node;
	tail = node;

	//headLock.unlock();
	//tailLock.unlock();
}

ga_queue::~ga_queue()
{
	//Free any resources held by the queue.
	/*if (head)
	{
		head->~Node();
		free(head);
		free(tail);
	}*/
	Node* node = head;
	Node* nextNode;
	while (node->next)
	{
		nextNode = node->next;
		free(node);
		node = nextNode;
	}
}

void ga_queue::push(void* data)
{
	//Push one element with value 'data' onto the queue

	//Node* node = (Node*)malloc(sizeof(Node));
	Node* node = new Node;

	node->val = data;
	node->next = NULL;
	
	tailLock.lock();
	tail->next = node;
	tail = node;
	tailLock.unlock();
}

bool ga_queue::pop(void** data)
{
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	
	headLock.lock();
	Node* node = head;
	Node* newHead = head->next;
	if (!newHead)
	{
		headLock.unlock();
		return false;
	}
	*data = newHead->val;
	head = newHead;
	headLock.unlock();
	free(node);
	return true;
}

int ga_queue::get_count() const
{
	// Get the number of elements currently in the queue.
	
	int count = 0;
	Node* node = head;
	while (node->next)
	{
		count++;
		node = node->next;
	}
	return count;
}
