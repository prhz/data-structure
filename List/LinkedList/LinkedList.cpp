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
	ENode *next;
}*LinkedList;
// ��ͷ���

bool Initial(LinkedList &list); // ��ʼ������
bool Clear(LinkedList &list);	// ����б�
bool Destroy(LinkedList &list); // �����б�

bool Insert(LinkedList &list, int index, ElemType elem);					// �������
bool Append(LinkedList &list, ElemType elem);								// ׷�Ӳ���

bool Delete(LinkedList &list, int index, ElemType &elem);					// ɾ������
bool DeleteAllByElem(LinkedList &list, ElemType elem);						// ɾ���б������е�ָ��Ԫ��

bool ModifyElemByIndex(LinkedList &list, int index, ElemType elem);			// ͨ�������޸�Ԫ��
bool ModifyAllByElem(LinkedList &list, ElemType oldElem, ElemType newElem);	// �޸����о�Ԫ�ر�Ϊ��Ԫ��

bool GetElemByIndex(LinkedList list, int index, ElemType &elem);			// ͨ���������Ԫ��	
int GetIndexByElem(LinkedList list, ElemType elem);							// ͨ��Ԫ�ػ������


int GetLength(LinkedList list);				// ���ص�ǰ��С
int GetMaxSize(LinkedList list);

bool IsEmpty(LinkedList list);				// �пղ���
bool Equal(ElemType elem1, ElemType elem2); // ��ֵ�ж�
void toString(LinkedList list);				// ��ӡ����



int main()
{
	LinkedList list;
	Initial(list);
	toString(list);
	return 0;
}
/**
*	�������
*/
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
	list->Length = 0;
	list->MaxSize = MAX_SIZE;
	list->next = NULL;
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
	return (list->next == NULL);
}