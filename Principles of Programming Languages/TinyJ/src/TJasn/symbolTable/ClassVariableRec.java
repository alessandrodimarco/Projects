package TJasn.symbolTable;

import TJasn.TJ;

public final class ClassVariableRec extends VariableRec {

    public ClassVariableRec(String idName, int varType, int dimensions, int addr) {
        super(idName, varType, dimensions, addr);
    }

    // for a Scanner variable
    public ClassVariableRec(String idName) {
        super(idName);
    }
}

