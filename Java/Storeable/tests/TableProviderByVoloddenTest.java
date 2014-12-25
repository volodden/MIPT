package ru.fizteh.fivt.students.Volodin_Denis.Storeable.tests;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.StoreableByVolodden;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.TableProviderByVolodden;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.TableProvider;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;

public class TableProviderByVoloddenTest {

    public final String name = "test123321123323";
    public final String nameTable = "nameTable";
    public final String end = ".." + File.separator + name;
    public final List<Class<?>> list = new ArrayList<Class<?>>();
    public final String nameOfTypes = "signature.tsv";

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    @Test(expected = IllegalStateException.class)
    public void testGetTableNotExists() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        TableProvider tableProvider = new TableProviderByVolodden(name);
        try {
            Table table = tableProvider.getTable(Paths.get(name, nameTable).toString());
        } catch (IllegalStateException e) {
            Files.deleteIfExists(path);
            throw new IllegalStateException();
        }
    }

    @Test
    public void testGetTable() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        TableProvider tableProvider = new TableProviderByVolodden(name);
        list.add(String.class);
        Table table = tableProvider.createTable(nameTable, list);
        Storeable val1St = new StoreableByVolodden("[v]", list);
        table.put("k", val1St);
        table.commit();
        table = tableProvider.getTable(nameTable);
        tableProvider.removeTable(nameTable);
        Files.deleteIfExists(path);
    }

    @Test
    public void testCreateTable() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        TableProvider tableProvider = new TableProviderByVolodden(path.toString());
        list.add(String.class);
        Table table = tableProvider.createTable(nameTable, list);
        assertEquals(true, Paths.get(path.toString(), nameTable).toFile().exists());
        Files.deleteIfExists(Paths.get(path.toString(), nameTable, nameOfTypes));
        Files.deleteIfExists(Paths.get(path.toString(), nameTable));
        Files.deleteIfExists(path);
    }

    @Test
    public void testCreateTableIfExists() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        TableProvider tableProvider = new TableProviderByVolodden(path.toString());
        Files.createDirectory(Paths.get(path.toString(), nameTable));
        list.add(String.class);
        Table table = tableProvider.createTable(nameTable, list);
        assertEquals(true, Paths.get(path.toString(), nameTable).toFile().exists());
        Files.deleteIfExists(Paths.get(path.toString(), nameTable, nameOfTypes));
        Files.deleteIfExists(Paths.get(path.toString(), nameTable));
        Files.deleteIfExists(path);
    }

    @Test
    public void testRemoveTable() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        TableProvider tableProvider = new TableProviderByVolodden(path.toString());
        list.add(String.class);
        Table table = tableProvider.createTable(nameTable, list);
        Storeable val1St = new StoreableByVolodden("[v]", list);
        table.put("k", val1St);
        table.commit();
        tableProvider.removeTable(nameTable);
        assertEquals(false, Paths.get(path.toString(), nameTable).toFile().exists());
        Files.deleteIfExists(Paths.get(path.toString(), nameTable, nameOfTypes));
        Files.deleteIfExists(Paths.get(path.toString(), nameTable));
        Files.deleteIfExists(path);
    }
}
