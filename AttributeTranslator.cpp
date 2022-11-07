#include <fstream> // file input
#include <sstream> // string input
#include <iostream>
#include "AttributeTranslator.h"

bool AttributeTranslator::Load(std::string filename) // TODO: impliment
{
    std::ifstream fileContents(filename);
//    std::cerr << fileContents.rdbuf();
    if (!fileContents)
        return false;
    std::string line;
    while (std::getline(fileContents, line)) // standard reading lines and inserting translations
    {
        AttValPair keyPair;
        AttValPair compatiblePair;
        
        std::istringstream iss(line);

        getline(iss, keyPair.attribute, ',');
        getline(iss, keyPair.value, ',');
        getline(iss, compatiblePair.attribute, ',');
        getline(iss, compatiblePair.value, ',');
        
        insertTranslation(keyPair, compatiblePair);
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs( const AttValPair& source) const // TODO: impliment
{
    std::string attvalstring = source.attribute + "," + source.value;
    std::vector<AttValPair> sharedPairs;
    
    // go through the loaded list and find matches
    std::vector<AttValPair>* vectorPtr = m_mappings.search(attvalstring);
    if (vectorPtr == nullptr)
        return sharedPairs;
    return *vectorPtr;
}

void AttributeTranslator::insertTranslation(AttValPair keyPair, AttValPair compatiblePair)
{
    std::string attvalstring = keyPair.attribute + "," + keyPair.value;
    std::vector<AttValPair>* pointerToVector =  m_mappings.search(attvalstring);
    if (pointerToVector != nullptr)
    {
        for (std::vector<AttValPair>::iterator i = pointerToVector->begin(); i != pointerToVector->end(); i++)
            if ((*i) == compatiblePair) // to make sure the compatible pair isn't already there
                return;
        pointerToVector->push_back(compatiblePair);
        return;
    }
    
    // the attval key doesn't map to anything yet
    std::vector<AttValPair> pairList;
    pairList.push_back(compatiblePair);
    m_mappings.insert(attvalstring, pairList);
    
    // OLD CODE
//    // create temp RadixTree node to be compared to or inserted into set
    
//    RadixTree<std::vector<AttValPair>> rt;
//    pairList.push_back(compatiblePair);
//    rt.insert(attvalstring, pairList);
//
//    std::unordered_set<RadixTree<std::vector<AttValPair>>>::iterator foundIterator = m_mappings.find(rt);
//    if (foundIterator != m_mappings.end())
//    {
//        std::vector<AttValPair>* vectorPointer = foundIterator->search(attvalstring);
//        for (std::vector<AttValPair>::iterator vectorIterator = vectorPointer->begin(); vectorIterator != vectorPointer->end(); vectorIterator++)
//        {
//            if (*vectorIterator == compatiblePair)
//                return; // the exact mapping is already there
//        }
//    }
    // none of this fucking works becasue you can't see if two RadixTrees are equal
    
    // attval not already in a RadixTree in set
//    m_mappings.insert(rt);
}
