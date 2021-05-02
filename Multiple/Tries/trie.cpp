#ifndef __TRIE_CPP
#define __TRIE_CPP

#include "trie.hpp"

trie::trie()
{
    root = shared_ptr<Node>(new Node);
    root->value = ' ';
}

vector<shared_ptr<Node>> sort(shared_ptr<Node> node)
{
    if(node->children.size() <= 1)
    {
        return node->children;
    }
    else
    {
        vector<shared_ptr<Node>> tempChild;
        tempChild.reserve(node->children.size());
        int index;
        for(int i = 0; i < node->children.size(); ++i)
        {
            tempChild.push_back(node->children[i]);
            for(int j = i; j > 0; --j)
            {
                char compareOne = tempChild[j]->value;
                char compareTwo = tempChild[j - 1]->value;
                if(compareOne < 97)
                {
                    compareOne += 32;
                }
                if(compareTwo < 97)
                {
                    compareTwo += 32;
                }
                if(compareOne >= compareTwo)
                {
                    break;
                }
                else
                {
                    shared_ptr<Node> temp = tempChild[j];
                    tempChild[j] = tempChild[j - 1];
                    tempChild[j - 1] = temp;
                }
            }
        }
        return tempChild;
    }
}

void trie::insertWord(string word)
{
    shared_ptr<Node> traverse = root;
    bool found = false;
    for(int i = 0; i < word.length(); ++i)
    {
        for(int j = 0; j < traverse->children.size(); ++j)
        {
            if(traverse->children[j]->value == word[i])
            {
                traverse = traverse->children[j];
                found = true;
                break;
            }
        }
        if(!found)
        {
            for(int j = i; j < word.length(); ++j)
            {
                shared_ptr<Node> newNode = shared_ptr<Node>(new Node);
                newNode->value = word[j];
                traverse->children.push_back(newNode);
                traverse->children = sort(traverse);
                traverse = newNode;
            }
            break;
        }
        found = false;
    }
}

bool trie::search(string word)
{
    if(root->children.size() == 0)
    {
        return false;
    }
    else
    {
        shared_ptr<Node> traverse = root;
        bool found = false;
        for(int i = 0; i < word.length(); ++i)
        {
            for(int j = 0; j < traverse->children.size(); ++j)
            {
                if(traverse->children[j]->value == word[i])
                {
                    traverse = traverse->children[j];
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                return false;
            }
            found = false;
        }
        return true;
    }
}
string trie::longestSubstr(string word)
{
    if(root->children.size() == 0)
    {
        return "";
    }
    else
    {
        shared_ptr<Node> traverse = root;
        bool found = false;
        string subString = "";
        for(int i = 0; i < word.length(); ++i)
        {
            for(int j = 0; j < traverse->children.size(); ++j)
            {
                if(traverse->children[j]->value == word[i])
                {
                    traverse = traverse->children[j];
                    found = true;
                    subString += word[i];
                    break;
                }
            }
            if(!found)
            {
                return subString;
            }
            found = false;
        }
        return subString;
    }
}

void depthFirstSearch(vector<string> &items, shared_ptr<Node> node, string word)
{
    if(node->children.size() == 0)
    {
        items.push_back(word);
        return;
    }
    for(int i = 0; i < node->children.size(); ++i)
    {
        depthFirstSearch(items, node->children[i], word + node->children[i]->value);
    }
}

vector<string> trie::getTrie()
{
    vector<string> items;
    string word = "";
    depthFirstSearch(items, root, word);
    return items;
}

void trie::deleteWord(string word)
{
    if(root->children.size() == 0)
    {
        return;
    }
    vector<string> listOfStrings = getTrie();
    bool found = false;
    for(int i = 0; i < listOfStrings.size(); ++i)
    {
        if(listOfStrings[i] == word)
        {
            found = true;
            break;
        }
    }
    if(found)
    {
        shared_ptr<Node> traverse = root;
        shared_ptr<Node> junction = root;
        char deleteChar = word[0];
        for(int i = 0; i < word.length(); ++i)
        {
            for(int j = 0; j < traverse->children.size(); ++j)
            {
                if(traverse->children[j]->value == word[i])
                {
                    if(traverse->children.size() > 1)
                    {
                        junction = traverse;
                        deleteChar = word[i];
                    }
                    traverse = traverse->children[j];
                    break;
                }
            }
        }
        vector<shared_ptr<Node>> tempChild;
        int length = junction->children.size();
        tempChild.reserve(length - 1);
        for(int i = 0; i < junction->children.size(); ++i)
        {
            if(junction->children[i]->value != deleteChar)
            {
                tempChild.push_back(junction->children[i]);
                junction->children[i] = NULL;
            }
        }
        junction->children = tempChild;
        return;
    }
}

#endif