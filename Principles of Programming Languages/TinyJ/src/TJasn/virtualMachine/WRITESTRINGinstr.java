package TJasn.virtualMachine;

import TJasn.TJ;

public class WRITESTRINGinstr extends TwoOperandInstruction {

    void execute() {
        for (int i = this.firstOperand; i <= this.secondOperand; i++) {
            System.out.print((char) TJ.data[i]);
        }
    }

    public WRITESTRINGinstr(int startOffset, int endOffset) {
        super(startOffset, endOffset, "WRITESTRING");
    }
}

