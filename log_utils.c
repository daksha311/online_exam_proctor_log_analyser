#include <stdio.h>
#include <string.h>
#include "log_utils.h"

void compress_logs()
{
    if (log_count == 0)
    {
        printf("No logs.\n");
        return;
    }

    printf("\n=== Compressed Log Summary ===\n");
    int count = 1;

    for (int i = 1; i <= log_count; i++)
    {
        if (i < log_count && strcmp(logs[i].action, logs[i - 1].action) == 0)
            count++;
        else
        {
            printf("%s - %d time%s (Timestamps: %d",
                   logs[i - 1].action, count,
                   (count > 1 ? "s" : ""), logs[i - count].timestamp);

            for (int j = i - count + 1; j < i; j++)
                printf(", %d", logs[j].timestamp);
            printf(")\n");

            count = 1;
        }
    }
}

void flag_irregularities()
{
    if (log_count == 0)
    {
        printf("No logs.\n");
        return;
    }

    int window_size = 20;
    int tab_threshold = 3;
    int cp_threshold = 4;
    int min_t = logs[0].timestamp, max_t = logs[0].timestamp;

    for (int i = 1; i < log_count; i++)
    {
        if (logs[i].timestamp < min_t)
            min_t = logs[i].timestamp;
        if (logs[i].timestamp > max_t)
            max_t = logs[i].timestamp;
    }

    printf("\n=== Fixed 20-second irregularity scan ===\n");
    int suspicious = 0;

    for (int wstart = min_t; wstart < max_t; wstart += window_size)
    {
        int wend = wstart + window_size;
        int tab_count = 0, cp_count = 0;

        for (int i = 0; i < log_count; i++)
        {
            int t = logs[i].timestamp;
            if (t >= wstart && t < wend)
            {
                if (strcmp(logs[i].action, "tab_switch") == 0)
                    tab_count++;
                if (strcmp(logs[i].action, "copy") == 0 ||
                    strcmp(logs[i].action, "paste") == 0)
                    cp_count++;
            }
        }

        if (tab_count >= tab_threshold)
        {
            printf("!Suspicious: %d tab switches in window %d-%d\n",
                   tab_count, wstart, wend);
            suspicious = 1;
        }

        if (cp_count >= cp_threshold)
        {
            printf("!Suspicious: %d copy/paste in window %d-%d\n",
                   cp_count, wstart, wend);
            suspicious = 1;
        }
    }

    if (!suspicious)
        printf("No irregularities detected.\n");
}
