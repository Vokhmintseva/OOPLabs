#pragma once
#include <vector>
#include <string>
#include <iostream>

class SearchServer
{
public: 
	struct Document
	{
		int id;
		std::string text;
		unsigned int relevance;
	};

	SearchServer();
	int AddDocument(std::string text);
	int GetDocumentCount() const;
	std::vector<int> FindDocumentsIds(const std::string& query) const;
	std::vector<Document> FindDocuments(const std::string& query) const;
	std::vector<Document> FindDocumentsIt(const std::string& query) const;
	std::vector<Document> FindDocumentsWithRelevance(const std::string& query) const;
private:
	std::vector<Document> m_documents;
};

static std::vector<std::string> GetQueryStrings(const std::string& query);
