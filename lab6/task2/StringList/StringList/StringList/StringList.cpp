#include "StringList.h"
#include <iostream>
#include <memory>

StringList::StringList()
    :m_count(0)
{
    m_linkItem = new Item("", nullptr, nullptr);
    InitLinkItem();
};

StringList::StringList(const StringList& otherStrList)
    : StringList()
{
    //m_linkItem = new Item("", nullptr, nullptr);
    //InitLinkItem();
    try
    {
        for (auto& item : otherStrList)
        {
            AppendItem(item.m_value);
        }

        /*for (StringList::Const_iterator iter = otherStrList.cbegin(); iter != otherStrList.cend(); ++iter)
        {
            AppendItem(iter->m_value);
        }*/
    }
    catch (std::exception const&)
    {
        Clear();
        delete m_linkItem;
        throw;
    }
}

StringList::StringList(StringList&& otherStrList)
    : m_count(0)
    , m_pHead(nullptr)
    , m_pTail(nullptr)
    , m_linkItem(nullptr)
{
    std::swap(m_count, otherStrList.m_count);
    std::swap(m_pHead, otherStrList.m_pHead);
    std::swap(m_pTail, otherStrList.m_pTail);
    std::swap(m_linkItem, otherStrList.m_linkItem);
}

void StringList::InitLinkItem()
{
    m_linkItem->m_pNext = m_linkItem;
    m_linkItem->m_pPrev = m_linkItem;
    m_pHead = m_linkItem;
    m_pTail = m_linkItem;
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
        Item* tempNode = m_pHead;
        m_pHead = m_pHead->m_pNext;
        delete tempNode;
        --m_count;
    }
    InitLinkItem();
}

StringList::~StringList()
{
    Clear();
    delete m_linkItem;
}

std::string StringList::GeatHeadValue() const
{
    return m_pHead->m_value;
}

std::string StringList::GeatTailValue() const
{
    return m_pTail->m_value;
}

StringList::Iterator StringList::begin() const
{
    return Iterator(m_pHead);
}

StringList::Iterator StringList::end() const
{
    return Iterator(m_pTail->m_pNext);
}

StringList::Const_iterator StringList::cbegin() const
{
    return Const_iterator(m_pHead);
}

StringList::Const_iterator StringList::cend() const
{
    return Const_iterator(m_pTail->m_pNext);
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
