// log_tree.h
#ifndef LOG_TREE_H
#define LOG_TREE_H

#include "log_core.h"

typedef struct
{
    int min_t;
    int max_t;
    int count;
} Node;

extern Node segtree[4 * MAX_LOGS];

void build_tree(int idx, int l, int r);
Node query_tree(int idx, int l, int r, int ql, int qr);
void query_logs_by_time();

#endif
