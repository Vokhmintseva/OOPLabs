#pragma once
#include <string>
#include <memory>
#include <iterator>

template<typename ValueType>
class StringListIterator;

class StringList
{
public:	
	struct Item
	{
		Item(std::string const& value, Item* pPrev, Item* pNext)
			: m_value(value)
			, m_pPrev(pPrev)
			, m_pNext(pNext)
		{};

    	std::string m_value;
		Item* m_pPrev;
		Item* m_pNext;
	};

	template<typename ValueType>
	class StringListIterator 
	{
	public:
		friend class StringList;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = ValueType;
		using pointer = ValueType*;
		using reference = ValueType&;
		
		StringListIterator(Item* ptr = nullptr) 
			: m_ptr(ptr)
		{}
		
		StringListIterator(const StringListIterator& iterator)
			: m_ptr(iterator.m_ptr)
		{}
		
		~StringListIterator() {}
		
		bool operator!=(StringListIterator const& other) const
		{
			return m_ptr != other.m_ptr;
		}

		bool operator==(StringListIterator const& other) const
		{
			return m_ptr == other.m_ptr;
		}
		
		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		StringListIterator<ValueType>& operator++()
		{
			m_ptr = m_ptr->m_pNext;
			return *this;
		}

		StringListIterator<ValueType> operator++(int)
		{
			StringListIterator<ValueType> temp = *this;
			++*this;
			return temp;
		}

		const StringListIterator<ValueType> operator--(int)
		{
			StringListIterator<ValueType> temp = *this;
			m_ptr = m_ptr->m_pPrev;
			return temp;
		}

		auto& operator--()
		{
			m_ptr = m_ptr->m_pPrev;
			return *this;
		}

		const std::string GetValue()
		{
			return m_ptr->m_value;
		}
		
	private:
		Item* m_ptr;
	};

	typedef StringListIterator<Item> Iterator;
	typedef StringListIterator<const Item> Const_iterator;
	typedef std::reverse_iterator<Const_iterator> Const_reverse_iterator;
	typedef std::reverse_iterator<Iterator> Reverse_iterator;

	Iterator begin() const; //возвращает объект с указателем на начало списка
	Iterator end() const; //возвращает объект с указателем на конец списка
	Const_iterator cbegin() const; 
	Const_iterator cend() const;
	Reverse_iterator rbegin() const;
	Reverse_iterator rend() const;
	Const_reverse_iterator crbegin() const;
	Const_reverse_iterator crend() const;
	
	StringList();
	~StringList();

	void PrependItem(std::string const& value);
	void AppendItem(std::string const& value);
	template <typename T> void InsertItem(const StringListIterator<T>& it, std::string const& value)
	{
		if (it.m_ptr == m_linkItem)
		{
			AppendItem(value);
		}
		else
		{
			Item* newItem = new Item(value, it.m_ptr->m_pPrev, it.m_ptr->m_pNext);
			it.m_ptr->m_pPrev->m_pNext = newItem;
			it.m_ptr->m_pNext->m_pPrev = newItem;
			++m_count;
		}
	}
	template <typename T> bool DeleteItem(const StringListIterator<T>& it)
	{
		return true;
	}
	bool IsEmpty() const;
	unsigned int GetCount() const;
	void Clear();
	std::string GeatHeadValue() const;
	std::string GeatTailValue() const;

private:
	void InitLinkItem();
	Item * m_pHead = nullptr;
	Item * m_pTail = nullptr;
	Item* m_linkItem;
	unsigned int m_count = 0;
};
