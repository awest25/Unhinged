#ifndef PersonProfile_h
#define PersonProfile_h

#include <string>
#include <vector>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email)
    : m_email(email), m_name(name), m_numattvals(0)
    {}
//    ~PersonProfile() // optional
    std::string GetName() const {return m_name;}
    std::string GetEmail() const {return m_email;}
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const {return m_numattvals;}
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    std::string m_email;
    std::string m_name;
    RadixTree<std::unordered_set<std::string>> m_attvaltree; // ordered binary tree
    int m_numattvals;
    
    std::vector<AttValPair> m_attValVector;
};

#endif /* PersonProfile_h */
