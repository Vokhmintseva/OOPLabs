#pragma once
#include <stdexcept>
#include <memory>
#include <initializer_list>
#include <algorithm>

template <typename T>
class MyArray
{
public:
	MyArray()
		: m_pItems(new T[DEFAULT_CAPACITY])
	{};

	MyArray(const std::initializer_list<T>& il)
		: m_pItems(new T[DEFAULT_CAPACITY])
	{
		for (const T& i : il)
		{
			PushBack(i);
		}
	};
	
	MyArray(const MyArray<T>& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		T* newArray = nullptr;
		try
		{
			newArray = new T[m_capacity];
			std::uninitialized_copy_n(other.m_pItems, m_capacity, newArray);
			m_pItems = newArray;
		}
		catch (...)
		{
			delete[] newArray;
			throw;
		}
	}
	
	MyArray(MyArray<T>&& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
		, m_pItems(other.m_pItems)
	{
		other.m_pItems = nullptr;
	}

	~MyArray()
	{
		delete[] m_pItems;
		m_pItems = nullptr;
	}

	void Clear()
	{
		MyArray newArray;
		newArray.swap(*this);
		newArray.m_pItems = nullptr;
	}

	template<typename T> class MyArrayIterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		MyArrayIterator()
			: m_ptr(nullptr)
		{}

		MyArrayIterator(T* p)
			: m_ptr(p)
		{}

		bool operator!=(MyArrayIterator const& other) const
		{
			return m_ptr != other.m_ptr;
		}

		bool operator==(MyArrayIterator const& other) const
		{
			return m_ptr == other.m_ptr;
		}

		T& operator*() const
		{
			return *m_ptr;
		}

		T* operator->() const
		{
			return m_ptr;
		}

		MyArrayIterator<T>& operator++()
		{
			++m_ptr;
			return *this;
		}

		MyArrayIterator<T> operator++(int)
		{
			MyArrayIterator temp(*this);
			++* this;
			return temp;
		}
		
		MyArrayIterator<T>& operator--()
		{
			--m_ptr;
			return *this;
		}

		MyArrayIterator<T> operator--(int)
		{
			MyArrayIterator<T> temp(*this);
			--* this;
			return temp;
		}
	private:
		T* m_ptr;
	};

	unsigned GetSize() const
	{
		return m_size;
	}

	void PushBack(T const& item) 
	{
		if (m_size == m_capacity)
		{
			T* newArray = nullptr;
			try
			{
				newArray = new T[m_capacity *= 2];
				std::uninitialized_copy_n(m_pItems, m_size, newArray);
				delete[] m_pItems;
				m_pItems = newArray;
			}
			catch (...)
			{
				delete[] newArray;
				throw;
			}
		}
		m_pItems[m_size++] = item;
	}

	T& operator[](unsigned index)
	{
		if (index >= m_size) 
		{
			throw std::out_of_range("index is out of range");
		}
		return *(m_pItems + index);
	}

	void Resize(unsigned newSize)
	{
		if (newSize == m_size)
		{
			return;
		}
		T* newArray = nullptr;
		try
		{
			newArray = new T[newSize];
			unsigned const minSize = (newSize < m_size) ? newSize : m_size;
			std::uninitialized_copy_n(m_pItems, minSize, newArray);
			for (unsigned i = minSize; i < newSize; ++i)
			{
				newArray[i] = T();
			}
		}
		catch (...)
		{
			delete[] newArray;
			throw;
		}
		delete[] m_pItems;
		m_pItems = newArray;
		m_size = newSize;
		m_capacity = newSize;
	}
	typedef std::reverse_iterator<MyArrayIterator<T>> Reverse_iterator;

	MyArrayIterator<T> begin() const
	{
		return MyArrayIterator<T>(m_pItems);
	}

	MyArrayIterator<T> end() const
	{
		return MyArrayIterator<T>(m_pItems + m_size);
	}

	Reverse_iterator rend() const
	{
		return std::reverse_iterator(begin());
	}

	Reverse_iterator rbegin() const
	{
		return std::reverse_iterator(end());
	}

	MyArray& operator =(MyArray const& other)
	{
		if (std::addressof(other) != this)
		{
			MyArray<T> tmp(other); //временная копия присваиваемого объекта
			tmp.swap(*this);
		}
		return *this;
	}

	MyArray& operator =(MyArray&& other)
	{
		if (std::addressof(other) != this)
		{
			delete[] m_pItems;
			other.swap(*this);
			other.m_pItems = nullptr;
		}
		return *this;
	}

	static const unsigned int DEFAULT_CAPACITY = 5;

private:
	void swap(MyArray& other) noexcept
	{
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_size, other.m_size);
		std::swap(m_pItems, other.m_pItems);
	}
	T* m_pItems;
	unsigned m_size = 0;
	unsigned m_capacity = DEFAULT_CAPACITY;
};





















/*template<typename T>
	T* UninitializedMoveNIfNoexcept(T* from, size_t n, T* to)
	{
		if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>)
		{
			return std::uninitialized_move_n(from, n, to).second;
		}
		else
		{
			return std::uninitialized_copy_n(from, n, to);
		}
	}

void Clear()
{
	MyArray * newArray = new T[DEFAULT_CAPACITY];
	delete[] m_pItems;
	m_pItems = newArray;
	unsigned m_size = 0;
	unsigned m_capacity = DEFAULT_CAPACITY;
}

MyArray& operator =(MyArray&& other)
{
	if (std::addressof(other) != this)
	{
		delete[] m_pItems;
		other.swap(*this);
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_pItems = other.m_pItems;
		other.m_pItems = nullptr;
	}
	return *this;
}
	template <typename T1>
	MyArray<T>& operator =(MyArray<T1> const& other)
	{
		MyArray<T> newArray;
		newArray.m_capacity = other.GetSize();
		newArray.m_size = other.GetSize();
		newArray.m_pItems = new T[m_capacity];
		for (unsigned i = 0; i < m_size; ++i)
		{
			newArray[i] = static_cast<T const&>(other[i]);
		}

		//std::for_each(other, m_size, [&newArray](T1 const& item) {newArray.pushBack(static_cast<T const&>(item));});
		newArray.swap(*this);
		return *this;
	}

*/