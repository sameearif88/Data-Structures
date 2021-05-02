#ifndef LUCKYDRAW_CPP
#define LUCKYDRAW_CPP
#include "luckyDraw.h"
#include "stack.cpp"
#include "queue.cpp"


luckyDraw::luckyDraw(int count)
{
    totalCount = count;
}

//populate lane_1 with the given array of winnersId   
void luckyDraw::populateQueue(int* winnersId)
{
    for(int i = 0; i < totalCount; ++i)
    {
        lane_1.enqueue(*(winnersId + i));
    }
}

//populate table_1 with the given array of giftsId   
void luckyDraw::populateTable(int* giftsId)
{
    for(int i =  0; i < totalCount; ++i)
    {
        table_1.push(*(giftsId + i));
    }
}

//reverse the queue keeping the conditions in mind
void luckyDraw::reverseQueue()
{
    while(!lane_1.isEmpty())
    {
        for(int i = 0; i < lane_1.length() - 1; ++i)
        {
            lane_1.enqueue(lane_1.dequeue());
        }
        lane_2.enqueue(lane_1.dequeue());
    }
    while(!lane_2.isEmpty())
    {
        lane_1.enqueue(lane_2.dequeue());
    }
}

//transfer the stack keeping the conditions in mind
void luckyDraw::transferStack()
{
    for(int i = 0; i < totalCount; ++i)
    {
        while(table_1.length() != 1)
        {
            table_2.push(table_1.pop());
        }
        specialVariable = table_1.pop();
        while(table_2.length() != i)
        {
            table_1.push(table_2.pop());
        }
        table_2.push(specialVariable);
    }
}

#endif