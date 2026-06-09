// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <chrono>
#include "bst.h"

void makeTree(BST<std::string>& bst, const char* filePath);
void printFreq(BST<std::string>& bst);

int main() {
    std::cout << "Binary Search Tree Word Frequency Analysis" << std::endl;
    std::cout << "Analyzing: War and Peace by Leo Tolstoy" << std::endl;
    
    BST<std::string> wordTree;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    makeTree(wordTree, "war_peace.txt");
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << "\nTree Statistics" << std::endl;
    std::cout << "Tree building time: " << elapsedMs.count() << " ms" << std::endl;
    std::cout << "Number of unique words: " << wordTree.size() << std::endl;
    std::cout << "Tree depth (height): " << wordTree.depth() << std::endl;
    
    std::cout << "\nSearch Examples" << std::endl;
    std::string testWords[] = {"war", "peace", "and", "tolstoy", "russian"};
    for (const auto& word : testWords) {
        int freq = wordTree.getFrequency(word);
        if (freq > 0) {
            std::cout << "Word '" << word << "' found " << freq << " times" << std::endl;
        } else {
            std::cout << "Word '" << word << "' not found" << std::endl;
        }
    }
    
    printFreq(wordTree);
    
    return 0;
}
