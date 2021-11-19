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
        insert(&head, newTask);
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
    int responded = 0;
    struct node *current = head;
    while (head != NULL)
    {
        while (current != NULL)
        {
            if (current->task->burst >= quantum)
            {
                if (responded == 0)
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
            else
            {
                if (responded == 0)
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
            current = current->next;
        }
        if (head != NULL && head->next == NULL)
        {
            if (responded == 0)
            {
                response += currentTime;
            }
            turnaround += (currentTime + head->task->burst);
            wait += currentTime;
            run(head->task, head->task->burst);
            currentTime += head->task->burst;
            delete (&head, head->task);
            total++;
        }
        responded = 1; //once the loop completes all the programs have been ran atleast once
        current = head;
    }
    printf("\n");
    printf("Average waiting time = %.2f\n", (double)wait / total);          //all wait times till last item / total
    printf("Average turnaround time = %.2f\n", (double)turnaround / total); //all finish time - start time / total
    printf("Average response time = %.2f\n", (double)response / total);     //time to execute each program / total
}