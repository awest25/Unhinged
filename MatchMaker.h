#ifndef MatchMaker_h
#define MatchMaker_h

#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
    : m_db(&mdb), m_at(&at)
    {}
//    ~MemberDatabase() // optional
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
    
private:
    const MemberDatabase* m_db;
    const AttributeTranslator* m_at;
};

#endif /* MatchMaker_h */
