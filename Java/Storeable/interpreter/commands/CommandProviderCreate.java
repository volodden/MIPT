package ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.JSONUtils;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.TableProvider;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class CommandProviderCreate extends Command {
    
    public CommandProviderCreate() {
        name = "create";
        quantityOfArguments = -1;
    }
    
    @Override
    public CommandHandler create() {
        return new CommandHandler(name, quantityOfArguments, 
            (interpreterState, args) -> {
                StringInterpreterState state = (StringInterpreterState) interpreterState;
                TableProvider tableProvider = state.getTableProvider();

                List<Class<?>> list = new ArrayList<Class<?>>();
                for (int i = 1; i < args.length; ++i) {
                    list.add(JSONUtils.stringToType(args[i]));
                }
                try {
                    tableProvider.getTable(args[0]);
                    System.out.println(name + " exists");
                } catch (IllegalArgumentException e) {
                    Table table = null;
                    try {
                        table = tableProvider.createTable(args[0], list);
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    if (table != null) {
                        System.out.println("created");
                    }
                }
            });
    }
}
