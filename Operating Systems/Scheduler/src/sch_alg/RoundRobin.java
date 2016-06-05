package sch_alg;

import java.io.File;
import java.util.LinkedList;

public class RoundRobin extends CPUSchedulingAlgorithms {

    private final int QUANTUM;
    private int curr_quantum;

    /**
     * constructor that will pass the job_file to the abstract
     * class and will instantiate the ready_queue as a LinkedList
     * and will set constant the quantum
     * @param job_file jobs to be processed
     * @param quantum
     */
    public RoundRobin(File job_file, String quantum) {
        super(job_file);
        ready_queue = new LinkedList<PCB>();
        QUANTUM = Integer.parseInt(quantum);
        curr_quantum = QUANTUM;
    }

    /**
     * this method will put the item in the cpu and process the burst. Once
     * the burst is finished the job will be placed in the blocked_queue
     * for 10 units of time. If there are no more burst then the job will
     * be completed and removed.
     */
    @Override
    void process_ready_queue() {
        in_cpu = ready_queue.peek(); // get front of ready_queue into cpu
        increment_waiting_time();    // increment wait times in ready_queue
        in_cpu.process_burst();      // burst -= 1 and processing time += 1
        curr_quantum -= 1;

        // if the burst is 0 and there are more burst
        if (in_cpu.getBurst() == 0 && in_cpu.bursts.size() > 1) {
            in_cpu.prepare_move_io();  // rm completed burst & add IO_delay
            blocked_queue.add(in_cpu); // mv job to blocked_queue
            ready_queue.poll();        // rm job from ready_queue
            curr_quantum = QUANTUM;    // reset quantum

            // else if the current burst is 0 and that's the only burst left
        } else if (in_cpu.getBurst() == 0 && in_cpu.bursts.size() == 1) {
            in_cpu.completion_time = cpu_clock;
            in_cpu.turnaround_time = in_cpu.completion_time - in_cpu.arrival_time;
            System.out.println(in_cpu);

            curr_quantum = QUANTUM;  // reset quantum
            ready_queue.poll();      // rm job from ready_queue
            completed_jobs += 1;     // mark job as complete
            increment_total_times(); // inc total: process, waiting, & turnaround
            add_job();               // add next job into ready_queue

        } else if (curr_quantum == 0) {
            ready_queue.add(ready_queue.poll()); // mv job to back of queue
            curr_quantum = QUANTUM;              // reset quantum
        }
    }
}
