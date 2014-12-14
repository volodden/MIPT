package ru.fizteh.fivt.students.Volodin_Denis.JUnit.main;

public class ErrorFunctions {

    public static void errorRead() throws Exception {
        throw new Exception("error reading from file");
    }

    public static void errorWrite() throws Exception {
        throw new Exception("error writing to file");
    }
    
    public static void invalidName(final String commandName, final String arg) throws Exception {
        throw new Exception(commandName + ": [" + arg + "] is invalid name.");
    }

    public static void nameIsNull(final String commandName,  final String arg) throws IllegalArgumentException {
        throw new IllegalArgumentException(commandName + ": [" + arg + "] is null.");
    }

    public static void notDirectory(final String commandName,  final String arg) throws IllegalStateException {
        throw new IllegalStateException(commandName + ": [" + arg + "] is not a directory.");
    }

    public static void notExists(final String commandName, final String arg) throws IllegalStateException {
        throw new IllegalStateException(commandName + ": [" + arg + "] does not exists.");
    }

    public static void notMkdir(final String commandName, final String arg) throws IllegalArgumentException {
        throw new IllegalArgumentException(commandName + ": failed to create a directory [" + arg + "].");
    }

    public static void security(final String commandName, final String arg) throws Exception {
        throw new Exception(commandName + ": access to the [" + arg + "] is prohibited.");
    }

    public static void smthWrong(final String commandName) throws Exception {
        throw new Exception(commandName + "something gone wrong.");
    }

    public static void smthWrong(final String commandName, final String message) throws Exception {
        throw new Exception(commandName + " :" + message);
    }

    public static void tableNameIsFile(final String commandName, final String arg) throws IllegalArgumentException {
        throw new IllegalArgumentException(commandName + ": [" + arg + "] is file");
    }

    public static void wrongInput(final String commandName) throws Exception {
        throw new Exception(commandName + ": wrong input.");
    }

    public static void wrongQuantityOfArguments(final String commandName) throws Exception {
        throw new Exception(commandName + ": wrong quantity of arguments.");
    }
}
