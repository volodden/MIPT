package ru.fizteh.fivt.students.Volodin_Denis.Storeable.main;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.InterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.TableProvider;

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
