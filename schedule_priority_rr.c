#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"

#define quantum 10
int position = 0;
struct node *head;

void add(char name[2], int priority, int burst)
{
    if (position == 0)
    {
        head = malloc(sizeof(struct node));
        struct task *newTask = malloc(sizeof(struct task));
        newTask->name = name;
        newTask->priority = priority;
        newTask->burst = burst;
        head->task = newTask;
        position++;
    }
    else
    {
        struct task *newTask = malloc(sizeof(struct task));
        newTask->name = name;
        newTask->priority = priority;
        newTask->burst = burst;
        if (newTask->priority > head->task->priority)
        {
            struct node *newNode = malloc(sizeof(struct node));
            newNode->task = newTask;
            newNode->next = head;
            head = newNode;
        }
        else
        {
            struct node *current = head;
            while (current->next != NULL && current->next->task->priority >= newTask->priority)
            {
                current = current->next;
            }
            struct node *temp = malloc(sizeof(struct node));
            temp = current->next;
            struct node *newNode = malloc(sizeof(struct node));
            newNode->task = newTask;
            current->next = newNode;
            newNode->next = temp;
        }
        position++;
    }
}
void schedule()
{
    int wait = 0;
    int turnaround = 0;
    int response = 0;
    int currentTime = 0;
    int total = 0;
    int responded = head->task->priority;
    struct node *current = head;
    while (head != NULL)
    {
        while (current != NULL)
        {
            if ((head != NULL && head->next != NULL && head->task->priority > head->next->task->priority) || (head != NULL && head->next == NULL))
            {
                while ((head != NULL && head->next != NULL && head->task->priority > head->next->task->priority) || (head != NULL && head->next == NULL))
                {
                    if (responded == head->task->priority)
                    {
                        response += currentTime;
                    }
                    turnaround += (currentTime + head->task->burst);
                    wait += currentTime;
                    run(head->task, head->task->burst);
                    currentTime += head->task->burst;
                    responded = head->task->priority - 1;
                    delete (&head, head->task);
                    total++;
                }
                current = head;
            }
            if (current != NULL && current->task->burst >= quantum)
            {
                if (responded == head->task->priority)
                {
                    response += currentTime;
                }
                run(current->task, quantum);
                current->task->burst -= quantum;
                if (current->task->burst == 0)
                {
                    turnaround += (currentTime + quantum);
                    wait += currentTime;
                    delete (&head, current->task);
                    total++;
                }
                else
                {
                    wait -= quantum;
                }
                currentTime += quantum;
            }
            else if (current != NULL)
            {
                if (responded == head->task->priority)
                {
                    response += currentTime;
                }
                turnaround += (currentTime + current->task->burst);
                wait += currentTime;
                run(current->task, current->task->burst);
                currentTime += current->task->burst;
                delete (&head, current->task);
                total++;
            }
            if (head != NULL && current->next != NULL && current->task->priority > current->next->task->priority)
            {
                responded = head->task->priority - 1;
                current = head;
            }
            else if (current != NULL)
            {
                current = current->next;
            }
        }
        current = head;
    }
    printf("\n");
    printf("Average waiting time = %.2f\n", (double)wait / total);          //all wait times till last item / total
    printf("Average turnaround time = %.2f\n", (double)turnaround / total); //all finish time - start time / total
    printf("Average response time = %.2f\n", (double)response / total);     //time to execute each program / total
}