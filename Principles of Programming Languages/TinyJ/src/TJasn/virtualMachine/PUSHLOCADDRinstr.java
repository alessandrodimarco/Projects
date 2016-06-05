package TJasn.virtualMachine;

import static TJasn.virtualMachine.CodeInterpreter.*;

public class PUSHLOCADDRinstr extends OneOperandInstruction {

    void execute() {
        EXPRSTACK[ESP++] = this.operand + FP;
    }


    public PUSHLOCADDRinstr(int stackFrameOffset) {
        super(stackFrameOffset, "PUSHLOCADDR");
    }
}

