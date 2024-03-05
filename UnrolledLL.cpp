#include "UnrolledLL.h"
#include <iostream>
/**
 * Constructor for a node in the unrolled linked list.
 * This should create a node with the given block siz.
 * @param size Size of the list
 * @param blksize Size of each block
 */
uNode::uNode(uNode* prev, u_int64_t blksize) : blksize(blksize) {
	/* Implement me! */
	datagrp = new int[blksize];
	if( prev != nullptr){
		prev -> next = this;
	}
	next = nullptr;
}

/**
 * Destructor for a node in the unrolled linked list.
 * This should deallocate all memory associated with the uNode.
 */
uNode::~uNode() {
	delete[] datagrp;
}

/**
 * Constructor for the unrolled linked list.
 * This should create a linked list of uNodes.
 * @param size Size of the list
 * @param blksize Size of each block
 */
UnrolledLL::UnrolledLL(u_int64_t size, u_int64_t blksize) {
	/* Implement me! */
	if( size == 0 || blksize == 0){
		head = nullptr;
		return;
	}

	head = new uNode(nullptr, blksize);
	uNode* current = head;
	u_int64_t remaining = size - blksize;

	while ( remaining > 0 ) {
		u_int64_t current_blksize = (remaining < blksize) ? remaining : blksize;
    current = new uNode( current, current_blksize);
    remaining -= current_blksize;
	}
  len = size;
}

/**
 * Destructor for the unrolled linked list.
 * This should deallocate all memory associated with the unrolled linked list.
 */
UnrolledLL::~UnrolledLL() {
	uNode* current = head;
	uNode* next;

	while (current != nullptr) {
		next = current->next;
		delete current;
		current = next;
	}

	head = nullptr;
}

/**
 * Iterate through the unrolled linked list.
 * Simply iterate through the unrolled linked list and access each element.
 */
void UnrolledLL::iterate_ullist() {
	/* Implement me! */
  uNode* current = head;
  while ( current != nullptr ) {
    for ( u_int64_t i = 0; i < current -> blksize; i++ ){
      std::cout << current -> datagrp[i] << " ";
    }
    current = current -> next;
  }

}
