#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "MemberDatabase.h"

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream fileContents(filename); // standard line reading
//    std::cerr << fileContents.rdbuf();
    if (!fileContents)
        return false;
    std::string line;
    while (std::getline(fileContents, line))
    {
        std::string name = line;
        
        std::string email;
        getline(fileContents, email);
//        m_emails.push_back(email);
        
        int numPairs;
        fileContents >> numPairs;
        
        std::string trash;
        getline(fileContents, trash);
        
        PersonProfile* tempProfilePtr = new PersonProfile(name, email); // create the profile object we're going to insert
        m_profilePointersToDelete.push_back(tempProfilePtr);
//        std::cout << name << email << numPairs << std::endl;
        
        while (std::getline(fileContents, line) && line != "") {
            // add attval to Person Profile
            AttValPair pair;
            
            std::istringstream iss(line);

            getline(iss, pair.attribute, ',');
            getline(iss, pair.value, ',');
            tempProfilePtr->AddAttValPair(pair);
            
            // add to attval to email RadixTree of vectors
            std::string attvalstring = pair.attribute + "," + pair.value;
            std::vector<std::string>* vectorPtr = m_attval_to_email.search(attvalstring);
            if (vectorPtr != nullptr)
                vectorPtr->push_back(email);
            else
            {
                std::vector<std::string> vectorToInsert;
                vectorToInsert.push_back(email);
                m_attval_to_email.insert(attvalstring, vectorToInsert);
            }
        }
        m_email_to_profilePtr.insert(email, tempProfilePtr);
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::string attvalstring = input.attribute + "," + input.value;
    std::vector<std::string>* vectorPtr = m_attval_to_email.search(attvalstring);
    
    std::vector<std::string> emptyVector;
    if (vectorPtr == nullptr)
        return emptyVector;
    
    std::vector<std::string> matchingMembers(vectorPtr->begin(), vectorPtr->end());
    return matchingMembers;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    PersonProfile** returnPtrPtr = m_email_to_profilePtr.search(email);
    if (returnPtrPtr == nullptr)
        return nullptr;
    return *returnPtrPtr;
}

MemberDatabase::~MemberDatabase()
{
    size_t amountOfEmails = m_profilePointersToDelete.size();
    for (size_t i = 0; i < amountOfEmails; i++)
        delete m_profilePointersToDelete[i];
}
