package ru.fizteh.fivt.students.Volodin_Denis.Parallel.main;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.InterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.TableProvider;

public class StringInterpreterState implements InterpreterState {
    private TableProvider tableProvider;
    private Table table;
    
    public StringInterpreterState(TableProvider tableProvider) {
        this.tableProvider = tableProvider;
    }
    
    public TableProvider getTableProvider() {
        return tableProvider;
    }
    
    public Table getTable() {
        return table;
    }
    
    public void setTable(Table table) {
        this.table = table; 
    }
}
