#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "LinkedList.cpp"

//===========================Helper Function Definition================================
void insert(long unsortedList[], long sortedList[], int length)
{
    int index;
    for(int i = 0; i < length; ++i)
    {
        sortedList[i] = unsortedList[i];
        index = i;
        while(index > 0 && sortedList[index] < sortedList[index - 1])
        {
            long temp = sortedList[index];
            sortedList[index] = sortedList[index - 1];
            sortedList[index - 1] = temp;
            index--;
        }
    }
}

shared_ptr<ListItem<long>> mergeList(shared_ptr<ListItem<long>> &listOne, shared_ptr<ListItem<long>> &listTwo)
{
    shared_ptr<ListItem<long>> sortedList = NULL;
    if(listTwo == NULL && listOne != NULL)
    {
        return listOne;
    }
    else if(listOne == NULL && listTwo != NULL)
    {
        return listTwo;
    }
    if(listOne->value < listTwo->value)
    {
        sortedList = listOne;
        sortedList->next = mergeList(listOne->next, listTwo);
        return sortedList;
    }
    else
    {
        sortedList = listTwo;
        sortedList->next = mergeList(listOne, listTwo->next);
        return sortedList;
    }
}

void splitList(shared_ptr<ListItem<long>> &list, int length)
{
    if(length == 1)
    {
        return;
    }
    shared_ptr<ListItem<long>> listOne = list;
    shared_ptr<ListItem<long>> listTwo = list;
    int middle = length/2;
    for(int i = 0; i < middle; ++i)
    {
        listTwo = listTwo->next;
    }
    listTwo->prev->next = NULL;
    listTwo->prev = NULL;
    splitList(listOne, middle);
    splitList(listTwo, length - middle);
    list = mergeList(listOne, listTwo);
}
//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    int length = nums.size();
    long unsortedList[length];
    long sortedList[length];
    vector<long> numsSorted;
	for(int i = 0; i < length; ++i)
    {
        unsortedList[i] = nums[i];
    }
    insert(unsortedList, sortedList, length);
    for(int i = 0; i < length; ++i)
    {
        numsSorted.insert(numsSorted.begin() + i, sortedList[i]);
    }
    return numsSorted;
}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
	int length = nums.size();
    LinkedList<long> unsortedList;
    vector<long> numsSorted;
    for(int i = length - 1; i >= 0; --i)
    {
        unsortedList.insertAtHead(nums[i]);
    }
    shared_ptr<ListItem<long>> listHead = unsortedList.getHead();
    splitList(listHead, length);
    while(listHead != NULL)
    {
        numsSorted.push_back(listHead->value);
        listHead = listHead->next;
    }
    return numsSorted;
}

//=====================================================================================
//==============================Helper Functions=======================================


#endif