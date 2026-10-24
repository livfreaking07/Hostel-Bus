
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure for a student node */
struct Student {
    int id;
    char name[50];
    struct Student *next;
};

/* Front and rear of the queue */
struct Student *front = NULL;
struct Student *rear = NULL;
/* Bus information */
int scheduledTime = 480;  
int estimatedTime = 480;  
int busCapacity = 40;     
int seatsOccupied = 0;    
int totalBoarded = 0;
int busStatus = 0;          
int estimatedArrival = 530; 
char currentLocation[50] = "Hostel";

/* Function to register a student */
void registerStudent() {
    struct Student *newStudent;

    newStudent = malloc(sizeof(struct Student));

    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);

    /* Check for duplicate IDs */
    struct Student *temp = front;

    while (temp != NULL) {
        if (temp->id == newStudent->id) {
            printf("Student ID already registered!\n");
            free(newStudent);
            return;
        }

        temp = temp->next;
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", newStudent->name);

    newStudent->next = NULL;

    /* Insert at the rear of the queue */
    if (front == NULL) {
        front = newStudent;
        rear = newStudent;
    } else {
        rear->next = newStudent;
        rear = newStudent;
    }

    printf("Student registered successfully!\n");
}

/* Function to display the queue */
void displayQueue() {
    struct Student *temp = front;

    if (front == NULL) {
        printf("The boarding queue is empty.\n");
        return;
    }

    printf("\n===== BOARDING QUEUE =====\n");

    while (temp != NULL) {
        printf("Student ID: %d | Name: %s\n",
               temp->id, temp->name);

        temp = temp->next;
    }
}

/* Function to board the first student */
void boardStudent() {
    struct Student *temp;

    if (front == NULL) {
        printf("No students are waiting to board.\n");
        return;
    }
    if (seatsOccupied >= busCapacity) {
    printf("BUS IS FULL! No more boarding allowed.\n");
    return;
}

    temp = front;

    printf("Student boarded: %s (ID: %d)\n",
           temp->name, temp->id);

    front = front->next;
    seatsOccupied++;
    totalBoarded++; 

    if (front == NULL) {
        rear = NULL;
    }

    free(temp);
}

/* Function to display bus status */
void showBusStatus() {
    int delay;

    delay = estimatedTime - scheduledTime;

    printf("\n===== BUS STATUS =====\n");

    printf("Scheduled departure: %02d:%02d\n",
           scheduledTime / 60, scheduledTime % 60);

    printf("Estimated departure: %02d:%02d\n",
           estimatedTime / 60, estimatedTime % 60);

    if (delay < 0) {
        printf("Bus is expected to depart early.\n");
        delay = 0;
    }

    printf("Delay: %d minutes\n", delay);

    if (delay == 0)
        printf("Status: ON TIME OR EARLY\n");
    else if (delay <= 15)
        printf("Status: SLIGHTLY DELAYED\n");
    else
        printf("Status: SIGNIFICANTLY DELAYED\n");

    printf("Seats occupied: %d/%d\n",
           seatsOccupied, busCapacity);

    printf("Seats remaining: %d\n",
           busCapacity - seatsOccupied);
}

/* Function to update departure times */
void updateBusTimes() {
    int hour, minute;

    printf("\nEnter scheduled departure time.\n");
    printf("Hour (0-23): ");

    if (scanf("%d", &hour) != 1 ||
        hour < 0 || hour > 23) {
        printf("Invalid hour!\n");
        return;
    }

    printf("Minute (0-59): ");

    if (scanf("%d", &minute) != 1 ||
        minute < 0 || minute > 59) {
        printf("Invalid minute!\n");
        return;
    }

    scheduledTime = hour * 60 + minute;

    printf("\nEnter estimated departure time.\n");
    printf("Hour (0-23): ");

    if (scanf("%d", &hour) != 1 ||
        hour < 0 || hour > 23) {
        printf("Invalid hour!\n");
        return;
    }

    printf("Minute (0-59): ");

    if (scanf("%d", &minute) != 1 ||
        minute < 0 || minute > 59) {
        printf("Invalid minute!\n");
        return;
    }

    estimatedTime = hour * 60 + minute;

    printf("Bus timings updated successfully!\n");
    showBusStatus();
}

/* Function to set bus capacity */
void setBusCapacity() {
    int capacity;

    printf("Enter total bus seats: ");

    if (scanf("%d", &capacity) != 1 ||
        capacity < 1) {
        printf("Enter a valid positive capacity.\n");
        return;
    }

    if (capacity < seatsOccupied) {
        printf("Capacity cannot be less than "
               "seats already occupied.\n");
        return;
    }

    busCapacity = capacity;

    printf("Bus capacity updated to %d seats.\n",
           busCapacity);
}
/* Function to display bus tracking information */
void showBusTracking() {
    printf("\n===== LIVE BUS TRACKER =====\n");

    printf("Current location: %s\n", currentLocation);

    if (busStatus == 0) {
        printf("Status: BUS NOT DEPARTED\n");
        printf("Scheduled departure: %02d:%02d\n",
               scheduledTime / 60, scheduledTime % 60);
        printf("Estimated departure: %02d:%02d\n",
               estimatedTime / 60, estimatedTime % 60);
    }
    else if (busStatus == 1) {
        printf("Status: BUS IS ON THE WAY\n");
        printf("Estimated arrival: %02d:%02d\n",
               estimatedArrival / 60,
               estimatedArrival % 60);
    }
    else if (busStatus == 2) {
        printf("Status: BUS HAS ARRIVED\n");
        printf("Destination reached!\n");
    }
}
/* Function to update bus tracking information */
void updateBusTracking() {
    int status;

    printf("\n===== UPDATE BUS TRACKING =====\n");
    printf("1. Bus has not departed\n");
    printf("2. Bus is on the way\n");
    printf("3. Bus has arrived\n");
    printf("Enter bus status: ");

    if (scanf("%d", &status) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (status < 1 || status > 3) {
        printf("Invalid status choice!\n");
        return;
    }

    busStatus = status - 1;

    printf("Enter current bus location: ");
    scanf(" %49[^\n]", currentLocation);

    if (busStatus == 1) {
        int hour, minute;

        printf("Enter estimated arrival hour (0-23): ");
        if (scanf("%d", &hour) != 1 ||
            hour < 0 || hour > 23) {
            printf("Invalid hour!\n");
            return;
        }

        printf("Enter estimated arrival minute (0-59): ");
        if (scanf("%d", &minute) != 1 ||
            minute < 0 || minute > 59) {
            printf("Invalid minute!\n");
            return;
        }

        estimatedArrival = hour * 60 + minute;
    }

    printf("Bus tracking information updated!\n");
}
/* Function to display boarding statistics */
void showBoardingStatistics() {
    int waiting = 0;
    struct Student *temp = front;

    /* Count students still waiting */
    while (temp != NULL) {
        waiting++;
        temp = temp->next;
    }

    printf("\n===== BOARDING STATISTICS =====\n");
    printf("Total students registered: %d\n",
           totalBoarded + waiting);
    printf("Total students boarded: %d\n",
           totalBoarded);
    printf("Students still waiting: %d\n",
           waiting);
    printf("Seats remaining: %d\n",
           busCapacity - seatsOccupied);
}

/* Main function */
int main() {
    int choice;

    do {
        printf("\n===== HOSTELBUS SYSTEM =====\n");
        printf("1. Register Student\n");
        printf("2. View Boarding Queue\n");
        printf("3. Confirm Boarding\n");
        printf("4. Check Bus Status\n");
        printf("5. Update Bus Timings\n");
        printf("6. Set Bus Capacity\n");
        printf("7. View Boarding Statistics\n");
        printf("8. Update Bus Tracking\n");
        printf("9. View Bus Tracking\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Restart the program.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                registerStudent();
                break;

            case 2:
                displayQueue();
                break;

            case 3:
                boardStudent();
                break;

            case 4:
                showBusStatus();
                break;

            case 5:
                updateBusTimes();
                break;

            case 6:
                setBusCapacity();
                break;

            case 7:
                showBoardingStatistics();
                break;

            case 8:
                updateBusTracking();
                break;

            case 9:
                showBusTracking();
                break;

            case 10:
                printf("Exiting HostelBus System.\n");
                break;
        }

    } while (choice != 10);

    /* Free all remaining linked-list nodes */
    while (front != NULL) {
        struct Student *temp = front;
        front = front->next;
        free(temp);
    }

    rear = NULL;

    return 0;
}