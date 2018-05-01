/**
 * CSCI 6620 Data Structures
 * Individual Programming Assignment No. 8D - BTree
 * Submitted By:    Steven Kho Ang
 * Date:            04/20/2018
 *
 * File Name: main.cpp
 *
 * This is a implementation of the following:
 * main()                                           Entry point of this program
 * commandMenu()                                    Print out the command menu and ask user to input his/ger choice
 * executeCommand(int command, BTree<int>* bTree)   Execute the command given
 * readDataFile(string fileName)                    This will read the file and store the data in a vector
 * welcomeMessage()                                 prints out welcome message
 *
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "BTNode.hpp"
#include "BTree.hpp"

using namespace std;

enum COMMAND {INSERT=1, READ_DATA_FILE, SEARCH, IN_ORDER, LEVEL_ORDER, QUIT};

int commandMenu();
void executeCommand(int command, BTree<int>* bTree);
vector<int> readDataFile(string fileName);
void welcomeMessage();

int main() {

    BTree<int>* tree = new BTree<int>();

    // Print out welcome message
    welcomeMessage();
    int command = 0;

    command = commandMenu();

    while (command != QUIT) {

        executeCommand(command, tree);

        command = commandMenu();
    }

    if (command == QUIT) {
        cout << "Thank you" << endl;
    }

    return 0;
}

/**
 * commandMenu()
 *
 * This will print out command menu and let the user select his action
 * based on the command menu shown
 *    1. Insert an item to a BTree.
 *    2. Search an item
 *    3. Print Tree (In-Order Traversal)
 *    4. Print Tree (Level-Order Travelsal)
 *    5. Quit
 *
 * @return int                  Command selected
 */
int commandMenu() {

    int command;
    string garbage;

    cout << "\n\nPlease choose from the following action.  "
            "Please enter the number of action you want to execute:" << endl;
    cout << "\t1. Insert an item to the BTree." << endl;
    cout << "\t2. Insert a data by reading data file." << endl;
    cout << "\t3. Search an item from BTree." << endl;
    cout << "\t4. Print in In-Order Traversal." << endl;
    cout << "\t5. Print in Level-Order Traversal" << endl;
    cout << "\t6. Quit" << endl;

    cout << "\nPlease enter the action code: ";

    cin >> command;
    // To clear the cin buffer
    cin.clear();
    getline(cin, garbage);

    if (! cin) {
        cout << "\nINVALID INPUT.  This program will terminated.  "
                "Please try again." << endl;
        exit(1);
    }

    return command;

}

/**
 * executeCommand(int command, ThreadedBinaryTree<PhonebookEntry>* tbt)
 *
 * This will parse the command and execute the appropriate action
 *
 * @param command               Command to be executed
 * @param tbt                   Pointer to Binary Search Tree
 */
void executeCommand(int command, BTree<int>* bTree) {

    int target;
    BTNode<int>* result;
    string fileName;
    vector<int> list;

    switch (command) {

        case INSERT:
            cout << "\tInsert to BTree" << endl;
            cout << "\t\tPlease enter the number you inserting: ";
            cin >> target;
            bTree->insert(target);
            break;
        case READ_DATA_FILE:
            cout << "\tRead DATA File and Build a BTree" << endl;
            cout << "\t\tPlease enter your data file's name: ";
            getline(cin, fileName);

            // Throw an error message and exit with error code
            // if user entered a blank string for file name
            if (fileName.empty()) {
                cout << "Invalid File Name. Please check you file "
                        "name and try again." << endl;
                break;
            }

            // Load the data to a vector of PhonebookEntry
            list = readDataFile(fileName);

            for (int index = 0; index < list.size(); index++) {

                bTree->insert(list.at(index));
                /*
                node = new Node<PhonebookEntry>();
                node->setData(list.at(index));
                node->setWeight(1);
                tbt->insertNode(node);
                 */
            }
            break;
        case SEARCH:
            cout << "\tSearch BTree: " << endl;
            cout << "\t\tPlease enter the number you are looking for: ";
            cin >> target;
            cout << "\t\t\tThe number you are looking for is " << target << endl;
            result = bTree->searchData(target);
            if (result == nullptr) {
                cout << "\t\t\tTarget '" << target << "' is not in trhe current BTree" << endl;
            } else {
                cout << "\t\t\tItem found.  The node contains the target is ";
                result->printNode();
                cout << endl;
            }
            break;
        case IN_ORDER:
            cout << "\tPrint BTree in IN-Order Traversal: ";
            bTree->printInOrderTraversal();
            cout << endl;
            break;
        case LEVEL_ORDER:
            cout << "\tPrint BTree in Level-Order Traversal." << endl;
            bTree->printNodesInLevelOrder(bTree->getRootNode());
            break;
        default:
            cout << "\t\tInvalid Option.  Please try again." << endl;
            break;

    }
}

/**
 * readDataFile(string fileName)
 *
 * This will read the file and store the data in a vector
 *
 * @param fileName              File name to be read
 * @return vector<T>            A vector which contains the data read from the file
 */
vector<int> readDataFile(string fileName) {

    vector<int> result;
    int counter;

    if (fileName.empty()) {
        cout << "\n\tInvalid File Name was inputed.  Program terminated." << endl;
        exit(1);
    } else {
        cout << "\n\tThe file name you inputed is \'" << fileName << "\'." << endl;
        // Open the file stream
        ifstream inputFile(fileName);
        string inLine;
        int input;
        counter = 0;

        if (inputFile.good()) {

            cout << "\tFile \'" << fileName << "\' opened." << endl;

            while (! inputFile.eof() && getline(inputFile, inLine)) {

                istringstream iss(inLine);

                if (!(iss >> input)) {
                    cout << "Error.  '" << inLine
                         << "' is not a valid integer.  The program will skip "
                            "this input and continue." << endl;
                } else {
                    result.push_back(input);
                }
                counter++;
            }

        } else {
            // Print out an error message if the file open failed and return -1.
            cout << "\tUnable to open file \'" << fileName << "\'.  ";
            cout << "Please check your file name and try again." << endl;
            inputFile.close();
            exit(1);
        }
    }

    return result;
}

/**
 * welcomeMessage()
 *
 * This will print out the welcome messgae and explain what this program can do.
 *
 */
void welcomeMessage() {

    cout << "***********************************************************************************************" << endl;
    cout << "*  CSCI 6620 Data Struture                                                                    *" << endl;
    cout << "*  Programming Assignment No. 8D                                                              *" << endl;
    cout << "*  BTree                                                                                      *" << endl;
    cout << "*                                                                                             *" << endl;
    cout << "*  Submitted by:  ANG, STEVEN KHO                                                             *" << endl;
    cout << "*                                                                                             *" << endl;
    cout << "*  This program can:                                                                          *" << endl;
    cout << "*     1. Create a BTree                 .                                                     *" << endl;
    cout << "*     2. User can do the following actions:                                                   *" << endl;
    cout << "*        - Add an item to the tree                                                            *" << endl;
    cout << "*        - Search the nodes that contains the item you looking for.                           *" << endl;
    cout << "*        - Print out the complete tree in In-Order Traversal                                  *" << endl;
    cout << "*        - Print out the complete tree in Level-Order Traversal                               *" << endl;
    cout << "*                                                                                             *" << endl;
    cout << "***********************************************************************************************" << endl;

}
