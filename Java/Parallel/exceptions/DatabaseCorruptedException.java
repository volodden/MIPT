package ru.fizteh.fivt.students.Volodin_Denis.Parallel.exceptions;

public class DatabaseCorruptedException extends Exception {
    public DatabaseCorruptedException() {
        super();
    }

    public DatabaseCorruptedException(final String message) {
        super(message);
    }
}
