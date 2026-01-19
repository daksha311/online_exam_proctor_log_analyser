# Online Exam Proctor Log Analyser

## Project Overview
The Online Exam Proctor Log Analyser is a C-based project designed to record, analyze, and
detect irregularities in user actions during online exams. It uses a Segment Tree for efficient
querying and provides functions to record logs, detect suspicious activities, and summarize
repeated actions.
## Objective
The main objective is to implement a data structure (Segment Tree) to handle real-time logs efficiently. It helps detect abnormal user behaviors like frequent tab switches or excessive copy-paste actions.

## Project Structure

**Files:**
- `main.c` — Menu-driven interface
- `log_core.c` / `log_core.h` — Handles core log recording and display
- `log_tree.c` / `log_tree.h` — Segment tree implementation and querying
- `log_utils.c` / `log_utils.h` — Compression and irregularity detection

## Data Structures Used

- **Struct: Action** — stores timestamp and user action.
- **Struct: Node** — stores min, max, and count of timestamps in Segment Tree nodes.

## Features

- **Add Log** – Records a new action with timestamp.
- **Display Logs** – Shows all stored logs with labels.
- **Query Logs** – Retrieves logs between two timestamps using Segment Tree.
- **Compress Logs** – Groups consecutive identical actions with timestamps.
- **Flag Irregularities** – Detects cheating patterns using sliding window scanning.



## Conclusion
This project successfully demonstrates how Segment Trees can be used for log analysis and activity monitoring. It efficiently records user actions, queries time-based data, detects anomalies, and compresses logs for clearer insights.