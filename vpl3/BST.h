#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

template <class T>
class BinarySearchTree
{
public:
    BinarySearchTree();// "по умолчанию" создает пустое дерево
    BinarySearchTree(const BinarySearchTree<T> & scr) = delete;
    BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
    BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
    BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
    virtual ~BinarySearchTree();

    bool searchInteractive (const T& key)ж

    bool insert(const T& key);

    void output(std::ostream& out) const;

    int getNumberOfNodes () const;

    int getHeight() const;

    void inorderWalkIterative () const;

    void inorderWalk() const;

    void walkByLevels() const;

private:
    Node<T>* searchIterative (const T& key) const;

    void output(std::ostream& out, Node<T>* root) const;

    int getNumberOfNodes(const Node<T>* node) const;

    int getHeight(const Node<T>* node) const;

    void inorderWalk(Node<T>* node) const;

    template <class T>
    struct Node {
    T key_; // значение ключа, содержащееся в узле
    Node<T> *left_; // указатель на левое поддерево
    Node<T> *right_; // указатель на правое поддерево
    Node<T> *p_; // указатель на родителя !!! не используется // Конструктор узла
    Node(T key, Node *left = nullptr, Node *right= nullptr,Node *p =nullptr):
    key_(key), left_ (left), right_(right), p_(p)
    { }
    };
    Node<T> *root_; // Указатель на корневой узел
};

#endif