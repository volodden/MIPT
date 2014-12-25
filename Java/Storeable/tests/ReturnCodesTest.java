package ru.fizteh.fivt.students.Volodin_Denis.Storeable.tests;

import org.junit.Test;
import ru.fizteh.fivt.students.Volodin_Denis.Storeable.main.ReturnCodes;

import static org.junit.Assert.*;

public class ReturnCodesTest {

    @Test
    public void testConstructor() {
        ReturnCodes rc = new ReturnCodes();
        assertEquals(rc.SUCCESS, ReturnCodes.SUCCESS);
    }
}
