#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERROR 1  // �ڴ�����ʧ��
#define MAX_SIZE 255

typedef struct{
	int Key;
	int Value;
}ElemType;			// ��������

typedef struct ENode{
	ElemType elem;
	ENode *next;
}ENode;

typedef struct HNode{
	int Length;
	int MaxSize;
	ENode *Head;
}*LinkedList;
// ��ͷ���

bool Initial(LinkedList &list); // ��ʼ������
bool Clear(LinkedList &list);	// ����б�
bool Destroy(LinkedList &list); // �����б�

bool Insert(LinkedList &list, int index, ElemType elem);					// �������
bool Append(LinkedList &list, ElemType elem);								// ׷�Ӳ���
bool InsertPrior(LinkedList &list, ENode *node, ElemType elem);							// ǰ��
bool InsertNext(LinkedList &list, ENode *node, ElemType elem);							// ���

bool Delete(LinkedList &list, int index, ElemType &elem);					// ɾ������
bool DeleteAllByElem(LinkedList &list, ElemType elem);						// ɾ���б������е�ָ��Ԫ��
bool DeleteNode(LinkedList &list, ENode *node);								// ɾ���ڵ�

bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem);			// ͨ�������޸�Ԫ��
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem);	// �޸����о�Ԫ�ر�Ϊ��Ԫ��

bool GetElemByIndex(LinkedList list, int index, ElemType &elem);			// ͨ���������Ԫ��	
int GetIndexByElem(LinkedList list, ElemType elem);							// ͨ��Ԫ�ػ������
bool GetNodeByIndex(LinkedList list, int index, ENode* &node);
bool GetNodeByElem(LinkedList list, ElemType elem, ENode* &node);
int GetLength(LinkedList list);				// ���ص�ǰ��С
int GetMaxSize(LinkedList list);

bool IsEmpty(LinkedList list);				// �пղ���
bool Equal(ElemType elem1, ElemType elem2); // ��ֵ�ж�
void toString(LinkedList list);				// ��ӡ����
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

	Delete(list, 2, temp);
	toString(list);

	return 0;
}
bool Clear(LinkedList &list)
{

	return false;
}
/**
*	��������  TODO
*/
bool Destroy(LinkedList &list)
{
	// һ��һ��Ԫ������
	return false; 
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
*	���ؽڵ�����
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
	if(index < -1 || index > GetLength(list)) // �����ж��Ƿ�Ϸ�
	{
		return false;
	}
// head -> NULL	
// head -> 0 -> 1 -> 2 -> 3 -> NULL
	ENode *p = list->Head;
	int current = -1;
	while(p!=NULL && current < index) // ���� ���� index ���ڵĽڵ�
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
*	���������ҵ��ڵ�
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
*	�Ƿ����ָ���ڵ�
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
*	׷�Ӳ���
*/
bool Append(LinkedList &list, ElemType elem)
{
	bool b = Insert(list, GetLength(list), elem);
	return b;
}
/**
*	�������
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
*	ɾ�� ����Ϊ index �Ľڵ�
*/	
bool Delete(LinkedList &list, int index, ElemType &elem)
{
	ENode *p;
	if(GetNodeByIndex(list, index-1, p)){
		// p Ϊ index-1 �ڵ�
		ENode *dNode = p->next;
		elem = dNode->elem; // ���ش�Ԫ��
	
		p->next = dNode->next;
		free(dNode);
		list->Length --;
		return true;
	}
	return false;

}
/**
*	ǰ�����
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
*	������
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
*	���
*/
void toString(LinkedList list)
{
	printf("Type: LinkedList\n");
	printf("Length: %d, MaxSize: %d\n", GetLength(list), GetMaxSize(list));
	printf("Data: [");

	ENode *hNode = list->Head;
	ENode *pNode = hNode;
	while((pNode=pNode->next)!=NULL)
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
*	��ȡ����
*/
int GetLength(LinkedList list)
{
	int len = (list->Length >= 0) ? list->Length : 0;
	return len;
}
/**
*	��ȡ���Size
*/
int GetMaxSize(LinkedList list)
{
	int Msize = (list->MaxSize >= 0) ? list->MaxSize : 0;
	return Msize;
}

/**
*	��ʼ������
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
*	��ֵ�ж�
*/
bool Equal(ElemType elem1, ElemType elem2)
{
	if(elem1.Key == elem2.Key && elem1.Value == elem2.Value){
		return true;
	}
	return false;
}
/**
*	�пղ���
*/
bool IsEmpty(LinkedList list)
{
	return (list->Length == 0);
}
