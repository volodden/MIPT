package ru.fizteh.fivt.students.Volodin_Denis.Storeable.exceptions;

public class DatabaseCorruptedException extends Exception {
    public DatabaseCorruptedException() {
        super();
    }

    public DatabaseCorruptedException(final String message) {
        super(message);
    }
}
