#pragma once

namespace sf { template <typename T> class Vector2; }

namespace Conure::Utility
{
    template <typename T>
    class AtomicVector2;

    /*!
    * \brief Simple 2d vector.
    * \tparam T - type of used data.
    */
    template <typename T>
    class Vector2
    {
    public:
        /*! Default destructor. */
        ~Vector2() = default;

        /*! Default constructor with default values as zero. */
        Vector2();

        /*!
         * \brief Constructor to create the vector from two values.
         * \param xValue - value for x parameter.
         * \param yValue - value for y parameter.
         */
        Vector2(T xValue, T yValue);

        /*!
         * \brief Copy constructor.
         * \param other - const reference to other vector with the same template type.
         */
        Vector2(const Vector2& other);

        /*!
         * \brief Move constructor.
         * \param other - double reference to other vector value with the same template type.
         */
        Vector2(Vector2&& other) noexcept;

        /*!
         * \brief Copy constructor.
         * \param other - const reference to sf::Vector2 with the same template type.
         */
        Vector2(const sf::Vector2<T>& other);

        /*!
         * \brief Move constructor.
         * \param other - double reference to sf::Vector2 value with the same template type.
         */
        Vector2(sf::Vector2<T>&& other);

        /*!
         * \brief Copy constructor.
         * \param other - const reference to AtomicVector2 with the same template type.
         */
        Vector2(const AtomicVector2<T>& other);

        /*!
         * \brief Move constructor.
         * \param other - double reference to AtomicVector2 value with the same template type.
         */
        Vector2(AtomicVector2<T>&& other);

        /*!
         * \brief Copy constructor.
         * \tparam U - different type of used data.
         * \param other - const reference to other vector with a different template type.
         *
         * A different type of vector as a parameter.
         */
        template <typename U>
        explicit Vector2(const Vector2<U>& other);

        /*!
         * \brief Move constructor.
         * \tparam U - different type of used data.
         * \param other - double reference to other vector value with a different template type.
         *
         * A different type of vector as a parameter.
         */
        template <typename U>
        explicit Vector2(Vector2<U>&& other);

        /*!
         * \brief Copy assignment operator.
         * \param other - const reference to other vector with the same template type.
         * \return Reference to vector after assignment.
         *
         * The same type of vector as a parameter.
         */
        Vector2& operator=(const Vector2& other);

        /*!
         * \brief Move assignment operator.
         * \param other - double reference to other vector value with the same template type.
         * \return Reference to vector after assignment.
         *
         * The same type of vector as a parameter.
         */
        Vector2& operator=(Vector2&& other) noexcept;

        /*!
         * \brief Copy assignment operator.
         * \tparam U - different type of used data.
         * \param other - const reference to other vector with a different template type.
         * \return Reference to vector after assignment.
         *
         *  A different type of vector as a parameter.
         */
        template <typename U>
        Vector2& operator=(const Vector2<U>& other);

        /*!
         * \brief Move assignment operator.
         * \tparam U - different type of used data.
         * \param other - double reference to other vector value with a different template type.
         * \return Reference to vector after assignment.
         *
         * A different type of vector as a parameter.
         */
        template <typename U>
        Vector2& operator=(Vector2<U>&& other);

        /*!
         * \brief Equality operator.
         *
         * \param right - const reference to other vector with the same template type.
         * \return True if vectors are equal. Otherwise - false.
         */
        bool operator==(const Vector2& right);

        /*!
         * \brief Inequality operator.
         *
         * \param right - const reference to other vector with the same template type.
         * \return True if vectors are unequal. Otherwise - false.
         */
        bool operator!=(const Vector2& right);

        /*!
         * \brief Multiplication operator.
         *
         * \param right - const reference to other vector with the same template type.
         * \return Scalar of the same template type.
         */
        T operator*(const Vector2& right) const;

        /*!
         * \brief Multiplication operator.
         * \param scalar - scalar value with the same template type.
         * \return New vector as result of math operation.
         */
        Vector2 operator*(T scalar) const;

        /*!
         * \brief Division operator.
         * \param scalar - scalar value with the same template type.
         * \return New vector as result of math operation.
         */
        Vector2 operator/(T scalar) const;

        /*!
         * \brief Addition operator.
         * \param right - const reference to other vector with the same template type.
         * \return New vector as result of math operation.
         */
        Vector2 operator+(const Vector2& right) const;

        /*!
         * \brief Subtraction operator.
         * \param right - const reference to other vector with the same template type.
         * \return New vector as result of math operation.
         */
        Vector2 operator-(const Vector2& right) const;

        /*!
         * \brief Addition and assignment operator.
         * \param right - const reference to other vector with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        Vector2& operator+=(const Vector2& right);

        /*!
         * \brief Subtraction and assignment operator.
         * \param right - const reference to other vector with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        Vector2& operator-=(const Vector2& right);

        /*!
         * \brief Division and assignment operator.
         * \param right - const reference to other vector with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        Vector2& operator/=(const Vector2& right);

        /*!
         * \brief Division and assignment operator.
         * \param scalar - scalar value with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        Vector2& operator/=(T scalar);

        /*!
         * \brief Multiplication and assignment operator.
         * \param scalar - scalar value with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        Vector2& operator*=(T scalar);

        /*!
         * \brief Sets each of vector parameters to zero.
         */
        void Zero();

        /*! X value of vector. */
        T x;
        /*! Y value of vector. */
        T y;
    };

    /*!
     * \brief Subtraction operator.
     * \tparam T - type of used data.
     * \param right - const reference to other vector with the same template type.
     * \return New vector with same but negative values as result of math operation.
     */
    template <typename T>
    Vector2<T> operator-(const Vector2<T>& right);

    /*!
     * \brief Multiplication operator.
     * \tparam T - type of used data.
     * \param scalar - scalar value with the same template type.
     * \param right - const reference to other vector with the same template type.
     * \return New vector as result of math operation.
     */
    template <typename T>
    Vector2<T> operator*(T scalar, const Vector2<T>& right);

#include "Vector2.inl"

    /*! Vector for float type. */
    using Vector2F = Vector2<float>;
    /*! Vector for int type. */
    using Vector2I = Vector2<int>;
}