#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "Post.hpp"
#include <vector>

struct AVLNode {
    Post post;
    AVLNode *left, *right;
    int height;
    AVLNode(const Post &p) : post(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode *root = nullptr;

    int height(AVLNode *node) { return node ? node->height : 0; }
    int getBalance(AVLNode *node) { return node ? height(node->left) - height(node->right) : 0; }

    AVLNode* rightRotate(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode *node, const Post &p) {
        if (!node) return new AVLNode(p);

        if (p.timestamp < node->post.timestamp)
            node->left = insert(node->left, p);
        else
            node->right = insert(node->right, p);

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);
        if (balance > 1 && p.timestamp < node->left->post.timestamp)
            return rightRotate(node);
        if (balance < -1 && p.timestamp > node->right->post.timestamp)
            return leftRotate(node);
        if (balance > 1 && p.timestamp > node->left->post.timestamp) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && p.timestamp < node->right->post.timestamp) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void reverseInorder(AVLNode *node, std::vector<Post> &posts, int &N) {
        if (!node || (N == 0)) return;
        reverseInorder(node->right, posts, N);
        if (N != 0) {
            posts.push_back(node->post);
            if (N > 0) N--;
        }
        reverseInorder(node->left, posts, N);
    }

public:
    void insert(const Post &p) { root = insert(root, p); }

    std::vector<Post> getRecentPosts(int N) {
        std::vector<Post> posts;
        reverseInorder(root, posts, N);
        return posts;
    }
};

#endif
