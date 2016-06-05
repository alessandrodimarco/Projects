package com.queens;

import javax.xml.bind.ValidationException;
import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static sun.audio.AudioPlayer.player;

public class DataFile {
    private Scanner playersData;
    private Scanner questionsData;
    private PrintWriter writePlayersData;

    private HashMap<String, Player> players;
    private HashMap<String, String[]> questions;
    private HashMap<String, String[]> questionsClone;

    public DataFile() {
        players = new HashMap<>();
        questions = new HashMap<>();
        getData();
    }

    public void getData() {

        String playersFilePath = "players_data.txt";
        if (!new File(playersFilePath).exists()) {
            try {
                PrintWriter writer = new PrintWriter(playersFilePath, "UTF-8");
            } catch (Exception e) {
                System.err.println("Problem creating player_data file");
                System.exit(1);
            }

        }

        try {
            playersData = new Scanner(new File(playersFilePath));
            questionsData = new Scanner(new File("questions.txt"));
        } catch (Exception e) {
            System.err.println(String.format("Unexpected error %s", e.getMessage()));
            System.exit(1);
        }

        // Add players to hash map players for easy lookup
        while (playersData.hasNext()) {
            String username = playersData.next();
            String password = playersData.next();

            int numberOfHighScores = playersData.nextInt();

            ArrayList<Integer> highScores = new ArrayList<>();

            for (int i = 0; i < numberOfHighScores; i++) {
                highScores.add(playersData.nextInt());
            }

            players.put(username, (new Player(username, password, highScores)));
        }

        // Read the entire file and remove new line characters
        String entire_file = questionsData.useDelimiter("\\Z").next().replace("\n", " ");

        Pattern p = Pattern.compile("\\s*([^\\?]*)\\?\\s*([^;]*);");  // "\s*(.*?)\?\s*(.*?);"
        Matcher m = p.matcher(entire_file);

        // Add questions to hash map questions
        while (m.find()) {
            // split answers by comma
            String[] answers = m.group(2).split(",");

            // remove leading and trailing spaces
            for (int i = 0; i < answers.length; i++) {
                answers[i] = answers[i].trim();
            }
            questions.put(m.group(1), answers);
        }

        questionsClone = (HashMap) questions.clone();

        playersData.close();
        questionsData.close();
    }

    public Player getPlayer(String username) {
        return players.get(username);
    }

    /**
     * Pick a question randomly, remove it from the pool of questions and
     * if all the questions are depleted then reset questionsClone.
     *
     * @return randomly selected question
     */
    public HashMap<String, String[]> getQuestion() {
        Random generator = new Random();
        Object[] keys = questionsClone.keySet().toArray();

        // pick a random key
        String randomKey = (String) keys[generator.nextInt(keys.length)];
        String[] answers = questionsClone.get(randomKey);

        // Add the random key and answers to a new Hashmap
        HashMap<String, String[]> randomQuestion = new HashMap<>();
        randomQuestion.put(randomKey, answers);

        // To prevent questions from repeating, remove question from hash map
        questionsClone.remove(randomKey);

        if (questionsClone.size() == 0) {
            questionsClone = (HashMap) questions.clone();
        }

        return randomQuestion;
    }

    /**
     * Check if the username and password is correct. First check if the username
     * is in the hash map players and if so then check if the password entered
     * matches the one on file.
     *
     * @param username to check
     * @param password to check
     * @return true or false depending on condition
     */
    public boolean checkPlayerCredentials(String username, String password) {
        return checkPlayerName(username) && players.get(username).getPassword().equals(password);
    }

    /**
     * Check if player name (username) is already in list of players
     *
     * @param username
     * @return true if username is already in players else false
     */
    public boolean checkPlayerName(String username){
        return players.containsKey(username);
    }

    /**
     * Add player to hash map players
     *
     * @param username for player
     * @param password for player
     * @throws ValidationException if username or password has whitespaces
     * @throws Exception           if username is already in hash map players
     */
    public void addPlayer(String username, String password) throws Exception {
        // check if username or password has whitespaces in it
        if (username.matches(".*\\s+.*") || password.matches(".*\\s+.*")) {
            throw new ValidationException("Username or password has whitespaces");
        }

        // check if username or password is empty
        if(username.isEmpty() || password.isEmpty()){
            throw new SecurityException("Username or password is blank");
        }

        // check if username is in players if not add him
        if (checkPlayerName(username)) {
            throw new Exception("Username already in data players filePath");
        }

        players.put(username, new Player(username, password, new ArrayList<>()));
    }

    /**
     * Write all players to file. Function shall be called at end of game.
     */
    public void writePlayers() {
        try {
            writePlayersData = new PrintWriter(new File("players_data.txt"));
        } catch (Exception e) {
            System.err.println(String.format("Unexpected error %s", e.getMessage()));
        }

        for (Player player : players.values()) {
            if (player.getUsername().equals("the computer"))
                continue;

            String scores = "";

            // go through players high scores and create one string
            // with spaces between scores
            for (Integer i : player.getHighScores()) {
                scores += Integer.toString(i) + " ";
            }

            // write username password num_of_scores <all scores separated by spaces>
            writePlayersData.write(String.format("%s %s %d %s\n", player.getUsername(),
                    player.getPassword(), player.getHighScores().size(), scores));
        }

        writePlayersData.close();
    }

}
