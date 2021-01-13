#include <stdio.h>
#include <stdllib.h>
#include <string.h>

#define MEM_ERROR 1;
#define MAX_SIZE 255

typedef struct{
	int Key;
	int Value;
}ElemType;

typedef struct ENode{
	ElemType elem;
	ENode *prior;
	ENode *next;
}ENode;

typedef struct HNode{
	int Length;
	int MaxSize;
	ENode *Head;
}*DeLinkedList;

bool Initial(DeLinkedList &list);
bool Clear(DeLinkedList &list);
bool Destroy(DeLinkedList &list);

bool Insert(DeLinkedList &list, int index, ElemType elem);					
bool Append(DeLinkedList &list, ElemType elem);								
bool InsertPrior(DeLinkedList &list, ENode *node, ElemType elem);							
bool InsertNext(DeLinkedList &list, ENode *node, ElemType elem);						

bool Delete(DeLinkedList &list, int index, ElemType &elem);					
bool DeleteAllByElem(DeLinkedList &list, ElemType elem);						
bool DeleteNode(DeLinkedList &list, ENode *node);								

bool ModifyElemByIndex(DeLinkedList &list, int index, ElemType elem);			
bool ModifyAllByElem(DeLinkedList &list, ElemType oldElem, ElemType newElem);	

bool GetElemByIndex(DeLinkedList list, int index, ElemType &elem);				
int GetIndexByElem(DeLinkedList list, ElemType elem);							
bool GetNodeByIndex(DeLinkedList list, int index, ENode* &node);
bool GetNodeByElem(DeLinkedList list, ElemType elem, ENode* &node);
int GetLength(DeLinkedList list);				
int GetMaxSize(DeLinkedList list);

bool IsEmpty(DeLinkedList list);				
bool Equal(ElemType elem1, ElemType elem2); 
void toString(DeLinkedList list);			
bool ContainNode(DeLinkedList list, ENode *node);
