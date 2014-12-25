package ru.fizteh.fivt.students.Volodin_Denis.Parallel.exceptions;

public class WrongQuantityOfArgumentsException extends Exception {
    public WrongQuantityOfArgumentsException() {
        super();
    }

    public WrongQuantityOfArgumentsException(final String message) {
        super(message);
    }
}
