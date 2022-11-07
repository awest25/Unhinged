#ifndef RadixTree_h
#define RadixTree_h

#include <string>
#include <vector>
#include <iostream>

//For your RadixTree class, try figuring out all the special cases first and draw diagrams showing what your tree will look like in each case. Doing so will dramatically reduce the number of bugs you have (and save you hours of implementation time).

template <typename ValueType>
class RadixTree {
public:
    RadixTree() : m_rootPtr(new Node(nullptr)) {}
    ~RadixTree() { deleteNodeAndChildren(m_rootPtr); delete m_rootPtr;}
    void insert(std::string key, const ValueType& value)
    {
        ValueType* valuePtr = const_cast<ValueType*>(new ValueType(value));
        insert(key, valuePtr, m_rootPtr, nullptr); // call to auxillary insert
    }
    ValueType* search(std::string key) const
    {
        return search(key, m_rootPtr); // call to auxillary search
    }
    
private:
    
    struct Node
    {
        Node(Node* parentIn, std::string prefixIn = "", ValueType* valuePtrIn = nullptr) : prefix(prefixIn), valuePtr(valuePtrIn), parent(parentIn), children() {} // 540k nodes created for memberDB
        std::string prefix;
        ValueType* valuePtr;
        Node* parent;
        Node* children[128];
    };
    
    void insert(std::string key, ValueType* value, Node* root, Node* parent)
    {
        char firstLetter = key.at(0);
        
        if (root == nullptr) // root isn't a node
        {
            parent->children[firstLetter] = new Node(parent, key, value);
            return;
        }
        
        std::string &currentPrefix = root->prefix;
        
        for (int i = 0; i < currentPrefix.size(); i++)
            if (i >= key.size() || currentPrefix.at(i) != key.at(i)) // reached mismach in prefix
            {
                if (i == 0) // no letters in common?
                {
                    insert(key, value, root->children[ key.at(0) ], root);
                    return;
                }
                // make new node between root and current node
                std::string newNodePrefix = currentPrefix.substr(0, i);
                Node* newNodePtr = new Node(parent, newNodePrefix);
                currentPrefix = currentPrefix.substr(i);
                newNodePtr->children[currentPrefix.at(0)] = root;
                parent->children[firstLetter] = newNodePtr;
                root->parent = newNodePtr;
                
                std::string newKey = key.substr(i);
                
                if (i >= key.size()) // if the key is over
                    newNodePtr->valuePtr = value;
                else
                    insert(key.substr(i), value, newNodePtr->children[newKey.at(0)], newNodePtr);
                return;
            }
        
        // we've reached the end of prefix
        std::string remainingString = key.substr(currentPrefix.size());
        if (remainingString == "")
        {
            root->valuePtr = value; // map the ending node to value
            return;
        }
        insert(remainingString, value, root->children[ remainingString.at(0) ], root);
    }
    
    ValueType* search(std::string key, Node* currentNode) const
    {
        if (currentNode == nullptr) return nullptr;
        if (key == "") return nullptr;
        if (key == currentNode->prefix)
            return currentNode->valuePtr;
        int i = 0;
        for ( ; i < currentNode->prefix.size(); i++)
            if (i >= key.size()) // reached mismach in prefix
            {
                if (key != "")
                    i--;
                break;
            }
            else if (currentNode->prefix.at(i) != key.at(i))
                return nullptr;
        int firstLetter = key.at(i);
        return search(key.substr(i), currentNode->children[firstLetter]);
    }
    
    void deleteNodeAndChildren(Node* currentNode)
    {
        if (currentNode == nullptr) return;
        std::string trash = currentNode->prefix;
        for (int i = 0; i < 128; i++)
        {
            if (currentNode->children[i] != nullptr)
            {
                deleteNodeAndChildren(currentNode->children[i]);
                if ((currentNode->children[i])->valuePtr != nullptr)
                    delete (currentNode->children[i])->valuePtr;
                delete currentNode->children[i];
            }
        }
    }
    
//    void dumpTree(Node* root, std::string str)
//    {
//        if (root == nullptr) return;
//        if (root->valuePtr != nullptr)
//            std::cerr << str << (root->prefix) << std::endl;
////        std::cerr << root->prefix << std::endl;
//        for (int i = 0; i < 128; i++)
//        {
//            dumpTree(root->children[i], str + root->prefix);
//        }
//    }
    
    Node* m_rootPtr;
};

//inline void RadixTree::insert(std::string key, const ValueType& value) {int i = 3;}
//int chrInt(char c)
//{
//    return c - 1;
//}

#endif /* RadixTree_h */
