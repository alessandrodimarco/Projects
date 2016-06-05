package sch_alg;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Scanner;

/**
 *  CPUScheduleAlgorithms class is the base class for FCFS, RR,
 *  SJF algorithms
 */
public abstract class CPUSchedulingAlgorithms {
    private Scanner        job_file;
    private ArrayList<PCB> job_queue;
    Queue<PCB>     ready_queue;
    ArrayList<PCB> blocked_queue;

    PCB in_cpu;
    int cpu_clock;
    int completed_jobs;
    private int number_of_jobs;
    private int total_processing_time;
    private int total_wait_time;
    private int total_turn_around_time;

    /**
     * constructor that takes in a job_file and
     * instantiates the job_queue, Scanner, blocked_queue
     * @param job_file incoming job
     */
    CPUSchedulingAlgorithms(File job_file) {
        try {
            this.job_file = new Scanner(job_file);
        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage());
        }

        job_queue = new ArrayList<PCB>();
        blocked_queue = new ArrayList<PCB>();
    }

    /**
     * reads job file, creates PCB object and adds jobs to
     * the job_queue
     */
    public void read_file() {
        while (job_file.hasNext()) {
            int job_ID              = job_file.nextInt();
            int time_of_arrival     = job_file.nextInt();
            int number_of_CPU_burst = job_file.nextInt();

            PCB curr_job = new PCB(job_ID, time_of_arrival, number_of_CPU_burst);
            for (int i = 0; i < number_of_CPU_burst; i++)
                curr_job.bursts.add(job_file.nextInt());

            job_queue.add(curr_job);
            number_of_jobs++;
        }
    }

    /**
     * this method will start the algorithm and will terminate
     * when all the jobs are processed
     */
    public void run() {
        // add jobs to ready_pq
        for (int i = 0; i < 10; i++)
            add_job();

        while (completed_jobs < number_of_jobs) {
            if (!ready_queue.isEmpty())
                process_ready_queue();

            if (!blocked_queue.isEmpty())
                process_blocked_queue();

            if (cpu_clock % 200 == 0)
                print_stats();

            cpu_clock += 1;
        }

        print_final_stats();
    }

    /**
     * adds job to the ready queue
     */
    void add_job() {
        if (!job_queue.isEmpty()) {
            if (job_queue.get(0).arrival_time <= cpu_clock)
                ready_queue.add(job_queue.remove(0));
        }
    }

    /**
     * this method will put the item in the cpu and process the burst. Once
     * the burst is finished the job will be placed in the blocked_queue
     * for 10 units of time. If there are no more burst then the job will
     * be completed and removed.
     */
    void process_ready_queue() {
        in_cpu = ready_queue.peek(); // get front of ready_queue into cpu
        increment_waiting_time();    // increment wait times in ready_queue
        in_cpu.process_burst();      // burst -= 1 and processing time += 1

        // if the burst is 0 and there are more burst
        if (in_cpu.getBurst() == 0 && in_cpu.bursts.size() > 1) {
            in_cpu.prepare_move_io();  // rm completed burst & add IO_delay
            blocked_queue.add(in_cpu); // mv job to blocked_queue
            ready_queue.poll();        // rm job from ready_queue

            // else if the curr_burst is 0 and that's the last burst
        } else if (in_cpu.getBurst() == 0 && in_cpu.bursts.size() == 1) {
            in_cpu.completion_time = cpu_clock;
            in_cpu.turnaround_time = in_cpu.completion_time - in_cpu.arrival_time;
            System.out.println(in_cpu);

            ready_queue.poll();      // rm job from ready_queue
            completed_jobs += 1;     // mark job as complete
            increment_total_times(); // inc total: process, waiting, & turnaround
            add_job();               // add next job into ready_queue
        }
    }

    /**
     * This method will perform the operation for
     * of io delaying
     */
    void process_blocked_queue() {
        PCB front_pcb = blocked_queue.get(0);

        // if the curr_io_time is greater than 0
        if (front_pcb.curr_io_time > 0) {
            front_pcb.curr_io_time -= 1;

            // else the curr_io_time has expired
        } else {
            ready_queue.add(front_pcb); // add front_pcb to the ready queue
            blocked_queue.remove(0);
        }
    }

    /**
     * This method will increment the wait times
     * for the items in the ready_queue
     */
    void increment_waiting_time() {
        for (PCB pcb_item : ready_queue) {
            if (pcb_item != in_cpu)
                pcb_item.waiting_time += 1;
        }
    }

    /**
     * This method will update the total_processing_time,
     * total_turn_around_time, and total_wait_time
     */
    void increment_total_times() {
        total_processing_time += in_cpu.processing_time;
        total_turn_around_time += in_cpu.turnaround_time;
        total_wait_time += in_cpu.waiting_time;
    }

    /**
     * This method will print the stats of the current state
     * of the algorithm
     */
    private void print_stats() {
        System.out.println("\n---Statistics---");
        System.out.print("ready_queue size   ");
        if (ready_queue.size() > 0)
            System.out.println(ready_queue.size() - 1);
        else
            System.out.println(ready_queue.size());
        System.out.println("blocked_queue size " + blocked_queue.size());
        System.out.println("completed jobs     " + completed_jobs);
    }

    /**
     * This method will print the final stats
     */
    private void print_final_stats() {
        System.out.println("\n" + this.getClass());
        System.out.println("CPU clock: " + cpu_clock);
        System.out.println("average processing time " + total_processing_time / completed_jobs);
        System.out.println("average waiting time    " + total_wait_time / completed_jobs);
        System.out.println("average turnaround time " + total_turn_around_time / completed_jobs);
        System.out.println("total completed jobs    " + completed_jobs);
    }
}
