package ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;

import java.io.IOException;

public class CommandTableCommit extends Command {
    
    public CommandTableCommit() {
        name = "commit";
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

                try {
                    System.out.println(table.commit());
                } catch (IOException e) {
                    e.printStackTrace();
                }
                state.setTable(table);
            });
    }
}
