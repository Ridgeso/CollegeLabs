import java.util.Random;
import java.util.Scanner;

public class Game {

    public Game(int size) {
        this.size = size;
        board = new char[2 * size][size];
        this.gameOver = false;
        initBoard();
        printBoard();
    }

    public void play() {
        Scanner moveScanner = new Scanner(System.in);
        while (!gameOver) {
            try {
                System.out.println("> Wykonaj ruch");
                String move = moveScanner.nextLine();
                makeMove(move);
            } catch (OptionNotRecognizedException e) {
                System.out.println(e + " Input must be: l | r | u | d | q");
            } finally {
                printBoard();
            }
        }
    }

    private int charCounter = 0;
    private void printBoard() {
        charCounter = 0;
        executeTheBoard((char oldChar) -> {
            System.out.print(oldChar);
            charCounter++;
            if (charCounter % (2 * size) == 0) {
                System.out.println();
            }
            return oldChar;
        });
    }

    private void makeMove(String move)
        throws OptionNotRecognizedException {
        switch (move) {
            case "l" -> { move(Direction.LEFT); }
            case "r" -> { move(Direction.RIGHT); }
            case "u" -> { move(Direction.UP); }
            case "d" -> { move(Direction.DOWN); }
            case "q" -> { gameOver = true; }
            default -> { throw new OptionNotRecognizedException(); }
        }
    }

    private void move(Direction dir) {
        int newX = playerX + dir.getDirX();
        int newY = playerY + dir.getDirY();

        CheckStep checkStep = (char[][] board, int i0, int j0, Direction direction) -> {
            if (i0 < 0 || i0 >= 2 * size)
                return false;
            if (j0 < 0 || j0 >= size)
                return false;
            return board[i0][j0] != 'X';
        };

        if (checkStep.check(board, newX, newY, dir)) {
            board[playerX][playerY] = '.';
            board[newX][newY] = 'o';

            playerX += dir.getDirX();
            playerY += dir.getDirY();
        }
    }

    private void initBoard() {
        Random randomMap = new Random();
        executeTheBoard((char oldChar) -> { return randomMap.nextFloat() < 0.3 ? 'X' : '.'; });

        playerX = randomMap.nextInt(2 * size);
        playerY = randomMap.nextInt(size);

        board[playerX][playerY] = 'o';
    }

    private void executeTheBoard(MapBoard mapBoard) {
        for (int i = 0; i < 2 * size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = mapBoard.newState(board[i][j]);
            }
        }
    }

    interface MapBoard {
        char newState(char oldChar);
    }

    interface CheckStep {
        boolean check(char[][] board, int i0, int j0, Direction direction);
    }

    static class OptionNotRecognizedException extends IllegalArgumentException { }


    private final char[][] board;
    private boolean gameOver;
    private int playerX, playerY;
    private final int size;
}
