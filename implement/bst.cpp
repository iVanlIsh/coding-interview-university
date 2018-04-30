#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T value;
    struct Node<T>* left=NULL;
    struct Node<T>* right=NULL;
    Node(T v) {value=v;}
};

template<typename T>
class BST {
private:
    struct Node<T>* root=NULL;
protected:
    struct Node<T>* insert_util(T value, struct Node<T>* node) {
        if(!node) return new Node<T>(value);
        else if(value < node->value) node->left = insert_util(value, node->left);
        else node->right = insert_util(value, node->right);
        return node;
    }
    struct Node<T>* delete_value_util(T value, struct Node<T>* node) {
        if(!node) return node;
        if(node->value == value) {
            if(!node->left && !node->right) {
                delete node;
                return NULL;
            } else if (!node->right) {
                struct Node<T>* n = node;
                node = node->left;
                delete n;
            } else if(!node->left) {
                struct Node<T>* n = node;
                node = node->right;
                delete n;
            } else {
                struct Node<T>* n = node->right;
                while(n->left)
                    n = n->left;
                node->value = n->value;
                node->right = delete_value_util(n->value, node->right);
            }
        } else if (node->value > value) {
            node->left = delete_value_util(value, node->left);
        } else {
            node->right = delete_value_util(value, node->right);
        }
        return node;
    }

    struct Node<T>* search(T value, struct Node<T>* node) {
        if(!node) return NULL;
        if(node->value == value) return node;
        if(value < node->value) return search(value, node->left);
        return search(value, node->right);
    }
public:
    BST() {}
    ~BST() {delete_tree(root);}
    struct Node<T>* get_root() {return root;}
    void insert(T value) {root = insert_util(value, root);}

    unsigned long get_subtree_node_count(struct Node<T>* node) {
        if(!node) return 0;
        return get_subtree_node_count(node->left) + get_subtree_node_count(node->right) + 1;
    }
    unsigned long get_node_count() {return get_subtree_node_count(root);}

    void print_subtree_values(struct Node<T>* node) {
        if(!node) return;
        print_subtree_values(node->left);
        cout << node->value;
        print_subtree_values(node->right);
        if(node == root) cout << endl;
    }
    void print_values() {print_subtree_values(root);}

    void delete_tree(struct Node<T>* tree) {
        if(tree->left) delete_tree(tree->left);
        if(tree->right) delete_tree(tree->right);
        delete tree;
    }

    bool is_in_subtree(T value, struct Node<T>* node) {
        if(!node) return false;
        if(node->value == value) return true;
        if(value < node->value) return is_in_subtree(value, node->left);
        return is_in_subtree(value, node->right);
    }
    bool is_in_tree(T value) {return is_in_subtree(value, root);}

    long long get_subtree_height(struct Node<T>* node) {
        if(!node) return -1;
        return max(get_subtree_height(node->left), get_subtree_height(node->right)) + 1;
    }
    unsigned long get_height() {return get_subtree_height(root);}

    T get_subtree_min(struct Node<T>* node) {
        if(!node) return NULL;
        return node->left? get_subtree_min(node->left) : node->value;
    }
    T get_min() {return get_subtree_min(root);}

    T get_subtree_max(struct Node<T> * node) {
        if(!node) return NULL;
        return node->right? get_subtree_max(node->right) : node->value;
    }
    T get_max() {return get_subtree_max(root);}

    void delete_value(T value) {delete_value_util(value, root);}

    T get_successor(T value) {
        struct Node<T>* node = search(value, root);
        if(!node) return -1;
        if(node->right) {
            struct Node<T>* next = node->right;
            while(next->left) next = next->left;
            return next->value;
        } else {
            struct Node<T>* parent = root, *successor = NULL;
            while(parent != node) {
                if(parent->value > node->value) {
                    successor = parent;
                    parent = parent->left;
                } else {
                    parent = parent->right;
                }
            }
            return successor? successor->value : -1;
        }
    }
};

template<typename T>
bool is_binary_search_tree(struct Node<T> * node,
                           T min_val=numeric_limits<T>::min(),
                           T max_val=numeric_limits<T>::max()) {
    if(!node) return true;
    if(node->value >= min_val && node->value <= max_val
       && is_binary_search_tree(node->left, min_val, node->value)
       && is_binary_search_tree(node->right, node->value, max_val)) return true;
    return false;
}

int main() {
    BST<int> bst;
    bst.insert(10);
    bst.insert(1);
    bst.insert(12);
    bst.insert(11);
    bst.insert(-1);
    bst.insert(8);
    cout << bst.get_node_count() << endl;
    bst.delete_value(1);
    bst.print_values();
    cout << bst.is_in_tree(10) << bst.is_in_tree(80) << is_binary_search_tree(bst.get_root()) << endl;
    cout << bst.get_height() << bst.get_min() << bst.get_max() << endl;
    cout << bst.get_successor(10) << bst.get_successor(12) << endl;
}
