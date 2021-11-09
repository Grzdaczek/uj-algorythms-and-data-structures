namespace nsd {

	template<typename P, typename T>
	class ConstIterator {
	private:
		P m_ptr;

	public:
		constexpr ConstIterator() noexcept
			: m_ptr(P())
		{}

		constexpr ConstIterator(const P& i) noexcept
			: m_ptr(i)
		{}

		constexpr bool
		operator==(const ConstIterator& other) const noexcept {
			return this->m_ptr == other.m_ptr;
		}

		constexpr bool
		operator!=(const ConstIterator& other) const noexcept {
			return !(this->m_ptr == other.m_ptr);
		}

		constexpr const T&
		operator*() const noexcept {
			return *this->m_ptr;
		}

		constexpr const T*
		operator->() const noexcept {
			return &(*m_ptr);
		}

		constexpr ConstIterator&
		operator++() noexcept {
			++this->m_ptr;
			return *this;
		}

		constexpr ConstIterator&
		operator--() noexcept {
			--this->m_ptr;
			return *this;
		}

		constexpr const P&
		base() const noexcept {
			return this->m_ptr;
		}
	};
	
	template<typename P, typename T>
	class Iterator {
	private:
		P m_ptr;

	public:
		constexpr Iterator() noexcept
			: m_ptr(P())
		{}

		constexpr Iterator(const P& i) noexcept
			: m_ptr(i)
		{}

		constexpr bool
		operator==(const Iterator& other) const noexcept {
			return this->m_ptr == other.m_ptr;
		}

		constexpr bool
		operator!=(const Iterator& other) const noexcept {
			return !(this->m_ptr == other.m_ptr);
		}

		constexpr T&
		operator*() const noexcept {
			return *this->m_ptr;
		}

		constexpr T*
		operator->() const noexcept {
			return &(*m_ptr);
		}

		constexpr Iterator&
		operator++() noexcept {
			++this->m_ptr;
			return *this;
		}

		constexpr Iterator&
		operator--() noexcept {
			--this->m_ptr;
			return *this;
		}

		constexpr const P&
		base() const noexcept {
			return this->m_ptr;
		}
	};

}
