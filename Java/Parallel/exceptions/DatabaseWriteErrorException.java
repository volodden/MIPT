package ru.fizteh.fivt.students.Volodin_Denis.Parallel.exceptions;

public class DatabaseWriteErrorException extends Exception {
    public DatabaseWriteErrorException() {
        super();
    }

    public DatabaseWriteErrorException(final String message) {
        super(message);
    }
}
