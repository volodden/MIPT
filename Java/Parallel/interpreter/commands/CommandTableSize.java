package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

public class CommandTableSize extends Command {
    
    public CommandTableSize() {
        name = "size";
        quantityOfArguments = 0;
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

                System.out.println(table.size());
            });
    }
}
