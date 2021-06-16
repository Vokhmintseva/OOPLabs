#pragma once
#include <string>
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

		operator StringListIterator<const Item>() const
		{
			return StringListIterator<const Item>(m_ptr);
		}

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
			if (m_ptr->m_pNext == nullptr)
			{
				throw std::out_of_range("can't increment iterator after past end");
			}
			m_ptr = m_ptr->m_pNext;
			return *this;
		}

		StringListIterator<ValueType> operator++(int)
		{
			if (m_ptr->m_pNext == nullptr)
			{
				throw std::out_of_range("can't increment iterator after past end");
			}
			StringListIterator<ValueType> temp = *this;
			++* this;
			return temp;
		}

		const StringListIterator<ValueType> operator--(int)
		{
			StringListIterator<ValueType> temp = *this;
			if (m_ptr->m_pPrev == nullptr)
			{
				throw std::out_of_range("can't decrement iterator before begin");
			}
			m_ptr = m_ptr->m_pPrev;
			return temp;
		}

		auto& operator--()
		{
			if (m_ptr->m_pPrev == nullptr)
			{
				throw std::out_of_range("can't decrement iterator before begin");
			}
			m_ptr = m_ptr->m_pPrev;
			return *this;
		}
	private:
		Item* m_ptr;
	};

	typedef StringListIterator<Item> Iterator;
	typedef StringListIterator<const Item> Const_iterator;
	typedef std::reverse_iterator<Const_iterator> Const_reverse_iterator;
	typedef std::reverse_iterator<Iterator> Reverse_iterator;

	Iterator begin() const;
	Iterator end() const;
	Const_iterator cbegin() const;
	Const_iterator cend() const;
	Reverse_iterator rbegin() const;
	Reverse_iterator rend() const;
	Const_reverse_iterator crbegin() const;
	Const_reverse_iterator crend() const;

	StringList();
	StringList(const StringList& otherStrList);
	StringList(StringList&& otherStrList);
	~StringList();

	void PrependItem(std::string const& value);
	void AppendItem(std::string const& value);

	template <typename T> void InsertItem(const StringListIterator<T>& it, std::string const& value)
	{
		Item* previous = it != m_pFirst ? it->m_pPrev : nullptr;
		Item* newItem = new Item(value, previous, it.m_ptr);
		if (previous)
		{
			it->m_pPrev->m_pNext = newItem;
		}
		it.m_ptr->m_pPrev = newItem;
		
		if (it == m_pFirst)
		{
			m_pFirst = newItem;
		}
		if (m_count == 0)
		{
			m_pPastTheLast->m_pNext = nullptr;
		}
		++m_count;
	}

	template <typename T> void DeleteItem(const StringListIterator<T>& it)
	{
		if (m_count == 0)
		{
			throw std::invalid_argument("the list is empty");
		}
		if (it == m_pPastTheLast)
		{
			throw std::invalid_argument("out of range iterator");
		}
		if (it->m_pPrev)
		{
			it->m_pPrev->m_pNext = it->m_pNext;
		}
		it.m_ptr->m_pNext->m_pPrev = it->m_pPrev;
		if (it == m_pFirst)
		{
			m_pFirst = it.m_ptr->m_pNext;
		}
		delete it.m_ptr;
		--m_count;
	}

	bool IsEmpty() const;
	unsigned int GetCount() const;
	void Clear();
private:
	void InitLinkItem();
	Item* m_pFirst;
	Item* m_pPastTheLast;
	unsigned int m_count = 0;
};
