package ru.fizteh.fivt.students.Volodin_Denis.Parallel.database;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.TableProviderFactory;

import java.io.IOException;

public class TableProviderFactoryByVolodden implements TableProviderFactory{

    @Override
    public TableProviderByVolodden create(String dir) throws IOException {
        if (dir == null) {
            throw new IllegalArgumentException("wrong directory");
        }

        try {
            return new TableProviderByVolodden(dir);
        } catch (Exception e) {
            throw  new IOException("IO wrong.");
        }
    }
}
