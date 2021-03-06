package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.database.JSONUtils;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.database.StoreableByVolodden;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

import java.util.Arrays;

public class CommandTablePut extends Command {
    
    public CommandTablePut() {
        name = "put";
        quantityOfArguments = -1;
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

                String[] buffer = Arrays.copyOfRange(args, 1, args.length);
                Storeable newValue = new StoreableByVolodden(table, buffer);
                Storeable value = table.put(args[0], newValue);
                if (value == null) {
                    System.out.println("new");
                } else {
                    System.out.println("overwrite");
                    System.out.println(JSONUtils.storeableToString(table, value));
                }
                state.setTable(table);
            });
    }
}
