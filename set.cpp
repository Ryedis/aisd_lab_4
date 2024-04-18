#include <iostream>
#include <stdexcept>

namespace custom_set {
    class CustomSet {
    private:
        struct Node {
            int data;
            Node* left;
            Node* right;

            Node(int val) : data(val), left(nullptr), right(nullptr) {}
        };

        Node* root;

        void destroyTree(Node* node) {
            if (node) {
                destroyTree(node->left);
                destroyTree(node->right);
                delete node;
            }
        }

        Node* copyTree(Node* node) {
            if (node == nullptr) {
                return nullptr;
            }

            Node* newNode = new Node(node->data);
            if (newNode == nullptr) {
                throw std::bad_alloc();
            }

            newNode->left = copyTree(node->left);
            newNode->right = copyTree(node->right);

            return newNode;
        }

        void printTree(Node* node) {
            if (node) {
                printTree(node->left);
                std::cout << node->data << " ";
                printTree(node->right);
            }
        }

        Node* eraseNode(Node* node, int key) {
            if (node == nullptr) {
                return nullptr;
            }

            if (key < node->data) {
                node->left = eraseNode(node->left, key);
            }
            else if (key > node->data) {
                node->right = eraseNode(node->right, key);
            }
            else {
                if (node->left == nullptr) {
                    Node* rightChild = node->right;
                    delete node;
                    return rightChild;
                }
                else if (node->right == nullptr) {
                    Node* leftChild = node->left;
                    delete node;
                    return leftChild;
                }
                else {
                    Node* successor = findMin(node->right);
                    node->data = successor->data;
                    node->right = eraseNode(node->right, successor->data);
                }
            }
            return node;
        }

    public:
        CustomSet() : root(nullptr) {}

        CustomSet(const CustomSet& other) {
            try {
                root = copyTree(other.root);
            }
            catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed in copy constructor: " << e.what() << std::endl;
                root = nullptr;
            }
        }

        ~CustomSet() {
            destroyTree(root);
        }

        CustomSet& operator=(const CustomSet& other) {
            if (this != &other) {
                try {
                    destroyTree(root);
                    root = copyTree(other.root);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed in assignment operator: " << e.what() << std::endl;
                    destroyTree(root);
                    root = nullptr;
                }
            }
            return *this;
        }

        void print() {
            printTree(root);
            std::cout << std::endl;
        }

        bool insert(int key) {
            try {
                Node* current = root;
                Node* parent = nullptr;

                while (current != nullptr) {
                    if (key == current->data) {
                        return false; // Element already exists
                    }
                    parent = current;
                    if (key < current->data) {
                        current = current->left;
                    }
                    else {
                        current = current->right;
                    }
                }

                Node* newNode = new Node(key);
                if (newNode == nullptr) {
                    throw std::bad_alloc();
                }

                if (parent == nullptr) {
                    root = newNode;
                }
                else if (key < parent->data) {
                    parent->left = newNode;
                }
                else {
                    parent->right = newNode;
                }

                return true;
            }
            catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed in insert method: " << e.what() << std::endl;
                return false;
            }
        }

        bool contains(int key) {
            Node* current = root;

            while (current != nullptr) {
                if (key == current->data) {
                    return true; // Element found
                }
                else if (key < current->data) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }

            return false; // Element not found
        }

        bool erase(int key) {
            root = eraseNode(root, key);
            return (root != nullptr); // Return true if root is not nullptr after deletion
        }

        

    };
}
