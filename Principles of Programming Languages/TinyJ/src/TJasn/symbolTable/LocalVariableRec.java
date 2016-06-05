package TJasn.symbolTable;

import TJasn.TJ;

public final class LocalVariableRec extends VariableRec {

    public LocalVariableRec(String idName, int varType, int dimensions, int stackframeOffset) {
        super(idName, varType, dimensions, stackframeOffset);
    }

    // for a Scanner variable
    public LocalVariableRec(String idName) {
        super(idName);
    }

}
