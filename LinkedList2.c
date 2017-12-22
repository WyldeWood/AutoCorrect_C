#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "linkedlist.h"
//#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>



struct Linked_List_Node {
	void * item;
	int Priority;
	struct Linked_List_Node * next;
};
struct Pointer_to_Linked_List {
	struct Linked_List_Node * head;
};
struct Linked_List_Opaque_Pointer {
	struct Pointer_to_Linked_List * Opaque_head;
};
Linked_List_Opaque_Pointer Create_LL() {
	Linked_List_Opaque_Pointer newLL = (Linked_List_Opaque_Pointer)malloc(sizeof(struct Pointer_to_Linked_List));
	newLL->head = NULL;
	return newLL;
}
void Destroy_LL(Linked_List_Opaque_Pointer * Pointer_to_Linked_List) {
	struct Linked_List_Node * Current_Linked_List_Node = (*Pointer_to_Linked_List)->head;
	while (Current_Linked_List_Node != NULL) {
		struct Linked_List_Node * Temp = Current_Linked_List_Node->next;
		free(Current_Linked_List_Node);
		Current_Linked_List_Node = Temp;
	} 
	free(*Pointer_to_Linked_List);
	(*Pointer_to_Linked_List) = NULL;
}
void* Priority_LL_Insert_(Linked_List_Opaque_Pointer * Pointer_to_LL, void* Item, int Priority) {
	struct Linked_List_Node * Head_Node = (*Pointer_to_LL)->head;
	struct Linked_List_Node* CurrItem = Head_Node;
	int Position = 0;
	while (Priority < CurrItem->Priority) {
		Position++;
		CurrItem = CurrItem->next;
		if (CurrItem == NULL) {
			break;
		}
	}
	LL_Insert(Pointer_to_LL, Item, Position, Priority);
}
void* LL_Insert(Linked_List_Opaque_Pointer * Pointer_to_LL, void* Item, int Position, int priority) {
	struct Linked_List_Node * Insert_Node = (struct Linked_List_Node*)malloc(sizeof(struct Linked_List_Node));//make a Linked List Node Space and set it equal to the head
	Insert_Node->item = Item;
	Insert_Node->Priority = priority;
	Insert_Node->next = NULL;
	struct Linked_List_Node * Head_Node = (*Pointer_to_LL)->head;
	if (Position > LL_Length(*Pointer_to_LL)) {
		printf("Tring to insert at index ouside of list, try inserting at position %d", LL_Length(*Pointer_to_LL));
	}
	else if (Position == 0) {
		Insert_Node->next = Head_Node;
		(*Pointer_to_LL)->head = Insert_Node;
	}
	else if (Position != 0 && Position == LL_Length(*Pointer_to_LL)) {
		struct Linked_List_Node * Current_Node = (*Pointer_to_LL)->head;
		while (Current_Node->next != NULL) {
			Current_Node = Current_Node->next;
		}
		Current_Node->next = Insert_Node;
	}
	else {
		printf("Inserting Somewhere else \n");
		struct Linked_List_Node * Prev_Node = (*Pointer_to_LL)->head;
		struct Linked_List_Node * Next_Node = Prev_Node->next;
		int Current_Position = 0;
		while (Current_Position < Position - 1) {
			Prev_Node = Next_Node;
			Next_Node = Next_Node->next;
			Current_Position = Current_Position + 1;
		}
		Prev_Node->next = Insert_Node;
		Insert_Node->next = Next_Node;
	}
	return Item;

}
int LL_Length(const Linked_List_Opaque_Pointer s) {
	int length = 0;
	struct Linked_List_Node * Current_Node = (s)->head;
	while (Current_Node != NULL) {
		Current_Node = Current_Node->next;
		length++;
	}
	return length;
}
void* LL_Find_By_Index(const Linked_List_Opaque_Pointer s, int index) {
	if (index > LL_Length(s)) {//the mems
		printf("Index out of bounds, Last index is %d", LL_Length(s));
	}
	struct Linked_List_Node * Current_Node = s->head;
	for (int i = 0; i < index; i++) {
		Current_Node = Current_Node->next;
	}
	return Current_Node->item;
}