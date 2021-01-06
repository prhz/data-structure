#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERROR 1  // 内存申请失败

#define INIT_SIZE 16 // 初始化为16 ，扩容每次翻倍

typedef struct{
	int Key;
	int Value;
}ElemType;			// 基本类型

typedef struct{
	ElemType *data;
	int MaxSize;
	int Length;
}ArrayList;			// 数组列表


bool Initial(ArrayList &list);				// 初始化线性表
bool Clear(ArrayList &list);				// 清空列表
bool Destroy(ArrayList &list);				// 销毁线性表

bool Insert(ArrayList &list, int index, ElemType elem);						// 插入操作
bool Append(ArrayList &list, ElemType elem);								// 追加操作

bool Delete(ArrayList &list, int index, ElemType &elem);					// 删除操作
bool DeleteAllByElem(ArrayList &list, ElemType elem);						// 删除列表中所有的指定元素

bool ModifyElemByIndex(ArrayList &list, int index, ElemType elem);			// 通过索引修改元素
bool ModifyAllByElem(ArrayList &list, ElemType oldElem, ElemType newElem);	// 修改所有旧元素变为新元素

bool GetElemByIndex(ArrayList list, int index, ElemType &elem);				// 通过索引获得元素	
int GetIndexByElem(ArrayList list, ElemType elem);							// 通过元素获得索引


int GetLength(ArrayList list);				// 返回当前大小
int GetMaxSize(ArrayList list);				// 返回最大容量


bool IsEmpty(ArrayList list);				// 判空操作
bool Equal(ElemType elem1, ElemType elem2); // 等值判断
void toString(ArrayList list);				// 打印内容

bool Extends(ArrayList &list, int times);	// 扩展线性表


int main()
{
	return 0;
}
/**
*	插入元素
*/

// 0 1 2 3 4 5 6 7 8 9 
bool Insert(ArrayList &list, int index, ElemType elem)
{
	if(GetLength(list) >= GetMaxSize(list))
	{
		Extends(list, 2); // 扩充
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
*	删除元素，并且带回删除的元素
*/
// 0 1 2 3 4 5 6 7 8 9 
bool Delete(ArrayList &list, int index, ElemType &elem)
{
	if(index < 0 || index >= GetLength(list))
	{
		return false;
	}
	elem = list.data[index]; // 取得删除的元素

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
*	根据索引查找元素
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
*	根据元素返回索引
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
*	根据索引修改元素
*/
bool ModifyElemByIndex(ArrayList &list, int index, ElemType elem)
{
	if(index < 0 || index >= GetLength(list))
	{
		return false;
	}
	list.data[index] = elem; // ？？？？？
//	list.data[index].Key = elem.Key;
//	list.data[index].Value = elem.Value;
	return true;
}
/**
*	修改所有的旧元素变为新元素
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
*	初始化列表
*/
bool Initial(ArrayList &list)
{
	list.data = (ElemType *)malloc(sizeof(ElemType)*INIT_SIZE);
	if(!list.data){
		exit(MEM_ERROR); // 存储分配失败
	}
	memset(list.data, 0, sizeof(ElemType)*INIT_SIZE); // 初始化0
	list.MaxSize = INIT_SIZE;			// 最大长度
	list.Length = 0;					// 当前长度
	return true;
}
/**
*	扩容操作，每次建议翻倍
*/
bool Extends(ArrayList &list, int times)
{
	ElemType *old_p = list.data;
	
	int len = sizeof(ElemType) * list.MaxSize * times; // 新的长度
	
	list.data = (ElemType *)malloc(len);
	if(!list.data)
	{
		exit(MEM_ERROR);
	}
	memset(list.data, 0, len);					// 申请空间并初始化
	
	list.MaxSize *= times;
	
	for(int i = 0; i < list.Length; i++)
	{
		list.data[i] = old_p[i];
	}

	free(old_p);							//释放旧的空间

	return true; 	
}
/**
*	清空列表
*/
bool Clear(ArrayList &list)
{	
	Destroy(list);
	bool b = Initial(list);
	return b;
}

/**
*	销毁列表
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
*	获取当前长度
*/
int GetLength(ArrayList list)
{
	int len = (list.Length >= 0) ? list.Length : 0;
	return len;
}
/**
*	获取最大容量
*/
int GetMaxSize(ArrayList list)
{
	int Msize = (list.MaxSize >= 0) ? list.MaxSize : 0;
	return Msize;
}

/**
*	判空操作
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
*	输出信息
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


