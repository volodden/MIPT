package ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;

public class CommandProviderUse extends Command {
    
    public CommandProviderUse() {
        name = "use";
        quantityOfArguments = 1;
    }
    
    @Override
    public CommandHandler create() {
        return new CommandHandler(name, quantityOfArguments, 
            (interpreterState, args) -> {
                StringInterpreterState state = (StringInterpreterState) interpreterState;
                Table table = state.getTable();
                if (table.getName().equals(args[0])) {
                    System.out.println("[" + args[0] + "] already used");
                    return;
                }
                int changes = table.getNumberOfUncommittedChanges();
                if (changes != 0) {
                    System.out.println(changes + " unsaved changes");
                    return;
                }
                try {
                    state.setTable(state.getTableProvider().getTable(args[0]));
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
            });
    }
}
