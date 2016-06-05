package com.queens;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;

public class Game {

    private DataFile data;
    private Board board;
    private Player currentPlayer;
    private Player player1;
    private Player player2;
    private String question;
    private String[] answers;
    private String celebrityAnswer;

    public Game(DataFile iData, Player[] players) {
        data = iData;
        board = new Board();
        player1 = players[0];
        player2 = players[1];

        // if player2 is null then make player2 "the computer"
        if (player2 == null) {
            player2 = new Player("the computer", "", new ArrayList<>());
        }

        board.setSecretSquare();
        pickFirstPlayer();
    }

    public Player getCurrentPlayer() {
        return currentPlayer;
    }

    public Player getPlayer1() {
        return player1;
    }

    public Player getPlayer2() {
        return player2;
    }

    public void pickFirstPlayer() {
        Random randomNum = new Random();
        int headsOrTails = randomNum.nextInt(2);

        // computer always goes second
        if (player2.getUsername().equals("the computer")) {
            headsOrTails = 0;
        }

        if (headsOrTails == 0) {
            currentPlayer = player1;
            player1.setMarker(1);
            player2.setMarker(2);

        } else {
            currentPlayer = player2;
            player2.setMarker(1);
            player1.setMarker(2);

        }
    }

    public void nextPlayer() {
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }
    }

    public void selectQuestion() {
        HashMap<String, String[]> randomQuestion = data.getQuestion();
        question = (String) (randomQuestion.keySet().toArray())[0];
        answers = randomQuestion.get(question);
        celebrityAnswer = answers[new Random().nextInt(answers.length)];
    }

    public int getSecretSquare() {
        return board.getSecretSquare();
    }

    public String getQuestion() {
        return question;
    }

    public String getCelebrityAnswer() {
        return celebrityAnswer;
    }

    public boolean checkCelebAnswer() {
        return celebrityAnswer.equals(answers[0]);
    }

    public int determineSquareFate(boolean playerAnswer, int index) {

        System.out.println("-- Current player is " + currentPlayer.getUsername() + ", determining square " + index + "'s fate");

        // if the current player has the correct answer, set the square
        if (playerAnswer && checkCelebAnswer() || !playerAnswer && !checkCelebAnswer()) {

            System.out.println("Marking current player (" + currentPlayer.getUsername() + ")");
            board.setSquare(index, currentPlayer);
            if (index == board.getSecretSquare()) {
                currentPlayer.incCurrentScore(5);
                currentPlayer.incMarkerCount(1);
                return currentPlayer.getMarker();
            } else {
                currentPlayer.incCurrentScore(1);
                currentPlayer.incMarkerCount(1);
                return currentPlayer.getMarker();
            }

            // else set the square for the otherPlayer but if the otherPlayer
            // wins then reset the square
        } else {

            Player otherPlayer = player1;
            if (currentPlayer == otherPlayer) {
                otherPlayer = player2;
            }

            System.out.println("Marking other player (" + otherPlayer.getUsername()
                    + ") and then going to check if he/she has won");

            board.setSquare(index, otherPlayer);
            if (index == board.getSecretSquare()) {
                otherPlayer.incMarkerCount(1);
                otherPlayer.incCurrentScore(5);
            } else {
                otherPlayer.incMarkerCount(1);
                otherPlayer.incCurrentScore(1);
            }

            // if the other player wins by setting square then resetSquare and
            // decrement markerCount and currentScore
            if (board.checkPlayerIsWinner(otherPlayer)) {
                System.out.println("Other player (" + otherPlayer.getUsername()
                        + ") wins if the square is set, square will now be reset");

                board.updateAvailableSquares();
                board.resetSquare(index);
                if (index == board.getSecretSquare()) {
                    otherPlayer.incMarkerCount(-1);
                    otherPlayer.incCurrentScore(-5);
                } else {
                    otherPlayer.incMarkerCount(-1);
                    otherPlayer.incCurrentScore(-1);
                }
                return 0;  // Nobody gets the square

                // else the other player does not win with the new square and gets to keep it
            } else {
                System.out.println("Other player (" + otherPlayer.getUsername()
                        + ") does not win, other player keeps the square");

                return otherPlayer.getMarker();
            }
        }
    }

    public boolean checkCurrentPlayerIsWinner() {
        if (board.checkPlayerIsWinner(currentPlayer)) {
            currentPlayer.addHighScore();
            data.writePlayers();
            return true;
        }

        return false;
    }

    public int computerSelectSquare() {
        int index = new Random().nextInt(board.getAvailableSquares().size());
        return board.getAvailableSquares().get(index);
    }

    public boolean computerResponse() {
        Random randomNum = new Random();
        int result = randomNum.nextInt(2);

        if (result == 0) {
            return true;
        } else {
            return false;
        }
    }

    public void restartGame() {
        board.resetBoard();
        player1.resetMarkerCount();
        player1.resetCurrentScore();
        player2.resetMarkerCount();
        player2.resetCurrentScore();
    }
}
