#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    char description[100];
    int isDone; // 0 = not done, 1 = done
    struct Task* next;
};

// Add a new task
struct Task* addTask(struct Task* head, char desc[]) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    strcpy(newTask->description, desc);
    newTask->isDone = 0;  // New task is not done
    newTask->next = NULL;

    if (head == NULL) {
        return newTask;
    }

    struct Task* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newTask;
    return head;
}

// Print all tasks
void viewTasks(struct Task* head) {
    if (head == NULL) {
        printf("No tasks in your list.\n");
        return;
    }
    int count = 1;
    printf("\nYour To-Do List:\n");
    while (head != NULL) {
        if (head->isDone)
            printf("%d. [✓] %s\n", count, head->description);
        else
            printf("%d. [ ] %s\n", count, head->description);
        head = head->next;
        count++;
    }
}

// Mark a task as done
void markTaskDone(struct Task* head, int taskNumber) {
    int count = 1;
    while (head != NULL) {
        if (count == taskNumber) {
            head->isDone = 1;
            printf("Task %d marked as done.\n", taskNumber);
            return;
        }
        head = head->next;
        count++;
    }
    printf("Invalid task number!\n");
}

// Delete all tasks
struct Task* deleteAll(struct Task* head) {
    struct Task* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("All tasks deleted.\n");
    return NULL;
}

int main() {
    struct Task* head = NULL;
    int choice;
    char input[100];
    int taskNumber;

    do {
        printf("\n--- To-Do List Menu ---\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete All Tasks\n");
        printf("4. Mark Task as Done\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                head = addTask(head, input);
                break;
            case 2:
                viewTasks(head);
                break;
            case 3:
                head = deleteAll(head);
                break;
            case 4:
                viewTasks(head);
                printf("Enter task number to mark as done: ");
                scanf("%d", &taskNumber);
                markTaskDone(head, taskNumber);
                break;
            case 5:
                head = deleteAll(head);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);

    return 0;
}
