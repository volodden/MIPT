package ru.fizteh.fivt.students.Volodin_Denis.Storeable.tests;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.FileUtils;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.JSONUtils;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.StoreableByVolodden;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.database.TableByVolodden;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.structured.Table;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;

public class TableByVoloddenTest {

    public final String name = "test123321123322";
    public final String end = ".." + File.separator + name;
    public final String key1 = "key1key1";
    public final String val1 = "[val1val1]";
    public final String val2 = "[val2lav2]";
    public final String val3 = "[val3lav3]";
    public final List<Class<?>> list = new ArrayList<Class<?>>();
    public final String nameOfTypes = "signature.tsv";

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    @Test
    public void testGetName() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(name, table.getName());
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testGetNameIfTableExist() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(name, table.getName());
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(temporaryFolder.toString(), ".." + File.separator, name)
                .toAbsolutePath().normalize());
    }

    @Test
    public void testGet() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(JSONUtils.storeableToString(table, null), JSONUtils.storeableToString(table, table.get(key1)));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testGetIfExists() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        table.put(key1, val1St);
        assertEquals(JSONUtils.storeableToString(table, val1St), JSONUtils.storeableToString(table, table.get(key1)));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testPut() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        assertEquals(null, JSONUtils.storeableToString(table, table.put(key1, val1St)));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testPutIfExists() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        Storeable val2St = new StoreableByVolodden(val2, list);
        table.put(key1, val1St);
        assertEquals(JSONUtils.storeableToString(table, val1St),
                     JSONUtils.storeableToString(table, table.put(key1, val2St)));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testPutIfExistsInDataBase() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        table.put(key1, val1St);
        table.commit();
        assertEquals(JSONUtils.storeableToString(table, val1St),
                     JSONUtils.storeableToString(table, table.put(key1, val1St)));
        table.remove(key1);
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testPutIfExistsInDataBaseEqual() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        Storeable val2St = new StoreableByVolodden(val2, list);
        table.put(key1, val1St);
        table.commit();
        table.put(key1, val2St);
        assertEquals(JSONUtils.storeableToString(table, val2St),
                JSONUtils.storeableToString(table, table.put(key1, val1St)));
        table.remove(key1);
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testPutIfExistsInDataBaseNotEqual() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        Storeable val2St = new StoreableByVolodden(val2, list);
        Storeable val3St = new StoreableByVolodden(val3, list);
        table.put(key1, val1St);
        table.commit();
        table.put(key1, val2St);
        assertEquals(JSONUtils.storeableToString(table, val2St),
                JSONUtils.storeableToString(table, table.put(key1, val3St)));
        table.remove(key1);
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testRemove() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(null, table.remove(key1));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }


    @Test
    public void testRemoveNull() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        Storeable val2St = new StoreableByVolodden(val2, list);
        table.put(key1, val2St);
        table.commit();
        table.remove(key1);
        assertEquals(null, table.remove(key1));
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testRemoveIfExists() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        table.put(key1, val1St);
        assertEquals(JSONUtils.storeableToString(table, val1St),
                JSONUtils.storeableToString(table, table.remove(key1)));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testSize() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(0, table.size());
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testSizeWithUncommittedValues() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        list.set(0, String.class);
        Storeable val1St = new StoreableByVolodden(val1, list);
        Storeable val2St = new StoreableByVolodden(val2, list);
        table.put(key1, val1St);
        table.commit();
        table.put(key1, val2St);
        assertEquals(1, table.size());
        table.remove(key1);
        assertEquals(0, table.size());
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testGetNumberOfUncommittedChanges() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(0, table.getNumberOfUncommittedChanges());
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testCommit() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(table.commit(), 0);
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testRollback() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        assertEquals(0, table.rollback());
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testList() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        List<String> list = table.list();
        assertEquals(0, list.size());
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testListWithValues() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        table.put(key1, val1St);
        List<String> list = table.list();
        assertEquals(1, list.size());
        assertEquals(key1, list.get(0));
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testListWithValuesInDataBase() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        table.put(key1, val1St);
        table.commit();
        List<String> list = table.list();
        assertEquals(1, list.size());
        assertEquals(key1, list.get(0));
        table.remove(key1);
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testListWithValuesInDataBaseAndInDiff() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        Storeable val2St = new StoreableByVolodden(val2, list);
        table.put(key1, val1St);
        table.commit();
        table.put(key1, val2St);
        List<String> list = table.list();
        assertEquals(1, list.size());
        assertEquals(key1, list.get(0));
        table.remove(key1);
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    @Test
    public void testReadFromDisk() throws Exception {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        create();
        Table table = new TableByVolodden(name);
        Storeable val1St = new StoreableByVolodden(val1, list);
        table.put(key1, val1St);
        table.commit();
        Table table2 = new TableByVolodden(name);
        assertEquals(JSONUtils.storeableToString(table, val1St), JSONUtils.storeableToString(table, table2.get(key1)));
        table.remove(key1);
        table.commit();
        Files.delete(FileUtils.get(path.toString(), nameOfTypes));
        Files.deleteIfExists(Paths.get(name));
    }

    public void create() throws IOException {
        Path path = Paths.get(temporaryFolder.toString(), end).toAbsolutePath().normalize();
        FileUtils.createDirectory(path.toString());
        File file = new File(FileUtils.get(path.toString(), nameOfTypes).toString());
        file.createNewFile();
        try (PrintWriter out = new PrintWriter(file)) {
            out.print("string");
        }
        list.add(String.class);
    }
}
