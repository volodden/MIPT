package ru.fizteh.fivt.students.Volodin_Denis.Parallel.database;

import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.ColumnFormatException;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Storeable;
import ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured.Table;

import java.util.*;

public class StoreableByVolodden implements Storeable{

    private List<Class<?>> types;
    private List<Object> values;
    private Set<Class<?>> validTypes;

    public StoreableByVolodden(Table table) {
        initializeValidTypes();
        List<Class<?>> newTypes = new ArrayList<>();
        for (int i = 0; i < table.getColumnsCount(); ++i) {
            newTypes.add(table.getColumnType(i));
        }
        for (Class<?> type : newTypes) {
            if (!validTypes.contains(type)) {
                throw new ColumnFormatException("Invalid column type");
            }
        }
        types = newTypes;
        values = new ArrayList<>();
        for (int i = 0; i < types.size(); i++) {
            values.add(null);
        }
    }

    public StoreableByVolodden(Table table, List<?> newValues) {
        this(table);
        if (newValues.size() != values.size()) {
            throw new IndexOutOfBoundsException("Other size of values");
        } else {
            for (int i = 0; i < newValues.size(); ++i) {
                if (newValues.get(i).getClass() != types.get(i)) {
                    throw new ColumnFormatException("Other type");
                } else {
                    values.set(i, newValues.get(i));
                }
            }
        }
    }

    public StoreableByVolodden(Table table, String[] array) {
        this(table);
        if (array.length != values.size()) {
            throw new IndexOutOfBoundsException("Other size of values");
        } else {
            for (int i = 0; i < array.length; ++i) {
                if (array[i].equals("null")) {
                    values.set(i, null);
                }
                if (table.getColumnType(i) == Integer.class) {
                    values.set(i, Integer.parseInt(array[i]));
                }
                if (table.getColumnType(i) == Long.class) {
                    values.set(i, Long.parseLong(array[i]));
                }
                if (table.getColumnType(i) == Byte.class) {
                    values.set(i, Byte.parseByte(array[i]));
                }
                if (table.getColumnType(i) == Float.class) {
                    values.set(i, Float.parseFloat(array[i]));
                }
                if (table.getColumnType(i) == Double.class) {
                    values.set(i, Double.parseDouble(array[i]));
                }
                if (table.getColumnType(i) == Boolean.class) {
                    values.set(i, Boolean.parseBoolean(array[i]));
                }
                if (table.getColumnType(i) == String.class) {
                    values.set(i, array[i]);
                }
            }
        }
    }

    public StoreableByVolodden(String string, List<Class<?>> inputTypes) {
        types = inputTypes;
        values = new ArrayList<Object>();
        if (string == null) {
            string = "[null]";
        }
        string = string.substring(1, string.length() - 1);
        String[] array = string.split(", ");
        for (int i = 0; i < array.length; ++i) {
            if (array[i].equals("null")) {
                values.add(null);
                continue;
            }
            if (types.get(i) == Integer.class) {
                values.add(Integer.parseInt(array[i]));
            }
            if (types.get(i) == Long.class) {
                values.add(Long.parseLong(array[i]));
            }
            if (types.get(i) == Byte.class) {
                values.add(Byte.parseByte(array[i]));
            }
            if (types.get(i) == Float.class) {
                values.add(Float.parseFloat(array[i]));
            }
            if (types.get(i) == Double.class) {
                values.add(Double.parseDouble(array[i]));
            }
            if (types.get(i) == Boolean.class) {
                values.add(Boolean.parseBoolean(array[i]));
            }
            if (types.get(i) == String.class) {
                values.add(array[i]);
            }
        }
    }

    private void initializeValidTypes() {
        if (validTypes == null) {
            validTypes = new HashSet<>();
            validTypes.add(Integer.class);
            validTypes.add(Long.class);
            validTypes.add(Byte.class);
            validTypes.add(Double.class);
            validTypes.add(Float.class);
            validTypes.add(Boolean.class);
            validTypes.add(String.class);
        }
    }

    @Override
    public void setColumnAt(int columnIndex, Object value) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        if (value != null) {
            checkFormat(columnIndex, value.getClass());
        }
        values.set(columnIndex, value);
    }

    @Override
    public Object getColumnAt(int columnIndex) throws IndexOutOfBoundsException {
        checkBounds(columnIndex);
        return values.get(columnIndex);
    }

    @Override
    public Integer getIntAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, Integer.class);
        return (Integer) values.get(columnIndex);
    }

    @Override
    public Long getLongAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, Long.class);
        return (Long) values.get(columnIndex);
    }

    @Override
    public Byte getByteAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, Byte.class);
        return (Byte) values.get(columnIndex);
    }

    @Override
    public Float getFloatAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, Float.class);
        return (Float) values.get(columnIndex);
    }

    @Override
    public Double getDoubleAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, Double.class);
        return (Double) values.get(columnIndex);
    }

    @Override
    public Boolean getBooleanAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, Boolean.class);
        return (Boolean) values.get(columnIndex);
    }

    @Override
    public String getStringAt(int columnIndex) throws ColumnFormatException, IndexOutOfBoundsException {
        checkBounds(columnIndex);
        checkFormat(columnIndex, String.class);
        return (String) values.get(columnIndex);
    }

    private void checkBounds(int index) throws IndexOutOfBoundsException {
        if (index >= types.size()) {
            throw new IndexOutOfBoundsException("Invalid index.");
        }
    }

    private void checkFormat(int index, Class<?> type) throws ColumnFormatException {
        if (!types.get(index).equals(type)) {
            throw new ColumnFormatException("Invalid format.");
        }
    }
}
