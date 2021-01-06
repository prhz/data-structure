#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERROR 1  // ÄÚ´æÉêÇëÊ§°Ü
#define MAX_SIZE 255

typedef struct{
	int Key;
	int Value;
}ElemType;			// »ù±¾ÀàÐÍ

typedef struct ENode{
	ElemType elem;
	ENode *next;
}ENode;

typedef struct HNode{
	int Length;
	int MaxSize;
	ENode *Head;
}*LinkedList;
// ´øÍ·½áµã

bool Initial(LinkedList &list); // ³õÊ¼»¯Á´±í
bool Clear(LinkedList &list);	// Çå¿ÕÁÐ±í
bool Destroy(LinkedList &list); // Ïú»ÙÁÐ±í

bool Insert(LinkedList &list, int index, ElemType elem);					// ²åÈë²Ù×÷
bool Append(LinkedList &list, ElemType elem);								// ×·¼Ó²Ù×÷
bool InsertPrior(LinkedList &list, ENode *node, ElemType elem);							// Ç°²å
bool InsertNext(LinkedList &list, ENode *node, ElemType elem);							// ºó²å

bool Delete(LinkedList &list, int index, ElemType &elem);					// É¾³ý²Ù×÷
bool DeleteAllByElem(LinkedList &list, ElemType elem);						// É¾³ýÁÐ±íÖÐËùÓÐµÄÖ¸¶¨ÔªËØ
bool DeleteNode(LinkedList &list, ENode *node);								// É¾³ý½Úµã

bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem);			// Í¨¹ýË÷ÒýÐÞ¸ÄÔªËØ
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem);	// ÐÞ¸ÄËùÓÐ¾ÉÔªËØ±äÎªÐÂÔªËØ

bool GetElemByIndex(LinkedList list, int index, ElemType &elem);			// Í¨¹ýË÷Òý»ñµÃÔªËØ	
int GetIndexByElem(LinkedList list, ElemType elem);							// Í¨¹ýÔªËØ»ñµÃË÷Òý
bool GetNodeByIndex(LinkedList list, int index, ENode* &node);
bool GetNodeByElem(LinkedList list, ElemType elem, ENode* &node);
int GetLength(LinkedList list);				// ·µ»Øµ±Ç°´óÐ¡
int GetMaxSize(LinkedList list);

bool IsEmpty(LinkedList list);				// ÅÐ¿Õ²Ù×÷
bool Equal(ElemType elem1, ElemType elem2); // µÈÖµÅÐ¶Ï
void toString(LinkedList list);				// ´òÓ¡ÄÚÈÝ
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
/**
*	Ïú»ÙÁ´±í  TODO
*/
bool Destroy(LinkedList &list)
{
	// Ò»¸öÒ»¸öÔªËØÏú»Ù
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
/**
*	·µ»Ø½ÚµãË÷Òý
*/
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
	if(index < -1 || index > GetLength(list)) // Ë÷ÒýÅÐ¶ÏÊÇ·ñºÏ·¨
	{
		return false;
	}
// head -> NULL	
// head -> 0 -> 1 -> 2 -> 3 -> NULL
	ENode *p = list->Head;
	int current = -1;
	while(p!=NULL && current < index) // ²éÕÒ Ë÷Òý index ËùÔÚµÄ½Úµã
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
/**
*	¸ù¾ÝË÷ÒýÕÒµ½½Úµã
*/
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
/**
*	ÊÇ·ñ°üº¬Ö¸¶¨½Úµã
*/
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

/**
*	×·¼Ó²Ù×÷
*/
bool Append(LinkedList &list, ElemType elem)
{
	bool b = Insert(list, GetLength(list), elem);
	return b;
}
/**
*	²åÈë²Ù×÷
*/
bool Insert(LinkedList &list, int index, ElemType elem)
{
	ENode *p;
	if(GetNodeByIndex(list, index-1,p))
	{
		return InsertNext(list,p, elem);
	}
	return false;
}

// head -> 0 -> 1 -> 2 -> 3 -> NULL
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
/**
*	É¾³ý Ë÷ÒýÎª index µÄ½Úµã
*/
// List : Head -> NULL	
bool Delete(LinkedList &list, int index, ElemType &elem)
{
	ENode *p;
	if(GetNodeByIndex(list, index-1, p)){
		// p Îª index-1 ½Úµã
		ENode *dNode = p->next;
		if(p->next == NULL){
			return false;
		}
		elem = dNode->elem; // ·µ»Ø´ËÔªËØ
	
		p->next = dNode->next;
		free(dNode);
		list->Length --;
		return true;
	}
	return false;

}
/**
*	Ç°²å²Ù×÷
*/
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
/**
*	ºó²å²Ù×÷
*/
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
/**
*	Êä³ö
*/
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

/**
*	»ñÈ¡³¤¶È
*/
int GetLength(LinkedList list)
{
	int len = (list->Length >= 0) ? list->Length : 0;
	return len;
}
/**
*	»ñÈ¡×î´óSize
*/
int GetMaxSize(LinkedList list)
{
	int Msize = (list->MaxSize >= 0) ? list->MaxSize : 0;
	return Msize;
}

/**
*	³õÊ¼»¯Á´±í
*/
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
/**
*	µÈÖµÅÐ¶Ï
*/
bool Equal(ElemType elem1, ElemType elem2)
{
	if(elem1.Key == elem2.Key && elem1.Value == elem2.Value){
		return true;
	}
	return false;
}
/**
*	ÅÐ¿Õ²Ù×÷
*/
bool IsEmpty(LinkedList list)
{
	return (list->Length == 0);
}
