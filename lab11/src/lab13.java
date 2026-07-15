import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

class lab13
{
    public static void  main(String[] args)
            throws IOException
    {
        var file = Files.newBufferedReader(Path.of("angpol.dic"));
        var historyFile = Files.newBufferedWriter(Path.of("history.dat"));

        var slownik = new HashMap<String, Translation>();

        String line;
        while ((line = file.readLine()) != null)
        {
            var tokens = line.split(",");
            Translation translation = null;
            switch (tokens.length)
            {
                case 3 -> translation = new Translation(Integer.parseInt(tokens[1]), tokens[2], null, null);
                case 4 -> translation = new Translation(Integer.parseInt(tokens[1]), tokens[2], tokens[3], null);
                case 5 -> translation = new Translation(Integer.parseInt(tokens[1]), tokens[2], tokens[3], tokens[4]);
            }
            slownik.put(tokens[0], translation);
        }
        file.close();

        var input = new Scanner(System.in);
        while (input.hasNext())
        {
            var text = input.next();
            if (text.equals("exit"))
            {
                break;
            }
            var tlum = slownik.getOrDefault(text, new Translation(0, "_", null, null));
            var wynik = "Tlumaczenie [" + text + "]: " + tlum + "\n";
            System.out.print(wynik);
            historyFile.write(wynik);
        }
        historyFile.close();


        /////////////////////////////////
        var temp = new StringArray();

        { // Poczatek
            var al = new ArrayList<String>();
            var ll = new LinkedList<String>();

            var frontAppendingAl = System.nanoTime();
            for (var rs : temp.getT1()) {
                al.add(0, rs);
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Dodanie na poczatek do ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            for (var rs : temp.getT1()) {
                ll.add(0, rs);
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Dodanie na poczatek do LinkedList zajelo: " + frontAppendingLLFinish);
        }

        System.out.println();

        { // Srodek
            var al = new ArrayList<String>();
            var ll = new LinkedList<String>();

            var frontAppendingAl = System.nanoTime();
            for (var rs : temp.getT1()) {
                al.add(al.size() / 2, rs);
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Dodanie na srodek do ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            for (var rs : temp.getT1()) {
                ll.add(ll.size() / 2, rs);
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Dodanie na srodek do LinkedList zajelo: " + frontAppendingLLFinish);
        }

        System.out.println();

        var al = new ArrayList<String>();
        var ll = new LinkedList<String>();
        { // Koniec
            var frontAppendingAl = System.nanoTime();
            for (var rs : temp.getT1()) {
                al.add(rs);
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Dodanie na koniec do ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            for (var rs : temp.getT1()) {
                ll.add(rs);
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Dodanie na koniec do LinkedList zajelo: " + frontAppendingLLFinish);
        }

        System.out.println();

        { // Szukanie t2
            var frontAppendingAl = System.nanoTime();
            for (var rs : temp.getT2()) {
                var isIm = al.contains(rs);
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Szukanie t2 w ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            for (var rs : temp.getT2()) {
                var isIm = ll.contains(rs);
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Szukanie t2 w LinkedList zajelo: " + frontAppendingLLFinish);
        }

        System.out.println();

        { // Szukanie t3
            var frontAppendingAl = System.nanoTime();
            for (var rs : temp.getT3()) {
                var isIm = al.contains(rs);
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Szukanie t3 w ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            for (var rs : temp.getT3()) {
                var isIm = ll.contains(rs);
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Szukanie t3 w LinkedList zajelo: " + frontAppendingLLFinish);
        }

        System.out.println();

        { // Iterowanie foreach

            var frontAppendingAl = System.nanoTime();
            for (int i = 0; i < al.size(); i++) {
                al.get(i);
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Iterowanie foreach w ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            for (int i = 0; i < ll.size(); i++) {
                ll.get(i);
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Iterowanie foreach w LinkedList zajelo: " + frontAppendingLLFinish);
        }

        System.out.println();

        { // iterowanie while
            var frontAppendingAl = System.nanoTime();
            int i = 0;
            while (i < al.size()) {
                al.get(i);
                i++;
            }
            var frontAppendingAlFinish = (System.nanoTime() - frontAppendingAl) / 1e9;
            System.out.println("Iterowanie while w ArrayList zajelo: " + frontAppendingAlFinish);

            var frontAppendingLL = System.nanoTime();
            i = 0;
            while (i < ll.size()) {
                ll.get(i);
                i++;
            }
            var frontAppendingLLFinish = (System.nanoTime() - frontAppendingLL) / 1e9;
            System.out.println("Iterowanie while w LinkedList zajelo: " + frontAppendingLLFinish);
        }
    }
}
