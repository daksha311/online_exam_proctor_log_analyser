#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log_core.h"
#include "log_tree.h"

Action logs[MAX_LOGS];
int log_count = 0;

static void warnings(const char *username, const char *action_type)
{
    if (strcmp(action_type, "tab_switch") != 0 &&
        strcmp(action_type, "copy") != 0 &&
        strcmp(action_type, "paste") != 0)
    {
        return; 
    }

    int count = 0;

    for (int i = 0; i < log_count; i++)
    {
        if (strcmp(logs[i].username, username) == 0 &&
            (strcmp(logs[i].action, "tab_switch") == 0 ||
             strcmp(logs[i].action, "copy") == 0 ||
             strcmp(logs[i].action, "paste") == 0))
        {
            count++;
        }
    }


    if (count == 1)
    {
        printf("WARNING: User '%s' performed a suspicious action.\n", username);
    }
    else if (count == 2)
    {
        printf("WARNING: User '%s' has repeated suspicious actions.\n", username);
    }
    else if (count >= 3)
    {
        printf("USER '%s' DELETED: 3 suspicious actions.\n", username);

        int new_count = 0;
        for (int i = 0; i < log_count; i++)
        {
            if (strcmp(logs[i].username, username) != 0)
            {
                logs[new_count++] = logs[i];
            }
        }
        log_count = new_count;

        printf("All logs for user '%s' have been removed.\n", username);
    }
}


void enqueue(const char *username, const char *action_type, int user_timestamp)
{
    if (log_count >= MAX_LOGS)
    {
        printf("Log full.\n");
        return;
    }

    logs[log_count].timestamp = user_timestamp;
    strcpy(logs[log_count].action, action_type);
    strcpy(logs[log_count].username, username);
    log_count++;

    printf("Recorded for user '%s'.\n", username);

    warnings(username, action_type);

    build_tree(1, 0, MAX_LOGS - 1);
}

void record_log()
{
    char action[50];
    char username[50];
    int timestamp;

    printf("Username: ");
    scanf("%49s", username);

    printf("Action: ");
    scanf("%49s", action);

    printf("Timestamp: ");
    scanf("%d", &timestamp);

    enqueue(username, action, timestamp);
}

void display_logs()
{
    if (log_count == 0)
    {
        printf("No logs.\n");
        return;
    }

    printf("\n=== Logs ===\n");
    for (int i = 0; i < log_count; i++)
        printf("Log %d = User: %s | Timestamp: %d | Action: %s\n",
               i + 1, logs[i].username, logs[i].timestamp, logs[i].action);
}
