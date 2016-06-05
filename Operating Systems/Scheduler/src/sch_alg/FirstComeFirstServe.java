package sch_alg;

import java.io.File;
import java.util.LinkedList;

public class FirstComeFirstServe extends CPUSchedulingAlgorithms {

    /**
     * This constructor will pass the job_file to the abstract
     * class and will instantiate the ready_queue as a LinkedList
     * @param job_file jobs to be processed
     */
    public FirstComeFirstServe(File job_file) {
        super(job_file);
        ready_queue = new LinkedList<PCB>();
    }
}
