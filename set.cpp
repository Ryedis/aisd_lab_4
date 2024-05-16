#include <iostream>
#include <stdexcept>
#include <stack>

namespace custom_set {
    class CustomSet {
    private:
        struct Node {
            int _data;
            Node* _left;
            Node* _right;

            Node(int val) : _data(val), _left(nullptr), _right(nullptr) {}
        };

        Node* root;

        void destroyTree(Node* node) {
            if (node) {
                destroyTree(node->_left);
                destroyTree(node->_right);
                delete node;
            }
        }

        Node* copyTree(Node* node) {
            if (node == nullptr) {
                return nullptr;
            }

            Node* newNode = new Node(node->_data);
            if (newNode == nullptr) {
                throw std::bad_alloc();
            }

            newNode->_left = copyTree(node->_left);
            newNode->_right = copyTree(node->_right);

            return newNode;
        }

        void printTree(Node* node) {
            if (node) {
                printTree(node->_left);
                std::cout << node->_data << " ";
                printTree(node->_right);
            }
        }

        Node* findMin(Node* node) const {
            if (node == nullptr) {
                return nullptr;
            }

            while (node->_left != nullptr) {
                node = node->_left;
            }

            return node;
        }

        Node* eraseNode(Node* node, int key) {
            if (node == nullptr) {
                return nullptr;
            }

            if (key < node->_data) {
                node->_left = eraseNode(node->_left, key);
            }
            else if (key > node->_data) {
                node->_right = eraseNode(node->_right, key);
            }
            else {
                if (node->_left == nullptr) {
                    Node* _rightChild = node->_right;
                    delete node;
                    return _rightChild;
                }
                else if (node->_right == nullptr) {
                    Node* _leftChild = node->_left;
                    delete node;
                    return _leftChild;
                }
                else {
                    Node* successor = findMin(node->_right);
                    node->_data = successor->_data;
                    node->_right = eraseNode(node->_right, successor->_data);
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
                    if (key == current->_data) {
                        return false; // Element already exists
                    }
                    parent = current;
                    if (key < current->_data) {
                        current = current->_left;
                    }
                    else {
                        current = current->_right;
                    }
                }

                Node* newNode = new Node(key);
                if (newNode == nullptr) {
                    throw std::bad_alloc();
                }

                if (parent == nullptr) {
                    root = newNode;
                }
                else if (key < parent->_data) {
                    parent->_left = newNode;
                }
                else {
                    parent->_right = newNode;
                }

                return true;
            }
            catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed in insert method: " << e.what() << std::endl;
                return false;
            }
        }

        bool contains(const int key) const {
            Node* current = root;

            while (current != nullptr) {
                if (key == current->_data) {
                    return true; // Element found
                }
                else if (key < current->_data) {
                    current = current->_left;
                }
                else {
                    current = current->_right;
                }
            }

            return false; // Element not found
        }

        bool erase(int key) {
            root = eraseNode(root, key);
            return (root != nullptr); // Return true if root is not nullptr after deletion
        }

        class Iterator {
        public:
            explicit Iterator(Node* start = nullptr) {
                if (start) {
                    traverse_left(start);
                }
            }

            int operator*() const {
                return stack.top()->_data;
            }

            Iterator& operator++() {
                Node* current = stack.top();
                stack.pop();

                if (current->_right) {
                    traverse_left(current->_right);
                }

                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return !stack.empty() || !other.stack.empty();
            }

        private:
            void traverse_left(Node* node) {
                while (node) {
                    stack.push(node);
                    node = node->_left;
                }
            }

            std::stack<Node*> stack;
        };

        Iterator begin() {
            return Iterator(root);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

        // Constant Forward Iterator for CustomSet
        class ConstIterator {
        public:
            explicit ConstIterator(Node* start = nullptr) {
                if (start) {
                    traverse_left(start);
                }
            }

            int operator*() const {
                return stack.top()->_data;
            }

            ConstIterator& operator++() {
                Node* current = const_cast<Node*>(stack.top());
                stack.pop();

                if (current->_right) {
                    traverse_left(current->_right);
                }

                return *this;
            }

            bool operator!=(const ConstIterator& other) const {
                return !stack.empty() || !other.stack.empty();
            }

        private:
            void traverse_left(Node* node) {
                while (node) {
                    stack.push(node);
                    node = node->_left;
                }
            }

            std::stack<const Node*> stack;
        };

        ConstIterator begin() const {
            return ConstIterator(root);
        }

        ConstIterator end() const {
            return ConstIterator(nullptr);
        }
    };

    // set1 intersection set2
    CustomSet findIntersection(const CustomSet& set1, const CustomSet& set2) {
        CustomSet intersection;

        for (int elem : set1) {
            if (set2.contains(elem)) {
                intersection.insert(elem);
            }
        }

        return intersection;
    }

    // set1 \ set2
    CustomSet findDifference(const CustomSet& set1, const CustomSet& set2) {
        CustomSet difference;

        for (int elem : set1) {
            if (!set2.contains(elem)) {
                difference.insert(elem);
            }
        }

        return difference;
    }
    
}
