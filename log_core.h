// log_core.h
#ifndef LOG_CORE_H
#define LOG_CORE_H

#define MAX_LOGS 100

typedef struct
{
    int timestamp;
    char action[50];
    char username[50];   
} Action;

extern Action logs[MAX_LOGS];
extern int log_count;

void enqueue(const char *username, const char *action_type, int user_timestamp);
void record_log();
void display_logs();

#endif