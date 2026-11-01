#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Min-heap: smallest frequency on top
struct Compare {
    bool operator()(Node *a, Node *b) {
        return a->freq > b->freq;
    }
};

// Prints codes at the leaves and adds up total bits
void printCodes(Node *root, string code, int &totalBits) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        // single-character case: tree is just one node, so give it code "0"
        if (code.empty()) code = "0";
        cout << root->ch << "\t" << root->freq << "\t" << code << endl;
        totalBits += root->freq * code.length();
        return;
    }

    printCodes(root->left, code + "0", totalBits);
    printCodes(root->right, code + "1", totalBits);
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    vector<char> chars(n);
    vector<int> freq(n);

    cout << "Enter each character and its frequency:\n";
    for (int i = 0; i < n; i++) {
        cin >> chars[i] >> freq[i];
    }

    priority_queue<Node *, vector<Node *>, Compare> pq;

    // Create leaf nodes
    for (int i = 0; i < n; i++) {
        pq.push(new Node(chars[i], freq[i]));
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node *root = pq.top();
    int totalBits = 0;

    cout << "\nHuffman Codes:\n";
    cout << "Char\tFreq\tCode\n";
    printCodes(root, "", totalBits);

    cout << "\nTotal bits after encoding: " << totalBits << endl;
    return 0;
}