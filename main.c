#include <stdio.h>
#include "log_core.h"
#include "log_tree.h"
#include "log_utils.h"

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Add log\n");
        printf("2. Display logs\n");
        printf("3. Query logs (segment tree)\n");
        printf("4. Flag irregularities\n");
        printf("5. Compress logs\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            record_log();
            break;
        case 2:
            display_logs();
            break;
        case 3:
            query_logs_by_time();
            break;
        case 4:
            flag_irregularities();
            break;
        case 5:
            compress_logs();
            break;
        case 6:
            printf("Bye\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
}
