// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
			++answer;

		return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	};
    };

	void list_piece(node *start_ptr, node *end_ptr, node *&head_ptr, node *&tail_ptr)
	{
		head_ptr = NULL;
		tail_ptr = NULL;
		cout << "hello" << endl;
		if (start_ptr == NULL || start_ptr == end_ptr) 
		{
			cout << "i am here" << endl;
			return;
		}
		cout << "hello" << endl;

		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;

		start_ptr = start_ptr->link();
		while (start_ptr != end_ptr)
		{
			list_insert(tail_ptr, start_ptr->data());
			tail_ptr = tail_ptr->link();
			start_ptr = start_ptr->link();
		}
	};
	
	size_t list_occurrences(node *head_ptr, const node::value_type &target)
	{
		size_t count = 0;
		while(head_ptr != NULL)
		{
			if(head_ptr->data() == target) count++;
			head_ptr = head_ptr->link();
		}
		return count;
	};

	//   void list_insert_at(Node*& head_ptr, const node::value_type& entry, size_t position)
	//     Precondition: head_ptr is the head pointer of a linked list, and
	//     position > 0 and position <= list_length(head_ptr)+1.
	//     Postcondition: A new node has been added to the linked list with entry
	//     as the data. The new node occurs at the specified position in the list.
	//     (The head node is position 1, the next node is position 2, and so on.)
	//     Any nodes that used to be after this specified position have been
	//     shifted to make room for the one new node.

	void list_insert_at(node *&head_ptr, const node::value_type &entry, size_t position)
	{
		// this might be problem function
		assert(position > 0 && position <= list_length(head_ptr) + 1);
		
		if(position == 1)
		{
			list_head_insert(head_ptr, entry);
			return;
		};

		node *prev_node = head_ptr;
		node *ins_node = head_ptr->link();
		for(size_t i = 2; i < position; i++)
		{
			prev_node = ins_node;
			ins_node = ins_node->link();

		};
		list_insert(prev_node, entry);
	};

	//   node::value_type list_remove_at(node*& head_ptr, size_t position)
	//     Precondition: head_ptr is the head pointer of a linked list, and
	//     position > 0 and position <= list_length(head_ptr).
	//     Postcondition: The node at the specified position has been removed from
	//     the linked list and the function has returned a copy of the data from
	//     the removed node.
	//     (The head node is position 1, the next node is position 2, and so on.)

	node::value_type list_remove_at(node *&head_ptr, size_t position)
	{
		// this might be problem function
		assert(position > 0 && position <= list_length(head_ptr) + 1);

		if (position == 1)
		{
			node::value_type ret = head_ptr->data();
			list_head_remove(head_ptr);
			return ret;
		};

		node *prev_node = head_ptr;
		node *rem_node = head_ptr->link();
		for (size_t i = 2; i < position; i++)
		{
			prev_node = rem_node;
			rem_node = rem_node->link();
		};
		node::value_type ret = prev_node->data();
		list_remove(prev_node);
		return ret;
	};

	//   node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
	//     Precondition: head_ptr is the head pointer of a linked list, and
	//     (1 <= start) and (start <= finish) and (finish <= list_length(head_ptr)).
	//     Postcondition: The value returned is the head pointer for
	//     a new list that contains copies of the items from the start position to
	//     the finish position in the list that head_ptr points to.
	//     (The head node is position 1, the next node is position 2, and so on.)
	//     The list pointed to by head_ptr is unchanged.
	//

	node *list_copy_segment(node *head_ptr, size_t start, size_t finish)
	{
		assert(1 <= start && start <= finish && finish <= list_length(head_ptr));
		node *ret = NULL;
		node *tail_trash = NULL;
		list_piece(list_locate(head_ptr, start), list_locate(head_ptr, finish), ret, tail_trash);
		return ret;
	};
	
	void list_print(const node *head_ptr)
	{
		cout << "am i seg" << endl;
		cout << "i am the head ptr: " << head_ptr << endl;
		if(head_ptr == NULL) 
		{
			cout << "help" << endl << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;

			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			cout << "kill me !";
			return;
		}
		cout << "help help help " << endl;
		cout << head_ptr->data();
		cout << ", ";
		list_print(head_ptr->link());
	};

	//   void list_remove_dups(node* head_ptr)
	//     Precondition: head_ptr is the head pointer of a linked list
	//     Postcondition: All the duplicates are removed from the linked list
	//     Example: If the list contains 1,1,1,2, after running this function the list
	//     contains 1,2

	void list_remove_dups(node *head_ptr)
	{
		node *iter_ptr = head_ptr;
		cout << "am seg";
		while(head_ptr->link() != NULL)
		{
			while(iter_ptr->link() != NULL)
			{
				cout << "am seg";
				if(iter_ptr->link()->data() == head_ptr->data()) 
				{
					cout << "am seg seg";
					list_remove(head_ptr);
					iter_ptr = head_ptr;
				};
			};
			cout << "am seg";
			head_ptr = head_ptr->link();
		};
	};
	
	node *list_detect_loop(node *head_ptr)
	{
		// make array of memory addresses
		node **address_arr = new node* [1000];
		size_t count = 0;
		// loop through list, check each memory adress
		while(head_ptr != NULL)
		{
			for(size_t i = 0; i < count; i++)
			{
				if(address_arr[i] == head_ptr) return head_ptr;
			}
			address_arr[count++] = head_ptr;
			head_ptr = head_ptr->link();
		}
		return NULL;
	};
	
}
