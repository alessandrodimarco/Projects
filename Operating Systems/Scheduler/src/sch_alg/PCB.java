package sch_alg;

import java.util.ArrayList;

public class PCB {
    static final int IO_DELAY = 10;

    ArrayList<Integer> bursts;

    int job_id;
    int arrival_time;
    int curr_io_time;
    int processing_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;

    public PCB(int job_id, int arrival_time, int burst_size) {
        this.job_id = job_id;
        this.arrival_time = arrival_time;
        this.bursts = new ArrayList<Integer>(burst_size);
    }

    public int getBurst() {
        return bursts.get(0);
    }

    public void process_burst() {
        bursts.set(0, (bursts.get(0)-1));
        processing_time += 1;
    }

    public void prepare_move_io() {
        bursts.remove(0);
        curr_io_time = IO_DELAY;
        processing_time += IO_DELAY;
    }

    public String toString() {
        String beg = "job id: " + job_id + ", arrival time: " + arrival_time + "\n";
        String mid = "completion time: " + completion_time + ", processing time: " + processing_time + "\n";
        String end = "waiting time: " + waiting_time + ", turnaround time: " + turnaround_time;

        return "\n***Job Terminated***\n" + beg + mid + end;
    }
}
