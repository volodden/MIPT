package ru.fizteh.fivt.students.Volodin_Denis.Storeable.main;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.TableProviderFactoryByVolodden;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.Interpreter;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.InterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.interpreter.commands.*;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.TableProvider;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.TableProviderFactory;

public class Main {
    
    public static void main(final String[] args) {
        try {
            TableProviderFactory tpf = new TableProviderFactoryByVolodden();
            String dir = System.getProperty("fizteh.db.dir");
            TableProvider tableProvider = tpf.create(dir);
            InterpreterState interpreterState = new StringInterpreterState(tableProvider);
            new Interpreter(interpreterState,
                    new CommandHandler[] {
                        new CommandTableGet().create(),
                        new CommandTableList().create(),
                        new CommandTablePut().create(),
                        new CommandTableRemove().create(),
                        new CommandTableSize().create(),
                        new CommandTableCommit().create(),
                        new CommandProviderCreate().create(),
                        new CommandProviderDrop().create(),
                        new CommandTableCommit().create(),
                        new CommandProviderUse().create()})
            .run(args);
        } catch (Exception exception) {
            System.err.println(exception.getMessage());
            System.exit(ReturnCodes.ERROR);
        }
        System.exit(ReturnCodes.SUCCESS);
    }
}
