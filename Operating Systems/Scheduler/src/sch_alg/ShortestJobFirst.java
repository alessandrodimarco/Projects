package sch_alg;

import java.io.File;
import java.util.PriorityQueue;

public class ShortestJobFirst extends CPUSchedulingAlgorithms {

    /**
     * This constructor will pass the job_file to the abstract
     * class and will instantiate the ready_queue as a PriorityQueue
     * and will pass a Comparator
     * @param job_file jobs to be processed
     */
    public ShortestJobFirst(File job_file) {
        super(job_file);
        ready_queue = new PriorityQueue<PCB>(10, new BurstComparator());
    }
}
