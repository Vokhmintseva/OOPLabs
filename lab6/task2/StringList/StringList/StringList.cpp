#include "StringList.h"
#include <memory>

StringList::StringList()
    :m_count(0)
{
    m_pPastTheLast = new Item("", nullptr, nullptr);
    InitLinkItem();
};

StringList::StringList(const StringList& otherStrList)
    : StringList()
{
    try
    {
        for (auto& item : otherStrList)
        {
            AppendItem(item.m_value);
        }
    }
    catch (std::exception const&)
    {
        Clear();
        delete m_pPastTheLast;
        throw;
    }
}

StringList::StringList(StringList&& otherStrList)
    : m_count(0)
    , m_pFirst(nullptr)
    , m_pPastTheLast(nullptr)
{
    std::swap(m_count, otherStrList.m_count);
    std::swap(m_pFirst, otherStrList.m_pFirst);
    std::swap(m_pPastTheLast, otherStrList.m_pPastTheLast);
}

void StringList::InitLinkItem()
{
    m_pPastTheLast->m_pNext = m_pPastTheLast;
    m_pPastTheLast->m_pPrev = m_pPastTheLast;
    m_pFirst = m_pPastTheLast;
}

void StringList::PrependItem(std::string const& value)
{
    InsertItem(begin(), value);
}

void StringList::AppendItem(std::string const& value)
{
    InsertItem(end(), value);
}

bool StringList::IsEmpty() const
{
    return m_count == 0;
}

unsigned int StringList::GetCount() const
{
    return m_count;
}

void StringList::Clear()
{
    while (m_count)
    {
        Item* tempNode = m_pFirst;
        m_pFirst = m_pFirst->m_pNext;
        delete tempNode;
        --m_count;
    }
    InitLinkItem();
}

StringList::~StringList()
{
    while (m_count)
    {
        Item* tempNode = m_pFirst;
        m_pFirst = m_pFirst->m_pNext;
        delete tempNode;
        --m_count;
    }
    delete m_pPastTheLast;
}

StringList::Iterator StringList::begin() const
{
    return Iterator(m_pFirst);
}

StringList::Iterator StringList::end() const
{
    return Iterator(m_pPastTheLast);
}

StringList::Const_iterator StringList::cbegin() const
{
    return Const_iterator(m_pFirst);
}

StringList::Const_iterator StringList::cend() const
{
    return Const_iterator(m_pPastTheLast);
}

StringList::Reverse_iterator StringList::rend() const
{
    return Reverse_iterator(begin());
}

StringList::Reverse_iterator StringList::rbegin() const
{
    return Reverse_iterator(end());
}

StringList::Const_reverse_iterator StringList::crbegin() const
{
    return Const_reverse_iterator(cend());
}

StringList::Const_reverse_iterator StringList::crend() const
{
    return Const_reverse_iterator(cbegin());
}
