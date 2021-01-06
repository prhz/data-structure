#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERROR 1  // 内存申请失败
#define MAX_SIZE 255

typedef struct{
	int Key;
	int Value;
}ElemType;			// 基本类型

typedef struct ENode{
	ElemType elem;
	ENode *next;
}ENode;

typedef struct HNode{
	int Length;
	int MaxSize;
	ENode *Head;
}*LinkedList;
// 带头结点

bool Initial(LinkedList &list); // 初始化链表
bool Clear(LinkedList &list);	// 清空列表
bool Destroy(LinkedList &list); // 销毁列表

bool Insert(LinkedList &list, int index, ElemType elem);					// 插入操作
bool Append(LinkedList &list, ElemType elem);								// 追加操作
bool InsertPrior(LinkedList &list, ENode *node, ElemType elem);							// 前插
bool InsertNext(LinkedList &list, ENode *node, ElemType elem);							// 后插

bool Delete(LinkedList &list, int index, ElemType &elem);					// 删除操作
bool DeleteAllByElem(LinkedList &list, ElemType elem);						// 删除列表中所有的指定元素
bool DeleteNode(LinkedList &list, ENode *node);								// 删除节点

bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem);			// 通过索引修改元素
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem);	// 修改所有旧元素变为新元素

bool GetElemByIndex(LinkedList list, int index, ElemType &elem);			// 通过索引获得元素	
int GetIndexByElem(LinkedList list, ElemType elem);							// 通过元素获得索引
bool GetNodeByIndex(LinkedList list, int index, ENode* &node);
bool GetNodeByElem(LinkedList list, ElemType elem, ENode* &node);
int GetLength(LinkedList list);				// 返回当前大小
int GetMaxSize(LinkedList list);

bool IsEmpty(LinkedList list);				// 判空操作
bool Equal(ElemType elem1, ElemType elem2); // 等值判断
void toString(LinkedList list);				// 打印内容
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
*	销毁链表  TODO
*/
bool Destroy(LinkedList &list)
{
	// 一个一个元素销毁
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
*	返回节点索引
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
	if(index < -1 || index > GetLength(list)) // 索引判断是否合法
	{
		return false;
	}
// head -> NULL	
// head -> 0 -> 1 -> 2 -> 3 -> NULL
	ENode *p = list->Head;
	int current = -1;
	while(p!=NULL && current < index) // 查找 索引 index 所在的节点
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
*	根据索引找到节点
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
*	是否包含指定节点
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
*	追加操作
*/
bool Append(LinkedList &list, ElemType elem)
{
	bool b = Insert(list, GetLength(list), elem);
	return b;
}
/**
*	插入操作
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
*	删除 索引为 index 的节点
*/	
bool Delete(LinkedList &list, int index, ElemType &elem)
{
	ENode *p;
	if(GetNodeByIndex(list, index-1, p)){
		// p 为 index-1 节点
		ENode *dNode = p->next;
		elem = dNode->elem; // 返回此元素
	
		p->next = dNode->next;
		free(dNode);
		list->Length --;
		return true;
	}
	return false;

}
/**
*	前插操作
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
*	后插操作
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
*	输出
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
*	获取长度
*/
int GetLength(LinkedList list)
{
	int len = (list->Length >= 0) ? list->Length : 0;
	return len;
}
/**
*	获取最大Size
*/
int GetMaxSize(LinkedList list)
{
	int Msize = (list->MaxSize >= 0) ? list->MaxSize : 0;
	return Msize;
}

/**
*	初始化链表
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
*	等值判断
*/
bool Equal(ElemType elem1, ElemType elem2)
{
	if(elem1.Key == elem2.Key && elem1.Value == elem2.Value){
		return true;
	}
	return false;
}
/**
*	判空操作
*/
bool IsEmpty(LinkedList list)
{
	return (list->Length == 0);
}
