import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;

public class SortOnDisk {

    private final static String folderName = "data";
    private final static String extension = ".dat";

    private class Helper {
        private DataInputStream input;
        private int number;
        private  int name;

        Helper(int _number, int _name) throws FileNotFoundException {
            number = _number;
            name = _name;
            input = new DataInputStream(new FileInputStream(name + extension));
        }
    }

    public void run() {
        try {
            int count = readAndSplit();
            if (count < 0) {
                return;
            }
            merge(count + 1);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    private int readAndSplit() {
        int n = -1;
        try (Scanner scanner = new Scanner(System.in)) {
            String name = scanner.nextLine();
            if (!Paths.get(name).toFile().exists()) {
                return n;
            }
            try (DataInputStream input = new DataInputStream(new FileInputStream(name))) {
                if (!Paths.get(folderName).toFile().exists()) {
                    Files.createDirectory(Paths.get(folderName));
                }
                if (!Paths.get(folderName).toFile().isDirectory()) {
                    Files.delete(Paths.get(folderName));
                    Files.createDirectory(Paths.get(folderName));
                }
                boolean flag = false;
                while (true) {
                    ++n;
                    TreeSet<Integer> set = new TreeSet<Integer>();
                    int k = 1;
                    try {
                        while (k <= 8388606) {
                            ++k;
                            set.add(input.readInt());
                        }
                    } catch (EOFException e) {
                        flag = true;
                    }
                    if (!set.isEmpty()) {
                        try (FileOutputStream output = new FileOutputStream(Paths.get(folderName, n + extension).toString())) {
                            for (Integer number : set) {
                                output.write(number.byteValue());
                            }
                        }
                    } else {
                        --n;
                    }
                    if (flag) {
                        break;
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                return n;
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return n;
    }

    private void merge(int count) throws IOException {
        System.setProperty("user.dir", folderName);
        int countFiles = 16;
        int currentNumber = 0;
        int maxNumber = count;

        while (true) {
            if (Paths.get("user.dir").toFile().list().length == 1) {
                String lastName = Paths.get("user.dir").toFile().list()[0];
                Files.copy(Paths.get(lastName), Paths.get("..", "output" + extension),  StandardCopyOption.COPY_ATTRIBUTES, StandardCopyOption.REPLACE_EXISTING);
                Files.delete(Paths.get(lastName));
                Files.delete(Paths.get("..", folderName));
                break;
            }
            boolean[] files = new boolean[countFiles];
            Helper[] inputs = new Helper[countFiles];
            int tempCurrent = countFiles;
            for (int i = 0; i < countFiles; ++i) {
                if (Paths.get(i + extension).toFile().exists()) {
                    inputs[i] = new Helper(i, currentNumber + i);
                    files[i] = false;
                } else {
                    files[i] = true;
                    if (tempCurrent > i) {
                        tempCurrent = i;
                    }
                }
            }
            if (tempCurrent != countFiles) {
                tempCurrent = currentNumber + tempCurrent;
            } else {
                tempCurrent = maxNumber;
                ++maxNumber;
                currentNumber += countFiles;
            }
            try (FileOutputStream output = new FileOutputStream(tempCurrent + extension)) {
                TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer>();
                for (int i = 0; i < countFiles; ++i) {
                    map.put(inputs[i].input.readInt(), inputs[i].number);
                }
                while (true) {
                    boolean result = true;
                    for (int i = 0; i < countFiles; ++i) {
                        result = result && files[i];
                    }
                    if (result) {
                        break;
                    }
                    output.write(map.firstKey().byteValue());
                    int first = map.get(map.firstKey());
                    try {
                        map.put(inputs[first].input.readInt(), map.remove(map.firstKey()));
                    } catch (EOFException e) {
                        files[first] = true;
                        inputs[first].input.close();
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
