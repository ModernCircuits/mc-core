#pragma once

#include "mc/cmath.hpp"
#include "mc/config.hpp"
#include "mc/limits.hpp"
#include "mc/numeric.hpp"
#include "mc/ratio.hpp"
#include "mc/type_traits.hpp"

namespace mc {

template <typename Rep>
struct TreatAsFloatingPoint : std::is_floating_point<Rep> {
};

template <typename Rep, typename Period = std::ratio<1>>
struct Frequency {
private:
    template <typename Rep2>
    using Ctor3 = std::enable_if<std::is_convertible<Rep2, Rep>::value
                                     && (TreatAsFloatingPoint<Rep>::value
                                         || !TreatAsFloatingPoint<Rep2>::value),
        int>;

    template <typename Rep2, typename Period2>
    using Ctor4
        = std::enable_if<TreatAsFloatingPoint<Rep>::value
                             || (std::ratio_divide<Period2, Period>::den == 1
                                 && !TreatAsFloatingPoint<Rep2>::value),
            int>;

public:
    using rep    = Rep;
    using period = typename Period::type;

    /// \brief (1) The default constructor is defaulted.
    constexpr Frequency() noexcept = default;

    /// \brief (2) The copy constructor makes a bitwise copy of the tick
    /// count.
    Frequency(Frequency const& /*other*/) = default;

    /// \brief (3) Constructs a Frequency with r ticks.
    ///
    /// Note that this constructor only participates in overload resolution
    /// if Rep2 const& (the argument type) is implicitly convertible to rep
    /// (the type of this Frequency's ticks) and
    /// TreatAsFloatingPoint<rep>::value is true, or
    /// TreatAsFloatingPoint<Rep2>::value is false.
    ///
    /// (that is, a Frequency with an integer tick count cannot be
    /// constructed from a floating-point value, but a Frequency with a
    /// floating-point tick count can be constructed from an integer value)
    template <typename Rep2, typename Ctor3<Rep2>::type = 0>
    constexpr explicit Frequency(Rep2 const& r) : ticks_(r)
    {
    }

    /// \brief Constructs a Frequency by converting d to an appropriate period
    /// and tick count.
    template <typename Rep2, typename Period2,
        typename Ctor4<Rep2, Period2>::type = 0>
    constexpr Frequency(Frequency<Rep2, Period2> const& other)
        : ticks_(static_cast<Rep>(
            other.count() * std::ratio_divide<Period2, period>::num))
    {
    }

    /// \brief Assigns the contents of one Frequency to another.
    constexpr auto operator=(Frequency const& other) -> Frequency& = default;

    /// \brief Returns the number of ticks for this Frequency.
    MC_NODISCARD constexpr auto count() const noexcept -> rep { return ticks_; }

    /// \brief Returns a copy of this Frequency object
    MC_NODISCARD constexpr auto operator+() const
        -> std::common_type_t<Frequency>
    {
        return std::common_type_t<Frequency>(*this);
    }

    /// \brief Returns a copy of this Frequency object, with the number of
    /// ticks negated.
    MC_NODISCARD constexpr auto operator-() const
        -> std::common_type_t<Frequency>
    {
        return std::common_type_t<Frequency>(-ticks_);
    }

private:
    Rep ticks_ { 0 };
};

template <typename Rep, typename Period>
constexpr auto operator+=(Frequency<Rep, Period>& lhs,
    Frequency<Rep, Period> const& rhs) noexcept(noexcept(std::declval<Rep>()
                                                         + std::declval<Rep>()))
    -> Frequency<Rep, Period>&
{
    lhs = Frequency<Rep, Period> { lhs.count() + rhs.count() };
    return lhs;
}

template <typename Rep, typename Period>
constexpr auto operator-=(Frequency<Rep, Period>& lhs,
    Frequency<Rep, Period> const& rhs) noexcept(noexcept(std::declval<Rep>()
                                                         - std::declval<Rep>()))
    -> Frequency<Rep, Period>&
{
    lhs = Frequency<Rep, Period> { lhs.count() - rhs.count() };
    return lhs;
}

template <typename Rep, typename Period>
constexpr auto operator*=(Frequency<Rep, Period>& lhs, Rep const& rhs) noexcept(
    noexcept(std::declval<Rep>() * std::declval<Rep>()))
    -> Frequency<Rep, Period>&
{
    lhs = Frequency<Rep, Period> { lhs.count() * rhs };
    return lhs;
}

template <typename Rep, typename Period>
constexpr auto operator/=(Frequency<Rep, Period>& lhs, Rep const& rhs) noexcept(
    noexcept(std::declval<Rep>() / std::declval<Rep>()))
    -> Frequency<Rep, Period>&
{
    lhs = Frequency<Rep, Period> { lhs.count() / rhs };
    return lhs;
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator+(
    Frequency<Rep1, Period1> const& lhs, Frequency<Rep2, Period2> const& rhs)
    -> std::common_type_t<Frequency<Rep1, Period1>, Frequency<Rep2, Period2>>
{
    using CD = std::common_type_t<Frequency<Rep1, Period1>,
        Frequency<Rep2, Period2>>;
    return CD(CD(lhs).count() + CD(rhs).count());
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator-(
    Frequency<Rep1, Period1> const& lhs, Frequency<Rep2, Period2> const& rhs)
    -> std::common_type_t<Frequency<Rep1, Period1>, Frequency<Rep2, Period2>>
{
    using CD = std::common_type_t<Frequency<Rep1, Period1>,
        Frequency<Rep2, Period2>>;
    return CD(CD(lhs).count() - CD(rhs).count());
}

template <typename Rep1, typename Period, typename Rep2>
MC_NODISCARD constexpr auto operator*(Frequency<Rep1, Period> const& d,
    Rep2 const& s) -> Frequency<std::common_type_t<Rep1, Rep2>, Period>
{
    using CD = Frequency<std::common_type_t<Rep1, Rep2>, Period>;
    return CD(CD(d).count() * s);
}

template <typename Rep1, typename Rep2, typename Period>
MC_NODISCARD constexpr auto operator*(
    Rep1 const& s, Frequency<Rep2, Period> const& d)
    -> Frequency<std::common_type_t<Rep1, Rep2>, Period>
{
    using CD = Frequency<std::common_type_t<Rep1, Rep2>, Period>;
    return CD(CD(d).count() * s);
}

template <typename Rep1, typename Period, typename Rep2>
MC_NODISCARD constexpr auto operator/(Frequency<Rep1, Period> const& d,
    Rep2 const& s) -> Frequency<std::common_type_t<Rep1, Rep2>, Period>
{
    using CD = Frequency<std::common_type_t<Rep1, Rep2>, Period>;
    return CD(CD(d).count() / s);
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator/(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> std::common_type_t<Rep1, Rep2>
{
    using CD = std::common_type_t<Frequency<Rep1, Period1>,
        Frequency<Rep2, Period2>>;
    return CD(lhs).count() / CD(rhs).count();
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator==(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> bool
{
    using CT = std::common_type_t<Frequency<Rep1, Period1>,
        Frequency<Rep2, Period2>>;
    return CT(lhs).count() == CT(rhs).count();
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator!=(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> bool
{
    return !(lhs == rhs);
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator<(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> bool
{
    using CT = std::common_type_t<Frequency<Rep1, Period1>,
        Frequency<Rep2, Period2>>;
    return CT(lhs).count() < CT(rhs).count();
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator<=(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> bool
{
    return !(rhs < lhs);
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator>(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> bool
{
    return rhs < lhs;
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
MC_NODISCARD constexpr auto operator>=(Frequency<Rep1, Period1> const& lhs,
    Frequency<Rep2, Period2> const& rhs) -> bool
{
    return !(lhs < rhs);
}

namespace detail {
template <typename T>
struct IsFrequency : std::false_type {
};

template <typename Rep, typename Period>
struct IsFrequency<mc::Frequency<Rep, Period>> : std::true_type {
};

template <typename ToFrequency, typename CF, typename CR, bool NumIsOne = false,
    bool DenIsOne = false>
struct FrequencyCastImpl {
    template <typename Rep, typename Period>
    constexpr auto operator()(Frequency<Rep, Period> const& frequency) const
        -> ToFrequency
    {
        using toRep = typename ToFrequency::rep;
        return ToFrequency(static_cast<toRep>(static_cast<CR>(frequency.count())
                                              * static_cast<CR>(CF::num)
                                              / static_cast<CR>(CF::den)));
    }
};

template <typename ToFrequency, typename CF, typename CR>
struct FrequencyCastImpl<ToFrequency, CF, CR, true, false> {
    template <typename Rep, typename Period>
    constexpr auto operator()(Frequency<Rep, Period> const& frequency) const
        -> ToFrequency
    {
        using toRep = typename ToFrequency::rep;
        return ToFrequency(static_cast<toRep>(
            static_cast<CR>(frequency.count()) / static_cast<CR>(CF::den)));
    }
};

template <typename ToFrequency, typename CF, typename CR>
struct FrequencyCastImpl<ToFrequency, CF, CR, false, true> {
    template <typename Rep, typename Period>
    constexpr auto operator()(Frequency<Rep, Period> const& frequency) const
        -> ToFrequency
    {
        using toRep = typename ToFrequency::rep;
        return ToFrequency(static_cast<toRep>(
            static_cast<CR>(frequency.count()) * static_cast<CR>(CF::num)));
    }
};

template <typename ToFrequency, typename CF, typename CR>
struct FrequencyCastImpl<ToFrequency, CF, CR, true, true> {
    template <typename Rep, typename Period>
    constexpr auto operator()(Frequency<Rep, Period> const& frequency) const
        -> ToFrequency
    {
        using toRep = typename ToFrequency::rep;
        return ToFrequency(static_cast<toRep>(frequency.count()));
    }
};

} // namespace detail

template <typename ToFreq, typename Rep, typename Period>
MC_NODISCARD constexpr auto frequencyCast(
    Frequency<Rep, Period> const& frequency)
    -> std::enable_if_t<detail::IsFrequency<ToFreq>::value, ToFreq>
{
    using detail::FrequencyCastImpl;
    using cf   = std::ratio_divide<Period, typename ToFreq::period>;
    using cr   = std::common_type_t<typename ToFreq::rep, Rep, std::intmax_t>;
    using impl = FrequencyCastImpl<ToFreq, cf, cr, cf::num == 1, cf::den == 1>;
    return impl {}(frequency);
}

template <typename To, typename Rep, typename Period>
MC_NODISCARD constexpr auto floor(Frequency<Rep, Period> const& f)
    -> std::enable_if_t<detail::IsFrequency<To>::value, To>
{
    auto const t = frequencyCast<To>(f);
    if (t > f) { return t - To { 1 }; }
    return t;
}

template <typename To, typename Rep, typename Period>
MC_NODISCARD constexpr auto ceil(Frequency<Rep, Period> const& f)
    -> std::enable_if_t<detail::IsFrequency<To>::value, To>
{
    auto const t = frequencyCast<To>(f);
    if (t < f) { return t + To { 1 }; }
    return t;
}

template <typename To, typename Rep, typename Period>
MC_NODISCARD constexpr auto round(Frequency<Rep, Period> const& f)
    -> std::enable_if_t<detail::IsFrequency<To>::value
                            && !TreatAsFloatingPoint<typename To::rep>::value,
        To>
{
    To t0      = floor<To>(f);
    To t1      = t0 + To { 1 };
    auto diff0 = f - t0;
    auto diff1 = t1 - f;
    if (diff0 == diff1) {
        if (t0.count() & 1) { return t1; }
        return t0;
    }
    if (diff0 < diff1) { return t0; }
    return t1;
}

template <typename Rep, typename Period>
MC_NODISCARD constexpr auto abs(Frequency<Rep, Period> const& f)
    -> std::enable_if_t<std::numeric_limits<Rep>::is_signed,
        Frequency<Rep, Period>>
{
    return f.count() >= Rep {} ? f : -f;
}

template <typename T>
using Hertz = Frequency<T>;

template <typename T>
using Kilohertz = Frequency<T, std::ratio<1'000>>;

template <typename T>
using BPM // NOLINT(readability-identifier-naming)
    = Frequency<T, std::ratio<1, 60>>;

} // namespace mc

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
struct std::common_type< // NOLINT(readability-identifier-naming)
    mc::Frequency<Rep1, Period1>, mc::Frequency<Rep2, Period2>> {
private:
    static constexpr auto num = mc::gcd(Period1::num, Period2::num);
    static constexpr auto den = mc::lcm(Period1::den, Period2::den);
    using common_t            = typename std::common_type<Rep1, Rep2>::type;

public:
    using type = mc::Frequency<common_t, std::ratio<num, den>>;
};