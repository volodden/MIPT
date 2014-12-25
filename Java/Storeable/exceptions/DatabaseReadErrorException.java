package ru.fizteh.fivt.students.Volodin_Denis.Storeable.exceptions;

public class DatabaseReadErrorException extends Exception {
    public DatabaseReadErrorException() {
        super();
    }

    public DatabaseReadErrorException(final String message) {
        super(message);
    }
}
