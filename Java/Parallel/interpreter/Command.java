package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter;


import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

public abstract class Command {
    
    protected String name;
    protected int quantityOfArguments;
    
    protected static void tableIsNull(final Table table) throws Exception {
        if (table == null) {
            System.out.print("no table");
            throw new Exception();
        }
    }
    
    public abstract CommandHandler create();
    
}
