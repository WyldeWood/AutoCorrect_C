#pragma once
//returns -1 if nothing is found that matches 
#ifndef Linked_List
#define Linked_List

typedef struct Pointer_to_Linked_List * Linked_List_Opaque_Pointer;//opaque pointer Hides how the struct actually works from user

Linked_List_Opaque_Pointer Create_LL();//creates linked list

void Destroy_LL(Linked_List_Opaque_Pointer* s);//destroys linked list, returns 1 if it worked and 0 if it didnt
void* LL_Insert(Linked_List_Opaque_Pointer * Pointer_to_LL, void* Item, int Position);
int LL_Length(const Linked_List_Opaque_Pointer s);

void* LL_Find_By_Index(const Linked_List_Opaque_Pointer s, int index);



#endif 