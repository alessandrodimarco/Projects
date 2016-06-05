import java.io.File;

import sch_alg.FirstComeFirstServe;
import sch_alg.RoundRobin;
import sch_alg.ShortestJobFirst;

/**
 *  Main program to call FCFS, SJF and RR based on
 *  user input
 *
 *  @author Alessandro DiMarco
 *  @author Vincent Li
 */
public class cpuscheduler {

    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.out.println("Missing Arguments");
            System.exit(1);
        }

        if (args[0].compareTo("FCFS") == 0) {
            FirstComeFirstServe first_come = new FirstComeFirstServe(new File(args[1]));
            first_come.read_file();
            first_come.run();
        }
        else if (args[0].compareTo("SJF") == 0) {
            ShortestJobFirst short_job = new ShortestJobFirst(new File(args[1]));
            short_job.read_file();
            short_job.run();
        }
        else {
            if (args.length < 3) {
                System.out.println("Missing Arguments");
                System.exit(1);
            }
            RoundRobin rr = new RoundRobin(new File(args[2]), args[1]);
            rr.read_file();
            rr.run();
        }
    }
}
