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
	ENode *next;
}*LinkedList;
// 带头结点

bool Initial(LinkedList &list); // 初始化链表
bool Clear(LinkedList &list);	// 清空列表
bool Destroy(LinkedList &list); // 销毁列表

bool Insert(LinkedList &list, int index, ElemType elem);					// 插入操作
bool Append(LinkedList &list, ElemType elem);								// 追加操作

bool Delete(LinkedList &list, int index, ElemType &elem);					// 删除操作
bool DeleteAllByElem(LinkedList &list, ElemType elem);						// 删除列表中所有的指定元素

bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem);			// 通过索引修改元素
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem);	// 修改所有旧元素变为新元素

bool GetElemByIndex(LinkedList list, int index, ElemType &elem);			// 通过索引获得元素	
int GetIndexByElem(LinkedList list, ElemType elem);							// 通过元素获得索引


int GetLength(LinkedList list);				// 返回当前大小
int GetMaxSize(LinkedList list);

bool IsEmpty(LinkedList list);				// 判空操作
bool Equal(ElemType elem1, ElemType elem2); // 等值判断
void toString(LinkedList list);				// 打印内容



int main()
{
	LinkedList list;
	Initial(list);
	toString(list);
	return 0;
}
/**
*	清空链表
*/
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
void toString(LinkedList list)
{
	printf("Type: LinkedList\n");
	printf("Length: %d, MaxSize: %d\n", GetLength(list), GetMaxSize(list));
	printf("Data: [");

	ENode *pNode;
	while((pNode=list->next)!=NULL)
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
	list->Length = 0;
	list->MaxSize = MAX_SIZE;
	list->next = NULL;
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
	return (list->next == NULL);
}