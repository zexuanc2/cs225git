/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies)
{
    std::stable_sort(frequencies.begin(), frequencies.end());
    buildTree(frequencies);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree& other)
{
    copy(other);
}

HuffmanTree::HuffmanTree(BinaryFileReader& bfile)
{
    root_ = readTree(bfile);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::~HuffmanTree()
{
    clear(root_);
}

const HuffmanTree& HuffmanTree::operator=(const HuffmanTree& rhs)
{
    if (this != &rhs) {
        clear(root_);
        copy(rhs);
    }
    return *this;
}

void HuffmanTree::clear(TreeNode* current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

void HuffmanTree::copy(const HuffmanTree& rhs)
{
    root_ = copy(rhs.root_);
}

HuffmanTree::TreeNode* HuffmanTree::copy(const TreeNode* current)
{
    if (current == NULL)
        return NULL;
    TreeNode* node = new TreeNode(current->freq);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

HuffmanTree::TreeNode*
HuffmanTree::removeSmallest(queue<TreeNode*>& singleQueue,
                            queue<TreeNode*>& mergeQueue)
{

    /**
     * @todo Your code here!
     *
     * Remove the smallest TreeNode * from the two queues given as
     * parameters. The entries on the queues are in sorted order, so the
     * smaller of the two queues heads is the smallest item in either of
     * the queues. Return this item after removing it from its queue.
     */
    if (singleQueue.size() == 0 && mergeQueue.size() == 0) {return NULL;}
    else if (singleQueue.size() == 0) {
        TreeNode* temp = mergeQueue.front();
        mergeQueue.pop();
        return temp;
    }
    else if (mergeQueue.size() == 0) {
        TreeNode* temp = singleQueue.front();
        singleQueue.pop();
        return temp;
    }
    else if (singleQueue.front()->freq.getFrequency() <= mergeQueue.front()->freq.getFrequency()) {
        TreeNode* temp = singleQueue.front();
        singleQueue.pop();
        return temp;
    }
    else {
        TreeNode* temp = mergeQueue.front();
        mergeQueue.pop();
        return temp;
    }
}

void HuffmanTree::buildTree(const vector<Frequency>& frequencies)
{
    queue<TreeNode*> singleQueue; // Queue containing the leaf nodes
    queue<TreeNode*> mergeQueue;  // Queue containing the inner nodes

    /**
     * @todo Your code here!
     *
     * First, place all of the leaf nodes into the singleQueue in
     * increasing order of frequency. Note: frequencies is already sorted
     * for you.
     *
     * Next, until there is only one node on the two queues (that is, one
     * of the queues is empty and one has a single node), remove the two
     * smallest entries from the two queues. Then, create a new internal
     * node with these nodes as children, whose frequency is the sum of
     * these two children's frequencies. Place the new internal node onto
     * the back of the mergeQueue.
     *
     * Finally, when there is a single node left, it is the root. Assign it
     * to the root and you're done!
     */

    for (unsigned i = 0; i < frequencies.size(); i++) {
        TreeNode* cur = new TreeNode(frequencies[i]);
        singleQueue.push(cur);

    }
     while (singleQueue.size() + mergeQueue.size() != 1) {
         TreeNode* smallOne = removeSmallest(singleQueue,mergeQueue);
         TreeNode* smallTwo = removeSmallest(singleQueue,mergeQueue);
         TreeNode* mergedNode = new TreeNode(smallTwo->freq.getFrequency() + smallOne->freq.getFrequency());
         mergedNode->left = smallOne;
         mergedNode->right = smallTwo;
         mergeQueue.push(mergedNode);
     }
     if (singleQueue.size() == 1) {
         root_ = singleQueue.front();
     } else if (mergeQueue.size() == 1) {
         root_= mergeQueue.front();
     }

}

string HuffmanTree::decodeFile(BinaryFileReader& bfile)
{
    stringstream ss;
    decode(ss, bfile);
    return ss.str();
}

void HuffmanTree::decode(stringstream& ss, BinaryFileReader& bfile)
{
    TreeNode* current = root_;
    bool direct;
    while (bfile.hasBits()) {
        /**
         * @todo Your code here!
         *
         * This code is reading in all of the bits in the binary file
         * given. After reading a bit, we go left if the bit was a 0 (or
         * false), and we go right if the bit was a 1 (or true).
         *
         * Special case: if we are at a leaf node, we should "print" its
         * character to the stringstream (with operator<<, just like cout)
         * and start traversing from the root node again.
         */
        direct = bfile.getNextBit();
        if (direct) {current = current->right;}
        else {current = current->left;}
        if (current->left == NULL && current->right == NULL) {
            ss<<current->freq.getCharacter();
            current = root_;
        }

    }
}

void HuffmanTree::writeTree(BinaryFileWriter& bfile)
{
    writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode* current, BinaryFileWriter& bfile)
{
    /**
     * @todo Your code here!
     *
     * This code is writing the current HuffmanTree in a compressed format
     * to the given BinaryFileWriter. The strategy for doing so is as
     * follows:
     *      1. If we are a leaf node, write the bit "1" followed by the
     *         byte that is the character of this node.
     *      2. If we are an internal node, writ the bit "0", and then
     *         encode the left and right subtree, recursively.
     *
     * Note that we don't encode the frequencies in this compressed
     * version: this is fine, as the structure of the tree still reflects
     * what the relative frequencies were.
     */
    if (current->left == NULL && current->right == NULL) {
        bfile.writeBit(true);
        bfile.writeByte(current->freq.getCharacter());
    } else {
        bfile.writeBit(false);
        writeTree(current->left, bfile);
        writeTree(current->right, bfile);
    }
}

HuffmanTree::TreeNode* HuffmanTree::readTree(BinaryFileReader& bfile)
{
    /**
     * @todo Your code here!
     *
     * This code is reading a HuffanTree in from a file in the format that
     * we wrote it above. The strategy, then, is as follows:
     *      1. If the file has no more bits, we're done.
     *      2. If we read a 1 bit, we are a leaf node: create a new
     *         TreeNode with the character that is the next byte in the
     *         file (its frequency should be 0, since we are ignoring
     *         frequency data now).
     *      3. If we read a 0 bit, create a new internal node (with
     *         frequency 0, since we are ignoring them now, and set its left
     *         child and right children to be the subtrees built recursively.
     *      4. Your function should return the TreeNode it creates, or NULL
     *         if it did not create one.
     */
    TreeNode* newNode = nullptr;
    if (!bfile.hasBits()) {
        return NULL;
    } else {
        if (bfile.getNextBit()) {
            return new TreeNode(Frequency(bfile.getNextByte(),0));
        } else {
            newNode = new TreeNode(0);
            newNode->left = readTree(bfile);
            newNode->right = readTree(bfile);
            return newNode;
        }
    }

}

void HuffmanTree::buildMap(TreeNode* current, vector<bool>& path)
{
    // Base case: leaf node.
    if (current->left == NULL && current->right == NULL) {
        bitsMap_[current->freq.getCharacter()] = path;
        return;
    }

    // Move left
    path.push_back(false);
    buildMap(current->left, path);
    path.pop_back();

    // Move right
    path.push_back(true);
    buildMap(current->right, path);
    path.pop_back();
}

void HuffmanTree::printInOrder() const
{
    printInOrder(root_);
    cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode* current) const
{
    if (current == NULL)
        return;
    printInOrder(current->left);
    cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
         << " ";
    printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string& data, BinaryFileWriter& bfile)
{
    for (auto it = data.begin(); it != data.end(); ++it)
        writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter& bfile)
{
    vector<bool> bits = getBitsForChar(c);
    for (auto it = bits.begin(); it != bits.end(); ++it)
        bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c)
{
    return bitsMap_[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor
    : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode>>
{
  public:
    HuffmanTreeNodeDescriptor(const TreeNode* root) : subRoot_(root)
    { /* nothing */
    }

    string key() const
    {
        std::stringstream ss;
        char ch = subRoot_->freq.getCharacter();
        int freq = subRoot_->freq.getFrequency();

        // print the sum of the two child frequencies
        if (ch == '\0')
            ss << freq;
        // print the leaf containing a character and its count
        else {
            if (ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
        return ss.str();
    }

    bool isNull() const
    {
        return subRoot_ == NULL;
    }
    HuffmanTreeNodeDescriptor left() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->left);
    }
    HuffmanTreeNodeDescriptor right() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->right);
    }

  private:
    const TreeNode* subRoot_;
};

int HuffmanTree::height(const TreeNode* subRoot) const
{
    if (subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream& out) const
{
    int h = height(root_);
    if (h > _max_print_height) {
        out << "Tree is too big to print. Try with a small file (e.g. "
               "data/small.txt)"
            << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}

Frequency
HuffmanTree::testRemoveSmallest(vector<Frequency> single,
                                vector<Frequency> merge)
{
    queue<TreeNode*> singleQueue;
    queue<TreeNode*> mergeQueue;
    for (auto it = single.begin(); it != single.end(); ++it) {
         singleQueue.push(new TreeNode(*it));
    }
    for (auto it = merge.begin(); it != merge.end(); ++it) {
         mergeQueue.push(new TreeNode(*it));
    }

    TreeNode* testNode = removeSmallest(singleQueue, mergeQueue);
    Frequency testFreq = testNode->freq;

    delete testNode;
    while (!singleQueue.empty()) {
        delete singleQueue.front();
        singleQueue.pop();
    }
    while (!mergeQueue.empty()) {
        delete mergeQueue.front();
        mergeQueue.pop();
    }

    return testFreq;
}
