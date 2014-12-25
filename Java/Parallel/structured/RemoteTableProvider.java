package ru.fizteh.fivt.students.Volodin_Denis.Parallel.structured;

import java.io.Closeable;

/**
 *  Расширенный интерфейс {@link TableProvider}, с предоставлением метода {@link #close()}.
 */
public interface RemoteTableProvider extends TableProvider, Closeable {
}
