package ru.fizteh.fivt.students.Volodin_Denis.Parallel.database;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.exceptions.DatabaseCorruptedException;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.main.ErrorFunctions;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.ColumnFormatException;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class TableByVolodden implements Table {

    private String dbPath;
    private FileMap fileMap;
    private List<Class<?>> types;

    private ReadWriteLock rwlLock = new ReentrantReadWriteLock();

    private final String signatureFileName = "signature.tsv";

    public TableByVolodden(final String path) throws Exception {
        dbPath = FileUtils.toAbsolutePath(path);
        fileMap = new FileMap(dbPath);
    }

    //---
    class HelpMap {
        public HashMap<String, String> map;
        public HelpMap() {
            map = new HashMap<String, String>();
        }
    }

    class FileMap implements Map<String, String>, AutoCloseable {

        private final int folders = 16;
        private final int files = 16;
        private final String encoding = "UTF-8";
        private final String dir = ".dir";
        private final String dat = ".dat";

        private String databasePath;
        private Map<String, String> database;
        private ThreadLocal<Map<String, String>> diff;

        public FileMap(final String dbPath) throws Exception {
            databasePath = dbPath;
            database = new HashMap<String, String>();
            diff = ThreadLocal.withInitial(() -> new HashMap<String, String>());
            if (FileUtils.exists(databasePath)) {

                rwlLock.readLock().lock();
                try {
                    readFromDisk();
                    readTypes();
                } finally {
                    rwlLock.readLock().unlock();
                }
            } else {
                if (types == null) {
                    throw new Exception("Table was not found");
                } else {
                    FileUtils.createDirectory(databasePath);
                    File file = new File(FileUtils.get(databasePath, signatureFileName).toString());
                    file.createNewFile();
                    try (PrintWriter out = new PrintWriter(file)) {
                        int i = 0;
                        for (Class type : types) {
                            if (i++ != 0) {
                                out.print(" ");
                            }
                            out.print(JSONUtils.typeToString(type));
                        }
                    } catch (Exception e) {
                        throw e;
                    }
                }
            }
        }

        private void readTypes() throws DatabaseCorruptedException {
            types = new ArrayList<>();
            List<String> list;
            try (Scanner in = new Scanner(new File(FileUtils.get(dbPath, signatureFileName).toString()))) {
                list = Arrays.asList(in.nextLine().split("\\s+"));
                for (String type : list) {
                    types.add(JSONUtils.stringToType(type));
                }
            } catch (FileNotFoundException e) {
                throw new DatabaseCorruptedException("Can't find a file with signatures.");
            } catch (IllegalArgumentException e) {
                throw new DatabaseCorruptedException(signatureFileName + " is corrupted.");
            } catch (NoSuchElementException e) {
                throw new DatabaseCorruptedException(signatureFileName + " is corrupted.");
            }
        }

        private void readFromDisk() throws Exception {
            for (int i = 0; i < folders; ++i) {
                for (int j = 0; j < files; ++j) {
                    Path somePath =  Paths.get(databasePath, Integer.toString(i) + dir, Integer.toString(j)
                            + dat).normalize();
                    if (somePath.toFile().exists()) {
                        try (DataInputStream input = new DataInputStream(new FileInputStream(somePath.toString()))) {
                            while (true) {
                                try {
                                    String key = readOneWordFromDisk(input);
                                    String value = readOneWordFromDisk(input);

                                    if ((Math.abs(key.hashCode()) % folders != i)
                                            || (Math.abs(key.hashCode()) / folders % files != j)) {
                                        throw new Exception("wrong input");
                                    }
                                    database.put(key, value);
                                } catch (EOFException e) {
                                    break;
                                }
                            }
                        } catch (Exception e) {
                            ErrorFunctions.errorRead();
                        }
                    }
                }
            }
        }

        private String readOneWordFromDisk(DataInputStream input) throws Exception {
            byte[] word = new byte[input.readInt()];
            input.readFully(word);
            return new String(word, encoding);
        }

        private void writeOnDisk() throws Exception {
            HelpMap[][] helpMap = new HelpMap[folders][files];
            for (int i = 0; i < folders; ++i) {
                for (int j = 0; j < files; ++j) {
                    helpMap[i][j] = new HelpMap();
                }
            }
            Set<String> keys = database.keySet();
            for (String key : keys) {
                helpMap[Math.abs(key.hashCode()) % folders][Math.abs(key.hashCode()) / folders % files].map
                        .put(key, database.get(key));
            }
            for (int i = 0; i < folders; ++i) {
                for (int j = 0; j < files; ++j) {
                    Path somePath =  Paths.get(databasePath, Integer.toString(i) + dir, Integer.toString(j)
                            + dat).normalize();
                    if (somePath.toFile().exists()) {
                        if (!somePath.toFile().delete()) {
                            ErrorFunctions.smthWrong("write", "file is not deleted");
                        }
                    }
                }
                Path somePath =  Paths.get(databasePath, Integer.toString(i) + dir).normalize();
                if (somePath.toFile().exists()) {
                    if (!somePath.toFile().delete()) {
                        ErrorFunctions.smthWrong("write", "folder is not deleted");
                    }
                }
            }
            for (int i = 0; i < folders; ++i) {
                for (int j = 0; j < files; ++j) {
                    Set<String> keyList = helpMap[i][j].map.keySet();
                    if (!keyList.isEmpty()) {
                        Path somePath =  Paths.get(databasePath, Integer.toString(i) + dir).normalize();
                        if (!somePath.toFile().exists()) {
                            Files.createDirectory(somePath);
                        }
                        somePath =  Paths.get(somePath.toString(), j + dat).normalize();
                        Files.createFile(somePath);

                        try (FileOutputStream output = new FileOutputStream(somePath.toString())) {
                            for (String key : keyList) {
                                writeOneWordOnDisk(key, output);
                                writeOneWordOnDisk(database.get(key), output);
                            }
                        } catch (Exception e) {
                            ErrorFunctions.errorWrite();
                        }
                    }
                }
            }
        }

        private void writeOneWordOnDisk(final String word, FileOutputStream output) throws Exception {
            ByteBuffer buffer = ByteBuffer.allocate(4);
            byte[] wordByte = buffer.putInt(word.getBytes(encoding).length).array();
            output.write(wordByte);
            output.write(word.getBytes(encoding));
        }

        private void upgrade() throws Exception {
            for (String key : diff.get().keySet()) {
                if (diff.get().get(key) == null) {
                    database.remove(key);
                } else {
                    database.put(key, diff.get().get(key));
                }
            }
            diff.get().clear();
            writeOnDisk();
        }

        private void downgrade() {
            diff.get().clear();
        }

        public int numUncommitedChanges() {
            return diff.get().size();
        }

        @Override
        public void close() throws Exception {
        }

        //Not used.
        @Override
        public void clear() {
            database.clear();
            diff.get().clear();
        }

        //Not used.
        @Override
        public boolean containsKey(Object key) {
            if (database.containsKey(key)) {
                if (diff.get().containsKey(key)) {
                    return (diff.get().get(key) != null);
                }
                return true;
            } else {
                return diff.get().containsKey(key);
            }
        }

        //Not used.
        @Override
        public boolean containsValue(Object value) {
            if (diff.get().containsValue(value)) {
                return true;
            } else {
                for (String key : database.keySet()) {
                    if (database.get(key).equals(value)) {
                        if (!diff.get().containsKey(key)) {
                            return true;
                        }
                    }
                }
                return false;
            }
        }

        // Not used.
        @Override
        public Set<java.util.Map.Entry<String, String>> entrySet() {
            return null;
        }

        @Override
        public String get(Object key) {
            if (diff.get().containsKey(key)) {
                return diff.get().get(key);
            } else {
                return database.get(key);
            }
        }

        @Override
        public boolean isEmpty() {
            return size() == 0;
        }

        @Override
        public Set<String> keySet() {

            Set<String> keysList = new HashSet<String>();
            if (isEmpty()) {
                return keysList;
            }

            for (String key : database.keySet()) {
                if (diff.get().containsKey(key)) {
                    if (diff.get().get(key) != null) {
                        keysList.add(key);
                    }
                } else {
                    keysList.add(key);
                }
            }
            for (String key : diff.get().keySet()) {
                if (!keysList.contains(key)) {
                    keysList.add(key);
                }
            }
            return keysList;
        }

        @Override
        public String put(String key, String value) {
            if (diff.get().containsKey(key)) {
                if (database.containsKey(key)) {
                    if (database.get(key).equals(value)) {
                        String oldValue = diff.get().get(key);
                        diff.get().remove(key);
                        return oldValue;
                    } else {
                        return diff.get().put(key, value);
                    }
                } else {
                    return diff.get().put(key, value);
                }
            } else {
                if (database.containsKey(key)) {
                    if (database.get(key).equals(value)) {
                        return database.get(key);
                    } else {
                        diff.get().put(key, value);
                        return database.get(key);
                    }
                } else {
                    return diff.get().put(key, value);
                }
            }
        }

        // Not used.
        @Override
        public void putAll(Map<? extends String, ? extends String> m) {
            return;
        }

        @Override
        public String remove(Object key) {
            if (diff.get().containsKey(key)) {
                if (diff.get().get(key) == null) {
                    return null;
                } else {
                    return diff.get().put((String) key, null);
                }
            } else {
                if (database.containsKey(key)) {
                    diff.get().put((String) key, null);
                }
                return database.get(key);
            }
        }

        @Override
        public int size() {
            int result = database.size();
            for (String key : database.keySet()) {
                if (diff.get().containsKey(key)) {
                    if (diff.get().get(key) == null) {
                        --result;
                    }
                }
            }
            for (String key : diff.get().keySet()) {
                if (!database.containsKey(key)) {
                    if (diff.get().get(key) != null) {
                        ++result;
                    }
                }
            }
            return result;
        }

        // Not used.
        @Override
        public Collection<String> values() {
            return null;
        }
    }

    //---

    @Override
    public Storeable put(String key, Storeable value) throws ColumnFormatException {

        rwlLock.readLock().lock();
        try {
            return JSONUtils.stringToStoreable(types, fileMap.put(key, JSONUtils.storeableToString(this, value)));
        } finally {
            rwlLock.readLock().unlock();
        }
    }

    @Override
    public Storeable remove(String key) {
        rwlLock.readLock().lock();
        try {
            return JSONUtils.stringToStoreable(types, fileMap.remove(key));
        } finally {
            rwlLock.readLock().unlock();
        }
    }

    @Override
    public int size() {
        rwlLock.readLock().lock();
        try {
            return fileMap.size();
        } finally {
            rwlLock.readLock().unlock();
        }
    }

    @Override
    public List<String> list() {
        rwlLock.readLock().lock();
        try {
            List<String> keys = new ArrayList<String>();
            for (String key : fileMap.keySet()) {
                keys.add(key);
            }
            return keys;
        } finally {
            rwlLock.readLock().unlock();
        }
    }

    @Override
    public int commit() {

        rwlLock.writeLock().lock();
        try {
            int changes = 0;
            try {
                fileMap.upgrade();
            } catch (Exception exception) {
                exception.printStackTrace();
            }
            return changes;
        } finally {
            rwlLock.writeLock().unlock();
        }
    }

    @Override
    public int rollback() {
        int changes = fileMap.numUncommitedChanges();
        fileMap.downgrade();
        return changes;
    }

    @Override
    public int getNumberOfUncommittedChanges() {
        rwlLock.readLock().lock();
        try {
            return fileMap.numUncommitedChanges();
        } finally {
            rwlLock.readLock().unlock();
        }
    }

    @Override
    public int getColumnsCount() {
        return types.size();
    }

    @Override
    public Class<?> getColumnType(int columnIndex) throws IndexOutOfBoundsException {
        return types.get(columnIndex);
    }

    @Override
    public String getName() {
        return FileUtils.getFileName(dbPath);
    }

    @Override
    public Storeable get(String key) {
        rwlLock.readLock().lock();
        try {
            return JSONUtils.stringToStoreable(types, fileMap.get(key));
        } finally {
            rwlLock.readLock().unlock();
        }
    }

}
