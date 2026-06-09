// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
class BST {
private:
    struct N {
        T key;
        int freq;
        N* left;
        N* right;
        
        N(const T& val) : key(val), freq(1), left(nullptr), right(nullptr) {}
    };
    
    N* m_root;
    int m_nodeCount;
    
    void deleteTree(N* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    
    N* addNode(N* node, const T& val, bool& isNew) {
        if (!node) {
            isNew = true;
            return new N(val);
        }
        
        if (val < node->key) {
            node->left = addNode(node->left, val, isNew);
        } else if (val > node->key) {
            node->right = addNode(node->right, val, isNew);
        } else {
            node->freq++;
            isNew = false;
        }
        return node;
    }
    
    N* findNode(N* node, const T& val) const {
        if (!node || node->key == val) {
            return node;
        }
        if (val < node->key) {
            return findNode(node->left, val);
        }
        return findNode(node->right, val);
    }
    
    int getHeight(N* node) const {
        if (!node) return 0;
        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
    
    void collectData(N* node, std::vector<std::pair<T, int>>& items) const {
        if (node) {
            collectData(node->left, items);
            items.push_back({node->key, node->freq});
            collectData(node->right, items);
        }
    }
    
public:
    BST() : m_root(nullptr), m_nodeCount(0) {}
    
    ~BST() {
        deleteTree(m_root);
    }
    
    bool insert(const T& val) {
        bool isNew = false;
        m_root = addNode(m_root, val, isNew);
        if (isNew) m_nodeCount++;
        return isNew;
    }
    
    bool search(const T& val) const {
        return findNode(m_root, val) != nullptr;
    }
    
    int getFrequency(const T& val) const {
        N* node = findNode(m_root, val);
        return node ? node->freq : 0;
    }
    
    int depth() const {
        return getHeight(m_root);
    }
    
    int size() const {
        return m_nodeCount;
    }
    
    bool isEmpty() const {
        return m_root == nullptr;
    }
    
    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<std::pair<T, int>> items;
        collectData(m_root, items);
        return items;
    }
    
    void display() const {
        std::vector<std::pair<T, int>> items;
        collectData(m_root, items);
        for (const auto& item : items) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    }
};

#endif  // INCLUDE_BST_H_
