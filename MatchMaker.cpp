#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "MatchMaker.h"

void printVectior (std::vector<AttValPair> v);

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    std::vector<AttValPair> profilePairs;
    const PersonProfile* profilePtr = m_db->GetMemberByEmail(email);
    for (int i = 0; i < profilePtr->GetNumAttValPairs(); i++)
    {
        AttValPair toInsert;
        profilePtr->GetAttVal(i, toInsert);
        profilePairs.push_back(toInsert);
    }
    // The previous code gives us the person of interest pairs

    std::vector<AttValPair> compatiblePairs;
    for (int i = 0; i < profilePairs.size(); i++)
    {
        std::vector<AttValPair> foundCompatibles = m_at->FindCompatibleAttValPairs(profilePairs[i]);
//#warning probably incorrect
        compatiblePairs.insert(compatiblePairs.end(), foundCompatibles.begin(), foundCompatibles.end()); // append vectors
    }
    for (std::vector<AttValPair>::iterator i = compatiblePairs.begin(); i != compatiblePairs.end(); i++) // removes duplicates
        for (std::vector<AttValPair>::iterator j = compatiblePairs.begin(); j != compatiblePairs.end(); j++)
            if (*i == *j && &(*i) != &(*j))
            {
                compatiblePairs.erase(j);
                j--;
            }
    
    // RIGHT NOW we have a vector of all compatible pairs to look for
    
    std::unordered_map<std::string, int> matchingEmailMap;
    for (int i = 0; i < compatiblePairs.size(); i++) // map each email to how many matches it gets
    {
        std::vector<std::string> tempMatchingEmails = m_db->FindMatchingMembers(compatiblePairs[i]);
        std::set<std::string> setOfTempMatchingEmails(tempMatchingEmails.begin(), tempMatchingEmails.end());
        for (std::set<std::string>::iterator j = setOfTempMatchingEmails.begin(); j != setOfTempMatchingEmails.end(); j++)
        {
            std::string currentEmail = *j;
            std::unordered_map<std::string, int>::iterator it = matchingEmailMap.find(currentEmail);
            if (it == matchingEmailMap.end())
                matchingEmailMap[currentEmail] = 1;
            else
                matchingEmailMap[currentEmail] += 1;
        }
    }
    
    // sort into an ordered map of ints to sets of strings
    std::map<int, std::set<std::string>> orderedMap;
    for (std::unordered_map<std::string, int>::iterator i = matchingEmailMap.begin(); i != matchingEmailMap.end(); i++)
        {
            std::map<int, std::set<std::string>>::iterator emailSetIterator = orderedMap.find((*i).second); // number
            if (emailSetIterator != orderedMap.end())
                emailSetIterator->second.insert((*i).first);
            else
            {
                std::set<std::string> tempSet;
                tempSet.insert(i->first);
                orderedMap[i->second] = tempSet;
            }
        }

    // iterate from end to beginning by number of matches
    std::vector<EmailCount> rankedMatches;
    std::map<int, std::set<std::string>>::iterator it = orderedMap.end();
    for (it--; it != orderedMap.begin(); it--)
    {
        if ((*it).first < threshold) continue;
        for (std::set<std::string>::iterator i = it->second.begin(); i != it->second.end(); i++)
        {
            if (*i != email)
                rankedMatches.push_back(EmailCount(*i , it->first));
        }
    }
    
    return rankedMatches;
}
