#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERROR 1  
#define MAX_SIZE 255

typedef struct{
	int Key;
	int Value;
}ElemType;			

typedef struct ENode{
	ElemType elem;
	ENode *next;
}ENode;

typedef struct HNode{
	int Length;
	int MaxSize;
	ENode *Head;
}*LinkedList;


bool Initial(LinkedList &list); 
bool Clear(LinkedList &list);	
bool Destroy(LinkedList &list); 

bool Insert(LinkedList &list, int index, ElemType elem);					
bool Append(LinkedList &list, ElemType elem);								
bool InsertPrior(LinkedList &list, ENode *node, ElemType elem);							
bool InsertNext(LinkedList &list, ENode *node, ElemType elem);							

bool Delete(LinkedList &list, int index, ElemType &elem);					
bool DeleteAllByElem(LinkedList &list, ElemType elem);						
bool DeleteNode(LinkedList &list, ENode *node);								

bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem);			
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem);	

bool GetElemByIndex(LinkedList list, int index, ElemType &elem);			
int GetIndexByElem(LinkedList list, ElemType elem);							
bool GetNodeByIndex(LinkedList list, int index, ENode* &node);
bool GetNodeByElem(LinkedList list, ElemType elem, ENode* &node);
int GetLength(LinkedList list);				
int GetMaxSize(LinkedList list);

bool IsEmpty(LinkedList list);				
bool Equal(ElemType elem1, ElemType elem2); 
void toString(LinkedList list);				
bool ContainNode(LinkedList list, ENode *node);


int main()
{
	LinkedList list;
	Initial(list);
	toString(list);
	ElemType temp;
	ElemType elem;
	elem.Key = 1;
	elem.Value=100;

	ElemType elem2;
	elem2.Key = 2;
	elem2.Value=200;

	Insert(list,0,elem);
	Insert(list,1,elem);
	Append(list,elem2);
	Append(list,elem2);
	toString(list);

	Destroy(list);

	toString(list);

	return 0;
}
bool Clear(LinkedList &list)
{
	ElemType temp;
	while(Delete(list, 0, temp)){
		printf("%d\n", list->Length);
	};
	return true;
}

bool Destroy(LinkedList &list)
{
	
	Clear(list);
	list->Head = NULL;
	list->Length = 0;
	list->MaxSize = 0;
	return true; 
}
bool GetNodeByElem(LinkedList list, ElemType elem, ENode* &node)
{
	ENode *p = list->Head;
	while((p=p->next)!=NULL && !Equal(p->elem, elem));
	node = p;
	if(node!=NULL){
		return true;
	}
	return false;
}
bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem)
{
	ENode * temp=NULL;
	GetNodeByIndex(list, index, temp);
	if(temp != NULL)
	{
		temp->elem = elem;
		return true;
	}
	return false;
}
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem)
{
	int index=-1;
	bool b = true;
	while((index = GetIndexByElem(list, oldElem))>=0)
	{
		b = ModifyElemByIndex(list, index, newElem);
	}
	return b;
}

int GetIndexByElem(LinkedList list, ElemType elem)
{
	int index = -1;
	ENode *temp = list->Head;
	while((temp=temp->next)!=NULL)
	{
		index ++;
		if(Equal(temp->elem, elem)){
			return index;
		}
	}
	return -1;
}
bool GetNodeByIndex(LinkedList list, int index, ENode* &node)
{
	if(index < -1 || index > GetLength(list)) 
	{
		return false;
	}

	ENode *p = list->Head;
	int current = -1;
	while(p!=NULL && current < index) 
	{
		p = p->next;
		current ++;
	}
	if(p==NULL)
	{
		return false;
	}
	node = p;
	return true;
}

bool GetElemByIndex(LinkedList list, int index, ElemType &elem)
{
	ENode* node;
	if(GetNodeByIndex(list, index, node))
	{
		elem = node->elem;
		return true;
	}
	return false;
}
bool DeleteAllByElem(LinkedList &list, ElemType elem)
{
	int index = -1;
	ElemType temp;
	bool b = true;
	while((index = GetIndexByElem(list, elem)) >= 0)
	{
		b = Delete(list, index, temp);
	}
	return b;
}

bool ContainNode(LinkedList list, ENode *node)
{
	if(node == NULL || IsEmpty(list))
	{
		return false;
	}
	
	ENode *temp = list->Head;
	while((temp = temp->next) != NULL)
	{
		if(temp == node){
			return true;
		}
	}

	return false;
}


bool Append(LinkedList &list, ElemType elem)
{
	bool b = Insert(list, GetLength(list), elem);
	return b;
}

bool Insert(LinkedList &list, int index, ElemType elem)
{
	ENode *p;
	if(GetNodeByIndex(list, index-1,p))
	{
		return InsertNext(list,p, elem);
	}
	return false;
}


bool DeleteNode(LinkedList &list, ENode *node)
{
	if(ContainNode(list, node))
	{	
		ENode *p = node->next;
		if(p!=NULL){
			node->elem = p->elem;
			node->next = p->next;
			free(p);
			list->Length --;
		}else{
			ElemType temp;
			Delete(list, GetLength(list)-1, temp);
		}
		return true;			
	}
	return false;
}	
	
bool Delete(LinkedList &list, int index, ElemType &elem)
{
	ENode *p;
	if(GetNodeByIndex(list, index-1, p)){
		
		ENode *dNode = p->next;
		if(p->next == NULL){
			return false;
		}
		elem = dNode->elem;
	
		p->next = dNode->next;
		free(dNode);
		list->Length --;
		return true;
	}
	return false;

}

bool InsertPrior(LinkedList &list, ENode *node, ElemType elem)
{
	if(node == NULL)
	{
		return false;
	}
	ENode *pNode = (ENode *)malloc(sizeof(ENode));
	pNode->elem = node->elem;
	pNode->next = node->next;
	node->next = pNode;
	node->elem = elem;

	list->Length ++;
	return true;
}

bool InsertNext(LinkedList &list, ENode *node, ElemType elem)
{
	if(node == NULL)
	{
		return false;
	}

	ENode *pNode = (ENode *)malloc(sizeof(ENode));
	pNode->elem = elem;
	pNode->next = node->next;
	node->next = pNode;

	list->Length ++;
	return true;
}

void toString(LinkedList list)
{
	printf("Type: LinkedList\n");
	printf("Length: %d, MaxSize: %d\n", GetLength(list), GetMaxSize(list));
	printf("Data: [");

	ENode *hNode = list->Head;
	ENode *pNode = hNode;
	while(hNode!=NULL && (pNode=pNode->next)!=NULL)
	{
		if(pNode->next == NULL){
			printf("%d", pNode->elem.Key);
		}else{
			printf("%d, ", pNode->elem.Key);
		}
	}
	printf("]\n");

}


int GetLength(LinkedList list)
{
	int len = (list->Length >= 0) ? list->Length : 0;
	return len;
}

int GetMaxSize(LinkedList list)
{
	int Msize = (list->MaxSize >= 0) ? list->MaxSize : 0;
	return Msize;
}


bool Initial(LinkedList &list)
{
	list = (HNode *)malloc(sizeof(HNode));
	if(list == NULL){
		exit(MEM_ERROR);
	}
	ENode *head = (ENode *)malloc(sizeof(ENode));
	if(head == NULL){
		exit(MEM_ERROR);
	}
	head->next  = NULL;

	list->Length = 0;
	list->MaxSize = MAX_SIZE;
	list->Head = head;
	
	return true;
}

bool Equal(ElemType elem1, ElemType elem2)
{
	if(elem1.Key == elem2.Key && elem1.Value == elem2.Value){
		return true;
	}
	return false;
}

bool IsEmpty(LinkedList list)
{
	return (list->Length == 0);
}
