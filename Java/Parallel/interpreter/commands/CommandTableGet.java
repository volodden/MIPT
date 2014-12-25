package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.database.JSONUtils;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

public class CommandTableGet extends Command {
    
    public CommandTableGet() {
        name = "get";
        quantityOfArguments = 1;
    }
    
    @Override
    public CommandHandler create() {
        return new CommandHandler(name, quantityOfArguments, 
            (interpreterState, args) -> {
                StringInterpreterState state = (StringInterpreterState) interpreterState;
                Table table = state.getTable();
                try {
                    tableIsNull(table);
                } catch (Exception e) {
                    return;
                }

                Storeable value = table.get(args[0]);
                if (value == null) {
                    System.out.println("not found");
                } else {
                    System.out.println("found");
                    System.out.println(JSONUtils.storeableToString(table, value));
                }
            });
    }
}
