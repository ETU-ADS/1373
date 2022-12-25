//
// Created by theta-sigma on 11/30/2022.
//

#include "ui.h"

void testsFunction() {

    /*    const int n = 4;
    std::string tests[] = {
            "(8 (3 (1) (6 (4) (7))))",
            "(8 (9 (5)) (1))",
            "(8 (3 (1) (6 (4) (7))) (10 (14 (13))))",
            "(8 () (5))"
    };

    std::string testsSolutions[n]{
            "(8 (3 (1 () ()) (6 (4 () ()) (7 () ()))) ())",
            "(8 (9 (5 () ()) ()) (1 () ()))",
            "(8 (3 (1 () ()) (6 (4 () ()) (7 () ()))) (10 (14 (13 () ()) ()) ()))",
            "(8 () (5 () ()))"
    };*/

    std::ifstream input("../tests.txt");
    if (input.is_open()) {
        std::string line;
        int nLines = 0;
        while (std::getline(input, line)) {
            BinaryTree bt;

            std::cout << "tests.txt[" << nLines << "]:\t" << line << std::endl;
            bt.parser(line);

            std::cout << "output[" << nLines << "]:\t";
            bt.printDfsBraces();

//        std::cout << "solution[" << nLines << "]:\t" << testsSolutions[i] << std::endl;
//
            std::cout << std::endl;
            nLines++;
        }
        input.close();
    }
}

bool innerDialog() {
    char answer;
    while (true) {
        std::cout << "Do you want to restart the program? y/n: " << std::endl;
        std::cin >> answer;
        switch (answer) {
            case 'n':
                std::cout << "Closing...";
                return false;
            case 'y':
                return true;
            default:
                break;
        }
    }
}

void consoleInputString(BinaryTree *&bt) {
    std::cout << "Input: " << std::endl;

    std::string sss;

    std::cin.ignore();

    std::getline(std::cin, sss);

    delete bt;
    bt = new BinaryTree();
    bt->parser(sss);

    std::cout << std::endl;
}

void fromFileInput(BinaryTree *& bt) {
    std::cout << "File: " << std::endl;

    std::string fileName;
    std::cin >> fileName;

    std::ifstream myFile;
    myFile.open(fileName);
    std::string myLine;
    if (myFile.is_open()) {
        std::getline(myFile, myLine);
    } else {
        std::cout << "Couldn't open file\n";
    }

    delete bt;
    bt = new BinaryTree();
    bt->parser(myLine);

    std::cout << std::endl;
}

void parserMessage(AvlTree *&pAvlTree) {
    bool toContinue = true;
    char answer;

    BinaryTree *pBt = nullptr;

    while (toContinue) {
        std::cout << "STRING TO BINARY TREE PARSER" << std::endl << std::endl;

        std::cout << "1. RUN TESTS\n"
                     "2. READ STRING FROM FILE\n"
                     "3. CONSOLE INPUT\n"
                     "4. PRETTY PRINT\n"
                     "5. PRINT DFS (WITH BRACES)\n"
                     "6. CREATE AVL-TREE FROM CURRENT BINARY TREE\n"
                     "<. BACK\n" << std::endl;

        std::cout << "Your input: ";
        std::cin >> answer;

        switch (answer) {
            case '1':
                testsFunction();
                break;
            case '2': {
                fromFileInput(pBt);
                break;
            }
            case '3':
                consoleInputString(pBt);
                break;
            case '4':
                if (pBt == nullptr) {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                } else {
                    pBt->prettyPrint(pBt->getRoot());
                }
                break;
            case '5':
                if (pBt == nullptr) {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                } else {
                    pBt->printDfsBraces();
                }
                break;
            case '6': {
                if (pBt == nullptr) {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                } else {
                    delete pAvlTree;
                    pAvlTree = new AvlTree(*pBt);
                    std::cout << "Done." << std::endl << std::endl;
                }
                break;
            }
            case '<':
                std::cout << "Closing..." << std::endl << std::endl;
                toContinue = false;
                break;
            default:
                std::cout << "Wrong input! 1/2/3/4/5/6/<" << std::endl << std::endl;
                break;
        }
    }

    delete pBt;
}

void dfsMessage(AvlTree *pAvlTree) {
    std::cout << "DFS" << std::endl << std::endl;
    std::cout << "W. BFS\n"
                 "X. PREORDER\n"
                 "Y. INORDER\n"
                 "Z. POSTORDER\n"
                 "<. BACK\n" << std::endl;

    bool toContinue = true;
    char answer;

    while (toContinue) {
        std::cout << "Your input: ";
        std::cin >> answer;

        switch (answer) {
            case 'W':
                pAvlTree->bfs();
                std::cout << std::endl;
                break;
            case 'X':
                pAvlTree->preorder();
                std::cout << std::endl;
                break;
            case 'Y':
                pAvlTree->inorder();
                std::cout << std::endl;
                break;
            case 'Z':
                pAvlTree->postorder();
                std::cout << std::endl;
                break;
            case '<':
                toContinue = false;
                break;
            default:
                std::cout << "Wrong input! W/X/Y/Z/<" << std::endl << std::endl;
                break;
        }
    }
}

void avlMessage() {
    bool toContinue = true;
    char answer;

    AvlTree *pAvlTree = nullptr;

    while (toContinue) {
        std::cout << "AVL-TREE" << std::endl << std::endl;

        std::cout << "A. NEW AVL-TREE\n"
                     "X. [CREATE BY] STRING TO BINARY TREE PARSER\n"
                     "B. INSERT\n"
                     "C. REMOVE\n"
                     "D. FIND\n"
                     "E. B\\DFS\n"
                     "F. PRETTY PRINT\n"
                     "0. QUIT\n" << std::endl;

        std::cout << "Your input: ";
        std::cin >> answer;

        switch (answer) {
            case 'A': {
                delete pAvlTree;
                pAvlTree = new AvlTree();
                std::cout << "Done!" << std::endl << std::endl;
                break;
            }
            case 'X': {
                delete pAvlTree;
                pAvlTree = new AvlTree();
                parserMessage(pAvlTree);
                break;
            }
            case 'B': { // insert
                if (pAvlTree != nullptr) {
                    int n;
                    std::cout << "Enter number of new values: " << std::endl;
                    std::cin >> n;

                    int *values = new int[n];

                    for (int i = 0; i < n; i++) {
                        std::cout << "value[" << i << "]: ";
                        std::cin >> values[i];
                    }

                    for (int i = 0; i < n; i++) {
                        pAvlTree->insert(values[i]);
                    }

                    break;
                } else {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                    break;
                }
            }
            case 'C': {
                if (pAvlTree != nullptr) {
                    int value;
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    pAvlTree->remove(value);
                    break;
                } else {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                    break;
                }
            }
            case 'D': {
                if (pAvlTree != nullptr) {
                    int value;
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    AvlNode *foundNode = pAvlTree->find(value);

                    if (foundNode != nullptr) {
                        std::cout << "Node value: " << foundNode->value << ", ";
                        if (foundNode->left != nullptr) {
                            std::cout << "Node->left: " << foundNode->left->value << ", ";
                        } else {
                            std::cout << "Node->left: " << "x" << ", ";
                        }
                        if (foundNode->right != nullptr) {
                            std::cout << "Node->right: " << foundNode->right->value << ";";
                        } else {
                            std::cout << "Node->right: " << "x" << ";";
                        }
                        std::cout << std::endl << std::endl;
                    } else {
                        std::cout << "Value not found..." << std::endl << std::endl;
                    }
                    break;
                } else {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                    break;
                }
            }
            case 'E': // dfs/bfs
            {
                dfsMessage(pAvlTree);
                break;
            }
            case 'F': // pretty
            {
                if (pAvlTree != nullptr) {
                    pAvlTree->prettyPrint(pAvlTree->getRoot());
                    break;
                } else {
                    std::cout << "First create a tree..." << std::endl << std::endl;
                    break;
                }
            }
            case '0': {
                std::cout << "Closing..." << std::endl << std::endl;
                toContinue = false;
                break;
            }
            default: {
                std::cout << "Wrong input! A/X/B/C/D/E/F/0" << std::endl << std::endl;
                break;
            }
        }
    }
    delete pAvlTree;
}

void menuMessage() {
    bool toContinue = true;
    char answer;

    while (toContinue) {
        std::cout << "MENU" << std::endl << std::endl;

        std::cout << "1. STRING TO BINARY TREE PARSER\n"
                     "2. AVL-TREE\n"
                     "0. QUIT\n" << std::endl;

        std::cout << "Your input: ";
        std::cin >> answer;

        switch (answer) {
            case '1':
//                parserMessage();
                break;
            case '2':
                avlMessage();
                break;
            case '0':
                std::cout << "Closing..." << std::endl << std::endl;
                toContinue = false;
                break;
            default:
                std::cout << "Wrong input! 1/2/0" << std::endl << std::endl;
                break;
        }
    }
}
