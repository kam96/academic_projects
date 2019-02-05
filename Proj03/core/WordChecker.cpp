// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"



WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return (words.contains(word)) ? true : false;
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::string currentWord = word;
    std::vector<std::string> suggestions;

    swapper(suggestions, currentWord);
    inserter(suggestions, currentWord);
    deleter(suggestions, currentWord);
    replacer(suggestions, currentWord);
    splitter(suggestions, currentWord);

    return suggestions;
}


void WordChecker::swapper(std::vector<std::string> &suggestions, std::string word) const
{
    for (int i = 0; i < word.size(); i++)
    {
        if (i == word.size()-1) return;
        std::string newWord = word;
        newWord[i] = word[i+1];
        newWord[i+1] = word[i];
        if (wordExists(newWord))
            suggestions.push_back(newWord);
    }
}


void WordChecker::inserter(std::vector<std::string> &suggestions, std::string word) const
{
    for (int i = 0; i <= word.size(); i++)
    {
        for (int j = 0; j < letters.size(); j++)
        {
            std::string newWord = word;
            newWord.insert(newWord.begin()+i, letters[j]);
            if (wordExists(newWord))
                suggestions.push_back(newWord);
        }
    }
}


void WordChecker::deleter(std::vector<std::string> &suggestions, std::string word) const
{
    for (int i = 0; i < word.size(); i++)
    {
        std::string newWord = word;
        newWord.erase(newWord.begin()+i);
        if (wordExists(newWord))
            suggestions.push_back(newWord);
    }
}


void WordChecker::replacer(std::vector<std::string> &suggestions, std::string word) const
{
    for (int i = 0; i < word.size(); i++)
    {
        for (int j = 0; j < letters.size(); j++)
        {
            std::string newWord = word;
            newWord[i] = letters[j];
            if (wordExists(newWord))
                suggestions.push_back(newWord);
        }
    }
}


void WordChecker::splitter(std::vector<std::string> &suggestions, std::string word) const
{
    for (int i = 1; i < word.size(); i++)
    {
        std::string first = word.substr(0,i);
        std::string second = word.substr(i,word.size()-1);
        std::string newWord = first + " " + second;
        if (wordExists(first) && wordExists(second))
            suggestions.push_back(newWord);
    }
}

