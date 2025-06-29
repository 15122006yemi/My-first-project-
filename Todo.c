#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure
struct Task {
    char description[100];
    struct Task* next;
};

// Function to add task
struct Task* addTask(struct Task* head, char desc[]) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    strcpy(newTask->description, desc);
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

// Function to print tasks
void viewTasks(struct Task* head) {
    if (head == NULL) {
        printf("No tasks in your list.\n");
        return;
    }
    int count = 1;
    printf("Your To-Do List:\n");
    while (head != NULL) {
        printf("%d. %s\n", count, head->description);
        head = head->next;
        count++;
    }
}

// Function to delete all tasks
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

    do {
        printf("\n--- To-Do List Menu ---\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete All Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';  // Remove newline
                head = addTask(head, input);
                break;
            case 2:
                viewTasks(head);
                break;
            case 3:
                head = deleteAll(head);
                break;
            case 4:
                head = deleteAll(head); // Free memory before exit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
