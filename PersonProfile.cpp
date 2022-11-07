#include "PersonProfile.h"

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    std::unordered_set<std::string>* setPointer = m_attvaltree.search(attval.attribute);
    if (setPointer == nullptr) // the attribute (ex. "hobby") has not been added yet
    {
        std::unordered_set<std::string> newSet; // create a new set, mapping the attribute to that set of 1 value
        newSet.insert(attval.value);
        m_attvaltree.insert(attval.attribute, newSet);
        m_attValVector.push_back(attval);
        m_numattvals++;
        return;
    }
    
    // the attribute already has values
    if (setPointer->find(attval.value) != setPointer->end())
        return;
    setPointer->insert(attval.value);
    m_attValVector.push_back(attval);
    m_numattvals++;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs()) return false;
    
    attval = m_attValVector[attribute_num];
    return true;
}
