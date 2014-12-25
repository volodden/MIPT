package ru.fizteh.fivt.students.Volodin_Denis.Parallel.database;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

import java.util.List;
import java.util.NoSuchElementException;

public class JSONUtils {

    public static String storeableToString(Table table, Storeable storeable) {
        if (storeable == null) {
            return null;
        }
        StringBuilder builder = new StringBuilder("[");
        for (int i = 0; i < table.getColumnsCount(); ++i) {
            builder.append(JSONUtils.valueInStoreable(table, storeable, i)).append(", ");
        }
        builder.deleteCharAt(builder.length() - 1);
        builder.deleteCharAt(builder.length() - 1);
        builder.append("]");
        return builder.toString();
    }

    public static String valueInStoreable(Table table, Storeable storeable, int index) {
        Class<?> type = table.getColumnType(index);
        if (storeable == null) {
            return "null";
        }
        if (type == Integer.class) {
            return storeable.getIntAt(index).toString();
        }
        if (type == Long.class) {
            return storeable.getLongAt(index).toString();
        }
        if (type == Byte.class) {
            return storeable.getByteAt(index).toString();
        }
        if (type == Float.class) {
            return storeable.getFloatAt(index).toString();
        }
        if (type == Double.class) {
            return storeable.getDoubleAt(index).toString();
        }
        if (type == Boolean.class) {
            return storeable.getBooleanAt(index).toString();
        }
        if (type == String.class) {
            return storeable.getStringAt(index).toString();
        }
        return "null";
    }

    public static Class<?> stringToType(String string) {
        if (string.equals("int")) {
            return Integer.class;
        }
        if (string.equals("long")) {
            return Long.class;
        }
        if (string.equals("byte")) {
            return Byte.class;
        }
        if (string.equals("float")) {
            return Float.class;
        }
        if (string.equals("double")) {
            return Double.class;
        }
        if (string.equals("bool")) {
            return Boolean.class;
        }
        if (string.equals("string")) {
            return String.class;
        }
        throw new NoSuchElementException();
    }

    public static Storeable stringToStoreable(List<Class<?>> types, String string) {
        if (string == null) {
            return null;
        }
        return new StoreableByVolodden(string, types);
    }

    public static Object stringToOneElementOfStoreable(Class<?> type, String string) {
        if (type == Integer.class) {
            return Integer.parseInt(string);
        }
        if (type == Long.class) {
            return Long.parseLong(string);
        }
        if (type == Byte.class) {
            return Byte.parseByte(string);
        }
        if (type == Float.class) {
            return Float.parseFloat(string);
        }
        if (type == Double.class) {
            return Double.parseDouble(string);
        }
        if (type == Boolean.class) {
            return Boolean.parseBoolean(string);
        }
        if (type == String.class) {
            return string;
        }
        return null;
    }

    public static String typeToString(Class type) {
        if (type == Integer.class) {
            return "int";
        }
        if (type == Long.class) {
            return "long";
        }
        if (type == Byte.class) {
            return "byte";
        }
        if (type == Float.class) {
            return "float";
        }
        if (type == Double.class) {
            return "double";
        }
        if (type == Boolean.class) {
            return "bool";
        }
        if (type == String.class) {
            return "string";
        }
        throw new NoSuchElementException();
    }
}
