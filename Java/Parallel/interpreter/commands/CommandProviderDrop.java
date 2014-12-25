package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.commands;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.Command;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter.CommandHandler;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.StringInterpreterState;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.TableProvider;

import java.io.IOException;

public class CommandProviderDrop extends Command {
    
    public CommandProviderDrop() {
        name = "drop";
        quantityOfArguments = 1;
    }
    
    @Override
    public CommandHandler create() {
        return new CommandHandler(name, quantityOfArguments,
            (interpreterState, args) -> {
                    StringInterpreterState state = (StringInterpreterState) interpreterState;
                    TableProvider tableProvider = state.getTableProvider();

                    try {
                        tableProvider.removeTable(args[0]);
                        System.out.println("dropped");
                    } catch (IllegalArgumentException e) {
                        System.err.println(e.getMessage());
                    } catch (IllegalStateException e) {
                        System.err.println(e.getMessage());
                    } catch (IOException e) {
                        System.err.println(e.getMessage());
                    }
            });
    }
}
