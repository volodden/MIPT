package ru.fizteh.fivt.students.Volodin_Denis.Storeable.tests;

import junit.framework.TestCase;
import org.junit.Test;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.TableProviderFactoryByVolodden;

import java.nio.file.Files;
import java.nio.file.Paths;

public class TableProviderFactoryByVoloddenTest extends TestCase {

    @Test
    public void testCreate() throws Exception {
        TableProviderFactoryByVolodden tpf = new TableProviderFactoryByVolodden();
        tpf.create("tableProvider");
        Files.deleteIfExists(Paths.get("tableProvider"));
    }
}
