#ifndef ACADPULSE_SCHEDULER_HPP
#define ACADPULSE_SCHEDULER_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "ds/queue.hpp"

namespace dsa {

struct AcademicTask {
    int id;
    int arrival_time;
    int burst_time;
    int priority; // lower value = higher priority
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;

    AcademicTask() : id(0), arrival_time(0), burst_time(0), priority(0),
                     remaining_time(0), waiting_time(0), turnaround_time(0), completion_time(0) {}

    AcademicTask(int pid, int arr, int burst, int prio = 0)
        : id(pid), arrival_time(arr), burst_time(burst), priority(prio),
          remaining_time(burst), waiting_time(0), turnaround_time(0), completion_time(0) {}
};

struct ScheduleMetrics {
    double avg_waiting_time = 0.0;
    double avg_turnaround_time = 0.0;
    Vector<AcademicTask> completed_tasks;
};

/**
 * Academic Task / Job Scheduler.
 * Covers Syllabus: Unit 3 (Applications of Queues: Job Scheduling)
 * Implements: FCFS, SJF, Priority, Round Robin.
 */
class TaskScheduler {
public:
    static ScheduleMetrics run_fcfs(Vector<AcademicTask> tasks) {
        ScheduleMetrics metrics;
        std::size_t n = tasks.size();
        if (n == 0) return metrics;

        // Sort by arrival time
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = i + 1; j < n; ++j) {
                if (tasks[j].arrival_time < tasks[i].arrival_time) {
                    AcademicTask tmp = tasks[i];
                    tasks[i] = tasks[j];
                    tasks[j] = tmp;
                }
            }
        }

        int current_time = 0;
        double total_wait = 0;
        double total_tat = 0;

        for (std::size_t i = 0; i < n; ++i) {
            if (current_time < tasks[i].arrival_time) {
                current_time = tasks[i].arrival_time;
            }
            tasks[i].waiting_time = current_time - tasks[i].arrival_time;
            current_time += tasks[i].burst_time;
            tasks[i].completion_time = current_time;
            tasks[i].turnaround_time = tasks[i].completion_time - tasks[i].arrival_time;

            total_wait += tasks[i].waiting_time;
            total_tat += tasks[i].turnaround_time;
            metrics.completed_tasks.push_back(tasks[i]);
        }

        metrics.avg_waiting_time = total_wait / n;
        metrics.avg_turnaround_time = total_tat / n;
        return metrics;
    }

    static ScheduleMetrics run_round_robin(Vector<AcademicTask> tasks, int quantum = 2) {
        ScheduleMetrics metrics;
        std::size_t n = tasks.size();
        if (n == 0) return metrics;

        CircularQueue<std::size_t> ready_q(tasks.size() * 4 + 16);
        Vector<bool> in_queue(n, false);

        int current_time = 0;
        std::size_t completed = 0;

        // Check who has arrived at time 0
        for (std::size_t i = 0; i < n; ++i) {
            if (tasks[i].arrival_time <= current_time && !in_queue[i]) {
                ready_q.enqueue(i);
                in_queue[i] = true;
            }
        }

        while (completed < n) {
            if (ready_q.empty()) {
                // Find next arriving task
                int min_arr = 1e9;
                for (std::size_t i = 0; i < n; ++i) {
                    if (tasks[i].remaining_time > 0 && tasks[i].arrival_time < min_arr) {
                        min_arr = tasks[i].arrival_time;
                    }
                }
                current_time = min_arr;
                for (std::size_t i = 0; i < n; ++i) {
                    if (tasks[i].arrival_time <= current_time && tasks[i].remaining_time > 0 && !in_queue[i]) {
                        ready_q.enqueue(i);
                        in_queue[i] = true;
                    }
                }
            }

            std::size_t idx = 0;
            ready_q.dequeue(idx);
            in_queue[idx] = false;

            int slice = (tasks[idx].remaining_time < quantum) ? tasks[idx].remaining_time : quantum;
            tasks[idx].remaining_time -= slice;
            current_time += slice;

            // Enqueue newly arrived tasks during this slice
            for (std::size_t i = 0; i < n; ++i) {
                if (i != idx && tasks[i].remaining_time > 0 && 
                    tasks[i].arrival_time <= current_time && !in_queue[i]) {
                    ready_q.enqueue(i);
                    in_queue[i] = true;
                }
            }

            if (tasks[idx].remaining_time > 0) {
                ready_q.enqueue(idx);
                in_queue[idx] = true;
            } else {
                tasks[idx].completion_time = current_time;
                tasks[idx].turnaround_time = tasks[idx].completion_time - tasks[idx].arrival_time;
                tasks[idx].waiting_time = tasks[idx].turnaround_time - tasks[idx].burst_time;
                completed++;
            }
        }

        double total_wait = 0, total_tat = 0;
        for (std::size_t i = 0; i < n; ++i) {
            total_wait += tasks[i].waiting_time;
            total_tat += tasks[i].turnaround_time;
            metrics.completed_tasks.push_back(tasks[i]);
        }
        metrics.avg_waiting_time = total_wait / n;
        metrics.avg_turnaround_time = total_tat / n;
        return metrics;
    }
};

} // namespace dsa

#endif // ACADPULSE_SCHEDULER_HPP

