//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <cstring>
//using namespace std;
//
//// TrieNode structure for suggestions
//class TrieNode {
//public:
//    char data;
//    bool isEnd;
//    TrieNode** children;
//
//    TrieNode(char c) : data(c), isEnd(false), children(new TrieNode* [26]()) {}
//
//    ~TrieNode() {
//        for (int i = 0; i < 26; ++i) {
//            delete children[i];
//        }
//        delete[] children;
//    }
//};
//
//// Trie class for suggestions
//class Trie {
//private:
//    TrieNode* root;
//
//    void insertWord(TrieNode* node, const string& word) {
//        for (char c : word) {
//            int index = c - 'a';
//            if (!node->children[index]) {
//                node->children[index] = new TrieNode(c);
//            }
//            node = node->children[index];
//        }
//        // Make sure to mark the last node as the end of the word
//        node->isEnd = true;
//    }
//
//    TrieNode* findNode(TrieNode* node, const string& prefix) {
//        for (char c : prefix) {
//            int index = c - 'a';
//            if (!node->children[index]) {
//                return nullptr; // Prefix not found
//            }
//            node = node->children[index];
//        }
//        return node;
//    }
//
//    void getSuggestions(TrieNode* node, const string& prefix) {
//        if (node == nullptr) {
//            return;
//        }
//
//        if (node->isEnd) {
//            cout << prefix << endl;
//        }
//
//        for (int i = 0; i < 26; ++i) {
//            if (node->children[i]) {
//                char nextChar = 'a' + i;
//                getSuggestions(node->children[i], prefix + nextChar);
//            }
//        }
//    }
//
//public:
//    Trie() : root(new TrieNode('\0')) {}
//
//    ~Trie() {
//        delete root;
//    }
//
//    void insert(const string& word) {
//        insertWord(root, word);
//    }
//
//    void getSuggestions(const string& prefix) {
//        TrieNode* node = findNode(root, prefix);
//        getSuggestions(node, prefix);
//    }
//};
//
//class AVLNode {
//public:
//    string key;
//    string meaning;
//    AVLNode* left;
//    AVLNode* right;
//    int height;
//
//    AVLNode(string word, string wordMeaning)
//        : key(word), meaning(wordMeaning), left(nullptr), right(nullptr), height(1) {}
//};
//
//class AVLTree {
//private:
//    AVLNode* root;
//    Trie suggestionsTrie; // Trie for storing suggestions
//
//    int getHeight(AVLNode* node) {
//        return (node == nullptr) ? 0 : node->height;
//    }
//
//    int getBalanceFactor(AVLNode* node) {
//        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
//    }
//
//    AVLNode* rotateRight(AVLNode* y) {
//        AVLNode* x = y->left;
//        AVLNode* T2 = x->right;
//
//        x->right = y;
//        y->left = T2;
//
//        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
//        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
//
//        return x;
//    }
//
//    AVLNode* rotateLeft(AVLNode* x) {
//        AVLNode* y = x->right;
//        AVLNode* T2 = y->left;
//
//        y->left = x;
//        x->right = T2;
//
//        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
//        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
//
//        return y;
//    }
//
//    AVLNode* insert(AVLNode* node, string key, string meaning) {
//        if (node == nullptr) {
//            return new AVLNode(key, meaning);
//        }
//
//        if (key < node->key) {
//            node->left = insert(node->left, key, meaning);
//        }
//        else if (key > node->key) {
//            node->right = insert(node->right, key, meaning);
//        }
//        else {
//            // Duplicate keys are not allowed
//            return node;
//        }
//
//        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//
//        int balance = getBalanceFactor(node);
//
//        // Left Left Case
//        if (balance > 1 && key < node->left->key) {
//            return rotateRight(node);
//        }
//
//        // Right Right Case
//        if (balance < -1 && key > node->right->key) {
//            return rotateLeft(node);
//        }
//
//        // Left Right Case
//        if (balance > 1 && key > node->left->key) {
//            node->left = rotateLeft(node->left);
//            return rotateRight(node);
//        }
//
//        // Right Left Case
//        if (balance < -1 && key < node->right->key) {
//            node->right = rotateRight(node->right);
//            return rotateLeft(node);
//        }
//
//        return node;
//    }
//
//    AVLNode* deleteNode(AVLNode* root, string key) {
//        if (root == nullptr) {
//            return root;
//        }
//
//        if (key < root->key) {
//            root->left = deleteNode(root->left, key);
//        }
//        else if (key > root->key) {
//            root->right = deleteNode(root->right, key);
//        }
//        else {
//            // Node with only one child or no child
//            if (root->left == nullptr) {
//                AVLNode* temp = root->right;
//                delete root;
//                return temp;
//            }
//            else if (root->right == nullptr) {
//                AVLNode* temp = root->left;
//                delete root;
//                return temp;
//            }
//
//            // Node with two children, get the inorder successor (smallest in the right subtree)
//            AVLNode* temp = findMinNode(root->right);
//
//            // Copy the inorder successor's data to this node
//            root->key = temp->key;
//            root->meaning = temp->meaning;
//
//            // Delete the inorder successor
//            root->right = deleteNode(root->right, temp->key);
//        }
//
//        // Update height and balance factor
//        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
//
//        int balance = getBalanceFactor(root);
//
//        // Left Left Case
//        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
//            return rotateRight(root);
//        }
//
//        // Left Right Case
//        if (balance > 1 && getBalanceFactor(root->left) < 0) {
//            root->left = rotateLeft(root->left);
//            return rotateRight(root);
//        }
//
//        // Right Right Case
//        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
//            return rotateLeft(root);
//        }
//
//        // Right Left Case
//        if (balance < -1 && getBalanceFactor(root->right) > 0) {
//            root->right = rotateRight(root->right);
//            return rotateLeft(root);
//        }
//        updateSuggestionsTrie(root);
//
//        return root;
//    }
//
//    AVLNode* search(AVLNode* node, const string& key) {
//        if (node == nullptr || key == node->key) {
//            return node;
//        }
//
//        if (key < node->key) {
//            return search(node->left, key);
//        }
//        else {
//            return search(node->right, key);
//        }
//    }
//
//    AVLNode* findMinNode(AVLNode* node) {
//        while (node->left != nullptr) {
//            node = node->left;
//        }
//        return node;
//    }
//
//
//    void inOrderTraversalHelper(AVLNode* node, ostream& output) {
//        if (node != nullptr) {
//            inOrderTraversalHelper(node->left, output);
//            output << node->key << " " << node->meaning << endl;
//            inOrderTraversalHelper(node->right, output);
//        }
//    }
//
//    void inOrderTraversal(AVLNode* node, ofstream& outputFile) {
//        inOrderTraversalHelper(node, outputFile);
//    }
//
//public:
//    AVLTree() : root(nullptr) {}
//
//    void insert(string key, string meaning) {
//        root = insert(root, key, meaning);
//        suggestionsTrie.insert(key); // Update suggestions trie
//    }
//
//    void loadFromFile(const string& filename) {
//        ifstream inputFile(filename);
//
//        if (!inputFile.is_open()) {
//            cerr << "Error opening the file.\n";
//            return;
//        }
//
//        cout << "Inserting words and meanings from file into AVL tree:\n";
//
//        string word, meaning;
//
//        // Read word and meaning from the file
//        while (inputFile >> word) {
//            // Read the rest of the line as the meaning
//            getline(inputFile >> ws, meaning);
//            insert(word, meaning);
//        }
//
//        cout << endl << "File Successfully Loaded!!!\n";
//        inputFile.close();
//    }
//
//    void addWordToFile(const string& filename, string key, string meaning) {
//        ofstream outputFile(filename, ios::app);
//
//        if (!outputFile.is_open()) {
//            cerr << "Error opening the file.\n";
//            return;
//        }
//
//        // Append the word and its meaning to the file
//        outputFile << key << " " << meaning << endl;
//
//        outputFile.close();
//
//        // After adding the word to the file, also update the AVL tree
//        insert(key, meaning);
//    }
//
//    void deleteWordFromFile(const string& filename, const string& key) {
//        // Search for the word in the AVL tree
//        AVLNode* nodeToDelete = searchWord(key);
//
//        if (nodeToDelete != nullptr) {
//            // Delete the word from the AVL tree
//            root = deleteNode(root, key);
//
//            // Update the file after deletion
//            ofstream outputFile(filename);
//
//            if (!outputFile.is_open()) {
//                cerr << "Error opening the file.\n";
//                return;
//            }
//
//            // Update the file with the remaining words in the AVL tree
//            inOrderTraversal(root, outputFile);
//
//            outputFile.close();
//
//            // Update suggestions trie after deletion
//            suggestionsTrie = Trie();
//            updateSuggestionsTrie(root);
//
//            cout << "Word deleted successfully!\n";
//        }
//        else {
//            cout << "Word not found.\n";
//        }
//    }
//
//
//    AVLNode* searchWord(const string& key) {
//        return search(root, key);
//    }
//
//    void updateWordMeaning(const string& key, const string& newMeaning) {
//        AVLNode* node = searchWord(key);
//
//        if (node != nullptr) {
//            node->meaning = newMeaning;
//            cout << "Word updated successfully!\n";
//        }
//        else {
//            cout << "Word not found.\n";
//        }
//    }
//
//    void displayInOrder(ostream& output = cout) {
//        if (root == nullptr) {
//            output << "AVL tree is empty.\n";
//            return;
//        }
//        inOrderTraversalHelper(root, output);
//    }
//
//    void displaySuggestions(const string& prefix) {
//        cout << "\nSuggestions for prefix '" << prefix << "':\n";
//        suggestionsTrie.getSuggestions(prefix);
//    }
//
//private:
//    void updateSuggestionsTrie(AVLNode* node) {
//        if (node != nullptr) {
//            updateSuggestionsTrie(node->left);
//            suggestionsTrie.insert(node->key);
//            updateSuggestionsTrie(node->right);
//        }
//    }
//};
//
//void displayMenu() {
//    cout << "\nMenu:\n";
//    cout << "1. Display AVL Tree (Words and Meanings)\n";
//    cout << "2. Add Word to AVL Tree and File\n";
//    cout << "3. Search for a Word\n";
//    cout << "4. Update Word Meaning\n";
//    cout << "5. Delete Word\n";
//    cout << "6. Display Suggestions\n";
//    cout << "7. Exit\n";
//}
//
//int main() {
//    AVLTree avlTree;
//
//    // Load data from file and insert into AVL tree
//    avlTree.loadFromFile("outfile.txt");
//
//    int choice;
//    do {
//        displayMenu();
//        cout << "Enter your choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            // Display AVL Tree
//            cout << "\nIn-order traversal of AVL tree (Words and Meanings):\n";
//            avlTree.displayInOrder();
//            break;
//        case 2: {
//            // Add a new word and meaning to the file and AVL tree
//            string newWord, newMeaning;
//            cout << "\nEnter the new word: ";
//            cin >> newWord;
//            cout << "Enter the meaning of the word: ";
//            cin.ignore();  // Clear newline from the buffer
//            getline(cin, newMeaning);
//            avlTree.addWordToFile("outfile.txt", newWord, newMeaning);
//            cout << "\nWord added successfully!\n";
//            break;
//        }
//        case 3: {
//            // Search for a word
//            string searchWord;
//            cout << "\nEnter the word to search: ";
//            cin >> searchWord;
//            AVLNode* result = avlTree.searchWord(searchWord);
//            if (result != nullptr) {
//                cout << "Word found: " << result->key << " - " << result->meaning << endl;
//            }
//            else {
//                cout << "Word not found.\n";
//            }
//            break;
//        }
//        case 4: {
//            // Update word meaning
//            string updateWord, newMeaning;
//            cout << "\nEnter the word to update: ";
//            cin >> updateWord;
//            cout << "Enter the new meaning: ";
//            cin.ignore();  // Clear newline from the buffer
//            getline(cin, newMeaning);
//            avlTree.updateWordMeaning(updateWord, newMeaning);
//            break;
//        }
//        case 5: {
//            // Delete word
//            string deleteWord;
//            cout << "\nEnter the word to delete: ";
//            cin >> deleteWord;
//            avlTree.deleteWordFromFile("outfile.txt", deleteWord);
//            break;
//        }
//        case 6: {
//            // Display suggestions
//            string prefix;
//            cout << "\nEnter the prefix to get suggestions: ";
//            cin >> prefix;
//            avlTree.displaySuggestions(prefix);
//            break; 
//        }
//        case 7:
//            cout << "\nExiting program. Goodbye!\n";
//            break;
//        default:
//            cout << "\nInvalid choice. Please enter a valid option.\n";
//        }
//    } while (choice != 7);
//    return 0;
//}