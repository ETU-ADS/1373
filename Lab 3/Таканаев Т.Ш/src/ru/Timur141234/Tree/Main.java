package ru.Timur141234.Tree;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Main {

    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("./src/test.txt");
        Scanner input = new Scanner(file);
        StringBuilder inputFromFile = new StringBuilder();

        while (input.hasNextLine()) {
            String line = input.nextLine();
            inputFromFile.append(line);
        }

        BinaryTreeBracketsParser parser = new BinaryTreeBracketsParser();
        BinaryTree tree = parser.BinaryTreeBracketsParserConvert(inputFromFile.toString());
        AVLTree avlTree = tree.getAVLTree();
        avlTree.dfs_nlr();
        avlTree.dfs_lrn();
        avlTree.dfs_lnr();
        avlTree.bfs();
    }
}
