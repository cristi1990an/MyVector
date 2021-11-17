#include <iostream>
#include <array>
#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <iterator>

template<typename T, typename Allocator_t = std::allocator<T>>
class MyVector : private Allocator_t
{
private:
	using traits = std::allocator_traits<Allocator_t>;
public:

	using allocator_type = Allocator_t;
	using value_type = T;
	using pointer = typename std::allocator_traits<allocator_type>::pointer;
	using reference = value_type&;
	using size_type = std::size_t;

	class iterator
	{
	public:

		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		constexpr iterator() noexcept : _ptr{ nullptr } {}
		constexpr explicit iterator(const pointer ptr) noexcept : _ptr{ ptr } {}
		constexpr iterator(const iterator&) noexcept = default;
		constexpr iterator(iterator&&) noexcept = default;
		constexpr iterator& operator=(const iterator&) noexcept = default;
		constexpr iterator& operator=(iterator&&) noexcept = default;

		constexpr reference operator*() const noexcept
		{
			return *_ptr;
		}

		constexpr pointer operator->() const noexcept
		{
			return _ptr;
		}

		constexpr iterator operator++() noexcept
		{
			++_ptr;
			return *this;
		}

		constexpr iterator operator++(int) noexcept
		{
			auto initial = *this;
			++_ptr;
			return initial;
		}

		constexpr iterator operator--() noexcept
		{
			--_ptr;
			return *this;
		}

		constexpr iterator operator--(int) noexcept
		{
			auto initial = *this;
			--_ptr;
			return initial;
		}

		constexpr iterator operator+(size_t offset) const noexcept
		{
			return iterator(_ptr + offset);
		}

		constexpr iterator operator-(size_t offset) const noexcept
		{
			return iterator(_ptr - offset);
		}

		constexpr void operator+=(size_t offset) const noexcept
		{
			_ptr += offset;
		}

		constexpr void operator-=(size_t offset) const noexcept
		{
			_ptr -= offset;
		}

		friend constexpr difference_type operator-(const iterator lhs, const iterator rhs) noexcept
		{
			return (lhs._ptr - rhs._ptr);
		}

		friend constexpr bool operator==(const iterator lhs, const iterator rhs) noexcept
		{
			return lhs._ptr == rhs._ptr;
		}

		friend constexpr bool operator!=(const iterator lhs, const iterator rhs) noexcept
		{
			return lhs._ptr != rhs._ptr;
		}

		friend constexpr bool operator<(const iterator lhs, const iterator rhs) noexcept
		{
			return lhs._ptr < rhs._ptr;
		}

		friend constexpr bool operator<=(const iterator lhs, const iterator rhs) noexcept
		{
			return lhs._ptr <= rhs._ptr;
		}

		friend constexpr bool operator>(const iterator lhs, const iterator rhs) noexcept
		{
			return lhs._ptr > rhs._ptr;
		}

		friend constexpr bool operator>=(const iterator lhs, const iterator rhs) noexcept
		{
			return lhs._ptr >= rhs._ptr;
		}

	private:
		pointer _ptr;
	};

	class const_iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = const T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		constexpr const_iterator() noexcept : _ptr{ nullptr } {}
		constexpr explicit const_iterator(const pointer ptr) noexcept : _ptr{ ptr } {}
		constexpr const_iterator(const const_iterator&) noexcept = default;
		constexpr const_iterator(const_iterator&&) noexcept = default;
		constexpr const_iterator& operator=(const const_iterator&) noexcept = default;
		constexpr const_iterator& operator=(const_iterator&&) noexcept = default;

		constexpr const_iterator(const MyVector::iterator other) noexcept : _ptr{ other._ptr } {}
		constexpr const_iterator& operator=(const iterator& other) noexcept
		{
			_ptr = other._ptr;
			return *this;
		}

		constexpr reference operator*() const noexcept
		{
			return *_ptr;
		}

		constexpr pointer operator->() const noexcept
		{
			return _ptr;
		}

		constexpr const_iterator operator++() noexcept
		{
			++_ptr;
			return *this;
		}

		constexpr const_iterator operator++(int) noexcept
		{
			auto initial = *this;
			++_ptr;
			return initial;
		}

		constexpr const_iterator operator--() noexcept
		{
			--_ptr;
			return *this;
		}

		constexpr const_iterator operator--(int) noexcept
		{
			auto initial = *this;
			--_ptr;
			return initial;
		}

		constexpr const_iterator operator+(int offset) noexcept
		{
			return const_iterator(_ptr + offset);
		}

		constexpr const_iterator operator-(int offset) noexcept
		{
			return const_iterator(_ptr - offset);
		}

		constexpr void operator+=(int offset) noexcept
		{
			_ptr += offset;
		}

		constexpr void operator-=(int offset) noexcept
		{
			_ptr -= offset;
		}

		friend constexpr difference_type operator-(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr - rhs._ptr;
		}

		friend constexpr bool operator==(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr == rhs._ptr;
		}

		friend constexpr bool operator!=(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr != rhs._ptr;
		}

		friend constexpr bool operator<(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr < rhs._ptr;
		}

		friend constexpr bool operator<=(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr <= rhs._ptr;
		}

		friend constexpr bool operator>(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr > rhs._ptr;
		}

		friend constexpr bool operator>=(const const_iterator lhs, const const_iterator rhs) noexcept
		{
			return lhs._ptr >= rhs._ptr;
		}

	private:
		pointer _ptr;
	};

	iterator begin() noexcept
	{
		return iterator(_data);
	}

	const_iterator begin() const noexcept
	{
		return const_iterator(_data);
	}

	const_iterator cbegin() const noexcept
	{
		return const_iterator(_data);
	}

	iterator end() noexcept
	{
		return iterator(_data + _size);
	}

	const_iterator end() const noexcept
	{
		return const_iterator(_data + _size);
	}

	const_iterator cend() const noexcept
	{
		return const_iterator(_data + _size);
	}

	MyVector(const Allocator_t& allocator = Allocator_t{}) noexcept
		: Allocator_t { allocator }
		, _size{ 0 }
		, _capacity{ 0 }
		, _data{ nullptr }
	{

	}

	MyVector(size_type size, const Allocator_t& allocator = Allocator_t{})
		: Allocator_t{ allocator }
	{
		_data = traits::allocate(get_allocator(), size);
		std::uninitialized_value_construct_n(_data, size);
		_size = size;
		_capacity = size;
	}

	MyVector(size_t size, const T& value, const Allocator_t& allocator = Allocator_t{})
		: Allocator_t{ allocator }
	{
		_data = traits::allocate(get_allocator(), size);

		std::uninitialized_fill_n(_data, size, value);

		_size = size;
		_capacity = size;
	}

	MyVector(const MyVector& other, const Allocator_t& allocator = Allocator_t{})
		: Allocator_t{ allocator }
	{
		_data = traits::allocate(get_allocator(), other._size);
		std::uninitialized_copy_n(other._data, other._size, _data);
		_size = other._size;
		_capacity = _size;
	}

	MyVector(MyVector&& other, const Allocator_t& allocator = Allocator_t{}) noexcept
		: Allocator_t{ allocator }
	{
		_data = std::exchange(other._data, nullptr);
		_size = std::exchange(other._size, 0);
		_capacity = std::exchange(other._capacity, 0);
	}

	MyVector(std::initializer_list<T> ilist, const Allocator_t& allocator = Allocator_t{})
		: Allocator_t{ allocator }
	{
		const size_type new_size = ilist.size();

		_data = traits::allocate(get_allocator(), new_size);
		std::uninitialized_copy_n(ilist.begin(), new_size, _data);

		_size = new_size;
		_capacity = new_size;
	}

	template<typename InputIt>
	MyVector(InputIt first, InputIt last, const Allocator_t& allocator = Allocator_t{})
		: Allocator_t{ allocator }
	{
		const size_type count = std::distance(first, last);

		_data = traits::allocate(get_allocator(), count);
		std::uninitialized_copy_n(first, count, _data);

		_size = count;
		_capacity = count;
	}

	MyVector& operator= (const MyVector& other)
	{
		if (this == &other)
			return *this;

		destroy_and_deallocate();

		if (!other._capacity)
		{
			_data = traits::allocate(get_allocator(), other._size);
			std::uninitialized_copy_n(other._data, other._size, _data);
		}

		_size = other._size;
		_capacity = _size;

		return *this;
	}

	MyVector& operator= (MyVector&& other) noexcept
	{
		if (this == &other)
			return *this;

		destroy_and_deallocate();

		_data = std::exchange(other._data, nullptr);
		_size = std::exchange(other._size, 0);
		_capacity = std::exchange(other._capacity, 0);

		return *this;
	}

	void assign(size_type count, const T& value)
	{
		std::destroy_n(_data, _size);

		if (_capacity < count)
		{
			if (_capacity)
				traits::deallocate(get_allocator(), _data, _capacity);

			_data = traits::allocate(get_allocator(), count);
			_capacity = count;
		}

		std::uninitialized_fill_n(_data, count, value);

		_size = count;
	}

	void assign(std::initializer_list<T> ilist)
	{
		const size_type count = ilist.size();

		std::destroy_n(_data, _size);

		if (_capacity < count)
		{
			if (_capacity)
				traits::deallocate(get_allocator(), _data, _capacity);

			_data = traits::allocate(get_allocator(), count);
			_capacity = count;
		}

		std::uninitialized_copy_n(ilist.begin(), count, _data);

		_size = count;
	}

	template <typename InputIt>
	void assign(InputIt first, InputIt last)
	{
		const size_type count = std::distance(first, last);

		std::destroy_n(_data, _size);

		if (_capacity < count)
		{
			if (_capacity)
				traits::deallocate(get_allocator(), _data, _capacity);

			_data = traits::allocate(get_allocator(), count);
			_capacity = count;
		}

		std::uninitialized_copy_n(first, count, _data);

		_size = count;
	}

	T& operator[](size_type index) noexcept
	{
		return _data[index];
	}

	const T& operator[](size_type index) const noexcept
	{
		return _data[index];
	}

	T& at(size_type index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return (*this)[index];
	}

	const T& at(size_type index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return (*this)[index];
	}

	bool empty() const noexcept
	{
		return !_size;
	}

	size_type size() const noexcept
	{
		return _size;
	}

	size_type capacity() const noexcept
	{
		return _capacity;
	}

	void reserve(size_type new_capacity)
	{
		if (_capacity < new_capacity)
		{
			T* new_buffer = traits::allocate(get_allocator(), new_capacity);

			if (_capacity)
			{
				std::uninitialized_copy_n(_data, _size, new_buffer);
				std::destroy_n(_data, _size);
				traits::deallocate(get_allocator(), _data, _capacity);
			}

			_data = new_buffer;
			_capacity = new_capacity;
		}
	}

	void push_back(const T& value)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new (_data + _size) T(value);
		_size++;
	}

	void push_back(T&& value)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new (_data + _size) T(std::move(value));
		_size++;
	}

	template<typename ... Args>
	void emplace_back(Args&& ... args)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new (_data + _size) T(std::forward<Args>(args)...);
		_size++;
	}

	void pop_back() noexcept
	{
		if (_size)
		{
			_data[_size - 1].~T();
			--_size;
		}
	}

	iterator insert(iterator pos, const T& value)
	{
		const size_type index = std::distance(begin(), pos);

		if (pos >= end())
		{
			throw std::out_of_range("Position is out of range!");
		}

		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new(_data + _size) T(std::move(_data + _size - 1));

		std::move_backward(_data + index, _data + _size - 1, _data + _size);

		_data[index] = value;

		_size++;

		return begin() + index;
	}

	iterator insert(const_iterator pos, const T& value)
	{
		const size_type index = std::distance(cbegin(), pos);

		if (pos >= cend())
		{
			throw std::out_of_range("Position is out of range!");
		}

		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new(_data + _size) T(std::move(_data[_size - 1]));

		std::move_backward(_data + index, _data + _size - 1, _data + _size);

		_data[index] = value;

		_size++;

		return begin() + index;
	}

	iterator erase(iterator pos) noexcept
	{
		const size_type index = std::distance(begin(), pos);

		if (index < _size)
		{
			std::move(_data + index + 1, _data + _size, _data + index);
			_data[_size - 1].~T();
			_size--;
		}

		return begin() + index;
	}

	const_iterator erase(const_iterator pos) noexcept
	{
		const size_type index = std::distance(cbegin(), pos);

		if (index < _size)
		{
			std::move(_data + index + 1, _data + _size, _data + index);
			_data[_size - 1].~T();
			_size--;
		}

		return begin() + index;
	}

	pointer data() const noexcept
	{
		return _data;
	}

	void clear()
	{
		destroy_and_deallocate();
		_size = 0;
		_capacity = 0;
	}

	void shrink_to_fit()
	{
		if (_capacity > _size)
		{
			if (_size)
			{
				T* new_buffer = traits::allocate(get_allocator(), _size);

				std::uninitialized_copy_n(_data, _size, new_buffer);

				std::swap(_data, new_buffer);

				std::destroy_n(new_buffer, _size);
				traits::deallocate(get_allocator(), new_buffer, _capacity);

				_capacity = _size;
			}
			else
			{
				traits::deallocate(get_allocator(), _data, _capacity);

				_data = nullptr;
				_capacity = 0;
			}
		}
	}

	reference front() noexcept
	{
		return _data[0];
	}

	reference front() const noexcept
	{
		return _data[0];
	}

	reference back() noexcept
	{
		return _data[_size - 1];
	}

	reference back() const noexcept
	{
		return _data[_size - 1];
	}

	void swap(MyVector& other) noexcept
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
	}

	~MyVector()
	{
		destroy_and_deallocate();
	}

private:

	allocator_type& get_allocator() noexcept
	{
		return *static_cast<allocator_type*>(this);
	}

	void destroy_and_deallocate()
	{
		if (_capacity)
		{
			std::destroy_n(_data, _size);
			traits::deallocate(get_allocator(), _data, _capacity);
			_data = nullptr;
		}
	}

	size_type _size;
	size_type _capacity;
	pointer _data;
};

template<typename T>
void print_range(const T& range)
{
	for (const auto& value : range)
	{
		std::cout << value << ' ';
	}
	std::cout << '\n';
}

template <typename InputIt>
constexpr double harmonic_media(InputIt first, InputIt last) noexcept
{
	double sum = 0;
	std::size_t n = 0;

	while (first != last)
	{
		sum += (1.0 / *first++);
		n++;
	}

	return (double)n / sum;
}

int main()
{
	MyVector<std::string> words = { "My", "vector", "do", "inserts" };

	auto it = words.insert(words.cbegin() + 2, "can");

	print_range(words);

	it = words.erase(words.begin() + 1);

	print_range(words);

	words = { "My", "vector", "can", "be", "iterated", "through" };

	print_range(words);

	std::sort(words.begin(), words.end());

	print_range(std::as_const(words));

	std::cout << '\n';

	MyVector v = { 1, 2, 3, 4, 5, 6 };

	std::cout << "Harmonic media: " << harmonic_media(cbegin(v), cend(v));
}