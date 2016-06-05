package com.queens;

import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Screen;
import javafx.stage.Stage;

public class GameGUI {

    private Button[] boardButtons;
    private Button agree;
    private Button disagree;
    private Button endTurn;
    private Button restart;
    private Text scores;
    private Text question;
    private Text celebrityResponse;
    private Text isCorrect;
    private Text currentPlayer;
    private Text currentPlayerHS;
    private int selectedSquare;

    public static boolean returnLogin = false;

    private Stage boardStage;
    private Scene gameScene;

    private static Game game;
    private static DataFile data;
    private static LoginGUI loginGUI;
    private Player[] players = new Player[2];

    public GameGUI(DataFile iData, Player[] iPlayers, LoginGUI iloginGUI) {
        data = iData;
        players = iPlayers;
        loginGUI = iloginGUI;
    }

    public void launchGame(Stage stage) {
        boardStage = stage;

        // Initialize game
        game = new Game(data, players);

        initializeButtonsAndText();

        // Initialize boardButtons
        for (Integer i = 0; i < boardButtons.length; i++) {
            boardButtons[i] = new Button();
            boardButtons[i].setPrefSize(100, 100);
            boardButtons[i].setId(Integer.toString(i));

            boardButtons[i].setOnAction(e -> {
                selectedSquare = Integer.parseInt(((Control) e.getSource()).getId());
                boardButtonBehavior();
            });
        }

        agree.setOnAction(e -> playerFeedback(game.determineSquareFate(true, selectedSquare)));
        disagree.setOnAction(e -> playerFeedback(game.determineSquareFate(false, selectedSquare)));

        //MENU OPTION PANE START
        GridPane grid = new GridPane();
        grid.setPrefSize(420, 10);
        grid.setHgap(20);
        grid.setVgap(20);

        Dialog<String> menu = new Dialog<>();
        menu.setTitle("MENU");

        menu.setHeaderText("Please select an option\nNote: To exit game close game window.");

        ButtonType restartBtn = new ButtonType("Reset Board", ButtonBar.ButtonData.RIGHT);
        ButtonType loginBtn = new ButtonType("Return to Login", ButtonBar.ButtonData.RIGHT);
        ButtonType cancelBtn = new ButtonType("Cancel", ButtonBar.ButtonData.CANCEL_CLOSE);

        menu.getDialogPane().getButtonTypes().addAll(restartBtn, loginBtn, cancelBtn);
        menu.getDialogPane().setContent(grid);

        restart.setOnAction(ex -> {
            menu.setResultConverter(button -> {
                if (button == restartBtn) {
                    return "restart";
                } else if (button == loginBtn) {
                    return "login";
                } else if (button == cancelBtn) {
                    return "exit";
                }
                return "exit";
            });

            menu.showAndWait().ifPresent(result -> {
                if (result.equals("exit")) menu.close();
                if (result.equals("restart")) {
                    game.restartGame();
                    this.launchGame(boardStage);
                } else if (result.equals("login")) {
                    returnLogin = true;
                    game.restartGame();
                    loginGUI.launchLogin(boardStage);
                }
            });
        });
        //END MENU PANE

        endTurn.setOnAction(e -> {
            game.nextPlayer();

            // if the next player is "the computer" then select a square and then call nextPlayer
            if (game.getCurrentPlayer().getUsername().equals("the computer")) {
                selectedSquare = game.computerSelectSquare();
                if (selectedSquare == game.getSecretSquare()) {
                    boardButtons[selectedSquare].setStyle("-fx-base: #33FFF6");
                }
                playerFeedback(game.determineSquareFate(game.computerResponse(), selectedSquare));
            }

            // if the computer does not win from the playerFeedback() call then enable the buttons
            if (!game.checkCurrentPlayerIsWinner()) {
                displayPlayerTurnAndInstructions();

                // Enable all buttons that are blank
                for (Button guiBoardSquare : boardButtons) {
                    if (guiBoardSquare.getText().equals("")) {
                        guiBoardSquare.setDisable(false);
                    }
                }
            }

            // Disable end turn button
            ((Control) e.getSource()).setVisible(false);
        });

        gameScene = new Scene(createGameBox(), 700, 600);

        Rectangle2D primScreenBounds = Screen.getPrimary().getVisualBounds();
        boardStage.setTitle("Hollywood Squares");
        boardStage.setX((primScreenBounds.getWidth() - stage.getWidth()) / 3);
        boardStage.setY((primScreenBounds.getHeight() - stage.getHeight()) / 5);
        boardStage.setScene(gameScene);
        boardStage.setResizable(true);
        boardStage.show();
    }

    private void playerFeedback(int squareMarker) {
        if (squareMarker == game.getCurrentPlayer().getMarker())
            isCorrect.setText("Correct");
        else
            isCorrect.setText("Wrong");

        displayCurrentScore();

        // Check if the current player is the winner
        if (game.checkCurrentPlayerIsWinner()) {
            System.out.println("Current player (" + game.getCurrentPlayer().getUsername() + ") is the winner\n");

            // Display winner on GUI
            question.setText(game.getCurrentPlayer().getUsername() + " has won");

            // Hide endTurn Button
            endTurn.setVisible(false);

            // Clear text on screen
            celebrityResponse.setText("");
            currentPlayer.setText("");
            currentPlayerHS.setText("");
            isCorrect.setText("");

        } else if (game.getCurrentPlayer().getUsername().equals("the computer")) {
            game.nextPlayer();
            System.out.println("Current player (" + game.getCurrentPlayer().getUsername() + ") is not the winner\n");
            endTurn.setVisible(true);
        } else {
            System.out.println("Current player (" + game.getCurrentPlayer().getUsername() + ") is not the winner\n");
            endTurn.setVisible(true);
        }

        agree.setVisible(false);
        disagree.setVisible(false);

        // Update marker on square
        if (squareMarker == 1)
            boardButtons[selectedSquare].setText("X");
        else if (squareMarker == 2)
            boardButtons[selectedSquare].setText("O");
    }

    private void boardButtonBehavior() {
        // When square is clicked, pick a question from the file
        game.selectQuestion();

        if (selectedSquare == game.getSecretSquare()) {
            boardButtons[selectedSquare].setStyle("-fx-base: #33FFF6");
            question.setText("SECRET SQUARE QUESTION!   " + game.getQuestion());
        } else {
            // set the Text for question and celebrityResponse
            question.setText(game.getQuestion());
        }
        celebrityResponse.setText("Celebrity response: " + game.getCelebrityAnswer());

        // set Text and Buttons visible
        agree.setVisible(true);
        disagree.setVisible(true);

        // Disable all buttons after one button is clicked
        for (Button guiBoardSquare : boardButtons) {
            guiBoardSquare.setDisable(true);
        }
    }

    private void initializeButtonsAndText() {
        // Initialize buttons
        boardButtons = new Button[9];
        agree = new Button("True");
        disagree = new Button("False");
        endTurn = new Button("End Turn");
        restart = new Button("MENU");

        // set size of buttons
        agree.setPrefSize(100, 20);
        disagree.setPrefSize(100, 20);
        endTurn.setPrefSize(100, 20);
        restart.setPrefSize(100, 20);

        // Hide agree, disagree and endTurn buttons
        agree.setVisible(false);
        disagree.setVisible(false);
        endTurn.setVisible(false);

        restart.setVisible(true);

        // Initialize text fields
        scores = new Text();
        question = new Text();
        celebrityResponse = new Text();
        isCorrect = new Text();
        currentPlayer = new Text();
        currentPlayerHS = new Text();

        displayPlayerTurnAndInstructions();
        displayCurrentScore();
    }

    private VBox createGameBox() {
        VBox gameBox = new VBox(20);
        gameBox.setAlignment(Pos.CENTER);

        HBox scoreBox = new HBox(20);
        scoreBox.setAlignment(Pos.CENTER);

        HBox questionBox = new HBox(20);
        questionBox.setAlignment(Pos.CENTER);

        HBox responseBox = new HBox(20);
        questionBox.setAlignment(Pos.CENTER);

        HBox firstRowSquares = new HBox(20);
        firstRowSquares.setAlignment(Pos.CENTER);

        HBox secondRowSquares = new HBox(20);
        secondRowSquares.setAlignment(Pos.CENTER);

        HBox thirdRowSquares = new HBox(20);
        thirdRowSquares.setAlignment(Pos.CENTER);

        HBox trueOrFalseBox = new HBox(20);
        trueOrFalseBox.setAlignment(Pos.CENTER);

        HBox highScoresBox = new HBox(20);
        highScoresBox.setAlignment(Pos.CENTER);

        firstRowSquares.getChildren().addAll(boardButtons[0], boardButtons[1], boardButtons[2]);
        secondRowSquares.getChildren().addAll(boardButtons[3], boardButtons[4], boardButtons[5]);
        thirdRowSquares.getChildren().addAll(boardButtons[6], boardButtons[7], boardButtons[8]);

        scoreBox.getChildren().addAll(scores);
        questionBox.getChildren().addAll(question);
        responseBox.getChildren().addAll(celebrityResponse, isCorrect);
        trueOrFalseBox.getChildren().addAll(currentPlayer, agree, disagree, endTurn, restart);
        highScoresBox.getChildren().addAll(currentPlayerHS);

        gameBox.getChildren().addAll(scoreBox, questionBox, responseBox, firstRowSquares, secondRowSquares, thirdRowSquares, trueOrFalseBox, highScoresBox);

        return gameBox;
    }

    private void displayPlayerTurnAndInstructions() {
        question.setText("Please select a square");
        celebrityResponse.setText("");
        isCorrect.setText("");
        currentPlayer.setText(game.getCurrentPlayer().getUsername() + "'s turn");
        currentPlayerHS.setText(game.getCurrentPlayer().getUsername() + "'s high scores: " + game.getCurrentPlayer().getHighScores().toString());
    }

    private void displayCurrentScore() {
        scores.setText("Scores:    " +
                game.getPlayer1().getUsername() + " (" + game.getPlayer1().getMarkerLetter() + "):   " + game.getPlayer1().getCurrentScore() + "        " +
                game.getPlayer2().getUsername() + " (" + game.getPlayer2().getMarkerLetter() + "):   " + game.getPlayer2().getCurrentScore());
    }

}
