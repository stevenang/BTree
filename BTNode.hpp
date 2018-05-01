/**
 * CSCI 6620 Data Structures
 * Individual Programming Assignment No. 8D - BTree
 * Submitted By:    Steven Kho Ang
 * Date:            04/20/2018
 *
 * File Name: BTNode.hpp
 *
 * Some of the codes are refer to
 *      1.  https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
 *      2.  https://www.geeksforgeeks.org/b-tree-set-1-insert-2/
 *
 * This is a declaration of the BTNode class with the following:
 * BTNode(bool leaf)                                    Default Constructor
 * decreamentItemCount()                                Decrease the item count by 1
 * getItemCount()                                       Return number of items in current node
 * getIsLeaf()                                          Return a boolean value to determined if the current node is leaf or not
 * getDataAt(int index)                                 Return a particular data at the position given
 * getLastItem()                                        Return the last item of the current node
 * getNodeAt(int index)                                 Return a child node at the position given
 * increamentItemCount()                                Increase the item count bby 1
 * insertItem(T value)                                  Insert an item to the current node
 * splitChildNode(int index, BTNode<T>* childNode)      Split the current node
 * isFull()                                             Return a boolean value to determine if the current node is full or not
 * isNeedSplit()                                        Return a boolean value to determine if the current node needs to split or not
 * printInOrderTraversal()                              Print the subtree of the current node in In-Order fashion
 * printNode()                                          Print the contents of the current node
 * printNodeWithChildNode()                             Print the contents of the current node with its next level child node
 * searchDataNode (T target)                            Return a node which contains the target value you looking for
 * setDataAt(int index, T value)                        Save the Data at the position given
 * setItemCount(int value)                              Set the item count equal to the value given
 * setNodeAt(int index, BTNode* node)                   Save the Child Node at the position given
 */

#ifndef BTREE2_BTNODE_HPP
#define BTREE2_BTNODE_HPP
#define MAX_SIZE 4

#include <iostream>

using namespace std;

template<class T>
class BTNode {

public:

    /**
     * BTNode(bool leaf)
     *
     * Constructor
     * This method will setup and allocate memory for this BTRee Node.
     *
     * @param leaf      Boolean value to indicate the node is leaf or not.
     *                  True if the node is a leaf, False if not.
     */
    BTNode(bool leaf) {
        this->setIsLeaf(leaf);
        this->data = new T[MAX_SIZE + 1];
        this->childNode = new BTNode<T>* [MAX_SIZE + 1];
        for(int index = 0; index < (MAX_SIZE + 1); index++) {
            this->childNode[index] = nullptr;
        }

        this->setItemCount(0);
    }

    /**
     * decreamentItemCount()
     *
     * This will decrease the item count by 1
     *
     */
    void decreamentItemCount() { this->itemCount--; }

    /**
     * getItemCount()
     *
     * This will return the item count of the current node.
     *
     * @return int              Number of item in in the current node
     */
    int getItemCount() { return this->itemCount; }

    /**
     * getIsLeaf()
     *
     * This will retun True if the current node is Leaf of the BTree and False
     * if it is not a Leaf of the BTree.
     *
     * @return Bool                 True if the current node is Leaf.
     *                              False if not.
     */
    bool getIsLeaf() { return this->isLeaf; }

    /**
     * getDataAt(int index)
     *
     * This will return a data of the spot you specified.
     * Error will occurred if you provide an index which is greather than the
     * defined MAX_SIZE or greather than the element count of the current node.
     *
     * @param index             Spot you want ti retrieve the data
     * @return T                Data at the spot you specified.
     */
    T getDataAt(int index) {

        if (index > MAX_SIZE) {
            cout << "\tError:  The index you looking for was out of range. "
                    "Program will be terminated due to this error." << endl;
            exit(1);
        }

        if (index > this->getItemCount()) {
            cout << "\tError:  The index you looking for was not assigned yet. "
                    "Program will be terminated due to this error." << endl;
            exit(1);
        }

        return this->data[index];

    }

    /**
     * getLastItem()
     * @return T                Last item of the node (Usually is the node need to move)
     */
    T getLastItem() {
        return this->data[MAX_SIZE];
    }

    /**
         * getNodeAt(int index)
         *
         * This will return a child node of the spot you specified.
         *
         * @param index             Spot you want ti retrieve the child node
         * @return BTNode*          Pointer to the child node.
     */
    BTNode* getNodeAt(int index) {

        return this->childNode[index];
    }

    /**
     * increamentItemCount()
     *
     * This will increase the item count of the current node by 1
     *
     */
    void increamentItemCount() { this->itemCount++; }

    /**
     * insertItem(T value)
     * @param value
     */
    void insertItem(T value) {

        cout << "\t\tBTNode - insertItem" << endl;
        int index = this->getItemCount() - 1;

        if (this->getIsLeaf() == true) {
            // The current node is a leaf - means no child nodes
            // The data will be inserted to this node
            // This while loop will find the first item from the right which is
            // less than the value to be inserted and move all data which is
            // greater than the value one slot to the right.
            cout << "\t\t\tThe node is a leaf" << endl;
            while(index >= 0 && this->getDataAt(index) > value) {
                this->setDataAt(index + 1, this->getDataAt(index));
                index--;
            }

            cout << "\t\t\tInsert " << value << " at ";
            this->printNode();
            this->setDataAt((index + 1), value);
            this->increamentItemCount();
            cout << "\t\t\tAfter insertion: ";
            this->printNode();

        } else {
            cout << "\t\t\tThe node is not a leaf" << endl;
            // The current node is not a leaf -> means have child nodes
            // We need to find out which child node we will insert our data
            // This while loop will find the first item from the right which is
            // less than the value to be inserted
            while(index >= 0 && this->getDataAt(index) > value)
                index--;

            this->getNodeAt(index + 1)->insertItem(value);

            // This will check the right nodes of the data we found in the
            // last while loop and see if it is full
            if (this->getNodeAt(index + 1)->isNeedSplit()) {
                // If the node where we will insert the data is full,
                // then split the node
                cout << "\t\t\tItem count: " << this->getNodeAt((index+1))->getItemCount() << endl;
                this->splitChildNode((index+1), this->getNodeAt((index+1)));

            }
        }

        cout << "\t\tBTNode - End of Insert" << endl;

    }

    /**
     * splitChildNode(int index, BTNode<T>* childNode)
     *
     * This will split the node given
     *
     * @param index                 Index of the node to be splitted
     * @param childNode             Node to be splitted
     */
    void splitChildNode(int index, BTNode<T>* childNode) {

        cout << "\t\tSplit Node" << endl;

        // Create an instance of a BTNode for a new node.
        BTNode<T>* newNode = new BTNode(childNode->getIsLeaf());

        // Move the last two item on the given node (childNode) to the newNode
        for (int newNodeIndex = 0; newNodeIndex < ((MAX_SIZE/2));
             newNodeIndex++) {

            cout << "\t\t\tMove " << childNode->getDataAt(
                    newNodeIndex + 3) << " to new node." << endl;

            newNode->setDataAt(newNodeIndex, childNode->getDataAt(
                    newNodeIndex + 3));

            if (childNode->getIsLeaf() == false) {

                cout << "\t\t\tMove node " << (newNodeIndex + 3)
                     << " to spot " << newNodeIndex
                     << " of the newNode." << endl;
                //childNode->getNodeAt(newNodeIndex + 3)->printNode();
                newNode->setNodeAt(newNodeIndex, childNode->getNodeAt(
                        newNodeIndex + 3));
            }

            // Increase the item count in the newNode
            newNode->increamentItemCount();
            // Decrease the item count in the old node
            childNode->decreamentItemCount();
        }

        // Not only the data need to be move.  If the given childNode is not
        // a leaf of BTree, then we need to handled the childNode's links properly
        if (childNode->getIsLeaf() == false && childNode->getNodeAt(5) !=
                                                       nullptr) {

            //childNode->printNode();

            /*for (int newNodeIndex = 0; newNodeIndex <= (MAX_SIZE/2);
                 newNodeIndex++) {
                cout << "\t\t\tMove node" << endl;

                newNode->setNodeAt(newNodeIndex, childNode->getNodeAt(
                        newNodeIndex + 3));

                childNode->decreamentItemCount();
            }*/

            //childNode->decreamentItemCount();

            newNode->setNodeAt(2, childNode->getNodeAt(5));

        }

        // Move the current node's child node to create a space for newNode.
        for (int innerIndex = this->getItemCount(); innerIndex >= index;
                innerIndex--) {
            this->setNodeAt(innerIndex+1, this->getNodeAt(innerIndex));
        }

        // Set the newNode to it's space
        this->setNodeAt(index + 1, newNode);

        // Since one key from the childNode given will move to the current node.
        // We also need to create a space for that.
        for (int innerIndex = this->getItemCount() - 1;
                innerIndex >= index; innerIndex--) {
            this->setDataAt((innerIndex + 1), this->getDataAt(innerIndex));
        }

        // Move the data from the childNode to the current node
        this->setDataAt(index, childNode->getDataAt(2));
        // Decrease the item count of the childNode
        childNode->decreamentItemCount();
        // Increate the item count of the current node.
        this->increamentItemCount();

        cout << "\t\t\tSize of Root node: " << this->getItemCount() << endl;
        cout << "\t\t\tSize of new node: " << newNode->getItemCount() << endl;
        cout << "\t\t\tSize of Child Node: " << childNode->getItemCount() << endl;

        cout << "\t\tSplit Node - End" << endl;

    }

    /**
     * isFull()
     *
     * Check whether the node is full or not
     * @return bool             True if the node item count equals to MAX_SIZE
     *                          False if not.
     */
    bool isFull() {
        return (this->getItemCount() == MAX_SIZE);
    }

    /**
     * isNeedSplit()
     *
     * Return a boolean value to determine if the current node needs
     * to split or not
     *
     * @return                  True if the node needs to split False if not
     */
    bool isNeedSplit() {
        return (this->getItemCount() == MAX_SIZE + 1);
    }

    /**
     * printInOrderTraversal
     *
     * This will print out the subtree of the current node in
     * In-Order Traversal fashion.
     *
     */
    void printInOrderTraversal() {

        int index = 0;

        for (index = 0; index < this->getItemCount(); index++) {

            if (this->getIsLeaf() == false && this->childNode[index] != nullptr) {
                this->childNode[index]->printInOrderTraversal();
            }
            cout << this->data[index] << " ";

        }

        // Print out the right most link of the last data
        if (this->getIsLeaf() == false && this->childNode[index] != nullptr) {
            this->childNode[index]->printInOrderTraversal();
        }
    }

    /**
     * printNode()
     *
     * This will print out the data stored in the current node;
     *
     */
    void printNode() {

        int index = 0;

        cout << "[";

        for (index = 0; index < this->getItemCount(); index++) {
            cout << this->data[index];
            if (index + 1 != this->getItemCount())
                cout << ", ";
        }

        cout << "]." << endl;

    }

    /**
     * printNodeWithChildNode()
     *
     * This will print out the data stored in the current node and
     * the child node linked to the current node
     *
     */
    void printNodeWithChildNode() {

        int index = 0;
        for (index = 0; index < this->getItemCount(); index++) {

            if (this->getIsLeaf() == false &&
                    this->childNode[index] != nullptr) {
                this->childNode[index]->printNode();
            }
            cout << this->data[index] << endl;

        }

        // Print out the right most link of the last data
        if (this->getIsLeaf() == false && this->childNode[index] != nullptr) {
            this->childNode[index]->printNode();
        }

    }

    /**
     * searchDataNode(T target)
     *
     * This will return a node which contains the target data
     *
     * @param target            Data you looking for
     * @return BTNode*          Pointer of the BTNode which contains target data
     */
    BTNode* searchDataNode (T target) {

        int index = 0;
        while (index < this->itemCount &&
               target > this->getDataAt(index)) {
            index++;
        }

        if (this->getDataAt(index) == target) {
            return this;
        }

        if (this->getIsLeaf() == false && this->getNodeAt(index) != nullptr) {
            return this->getNodeAt(index)->searchDataNode(target);
        }

        return nullptr;

    }

    /**
     * setDataAt(int index, T value)
     *
     * This will stored the data you provided at the spot you specifed.
     *
     * @param index                 Index of the spot where you want to save your data.
     * @param value                 Data to be stored.
     */
    void setDataAt(int index, T value) {
        //cout << "\tSet data " << value << " at spot " << index << "." << endl;
        this->data[index] = value;
    }

    /**
     * setItemCount(int value)
     *
     * Set the item count of the node.
     *
     * @param value                 New Item Count value.
     */
    void setItemCount(int value) { this->itemCount = value; }

    /**
     * setIsLeaf(bool value)
     * @param value
     */
    void setIsLeaf(bool value) { this->isLeaf = value; }

    /**
     * setNodeAt(int index, BTNode* node)
     *
     * This will save the node provided to the spot specified.
     *
     * @param index                 Spot specified where to save the node
     * @param node                  Node to be saved in the BTree.
     *
     */
    void setNodeAt(int index, BTNode* node) {
        this->childNode[index] = node;
    }

private:

    T*          data;
    bool        isLeaf;
    int         itemCount;
    BTNode**    childNode;
};
#endif //BTREE2_BTNODE_HPP
