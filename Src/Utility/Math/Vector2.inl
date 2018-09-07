#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>::Vector2() : x(0), y(0)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>::Vector2(const T xValue, const T yValue) : x(xValue), y(yValue)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool OtherVectorIsAtomic>
Vector2<T, IsAtomic>::Vector2(const Vector2<T, OtherVectorIsAtomic>& otherVector)
{
    if constexpr (OtherVectorIsAtomic)
    {
        x = otherVector.x.load();
        y = otherVector.y.load();
    }
    else
    {
        x = otherVector.x;
        y = otherVector.y;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>::Vector2(C2D::Vector2<T, false>&& nonatomicVector) noexcept
: x(std::move(nonatomicVector.x))
, y(std::move(nonatomicVector.y))
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>::Vector2(const sf::Vector2<T>& sfmlVector) : x(sfmlVector.x), y(sfmlVector.y)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>::Vector2(sf::Vector2<T>&& sfmlVector)
: x(std::move(sfmlVector.x))
, y(std::move(sfmlVector.y))
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool OtherVectorIsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator=(const C2D::Vector2<T, OtherVectorIsAtomic>& otherVector)
{
    if constexpr (OtherVectorIsAtomic)
    {
        x = otherVector.x.load();
        y = otherVector.y.load();
    }
    else
    {
        x = otherVector.x;
        y = otherVector.y;
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator=(Vector2<T, false>&& nonatomicVector)
{
    x = nonatomicVector.x;
    y = nonatomicVector.y;

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator=(const sf::Vector2<T>& sfmlVector)
{
    x = sfmlVector.x;
    y = sfmlVector.y;

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator=(sf::Vector2<T>&& sfmlVector)
{
    x = std::move(sfmlVector.x);
    y = std::move(sfmlVector.y);

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
bool Vector2<T, IsAtomic>::operator==(const Vector2<T, RightVectorIsAtomic>& rightVector) const
{
    T otherVectorX;
    T otherVectorY;

    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            return rightVector.x.load() == x.load() &&
                   rightVector.y.load() == y.load();
        }
        else
        {
            return rightVector.x.load() == x &&
                   rightVector.y.load() == y;
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            return rightVector.x == x.load() &&
                   rightVector.y == y.load();
        }
        else
        {
            return rightVector.x == x &&
                   rightVector.y == y;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
bool Vector2<T, IsAtomic>::operator!=(const Vector2<T, RightVectorIsAtomic>& rightVector) const
{
    return !(*this == rightVector);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <typename U, bool RightVectorIsAtomic>
T Vector2<T, IsAtomic>::operator*(const Vector2<U, RightVectorIsAtomic>& rightVector) const
{
    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            return static_cast<T>(x.load() * rightVector.x.load() + y.load() * rightVector.y.load());
        }
        else
        {
            return static_cast<T>(x * rightVector.x.load() + y * rightVector.y.load());
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            return static_cast<T>(x.load() * rightVector.x + y.load() * rightVector.y);
        }
        else
        {
            return static_cast<T>(x * rightVector.x + y * rightVector.y);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <typename U>
Vector2<T, false> Vector2<T, IsAtomic>::operator*(const U scalar) const
{
    if constexpr (IsAtomic)
    {
        return Vector2<T, false>(static_cast<T>(x.load() * scalar),
                                    static_cast<T>(y.load() * scalar));
    }
    else
    {
        return Vector2<T, false>(static_cast<T>(x * scalar),
                                    static_cast<T>(y * scalar));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <typename U>
Vector2<T, false> Vector2<T, IsAtomic>::operator/(const U scalar) const
{
    constexpr double invertedScalar(1.0 / scalar);

    if constexpr (IsAtomic)
    {
        return Vector2<T, false>(static_cast<T>(x.load() * invertedScalar),
                                    static_cast<T>(y.load() * invertedScalar));
    }
    else
    {
        return Vector2<T, false>(static_cast<T>(x * invertedScalar),
                                    static_cast<T>(y * invertedScalar));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
Vector2<T, false> Vector2<T, IsAtomic>::operator+(const Vector2<T, RightVectorIsAtomic>& rightVector) const
{
    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            return Vector2<T, false>(static_cast<T>(x.load() + rightVector.x.load()),
                                        static_cast<T>(y.load() + rightVector.y.load()));
        }
        else
        {
            return Vector2<T, false>(static_cast<T>(x + rightVector.x.load()),
                                        static_cast<T>(y + rightVector.y.load()));
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            return Vector2<T, false>(static_cast<T>(x.load() + rightVector.x),
                                        static_cast<T>(y.load() + rightVector.y));
        }
        else
        {
            return Vector2<T, false>(static_cast<T>(x + rightVector.x),
                                        static_cast<T>(y + rightVector.y));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
Vector2<T, false> Vector2<T, IsAtomic>::operator-(const Vector2<T, RightVectorIsAtomic>& rightVector) const
{
    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            return Vector2<T, false>(static_cast<T>(x.load() - rightVector.x.load()),
                                        static_cast<T>(y.load() - rightVector.y.load()));
        }
        else
        {
            return Vector2<T, false>(static_cast<T>(x - rightVector.x.load()),
                                        static_cast<T>(y - rightVector.y.load()));
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            return Vector2<T, false>(static_cast<T>(x.load() - rightVector.x),
                                        static_cast<T>(y.load() - rightVector.y));
        }
        else
        {
            return Vector2<T, false>(static_cast<T>(x - rightVector.x),
                                        static_cast<T>(y - rightVector.y));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator+=(const Vector2<T, RightVectorIsAtomic>& rightVector)
{
    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            x = x.load() + rightVector.x.load();
            y = y.load() + rightVector.y.load();
        }
        else
        {
            x = x + rightVector.x.load();
            y = y + rightVector.y.load();
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            x = x.load() + rightVector.x;
            y = y.load() + rightVector.y;
        }
        else
        {
            x = x + rightVector.x;
            y = y + rightVector.y;
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator-=(const Vector2<T, RightVectorIsAtomic>& rightVector)
{
    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            x = x.load() - rightVector.x.load();
            y = y.load() + rightVector.y.load();
        }
        else
        {
            x = x - rightVector.x.load();
            y = y - rightVector.y.load();
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            x = x.load() - rightVector.x;
            y = y.load() - rightVector.y;
        }
        else
        {
            x = x - rightVector.x;
            y = y - rightVector.y;
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <bool RightVectorIsAtomic>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator/=(const C2D::Vector2<T, RightVectorIsAtomic>& rightVector)
{
    if constexpr (RightVectorIsAtomic)
    {
        if constexpr (IsAtomic)
        {
            x = x.load() / rightVector.x.load();
            y = y.load() / rightVector.y.load();
        }
        else
        {
            x = x / rightVector.x.load();
            y = y / rightVector.y.load();
        }
    }
    else
    {
        if constexpr (IsAtomic)
        {
            x = x.load() / rightVector.x;
            y = y.load() / rightVector.y;
        }
        else
        {
            x = x / rightVector.x;
            y = y / rightVector.y;
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <typename U>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator*=(const U scalar)
{
    if constexpr (IsAtomic)
    {
        x = x.load() * scalar;
        y = y.load() * scalar;
    }
    else
    {
        x *= scalar;
        y *= scalar;
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
template <typename U>
Vector2<T, IsAtomic>& Vector2<T, IsAtomic>::operator/=(const U scalar)
{
    constexpr T invertedScalar(1.0 / scalar);

    if constexpr (IsAtomic)
    {
        x = x.load() * invertedScalar;
        y = y.load() * invertedScalar;
    }
    else
    {
        x *= invertedScalar;
        y *= invertedScalar;
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
void Vector2<T, IsAtomic>::Zero()
{
    x = y = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, bool IsAtomic>
Vector2<T, false> operator-(const Vector2<T, IsAtomic>& vector)
{
    if constexpr (IsAtomic)
    {
        return Vector2<T, false>(-vector.x.load(), -vector.y.load());
    }
    else
    {
        return Vector2<T, false>(-vector.x, -vector.y);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename U, typename T, bool IsAtomic>
Vector2<T, false> operator*(U scalar, const Vector2<T, IsAtomic>& vector)
{
    if constexpr (IsAtomic)
    {
        return Vector2<T, false>(static_cast<T>(vector.x.load() * scalar),
                                    static_cast<T>(vector.y.load() * scalar));
    }
    else
    {
        return Vector2<T, false>(static_cast<T>(vector.x * scalar),
                                    static_cast<T>(vector.y * scalar));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////