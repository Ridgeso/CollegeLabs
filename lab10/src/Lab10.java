import java.util.InputMismatchException;
import java.util.Scanner;

public class Lab10 {
    public static void validateSize(int size)
        throws IllegalArgumentException {
        if (size <= 1)
            throw new IllegalArgumentException();
    }

    public static void main(String[] args) {
        int size = 2;

        boolean finalyPlay = false;

        while (!finalyPlay) {
            try {
                System.out.println("> Podaj wysokosc planszy");
                Scanner sc = new Scanner(System.in);
                size = sc.nextInt();
                validateSize(size);
                finalyPlay = true;
            } catch (InputMismatchException e) {
                System.out.println("Input must be a number!\tTry Again");
            } catch (IllegalArgumentException e) {
                System.out.println("Board Size cannot be less than 1x1\tTry Again");
            }
        }

        Game game = new Game(size);
        game.play();
    }
}
