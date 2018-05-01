/**
 * CSCI 6620 Data Structures
 * Individual Programming Assignment No. 8D - BTree
 * Submitted By:    Steven Kho Ang
 * Date:            04/20/2018
 *
 * File Name: BTree.hpp
 *
 * Some of the codes are refer to
 *      1.  https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
 *      2.  https://www.geeksforgeeks.org/b-tree-set-1-insert-2/
 *
 * This is a declaration of the BTree class with the following:
 * BTree()                                      Default Constructor
 * getRootNode()                                Return the rootnode of the current BTree
 * insert(T value)                              Insert an item to current BTree
 * printInOrderTraversal()                      Print current BTree in In-Order Traversal
 * printNodesInLevelOrder(BTNode<T>* node)      Print current BTree in Level-Order Traversal
 * searchData(T target)                         Search the target data in current BTree
 * setRootNode(BTNode<T>* node)                 Set the given nodes as root node of the current BTree
 *
 */

#ifndef BTREE2_BTREE_HPP
#define BTREE2_BTREE_HPP

#include <queue>
#include "BTNode.hpp"

using namespace std;

template <class T>
class BTree {

public:
    /**
     * Constructor of the BTree
     */
    BTree() {
        root = nullptr;
    }

    /**
     * getRootNode()
     *
     * This will return a root node of the current BTree
     *
     * @return BTNode*                  Pointer of the root of the current BTree
     */
    BTNode<T>* getRootNode() {
        return this->root;
    }

    /**
     * insert(T value)
     *
     * Insert the value provided by the user to the current BTree
     *
     * @param value                     Data to be inserted.
     */
    void insert(T value) {

        cout << "\tBTree - Insert " << value << endl;

        int index = 0;

        if (this->getRootNode() == nullptr) {

            // If the current root node is nullptr, then create a new instance of
            // BTNode and assign it as a root node
            BTNode<T>* rootNode = new BTNode<T>(true);
            rootNode->insertItem(value);
            this->setRootNode(rootNode);

        } else {

            // Check if the root node of the BTree needs to be split or not
            if (this->getRootNode()->isNeedSplit()) {

                // The root node's size if = MAX_SIZE + 1 -> needs to split
                cout << "\t\tThe root node is full.  Current root will be splitted." << endl;
                // Create a new nodes as a future root.
                BTNode<T>* newRootNode = new BTNode<T>(false);
                // Set the current root node as a child node of new node in position 0
                newRootNode->setNodeAt(0, this->getRootNode());
                // Split the child of the new node at position 0
                newRootNode->splitChildNode(0, newRootNode->getNodeAt(0));

                // Check where to insert the new data
                int index = 0;
                if (newRootNode->getDataAt(0) < value)
                    index++;
                // Insert the new data
                newRootNode->getNodeAt(index)->insertItem(value);
                // Re-assign the new node as a root node of the current BTree
                this->setRootNode(newRootNode);

            } else {
                // If the root nodes is not reach to the split point
                cout << "\t\tRoot is no need for split yet" << endl;
                cout << "\t\tRoot's item count: " << this->getRootNode()->getItemCount() << endl;
                // Insert the new item
                this->getRootNode()->insertItem(value);

                // Check if the root node of the BTree needs to be split or not
                if (this->getRootNode()->isNeedSplit()) {

                    cout << "\t\tThe root node is full.  "
                            "Current root will be splitted." << endl;


                    BTNode<T>* newRootNode = new BTNode<T>(false);
                    newRootNode->setNodeAt(0, this->getRootNode());
                    newRootNode->splitChildNode(0, newRootNode->getNodeAt(0));

                    this->setRootNode(newRootNode);
                }
            }


        }

        cout << "\tBTree - End of Insert" << endl;

        // Print out the current root node.
        cout << "\tRoot Node after insertion: ";
        this->getRootNode()->printNode();
        cout << endl;
    }

    /**
     * printInOrderTraversal()
     *
     * This will print the current BTree in In-Order Traversal Fashion
     */
    void printInOrderTraversal() {

        if (this->getRootNode() == nullptr) {
            cout << "\tThis is an empty tree." << endl;
            return;
        }

        return this->getRootNode()->printInOrderTraversal();
    }

    /**
     * printNodesInLevelOrder(BTNode<T>* node)
     *
     * This will print out the BTree in a Level Order
     *
     * @param node          Root node of the sub-tree to be printed
     */
    void printNodesInLevelOrder(BTNode<T>* node) {


        int levelCount = 1;

        if (node == nullptr)
            return;

        // Using queue to store the nodes we received from the travelsal
        queue<BTNode<T>*> nodeQueue;

        nodeQueue.push(node);

        while (true) {

            int count = nodeQueue.size();

            if (count == 0)
                break;
            cout << "\t\tLevel: " << levelCount << endl;
            while (count > 0) {

                BTNode<T>* front = nodeQueue.front();
                cout << "\t\t\t";
                front->printNode();
                nodeQueue.pop();

                for (int index = 0; index <= front->getItemCount(); index++) {

                    if (front->getNodeAt(index) != nullptr) {
                        nodeQueue.push(front->getNodeAt(index));
                    }
                }


                count--;

            }

            cout << endl;

            levelCount++;

        }





    }

    /**
     * searchData(T target)
     *
     * This will search the current BTree and see if there is any data matched
     * with the target given
     *
     * @param target                Data you are looking for
     * @return BTNode<T>*           Node which contains the data you looking for
     *                              nullptr will be return if data doesn't in
     *                              the current BTree
     */
    BTNode<T>* searchData(T target) {

        if (this->getRootNode() == nullptr) {
            cout << "\tThis is an empty tree." << endl;
            return nullptr;
        }

        return this->getRootNode()->searchDataNode(target);
    }

    /**
     * setRootNode(BTNode* node)
     *
     * This will aqssigned the given node as a root of the current BTree
     *
     * @param node                  Node to be assigned as new root
     */
    void setRootNode(BTNode<T>* node) {
        this->root = node;
    }


private:
    BTNode<T>* root;

};

#endif //BTREE2_BTREE_HPP
