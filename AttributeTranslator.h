#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <string>
#include <vector>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator
{
public:
    AttributeTranslator() {}
//    ~AttributeTranslator() // optional
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs( const AttValPair& source) const;
private:
    void insertTranslation(AttValPair keyPair, AttValPair compatiblePair);
    RadixTree<std::vector<AttValPair>> m_mappings;
};

#endif /* AttributeTranslator_h */
