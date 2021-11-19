#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"

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
    struct node *current = head;
    while (current != NULL)
    {
        wait += currentTime;
        response += currentTime;
        turnaround += (currentTime + current->task->burst);
        run(current->task, current->task->burst);
        currentTime += current->task->burst;
        current = current->next;
        total++;
    }
    printf("\n");
    printf("Average waiting time = %.2f\n", (double)wait / total);          //all wait times till last item / total
    printf("Average turnaround time = %.2f\n", (double)turnaround / total); //all finish time - start time / total
    printf("Average response time = %.2f\n", (double)response / total);     //time to execute each program / total
}