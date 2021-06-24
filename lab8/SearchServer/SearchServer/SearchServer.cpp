#include "SearchServer.h"
#include <sstream>
#include <algorithm>
#include <set>

SearchServer::SearchServer() {};

int SearchServer::AddDocument(std::string text)
{
	int idx = m_documents.size();
	Document newDocument = { idx, text };
	m_documents.emplace_back(std::move(newDocument));
	return idx;
}

int SearchServer::GetDocumentCount() const
{
	return m_documents.size();
}

std::vector<int> SearchServer::FindDocumentsIds(const std::string& query) const
{
	std::vector<int> results;
	//std::stringstream queryStrm(query);
	std::vector<std::string> queryStrings = GetQueryStrings(query);
	/*std::string str;
	while (queryStrm >> str)
	{
		queryStrings.push_back(str);
	}*/

	for (auto doc : m_documents)
	{
		bool found = false;
		std::stringstream textStrm(doc.text);
		std::string word;
		while (textStrm >> word)
		{
			for (auto queryStr : queryStrings)
			{
				if (word == queryStr)
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				results.push_back(doc.id);
				break;
			}
		}
	}
	return results;
}

std::vector<SearchServer::Document> SearchServer::FindDocumentsIt(const std::string& query) const
{
	std::vector<std::string> queryStrings = GetQueryStrings(query);

	std::vector<SearchServer::Document> results;
	for (auto doc : m_documents)
	{
		std::stringstream text(doc.text);
		std::istream_iterator<std::string> f;
		auto it = std::find_if(std::istream_iterator<std::string>(text),
			f,
			[queryStrings](const std::string& str)
			{
				for (auto queryStr : queryStrings)
				{
					if (queryStr == str)
					{
						return true;
					}
				}
			}
		);
		if (it != f)
		{
			Document foundDocument = { doc.id, doc.text };
			results.emplace_back(std::move(foundDocument));
		}
	}
	return results;
}

std::vector<SearchServer::Document> SearchServer::FindDocuments(const std::string& query) const
{
	std::vector<std::string> queryStrings = GetQueryStrings(query);

	std::vector<SearchServer::Document> results;
	for (auto doc : m_documents)
	{
		bool found = false;
		std::stringstream textStrm(doc.text);
		std::string word;
		while (textStrm >> word)
		{
			for (auto queryStr : queryStrings)
			{
				if (word == queryStr)
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				Document foundDocument = { doc.id, doc.text };
				results.push_back(std::move(foundDocument));
				break;
			}
		}
	}
	return results;
}

std::vector<SearchServer::Document> SearchServer::FindDocumentsWithRelevance(const std::string& query) const
{
	std::vector<std::string> queryStrings = GetQueryStrings(query);

	std::vector<SearchServer::Document> results;
	for (auto doc : m_documents)
	{
		std::set<std::string> foundWords;
		bool found = false;
		std::stringstream textStrm(doc.text);
		std::string word;
		while (textStrm >> word)
		{
			for (auto queryStr : queryStrings)
			{
				if (word == queryStr)
				{
					found = true;
					foundWords.insert(word);
				}
			}
		}
		if (found)
		{
			Document foundDocument = { doc.id, doc.text, foundWords.size() };
			results.emplace_back(std::move(foundDocument));
		}
	}
	std::sort(std::begin(results), std::end(results), [](Document const& doc1, Document const& doc2) {
		return doc1.relevance > doc2.relevance; });
	return results;
}


std::vector<std::string> GetQueryStrings(const std::string& query)
{
	std::vector<SearchServer::Document> results;
	std::stringstream queryStrm(query);
	std::vector<std::string> queryStrings;
	std::string str;
	while (queryStrm >> str)
	{
		queryStrings.push_back(str);
	}
	return queryStrings;
}