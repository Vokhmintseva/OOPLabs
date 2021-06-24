#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <optional>

class SearchServer
{
public: 
	struct Document
	{
		int id;
		std::string text;
	};

	struct Doc
	{
		int id;
		unsigned int relevance;
	};

	SearchServer();
	int AddDocument(std::string text);
	int GetDocumentCount() const;
	std::vector<int> FindDocumentsIds(const std::string& query) const;
	std::vector<Document> FindDocuments(const std::string& query) const;
	std::vector<Doc> FindDocumentsWithRelevance(const std::string& query) const;
private:
	std::vector<Document> m_documents;
	//std::optional<Document>const& GetDocumentById(int id);

};

std::vector<std::string> GetQueryStrings(const std::string& query);
