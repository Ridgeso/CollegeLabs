import java.time.LocalDate;
import java.util.*;
import java.io.*;

/**
 * Java laboratories number 5
 * Project Name: Reading from files
 */
public class Lab5 {
    /**
     * Program reads and parses csv file with specific params for more
     * @see Movie
     * @see VHS
     * @param args: empty array
     */
    public static void main(String[] args) {
        VHS[] vhss = null;
        try
        {
            BufferedReader f = new BufferedReader(new FileReader("VHS.csv") );
            f.readLine(); // skipping first line
            String s;
            StringBuilder fileContent = new StringBuilder();
            while( (s = f.readLine()) != null )
            {
                fileContent.append(s);
                fileContent.append("\n");
            }
            String[] fileLines = fileContent.toString().split("\n");
            vhss = new VHS[fileLines.length];
            for (int i = 0; i < fileLines.length; i++)
            {
                String[] spliteData = fileLines[i].split(",");

                UUID localUUID = UUID.fromString(spliteData[0]);

                Movie localMovie = new Movie(Integer.parseInt(spliteData[2]), spliteData[1], spliteData[3]);

                String[] sReturnal = spliteData[5].split("-");
                LocalDate LReturnalDate = LocalDate.of(
                    Integer.parseInt(sReturnal[0]),
                    Integer.parseInt(sReturnal[1]),
                    Integer.parseInt(sReturnal[2])
                );

                String[] sRental = spliteData[4].split("-");
                LocalDate LRentalDate = LocalDate.of(
                    Integer.parseInt(sRental[0]),
                    Integer.parseInt(sRental[1]),
                    Integer.parseInt(sRental[2])
                );

                vhss[i] = new VHS(localMovie, LReturnalDate, localUUID, LRentalDate);
            }
        }
        catch( Throwable e )
        {
            System.out.println("Nie ma go");
        }
        if (vhss != null)
        {
            System.out.println(vhss.length);
            for (VHS vhs : vhss)
                System.out.println(vhs);
        }
    }
}