#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log_tree.h"

Node segtree[4 * MAX_LOGS];

void query_logs_by_time()
{
    if (log_count == 0)
    {
        printf("No logs.\n");
        return;
    }

    int t_start, t_end;
    printf("Enter starting timestamp: ");
    scanf("%d", &t_start);
    printf("Enter ending timestamp: ");
    scanf("%d", &t_end);

    if (t_start > t_end)
    {
        printf("Invalid range. Start time must be <= end time.\n");
        return;
    }

    // Find first log index >= t_start
    int ql = -1, qr = -1;
    for (int i = 0; i < log_count; i++)
    {
        if (logs[i].timestamp >= t_start)
        {
            ql = i;
            break;
        }
    }

    // Find last log index <= t_end
    for (int i = log_count - 1; i >= 0; i--)
    {
        if (logs[i].timestamp <= t_end)
        {
            qr = i;
            break;
        }
    }

    if (ql == -1 || qr == -1 || ql > qr)
    {
        printf("No logs found in the given time range.\n");
        return;
    }

    Node result = query_tree(1, 0, MAX_LOGS - 1, ql, qr);

    printf("\n=== Segment Tree Query Result ===\n");
    printf("Time Range: %d to %d\n", t_start, t_end);
    printf("Index Range: logs[%d] to logs[%d]\n", ql, qr);
    printf("Total logs in range: %d\n", result.count);
    printf("Earliest timestamp: %d\n", result.min_t);
    printf("Latest timestamp: %d\n", result.max_t);
}

Node merge(Node a, Node b)
{
    Node r;
    r.count = a.count + b.count;
    r.min_t = (a.min_t < b.min_t) ? a.min_t : b.min_t;
    r.max_t = (a.max_t > b.max_t) ? a.max_t : b.max_t;
    return r;
}

void build_tree(int idx, int l, int r)
{
    if (l == r)
    {
        if (l < log_count)
        {
            segtree[idx].min_t = logs[l].timestamp;
            segtree[idx].max_t = logs[l].timestamp;
            segtree[idx].count = 1;
        }
        else
        {
            segtree[idx].min_t = 999999999;
            segtree[idx].max_t = -999999999;
            segtree[idx].count = 0;
        }
        return;
    }

    int mid = (l + r) / 2;
    build_tree(idx * 2, l, mid);
    build_tree(idx * 2 + 1, mid + 1, r);
    segtree[idx] = merge(segtree[idx * 2], segtree[idx * 2 + 1]);
}

Node query_tree(int idx, int l, int r, int ql, int qr)
{
    if (ql > r || qr < l)   // boundary condition
    {
        Node empty = {999999999, -999999999, 0};
        return empty;
    }
    if (ql <= l && r <= qr)
        return segtree[idx];

    int mid = (l + r) / 2;
    Node left = query_tree(idx * 2, l, mid, ql, qr);
    Node right = query_tree(idx * 2 + 1, mid + 1, r, ql, qr);
    return merge(left, right);
}

