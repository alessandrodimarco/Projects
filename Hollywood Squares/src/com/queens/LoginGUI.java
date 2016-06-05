package com.queens;

import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import javax.xml.bind.ValidationException;
import java.util.Optional;

public class LoginGUI {

    private Stage loginStage;
    private Player[] players = new Player[2];
    private static DataFile data;
    private GameGUI gameGUI;

    public LoginGUI(DataFile data, Player[] players) {
        LoginGUI.data = data;
        this.players = players;
    }

    public void launchLogin(Stage stage) {
        loginStage = stage;

        // LOGIN PANEL FRAME CREATION
        GridPane loginPane = new GridPane();
        loginPane.setAlignment(Pos.CENTER);
        loginPane.setHgap(10);
        loginPane.setVgap(10);
        loginPane.setPadding(new Insets(25, 25, 25, 25));

        // LOGIN TITLE
        Text scenetitle = new Text("Please Login or Register");
        scenetitle.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        loginPane.add(scenetitle, 0, 0, 2, 1);

        // POP UP MESSAGES
        Alert loginAlert = new Alert(Alert.AlertType.WARNING);
        Alert selectAlert = new Alert(Alert.AlertType.CONFIRMATION);
        ButtonType buttonTypeOne = new ButtonType("One");
        ButtonType buttonTypeTwo = new ButtonType("Two");
        ButtonType buttonTypeCancel = new ButtonType("Cancel", ButtonBar.ButtonData.CANCEL_CLOSE);
        selectAlert.getButtonTypes().setAll(buttonTypeOne, buttonTypeTwo, buttonTypeCancel);
        selectAlert.setTitle("Hollywood Squares");
        selectAlert.setHeaderText("");
        selectAlert.setContentText("Select number of players: ");

        // USER NAME BOX
        Label userName = new Label("Username:");
        loginPane.add(userName, 0, 1);
        TextField userField = new TextField();
        userField.setPromptText("Username");
        loginPane.add(userField, 1, 1);

        // PASSWORD BOX
        Label password = new Label("Password:");
        loginPane.add(password, 0, 2);
        PasswordField passField = new PasswordField();
        passField.setPromptText("Password");
        loginPane.add(passField, 1, 2);

        //PASSWORD CONFIRMATION DIALOG BOX
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(20, 10, 10, 10));

        Dialog<String> confirm = new Dialog<>();
        confirm.setTitle("Password Check");
        confirm.setHeaderText("Please confirm your password");
        PasswordField confirmPass = new PasswordField();
        confirmPass.setPromptText("Password");

        ButtonType confirmBtn = new ButtonType("Confirm");
        ButtonType cancelBtn = new ButtonType("Cancel");

        //ButtonType loginButtonType = new ButtonType("Confirm", ButtonBar.ButtonData.OK_DONE);
        confirm.getDialogPane().getButtonTypes().addAll(confirmBtn, cancelBtn);

        grid.add(new Label("Password:"), 0, 0);
        grid.add(confirmPass, 1, 0);

        confirm.getDialogPane().setContent(grid);


        // LOGIN BUTTON
        Button logBtn = new Button("Login");
        HBox hbBtn = new HBox(10);
        hbBtn.setAlignment(Pos.BOTTOM_RIGHT);
        hbBtn.getChildren().add(logBtn);
        loginPane.add(hbBtn, 1, 4);

        // REGISTER BUTTON
        Button rBtn = new Button("Register");
        HBox hbBtn2 = new HBox(10);
        hbBtn2.setAlignment(Pos.BOTTOM_RIGHT);
        hbBtn2.getChildren().add(rBtn);
        loginPane.add(hbBtn2, 1, 5);

        // Disable password field until previous field filled
        Node loginButton = logBtn;
        logBtn.setDisable(true);

        Node registerButton = rBtn;
        registerButton.setDisable(true);

        userField.textProperty().addListener((observable, oldValue, newValue) -> {
            passField.textProperty().addListener((ob, ov, nv) -> {
                registerButton.setDisable(nv.trim().isEmpty());
                loginButton.setDisable(nv.trim().isEmpty());
            });
        });

        // LOGIN button action
        logBtn.setOnAction(e -> {
            String tempUser = userField.getText();
            String tempPass = passField.getText();

            //check if player credentials are valid based on their input
            if (data.checkPlayerCredentials(tempUser, tempPass)) {

                if (GameGUI.returnLogin) {
                    players[0] = null;
                    players[1] = null;
                    GameGUI.returnLogin = false;
                }

                // assign verified players to array depending on case 1 or case 2
                if (players[0] == null) {
                    players[0] = data.getPlayer(tempUser);

                } else if (players[1] == null) {
                    players[1] = data.getPlayer(tempUser);

                    //check if player 2 is duplicate player 1
                    if (players[1].getUsername().equals(players[0].getUsername())) {
                        loginAlert.setTitle("Error");
                        loginAlert.setHeaderText("You can't play against yourself, dummy");
                        loginAlert.setContentText("Make sure player two is a different account");
                        loginAlert.showAndWait();
                        players[1] = null;
                    }
                }

                // TWO PLAYERS LOGGED IN, SWITCH STAGE TO GAME STAGE
                if (players[1] != null && players[0] != null) {
                    loginAlert.setTitle("Game Start");
                    loginAlert.setHeaderText("Two player game ");
                    loginAlert.setContentText("Press OK to start!");
                    loginAlert.showAndWait();
                    gameGUI = new GameGUI(data, players, this);
                    gameGUI.launchGame(loginStage);
                }

                // PLayer 1 logged in successfully, BEGIN SELECTION SEQUENCE
                if (players[0] != null && players[1] == null) {
                    Optional<ButtonType> result = selectAlert.showAndWait();

                    // START GAME WITH PLAYER 1 VS CPU
                    if (result.get() == buttonTypeOne) {
                        loginAlert.setTitle("Game Start");
                        loginAlert.setHeaderText("One player game ");
                        loginAlert.setContentText("Press OK to start!");
                        loginAlert.showAndWait();
                        gameGUI = new GameGUI(data, players, this);
                        gameGUI.launchGame(loginStage);

                        // GO BACK TO LOGIN SCREEN AND REGISTER PLAYER 2
                    } else if (result.get() == buttonTypeTwo) {
                        userField.clear();
                        passField.clear();
                        scenetitle.setText("Player 2 - Please Login");

                        // USER PRESSED X OR CANCEL, reset player 0
                    } else {
                        players[0] = null;
                        passField.clear();
                    }
                }
            } else {
                loginAlert.setTitle("Login Error");
                loginAlert.setHeaderText("Username or password incorrect");
                loginAlert.setContentText("Are you registered?");
                loginAlert.showAndWait();
                passField.clear();
            }
        });

        // REGISTER button action
        rBtn.setOnAction(e -> {

            String tempUser = userField.getText();
            String tempPass = passField.getText();
            Platform.runLater(() -> confirmPass.requestFocus());

            confirm.setResultConverter(button -> {
                if (button == confirmBtn) {
                    return "ok";
                } else if (button == cancelBtn) {
                    return "cancel";
                } else return "exit";
            });

            confirm.showAndWait().ifPresent(result -> {
                if (result.equals("ok")) {
                    if (tempPass.equals(confirmPass.getText())) {
                        try {
                            data.addPlayer(tempUser, tempPass);
                            data.writePlayers();
                            loginAlert.setTitle("Registration");
                            loginAlert.setHeaderText("Registration Successful");
                            loginAlert.setContentText("You can now login with your account");
                            loginAlert.showAndWait();
                            confirmPass.clear();

                        } catch (ValidationException e0) {
                            loginAlert.setTitle("Registration Error");
                            loginAlert.setHeaderText("");
                            loginAlert.setContentText("Text fields cannot have blank spaces");
                            loginAlert.showAndWait();
                            passField.clear();
                            userField.clear();

                        } catch (SecurityException e1) {
                            loginAlert.setTitle("Registration Error");
                            loginAlert.setHeaderText("");
                            loginAlert.setContentText("Text fields cannot be empty!");
                            loginAlert.showAndWait();

                        } catch (Exception e2) {
                            loginAlert.setTitle("Registration Error");
                            loginAlert.setHeaderText("Username " + tempUser + " is already taken");
                            loginAlert.setContentText("Please try an alternative");
                            loginAlert.showAndWait();
                            passField.clear();
                            userField.clear();
                        }

                    } else {
                        loginAlert.setTitle("Registration Error");
                        loginAlert.setHeaderText("Password fields did not match");
                        loginAlert.setContentText("Please type carefully");
                        loginAlert.showAndWait();
                        confirmPass.clear();
                        passField.clear();
                    }
                }
            });
        });

        Scene loginScene = new Scene(loginPane, 340, 250);
        loginStage.setTitle("Hollywood Squares");
        loginStage.setScene(loginScene);
        loginStage.setResizable(true);
        loginStage.show();
    }
}
