package ru.fizteh.fivt.students.Volodin_Denis.Parallel.interpreter;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.ErrorFunctions;

import java.util.function.BiConsumer;

public class CommandHandler {
    
    private String name;
    private int quantityOfArguments;
    private BiConsumer<InterpreterState, String[]> callback;

    public CommandHandler(String name, int quantityOfArguments, 
            BiConsumer<InterpreterState, String[]> callback) {
        this.name = name;
        this.quantityOfArguments = quantityOfArguments;
        this.callback = callback;
    }

    public CommandHandler(final String name, final int quantityOfArguments) {
        this.name = name;
        this.quantityOfArguments = quantityOfArguments;
    }
    
    public String getName() {
        return name;
    }
    
    private void checkQuantityOfArguments(final String[] args, final String commandName) throws Exception {
        if (((args.length != quantityOfArguments) && (quantityOfArguments != -1))
          || (args.length < 2) && (quantityOfArguments == -1)) {
            ErrorFunctions.wrongQuantityOfArguments(commandName);
        }
        if (args.length > 1) {
            for (int i = 1; i < args.length; ++i) {
                if (args[i].isEmpty()) {
                    ErrorFunctions.wrongInput(commandName);
                }
            }
        }
    }
    
    public void execute(InterpreterState interpreterState, String[] args) throws Exception {
        checkQuantityOfArguments(args, name);
        
        callback.accept(interpreterState, args);
    }
}
