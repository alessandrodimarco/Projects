package sch_alg;

import java.util.Comparator;

public class BurstComparator implements Comparator<PCB> {

    @Override
    public int compare(PCB x, PCB y) {
        return x.bursts.get(0) - y.bursts.get(0);
    }
}
