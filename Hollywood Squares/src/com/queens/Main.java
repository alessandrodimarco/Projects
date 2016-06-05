package com.queens;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    private static DataFile data;
    private static Player[] players = new Player[2];

    public void start(Stage primaryStage) throws Exception {
        LoginGUI loginGUI = new LoginGUI(data, players);
        loginGUI.launchLogin(primaryStage);
    }

    public static void main(String[] args) {
        data = new DataFile();
        launch(args);
    }
}
