// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
#include "bst.h"

bool isLatinChar(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

void makeTree(BST<std::string>& bst, const char* filePath) {
    std::ifstream inputFile(filePath);
    
    if (!inputFile) {
        std::cout << "File error! Cannot open file: " << filePath << std::endl;
        return;
    }
    
    std::string currentToken;
    
    while (!inputFile.eof()) {
        int symbol = inputFile.get();
        
        if (symbol == EOF) break;
        
        char ch = static_cast<char>(symbol);
        
        if (isLatinChar(ch)) {
            currentToken += toLower(ch);
        } else {
            if (!currentToken.empty()) {
                bst.insert(currentToken);
                currentToken.clear();
            }
        }
    }
    
    if (!currentToken.empty()) {
        bst.insert(currentToken);
    }
    
    inputFile.close();
    
    std::cout << "File processed successfully!" << std::endl;
    std::cout << "Unique words: " << bst.size() << std::endl;
    std::cout << "Tree depth: " << bst.depth() << std::endl;
}

void printFreq(BST<std::string>& bst) {
    std::vector<std::pair<std::string, int>> allEntries = bst.getAllNodes();
    
    std::sort(allEntries.begin(), allEntries.end(), 
        [](const std::pair<std::string, int>& first, const std::pair<std::string, int>& second) {
            if (first.second != second.second) {
                return first.second > second.second;
            }
            return first.first < second.first;
        });
    
    std::ofstream outputFile("result/freq.txt");
    if (!outputFile) {
        std::cout << "Cannot create result/freq.txt file!" << std::endl;
        return;
    }
    
    std::cout << "Word Frequency Analysis" << std::endl;
    std::cout << "Total unique words: " << allEntries.size() << std::endl;
    
    outputFile << "Word Frequency Analysis" << std::endl;
    outputFile << "Total unique words: " << allEntries.size() << std::endl;
    outputFile << "Word : Frequency" << std::endl;
    
    int limitDisplay = std::min(50, static_cast<int>(allEntries.size()));
    
    for (size_t idx = 0; idx < allEntries.size(); idx++) {
        const auto& entry = allEntries[idx];
        outputFile << entry.first << " : " << entry.second << std::endl;
        
        if (idx < limitDisplay) {
            std::cout << entry.first << " : " << entry.second << std::endl;
        } else if (idx == limitDisplay) {
            std::cout << "... and " << (allEntries.size() - limitDisplay) << " more words (see freq.txt)" << std::endl;
        }
    }
    
    outputFile.close();
    std::cout << "\nFull frequency table saved to freq.txt" << std::endl;
}
