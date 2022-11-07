#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <string>
#include "provided.h"
#include "PersonProfile.h"

class MemberDatabase
{
public:
    MemberDatabase() {}
    ~MemberDatabase(); // optional
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
private:
    RadixTree<PersonProfile*> m_email_to_profilePtr;
    RadixTree<std::vector<std::string>> m_attval_to_email;
    std::vector<PersonProfile*> m_profilePointersToDelete;
};

#endif /* MemberDatabase_h */
