// SearchServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "SearchServer.h"

int main()
{
    SearchServer ss;
    
    std::string inputStr;
    while (getline(std::cin, inputStr))
    {
        if (inputStr == "")
        {
            break;
        }
        ss.AddDocument(inputStr);
    }

    while (getline(std::cin, inputStr))
    {
        std::vector<SearchServer::Document> foundDocs = ss.FindDocuments(inputStr);
        for (auto doc : foundDocs)
        {
            std::cout << "index is " << doc.id << " text is " << doc.text << std::endl;
        }

        std::vector<int> foundDocsIds = ss.FindDocumentsIds(inputStr);
        for (auto idx : foundDocsIds)
        {
            std::cout << "index is " << idx << std::endl;
        }
        
        std::vector<SearchServer::Document> foundDocsWithRelevance = ss.FindDocumentsWithRelevance(inputStr);
        for (auto doc : foundDocsWithRelevance)
        {
            std::cout << "index is " << doc.id << " text is " << doc.text << " relevance is " << doc.relevance << std::endl;
        }

        if (inputStr == "end")
        {
            break;
        }
    }
    return 0;
}
