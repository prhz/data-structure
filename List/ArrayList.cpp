#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERROR 1  // �ڴ�����ʧ��

#define INIT_SIZE 16 // ��ʼ��Ϊ16 ������ÿ�η���

typedef struct{
	int Key;
	int Value;
}ElemType;			// ��������

typedef struct{
	ElemType *data;
	int MaxSize;
	int Length;
}ArrayList;			// �����б�


bool Initial(ArrayList &list);				// ��ʼ�����Ա�
bool Clear(ArrayList &list);				// ����б�
bool Destroy(ArrayList &list);				// �������Ա�

bool Insert(ArrayList &list, int index, ElemType elem);						// �������
bool Append(ArrayList &list, ElemType elem);								// ׷�Ӳ���

bool Delete(ArrayList &list, int index, ElemType &elem);					// ɾ������
bool DeleteAllByElem(ArrayList &list, ElemType elem);						// ɾ���б������е�ָ��Ԫ��

bool ModifyElemByIndex(ArrayList &list, int index, ElemType elem);			// ͨ�������޸�Ԫ��
bool ModifyAllByElem(ArrayList &list, ElemType oldElem, ElemType newElem);	// �޸����о�Ԫ�ر�Ϊ��Ԫ��

bool GetElemByIndex(ArrayList list, int index, ElemType &elem);				// ͨ���������Ԫ��	
int GetIndexByElem(ArrayList list, ElemType elem);							// ͨ��Ԫ�ػ������


int GetLength(ArrayList list);				// ���ص�ǰ��С
int GetMaxSize(ArrayList list);				// �����������


bool IsEmpty(ArrayList list);				// �пղ���
bool Equal(ElemType elem1, ElemType elem2); // ��ֵ�ж�
void toString(ArrayList list);				// ��ӡ����

bool Extends(ArrayList &list, int times);	// ��չ���Ա�


int main()
{
	return 0;
}
/**
*	����Ԫ��
*/

// 0 1 2 3 4 5 6 7 8 9 
bool Insert(ArrayList &list, int index, ElemType elem)
{
	if(GetLength(list) >= GetMaxSize(list))
	{
		Extends(list, 2); // ����
	}
	if(index < 0 || index > GetLength(list))
	{
		return false;
	}
	for(int i = GetLength(list); i > index; i--)
	{
		list.data[i] = list.data[i-1];	
	}
	list.data[index] = elem; 
	
	list.Length ++;
	
	return true;
}
bool Append(ArrayList &list, ElemType elem)
{
	bool b = Insert(list, GetLength(list), elem);
	return b;
}	

/**
*	ɾ��Ԫ�أ����Ҵ���ɾ����Ԫ��
*/
// 0 1 2 3 4 5 6 7 8 9 
bool Delete(ArrayList &list, int index, ElemType &elem)
{
	if(index < 0 || index >= GetLength(list))
	{
		return false;
	}
	elem = list.data[index]; // ȡ��ɾ����Ԫ��

	for(int i = index; i < GetLength(list)-1; i++)
	{
		list.data[i] = list.data[i+1];
	}
	list.Length --;
	return true;
}
bool DeleteAllByElem(ArrayList &list, ElemType elem)
{
	ElemType temp;
	bool b;
	int index;
	while((index = GetIndexByElem(list, elem)) >= 0)
	{
		 b = Delete(list, index, temp);		
	}
	return b;		
}

/**
*	������������Ԫ��
*/
bool GetElemByIndex(ArrayList list, int index, ElemType &elem)
{
	if(index < 0 || index >= GetLength(list))
	{
		return false;
	}
	elem = list.data[index];
	return true;
}
/**
*	����Ԫ�ط�������
*/
int GetIndexByElem(ArrayList list, ElemType elem)
{
	int index = -1;
	for(int i = 0; i < GetLength(list); i++)
	{
		
		if(Equal(list.data[i], elem))
		{
			index = i;
			break;
		}
	}
	return index;
}

/**
*	���������޸�Ԫ��
*/
bool ModifyElemByIndex(ArrayList &list, int index, ElemType elem)
{
	if(index < 0 || index >= GetLength(list))
	{
		return false;
	}
	list.data[index] = elem; // ����������
//	list.data[index].Key = elem.Key;
//	list.data[index].Value = elem.Value;
	return true;
}
/**
*	�޸����еľ�Ԫ�ر�Ϊ��Ԫ��
*/
bool ModifyAllByElem(ArrayList &list, ElemType oldElem, ElemType newElem)
{
	for(int i = 0; i <= GetLength(list); i++)
	{
		if(Equal(oldElem, newElem))
		{
			list.data[i] = newElem;
		}
	}
	return true;
}

/**
*	��ʼ���б�
*/
bool Initial(ArrayList &list)
{
	list.data = (ElemType *)malloc(sizeof(ElemType)*INIT_SIZE);
	if(!list.data){
		exit(MEM_ERROR); // �洢����ʧ��
	}
	memset(list.data, 0, sizeof(ElemType)*INIT_SIZE); // ��ʼ��0
	list.MaxSize = INIT_SIZE;			// ��󳤶�
	list.Length = 0;					// ��ǰ����
	return true;
}
/**
*	���ݲ�����ÿ�ν��鷭��
*/
bool Extends(ArrayList &list, int times)
{
	ElemType *old_p = list.data;
	
	int len = sizeof(ElemType) * list.MaxSize * times; // �µĳ���
	
	list.data = (ElemType *)malloc(len);
	if(!list.data)
	{
		exit(MEM_ERROR);
	}
	memset(list.data, 0, len);					// ����ռ䲢��ʼ��
	
	list.MaxSize *= times;
	
	for(int i = 0; i < list.Length; i++)
	{
		list.data[i] = old_p[i];
	}

	free(old_p);							//�ͷžɵĿռ�

	return true; 	
}
/**
*	����б�
*/
bool Clear(ArrayList &list)
{	
	Destroy(list);
	bool b = Initial(list);
	return b;
}

/**
*	�����б�
*/
bool Destroy(ArrayList &list)
{
	free(list.data);
	list.data = NULL;
	list.Length = 0;
	list.MaxSize = 0;

	return true;
}
/**
*	��ȡ��ǰ����
*/
int GetLength(ArrayList list)
{
	int len = (list.Length >= 0) ? list.Length : 0;
	return len;
}
/**
*	��ȡ�������
*/
int GetMaxSize(ArrayList list)
{
	int Msize = (list.MaxSize >= 0) ? list.MaxSize : 0;
	return Msize;
}

/**
*	�пղ���
*/
bool IsEmpty(ArrayList list)
{
	if(GetLength(list) > 0){
		return false;
	}
	return true;	
}
bool Equal(ElemType elem1, ElemType elem2)
{
	if(elem1.Key == elem2.Key && elem1.Value == elem2.Value){
		return true;
	}
	return false;
}	
/**
*	�����Ϣ
*/
void toString(ArrayList list)
{
	printf("Type: ArrayList\n");
	printf("MaxSize: %d, Length: %d\n", GetMaxSize(list), GetLength(list));
	printf("data: [");
	for(int i = 0; i < GetLength(list); i++)
	{	
		
		if(i == (GetLength(list)-1))
		{
			printf("%d", list.data[i].Key);
		}else{
			printf("%d, ", list.data[i].Key);
		}
	}
	printf("]\n");
}


