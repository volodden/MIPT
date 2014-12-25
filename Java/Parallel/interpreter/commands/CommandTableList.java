package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

import java.util.List;

public class CommandTableList extends Command {
    
    public CommandTableList() {
        name = "list";
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

                List<String> list = table.list();
                int i = list.size();
                for (String key : list) {
                    System.out.print(key);
                    --i;
                    if (i > 0) {
                        System.out.print(", ");
                    }
                }
                System.out.println();
            });
    }
}
