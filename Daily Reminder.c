#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define MAX_REMINDERS 10

typedef struct {
    char message[100];
    int hour;
    int minute;
    int triggered;  // whether already triggered
} Reminder;

int main() {
    Reminder reminders[MAX_REMINDERS];
    int count = 0;

    printf("Enter reminders (up to %d):\n", MAX_REMINDERS);
    while (count < MAX_REMINDERS) {
        printf("Reminder #%d:\n", count + 1);

        printf("Message: ");
        scanf(" %[^\n]", reminders[count].message);

        printf("Hour (0-23): ");
        scanf("%d", &reminders[count].hour);

        printf("Minute (0-59): ");
        scanf("%d", &reminders[count].minute);

        reminders[count].triggered = 0;
        count++;

        char more;
        printf("Add another reminder? (y/n): ");
        scanf(" %c", &more);
        if (more == 'n' || more == 'N') break;
    }

    printf("Listening for reminders...\n");

    while (1) {
        time_t now = time(NULL);
        struct tm *current = localtime(&now);

        for (int i = 0; i < count; i++) {
            if (!reminders[i].triggered &&
                current->tm_hour == reminders[i].hour &&
                current->tm_min == reminders[i].minute) {
                printf("\n🔔 Reminder at %02d:%02d - %s\n",
                       reminders[i].hour, reminders[i].minute, reminders[i].message);
                reminders[i].triggered = 1;  // mark as triggered
                Beep(1000, 500);  // 1000 Hz, 500 ms
                Beep(1000, 500);
                Beep(1000, 500);
            }
        }

        Sleep(30000);  // check every 30 seconds
    }

    return 0;
}














