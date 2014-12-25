package ru.fizteh.fivt.students.Volodin_Denis.Storeable.database;

import ru.fizteh.fivt.students.Volodin_Denis.Storeable.main.ErrorFunctions;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.ColumnFormatException;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.TableProvider;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class TableProviderByVolodden implements TableProvider {

    private String dbPath;
    private Set<String> tables;


    private final String signatureFileName = "signature.tsv";


    private final String regExpToSplitJSON = ",(?=([^\"]*\"[^\"]*\")*[^\"]*$)";

    public TableProviderByVolodden(String dir) throws Exception {
        dbPath = FileUtils.toAbsolutePath(dir);
        if (!FileUtils.exists(dbPath)) {
            FileUtils.createDirectory(dbPath);
        }
        tables = readOldTables(Paths.get(dbPath));
    }

    @Override
    public Table getTable(String name) throws IllegalArgumentException {
        if (!FileUtils.exists(dbPath, name)) {
            ErrorFunctions.notExists("get table", name);
        }
        Table dbTable;
        try {
            dbTable = new TableByVolodden(FileUtils.get(dbPath, name).toString());
        } catch (Exception exception) {
            throw new RuntimeException(exception);
        }
        return dbTable;
    }

    @Override
    public Table createTable(String name, List<Class<?>> columnTypes) throws IOException {
        if (name == null) {
            ErrorFunctions.nameIsNull("create", name);
        }
        Table dbTable = null;
        if (FileUtils.exists(dbPath, name)) {
            if (!FileUtils.isDirectory(dbPath, name)) {
                ErrorFunctions.tableNameIsFile("create", name);
            }
        } else {
            boolean exists = false;
            try {
                exists = FileUtils.createDirectory(dbPath, name);
            } catch (Exception exception) {
                throw new RuntimeException(exception);
            }
            if (exists) {
                try {
                    File file = Paths.get(dbPath, name, signatureFileName).toFile();
                    file.createNewFile();
                    try (PrintWriter out = new PrintWriter(file)) {
                        int i = 0;
                        for (Class type : columnTypes) {
                            if (i++ != 0) {
                                out.print(" ");
                            }
                            out.print(JSONUtils.typeToString(type));
                        }
                    } catch (Exception e) {
                        throw e;
                    }
                    dbTable = new TableByVolodden(Paths.get(dbPath, name).normalize().toFile().toString());
                    tables.add(name);
                } catch (Exception exception) {
                    exception.printStackTrace();
                }
            } else {
                ErrorFunctions.notMkdir("create", name);
            }
        }
        return dbTable;
    }

    @Override
    public void removeTable(String name) throws IOException {
        if (!FileUtils.exists(dbPath, name)) {
            throw new IllegalStateException("[" + name + "] not exists");
        }
        if (!FileUtils.getParentName(dbPath, name).equals(FileUtils.getFileName(dbPath))) {
            ErrorFunctions.notExists("drop", name);
        }
        if (!FileUtils.isDirectory(dbPath)) {
            ErrorFunctions.notDirectory("drop", name);
        }

        try {
            recursiveDrop(FileUtils.get(dbPath));
            tables.remove(name);
        } catch (Exception exception) {
            throw new RuntimeException(exception);
        }
    }

    @Override
    public Storeable deserialize(Table table, String value) throws ParseException {
        if (!value.startsWith("[")) {
            throw new ParseException("Can't deserialize <" + value + ">: argument doesn't start with \"[\".", 0);
        }
        if (!value.endsWith("]")) {
            throw new ParseException("Can't deserialize <" + value + ">: argument doesn't end with \"]\".",
                    value.length() - 1);
        }
        value = value.substring(1, value.length() - 1);
        String[] parsedValues = value.split(regExpToSplitJSON);
        Storeable answer = createFor(table);
        int i = 0;
        try {
            for (i = 0; i < parsedValues.length; ++i) {
                answer.setColumnAt(i, JSONUtils.stringToOneElementOfStoreable(table.getColumnType(i), parsedValues[i]));
            }
        } catch (ColumnFormatException e) {
            throw new ParseException(e.getMessage(), i);
        } catch (IndexOutOfBoundsException e) {
            throw new ParseException(e.getMessage(), i);
        }
        if (i < table.getColumnsCount()) {
            throw new ParseException("Too few elements.", i);
        }
        return answer;
    }

    @Override
    public String serialize(Table table, Storeable value) throws ColumnFormatException {
        return JSONUtils.storeableToString(table, value);
    }

    @Override
    public Storeable createFor(Table table) {
        return new StoreableByVolodden(table);
    }

    @Override
    public Storeable createFor(Table table, List<?> values) throws ColumnFormatException, IndexOutOfBoundsException {
        return new StoreableByVolodden(table, values);
    }

    @Override
    public List<String> getTableNames() {
        List<String> result = new ArrayList<>();
        for (String name : tables) {
            result.add(name);
        }
        return result;
    }

    private static void recursiveDrop(final Path pathToFile) throws Exception {
        if (!pathToFile.toFile().exists()) {
            return;
        }
        if (pathToFile.toFile().isFile()) {
            if (!pathToFile.toFile().delete()) {
                ErrorFunctions.smthWrong("drop");
            }
        }
        try {
            if (pathToFile.toFile().isDirectory()) {
                String[] names = pathToFile.toFile().list();
                if (names.length != 0) {
                    for (String name : names) {
                        if (FileUtils.isDirectory(pathToFile.toString(), name)) {
                            recursiveDrop(Paths.get(pathToFile.toString(), name).normalize());
                        } else {
                            if (!FileUtils.delete(pathToFile.toString(), name)) {
                                ErrorFunctions.smthWrong("drop");
                            }
                        }
                    }
                }
                if (!pathToFile.toFile().delete()) {
                    ErrorFunctions.smthWrong("drop");
                }
            }
        } catch (SecurityException secException) {
            ErrorFunctions.security("drop", secException.getMessage());
        }
    }

    private Set<String> readOldTables(final Path path) throws Exception {
        Set<String> setOfNames = new HashSet<String>();
        String[] names = path.toFile().list();
        try {
            for (String name : names) {
                if (FileUtils.isDirectory(path.toString(), name)) {
                    Table temp = new TableByVolodden(name);
                    temp.size();
                    setOfNames.add(name);
                } else {
                    Files.delete(Paths.get(dbPath, name));
                }
            }
            return setOfNames;
        } catch (Exception exception) {
            ErrorFunctions.smthWrong("read");
            return null;
        }
    }
}
