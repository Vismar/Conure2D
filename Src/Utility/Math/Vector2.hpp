#pragma once
#include <atomic>
#include <type_traits>

namespace sf { template <typename T> class Vector2; }

namespace C2D
{
    /*!
     * Simple 2d vector that can use nonatomic and atomic types.
     * \tparam T - type of data that will be stored within a vector.
     * \tparam IsAtomic - flag that defines if vector will store atomic or nonatomic data.
     */
    template <typename T, bool IsAtomic = false>
    class Vector2
    {
        // Vector must be used only with primitive types
        static_assert(std::is_fundamental<T>::value);
    public:
        ~Vector2() = default;
        Vector2(Vector2<T, true>&& atomicVector) = delete;
        Vector2& operator=(Vector2<T, true>&& atomicVector) = delete;

        /*! Type that is used in Vector2. */
        using Type = typename std::conditional<IsAtomic, std::atomic<T>, T>::type;

        /*!
         * \brief Default constructor with default values as zero.
         */
        Vector2();

        /*!
         * \brief Constructor to create a vector from two values.
         * \param xValue - value of x parameter.
         * \param yValue - value of y parameter.
         */
        Vector2(T xValue, T yValue);

        /*!
         * \brief Copy constructor.
         * \tparam OtherVectorIsAtomic - flag that defines if otherVector is atomic or not.
         * \param otherVector - other vector from which values will be copied.
         */
        template <bool OtherVectorIsAtomic>
        explicit Vector2(const Vector2<T, OtherVectorIsAtomic>& otherVector);

        /*!
         * \brief Move constructor.
         * \param nonatomicVector - other vector which values will be used.
         */
        explicit Vector2(Vector2<T, false>&& nonatomicVector) noexcept;
        /*!
         * \brief Copy constructor.
         * \param sfmlVector - sf::Vector2 from which values will be copied.
         */
        explicit Vector2(const sf::Vector2<T>& sfmlVector);

        /*!
         * \brief Copy constructor.
         * \param sfmlVector - sf::Vector2 which values will be used.
         */
        explicit Vector2(sf::Vector2<T>&& sfmlVector);

        /*!
         * \brief Copy assignment operator.
         * \tparam OtherVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param otherVector - const reference to other vector with the same template type.
         * \return Reference to vector after assignment.
         */
        template <bool OtherVectorIsAtomic>
        Vector2<T, IsAtomic>& operator=(const Vector2<T, OtherVectorIsAtomic>& otherVector);

        /*!
         * \brief Copy assignment operator.
         * \param nonatomicVector - other vector which values will be used.
         * \return Reference to vector after assignment.
         */
        Vector2<T, IsAtomic>& operator=(Vector2<T, false>&& nonatomicVector);

        /*!
         * \brief Copy assignment operator.
         * \param sfmlVector - sf::Vector2 from which values will be copied.
         * \return Reference to vector after assignment.
         */
        Vector2<T, IsAtomic>& operator=(const sf::Vector2<T>& sfmlVector);

        /*!
         * \brief Copy assignment operator.
         * \param sfmlVector - sf::Vector2 which values will be used.
         * \return Reference to vector after assignment.
         */
        Vector2<T, IsAtomic>& operator=(sf::Vector2<T>&& sfmlVector);

        /*!
         * \brief Equality operator.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return True if vectors are equal (x == rightVector.x && y == rightVector.y). Otherwise - false.
         */
        template <bool RightVectorIsAtomic>
        bool operator==(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Inequality operator.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return True if vectors are not equal (x != rightVector.x && y != rightVector.y). Otherwise - false.
         */
        template <bool RightVectorIsAtomic>
        bool operator!=(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Multiplication operator by another Vector2.
         * \tparam U - type that is used in rightVector.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same or different template type.
         * \return Scalar of the same template type as "left" vector.
         */
        template <typename U, bool RightVectorIsAtomic>
        T operator*(const Vector2<U, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Multiplication operator by scalar.
         * \tparam U - type of a scalar.
         * \param scalar - value of a scalar.
         * \return New vector as result of math operation.
         */
        template <typename U>
        Vector2<T, false> operator*(U scalar) const;

        /*!
         * \brief Division operator by scalar.
         * \tparam U - type of a scalar.
         * \param scalar - value of a scalar.
         * \return New vector as result of math operation.
         */
        template <typename U>
        Vector2<T, false> operator/(U scalar) const;

        /*!
         * \brief Addition operator.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return New vector as result of math operation.
         */
        template <bool RightVectorIsAtomic>
        Vector2<T, false> operator+(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Subtraction operator.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return New vector as result of math operation.
         */
        template <bool RightVectorIsAtomic>
        Vector2<T, false> operator-(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Addition and assignment operator.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return
         */
        template <bool RightVectorIsAtomic>
        Vector2& operator+=(const Vector2<T, RightVectorIsAtomic>& rightVector);

        /*!
         * \brief Subtraction and assignment operator.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return
         */
        template <bool RightVectorIsAtomic>
        Vector2& operator-=(const Vector2<T, RightVectorIsAtomic>& rightVector);

        /*!
         * \brief Division and assignment operator by vector.
         * \tparam RightVectorIsAtomic - flag that defines if rightVector is atomic or not.
         * \param rightVector - const reference to other vector with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        template <bool RightVectorIsAtomic>
        Vector2& operator/=(const Vector2<T, RightVectorIsAtomic>& rightVector);

        /*!
         * \brief Multiplication and assignment operator by scalar.
         * \tparam U - type of a scalar.
         * \param scalar - value of a scalar.
         * \return Reference to vector after math operation and assignment.
         */
        template <typename U>
        Vector2& operator*=(U scalar);

        /*!
         * \brief Division and assignment operator by scalar.
         * \tparam U - type of a scalar.
         * \param scalar - value of a scalar.
         * \return Reference to vector after math operation and assignment.
         */
        template <typename U>
        Vector2& operator/=(U scalar);

        /*!
         * \brief Sets each of vector parameters to zero.
         */
        void Zero();

        /*! X value of vector. */
        Type x;
        /*! Y value of vector. */
        Type y;
    };

    /*!
     * \brief Subtraction operator.
     * \tparam T - type that is used be vector.
     * \tparam IsAtomic - flag that defines if vector is atomic or not.
     * \param vector - const reference to a vector.
     * \return New vector with same but negative values as result of math operation.
     */
    template <typename T, bool IsAtomic>
    Vector2<T, false> operator-(const Vector2<T, IsAtomic>& vector);

    /*!
     * \brief Multiplication operator.
     * \tparam U - type of a scalar.
     * \tparam T - type that is used be vector.
     * \tparam IsAtomic - flag that defines if vector is atomic or not.
     * \param scalar - value of a scalar.
     * \param vector - const reference to a vector.
     * \return New vector as result of math operation.
     */
    template <typename U, typename T, bool IsAtomic>
    Vector2<T, false> operator*(U scalar, const Vector2<T, IsAtomic>& vector);

#include "Vector2.inl"

    /*! Atomic vector with float type. */
    using Vector2af = Vector2<float, true>;
    /*! Atomic vector with int8_t type. */
    using Vector2ai8 = Vector2<int8_t, true>;
    /*! Atomic vector with int16_t type. */
    using Vector2ai16 = Vector2<int16_t, true>;
    /*! Atomic vector with int32_t type. */
    using Vector2ai32 = Vector2<int32_t, true>;
    /*! Atomic vector with int64_t type. */
    using Vector2ai64 = Vector2<int64_t, true>;
    /*! Nonatomic vector with float type. */
    using Vector2f = Vector2<float, false>;
    /*! Nonatomic vector with int8_t type. */
    using Vector2i8 = Vector2<int8_t, false>;
    /*! Nonatomic vector with int16_t type. */
    using Vector2i16 = Vector2<int16_t, false>;
    /*! Nonatomic vector with int32_t type. */
    using Vector2i32 = Vector2<int32_t, false>;
    /*! Nonatomic vector with int64_t type. */
    using Vector2i64 = Vector2<int64_t, false>;
}