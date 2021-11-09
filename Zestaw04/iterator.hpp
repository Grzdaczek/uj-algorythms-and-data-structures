namespace nsd {

	template<typename _Iter, typename _Type>
	class m_base_iterator {
	protected:
		_Iter m_iterator;

			// typedef std::iterator_traits<I>		__traits_type;

	public:
			// typedef I					iterator_type;
			// typedef typename __traits_type::iterator_category iterator_category;
			// typedef typename __traits_type::value_type  	value_type;
			// typedef typename __traits_type::difference_type 	difference_type;
			// typedef typename __traits_type::reference 	reference;
			// typedef typename __traits_type::pointer   	pointer;

		constexpr m_base_iterator() noexcept
			: m_iterator(_Iter())
		{}

		constexpr m_base_iterator(const _Iter& i) noexcept
			: m_iterator(i)
		{}

			// ? ???????? ???? ??????! !?! ?????????????????? !!!! !??!??! !? !? !? !? !? !?
			// Allow iterator to const_T conversion

			// template<typename _Iter>
			// 	constexpr
			// 	iterator(const iterator<_Iter,
			// 	typename __enable_if<
			// 					(std::__are_same<_Iter, typename C::pointer>::__value),
			// 		C>::__type>& __i) noexcept
			// 	: m_iterator(__i.base()) { }

		// Forward iterator requirements
		constexpr bool
		operator==(const m_base_iterator& other) const noexcept {
			return m_iterator == other.m_iterator;
		}

		constexpr bool
		operator!=(const m_base_iterator& other) const noexcept {
			return !(m_iterator == other.m_iterator);
		}

		constexpr _Type&
		operator*() const noexcept {
			return *m_iterator;
		}

		constexpr _Type*
		operator->() const noexcept {
			return &(*m_iterator);
		}

		constexpr m_base_iterator&
		operator++() noexcept {
			++m_iterator;
			return *this;
		}

		constexpr m_base_iterator
		operator++(int) noexcept {
			return m_base_iterator(m_iterator++);
		}

		// Bidirectional iterator requirements
		constexpr m_base_iterator&
		operator--() noexcept {
			--m_iterator;
			return *this;
		}

		constexpr m_base_iterator
		operator--(int) noexcept {
			return m_base_iterator(m_iterator--);
		}

		// Random access iterator requirements
		
		// constexpr reference
		// operator[](int n) const noexcept {
		// 	return m_iterator[n];
		// }

		// constexpr iterator&
		// operator+=(int n) noexcept {
		// 	m_iterator += n;
		// 	return *this;
		// }

		// constexpr iterator
		// operator+(int n) const noexcept {
		// 	return iterator(m_iterator + n);
		// }

		// constexpr iterator&
		// operator-=(int n) noexcept {
		// 	m_iterator -= n;
		// 	return *this;
		// }

		// constexpr iterator
		// operator-(int n) const noexcept {
		// 	return iterator(m_iterator - n);
		// }

		constexpr const _Iter&
		base() const noexcept {
			return m_iterator;
		}
	};

	template<typename _Iter, typename _Type>
	class const_iterator : public m_base_iterator<_Iter, _Type> {
	protected:
		_Iter m_iterator;

	public:
		constexpr const _Type&
		operator*() const noexcept {
			return *m_iterator;
		}
	};
	
}
