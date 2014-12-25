package ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.JSONUtils;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;

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
