package com.queens;

import java.util.ArrayList;
import java.util.Random;

public class Board {
    private int[] board;
    private ArrayList<Integer> availableSquares; // list available squares
    private int secretSquare;

    public Board() {
        board = new int[9];
        availableSquares = new ArrayList<>();

        updateAvailableSquares();
    }

    public ArrayList<Integer> getAvailableSquares() {
        return availableSquares;
    }

    public void updateAvailableSquares() {
        availableSquares = new ArrayList<>();

        for (int i = 0; i < board.length; i++) {
            if (board[i] == 0) {
                availableSquares.add(i);
            }
        }
    }

    public int[] getBoard() {
        return board;
    }

    public void resetBoard() {

        for (int i = 0; i < board.length; i++) {
            board[i] = 0;
        }
    }

    public void setSecretSquare() {
        secretSquare = new Random().nextInt(9);
        System.out.println("Secret square has been set. "+ secretSquare);
    }

    public int getSecretSquare() {
        return secretSquare;
    }

    public void setSquare(int index, Player currentPlayer) {
        if (board[index] != 0) {
            System.out.println("Error, spot on board is already filled");
            System.exit(1);
        }

        this.board[index] = currentPlayer.getMarker();

        updateAvailableSquares();
        System.out.print("Available squares after selection " + availableSquares);

        System.out.print("     Board state: ");
        for (int i: board) {
            System.out.print(i);
        }
        System.out.println();
    }

    public void resetSquare(int index) {
        this.board[index] = 0;
    }

    /**
     * Check if current player has won the game
     *
     *  0 1 2  |
     *  3 4 5  |-->  [0 1 2 3 4 5 6 7 8]
     *  6 7 8  |
     *
     * @return true or false depending on if currentPlayer has won
     */
    public boolean checkPlayerIsWinner(Player incomingPlayer) {
        int marker = incomingPlayer.getMarker();

                // horizontal wins
        return  (board[0] == board[1] && board[0] == board[2] && board[0] == marker) ||
                (board[3] == board[4] && board[3] == board[5] && board[3] == marker) ||
                (board[6] == board[7] && board[6] == board[8] && board[6] == marker) ||

                // vertical wins
                (board[0] == board[3] && board[0] == board[6] && board[0] == marker) ||
                (board[1] == board[4] && board[1] == board[7] && board[1] == marker) ||
                (board[2] == board[5] && board[2] == board[8] && board[2] == marker) ||

                // diagonal wins
                (board[0] == board[4] && board[0] == board[8] && board[0] == marker) ||
                (board[2] == board[4] && board[2] == board[6] && board[2] == marker) ||

                (incomingPlayer.getMarkerCount() >= 5);
    }
}
