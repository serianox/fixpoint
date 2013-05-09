
#pragma once
#if !defined(__FIXPOINT_HPP__)
#	define __FIXPOINT_HPP__ 1

#	include <cstdlib>
#	include <limits>

template<signed I = 0, signed Q = std::numeric_limits<unsigned>::digits - I, typename s = unsigned>
struct fixpoint
{
 	static constexpr unsigned I_ = I;
 	static constexpr unsigned Q_ = Q;

 	static constexpr s one_ = 1 << Q;

 	// TODO: move to std::numeric_limits
 	static constexpr int digits = I + Q;
 	static constexpr bool is_signed = std::numeric_limits<s>::is_signed;

	typedef fixpoint<I, Q, s> self_t;
	typedef fixpoint<I - (is_signed?0:1), Q, signed> signed_self_t;

	static_assert(I >= 0, "");
	static_assert(Q >= 1, "");
	static_assert(std::numeric_limits<s>::is_integer, "");
 	static_assert(I + Q <= std::numeric_limits<s>::digits, "");
 	static_assert(std::numeric_limits<s>::digits <= std::numeric_limits<unsigned>::digits, "");

	s value_ : (is_signed?1:0) + digits;

	explicit fixpoint(s that) : value_(that) {}
	explicit constexpr fixpoint(const unsigned long long that) : value_(that << Q) {}
	explicit constexpr fixpoint(const long double that) : value_(that * (1 << Q)) {}

	operator s ()
	{
		return this->value_ >> Q;
	}

	template<signed J, signed R>
	operator fixpoint<J, R, s> ()
	{
		if (self_t::digits > fixpoint<J, R, s>::digits)
		{
			if ((R - Q) > 0)
			{
				return fixpoint<J, R, s>(static_cast<s>(this->value_ << abs(R - Q)));
			}
			else
			{
				return fixpoint<J, R, s>(static_cast<s>(this->value_ >> abs(R - Q)));
			}
		}
		else
		{
			if ((R - Q) > 0)
			{
				return fixpoint<J, R, s>(static_cast<s>(this->value_) << abs(R - Q));
			}
			else
			{
				return fixpoint<J, R, s>(static_cast<s>(this->value_) >> abs(R - Q));
			}
		}
	}

	signed_self_t operator - ()
	{
		return signed_self_t(-static_cast<signed>(this->value_));
	}

	self_t operator + (const self_t & that)
	{
		return self_t(this->value_ + that.value_);
	}

	self_t operator - (const self_t & that)
	{
		return self_t(this->value_ - that.value_);
	}
};

typedef fixpoint<15, 16, signed> fx15_16_t;
typedef fixpoint<16, 16> ufx16_16_t;

typedef fixpoint<7, 8, signed> fx7_8_t;
typedef fixpoint<8, 8> ufx8_8_t;

typedef fixpoint<3, 4, signed> fx3_4_t;
typedef fixpoint<4, 4> ufx4_4_t;

constexpr ufx16_16_t operator "" _ufx (const unsigned long long literal)
{
	return ufx16_16_t(literal);
}

constexpr fx15_16_t operator "" _fx (const unsigned long long literal)
{
	return fx15_16_t(literal);
}

constexpr ufx16_16_t operator "" _ufx (const long double literal)
{
	return ufx16_16_t(literal);
}

constexpr fx15_16_t operator "" _fx (const long double literal)
{
	return fx15_16_t(literal);
}

template<signed I, signed Q, typename s>
std::ostream & operator << (std::ostream & out, const fixpoint<I, Q, s> & that)
{
	return out << (static_cast<long double>(that.value_) / (1 << Q));
}

#endif // !defined(__FIXPOINT_HPP__)
