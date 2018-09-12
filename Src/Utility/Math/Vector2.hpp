#pragma once
#include <atomic>
#include <type_traits>

namespace sf { template <typename T> class Vector2; }

namespace C2D
{
    /*!
     * \ingroup Utility
     *
     * \brief Simple 2d vector that can use atomic and nonatomic types.
     * \tparam T Type of data that will be stored within a vector.
     * \tparam IsAtomic Flag that defines if vector will store atomic or nonatomic data.
     *
     * C2D::Vector2 is a simple math vector with two coordinates (x and y).
     * It can be used to represent a position, a size, a velocity, etc.
     *
     * The class has two template parameters: T and IsAtomic. T is the type of the coordinates.
     * T can be only a primitive type like int or float.
     * IsAtomic - flag that defines if T will be stored as is or as an atomic variable.
     * \code
     * C2D::Vector2<float, false> nonatomicVector(53.9f, 16.1f);
     * C2D::Vector2<float, true> atomicVector(53.9f, 16.1f);
     *
     * // OK to write like that
     * std::cout << "Nonatomic vector values:\n x= << nonatomicVector.x << "; y=" << nonatomicVector.y << ';';
     * // Possible ERROR within the multithreaded application.
     * std::cout << "Atomic vector values:\n x= << atomicVector.x << "; y=" << atomicVector.y << ';';
     * // Much better
     * std::cout << "Atomic vector values:\n x= << atomicVector.x.load() << "; y=" << atomicVector.y.load() << ';';
     * \endcode
     *
     * Generally, you do not need to care about long type definition like C2D::Vector2<float, false>,
     * almost every primitive type specialization have special alias:
     * \li C2D::Vector2f is C2D::Vector2<float, false>
     * \li C2D::Vector2af is C2D::Vector2<float, true>
     * \li C2D::Vector2i32 is C2D::Vector2<int32_t, false>
     * \li C2D::Vector2ai32 is C2D::Vector2<int32_t, true>
     *
     * Usage example:
     * \code
     * C2D::Vector2f vector1(0.2f, 100.0f);
     * vector1.x = 200.0f;
     * float y = vector1.y;
     *
     * C2D::Vector2f vector2(sf::Vector2f(1.0f, -55.4f));
     * C2D::Vector2f vector3 = vector1 + vector2;
     *
     * bool different = (vector2 != vector3);
     * \endcode
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
        constexpr Vector2();

        /*!
         * \brief Constructor to create a vector from two values.
         * \param xValue Value of x parameter.
         * \param yValue Value of y parameter.
         */
        constexpr Vector2(T xValue, T yValue);

        /*!
         * \brief Copy constructor.
         * \param otherVector Other vector from which values will be copied.
         */
        constexpr Vector2(const Vector2<T, IsAtomic>& otherVector);

        /*!
         * \brief Copy constructor.
         * \tparam OtherVectorIsAtomic Flag that defines if otherVector is atomic or not.
         * \param otherVector Other vector from which values will be copied.
         */
        template <bool OtherVectorIsAtomic>
        constexpr explicit Vector2(const Vector2<T, OtherVectorIsAtomic>& otherVector);

        /*!
         * \brief Move constructor.
         * \param nonatomicVector Other vector which values will be used.
         */
        constexpr explicit Vector2(Vector2<T, false>&& nonatomicVector) noexcept;
        /*!
         * \brief Copy constructor.
         * \param sfmlVector sf::Vector2 from which values will be copied.
         */
        constexpr explicit Vector2(const sf::Vector2<T>& sfmlVector);

        /*!
         * \brief Move constructor.
         * \param sfmlVector sf::Vector2 which values will be used.
         */
        constexpr explicit Vector2(sf::Vector2<T>&& sfmlVector);

        /*!
         * \brief Copy assignment operator.
         * \param otherVector Other vector from which values will be copied.
         * \return Reference to vector after assignment.
         */
        constexpr Vector2<T, IsAtomic>& operator=(const Vector2<T, IsAtomic>& otherVector);

        /*!
         * \brief Copy assignment operator.
         * \tparam OtherVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param otherVector Const reference to other vector with the same template type.
         * \return Reference to vector after assignment.
         */
        template <bool OtherVectorIsAtomic>
        constexpr Vector2<T, IsAtomic>& operator=(const Vector2<T, OtherVectorIsAtomic>& otherVector);

        /*!
         * \brief Move assignment operator.
         * \param nonatomicVector Other vector which values will be used.
         * \return Reference to vector after assignment.
         */
        constexpr Vector2<T, IsAtomic>& operator=(Vector2<T, false>&& nonatomicVector);

        /*!
         * \brief Copy assignment operator.
         * \param sfmlVector sf::Vector2 from which values will be copied.
         * \return Reference to vector after assignment.
         */
        constexpr Vector2<T, IsAtomic>& operator=(const sf::Vector2<T>& sfmlVector);

        /*!
         * \brief Move assignment operator.
         * \param sfmlVector sf::Vector2 which values will be used.
         * \return Reference to vector after assignment.
         */
        constexpr Vector2<T, IsAtomic>& operator=(sf::Vector2<T>&& sfmlVector);

        /*!
         * \brief Equality operator.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same template type.
         * \return True if vectors are equal (x == rightVector.x && y == rightVector.y). Otherwise - false.
         */
        template <bool RightVectorIsAtomic>
        constexpr bool operator==(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Inequality operator.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same template type.
         * \return True if vectors are not equal (x != rightVector.x && y != rightVector.y). Otherwise - false.
         */
        template <bool RightVectorIsAtomic>
        constexpr bool operator!=(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Multiplication operator by another Vector2.
         * \tparam U Type that is used in rightVector.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same or different template type.
         * \return Scalar of the same template type as "left" vector.
         */
        template <bool RightVectorIsAtomic>
        constexpr T operator*(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Multiplication operator by scalar.
         * \tparam U Type of a scalar.
         * \param scalar Value of a scalar.
         * \return New vector as result of math operation.
         */
        template <typename U>
        constexpr Vector2<T, false> operator*(U scalar) const;

        /*!
         * \brief Division operator by scalar.
         * \tparam U Type of a scalar.
         * \param scalar Value of a scalar.
         * \return New vector as result of math operation.
         */
        template <typename U>
        constexpr Vector2<T, false> operator/(U scalar) const;

        /*!
         * \brief Addition operator.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same template type.
         * \return New vector as result of math operation.
         */
        template <bool RightVectorIsAtomic>
        constexpr Vector2<T, false> operator+(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Subtraction operator.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same template type.
         * \return New vector as result of math operation.
         */
        template <bool RightVectorIsAtomic>
        constexpr Vector2<T, false> operator-(const Vector2<T, RightVectorIsAtomic>& rightVector) const;

        /*!
         * \brief Addition and assignment operator.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        template <bool RightVectorIsAtomic>
        constexpr Vector2& operator+=(const Vector2<T, RightVectorIsAtomic>& rightVector);

        /*!
         * \brief Subtraction and assignment operator.
         * \tparam RightVectorIsAtomic Flag that defines if rightVector is atomic or not.
         * \param rightVector Const reference to other vector with the same template type.
         * \return Reference to vector after math operation and assignment.
         */
        template <bool RightVectorIsAtomic>
        constexpr Vector2& operator-=(const Vector2<T, RightVectorIsAtomic>& rightVector);

        /*!
         * \brief Multiplication and assignment operator by scalar.
         * \tparam U Type of a scalar.
         * \param scalar Value of a scalar.
         * \return Reference to vector after math operation and assignment.
         */
        template <typename U>
        constexpr Vector2& operator*=(U scalar);

        /*!
         * \brief Division and assignment operator by scalar.
         * \tparam U Type of a scalar.
         * \param scalar Value of a scalar.
         * \return Reference to vector after math operation and assignment.
         */
        template <typename U>
        constexpr Vector2& operator/=(U scalar);

        /*!
         * \brief Sets each of vector parameters to zero.
         */
        constexpr void Zero();

        /*! X value of vector. */
        Type x;
        /*! Y value of vector. */
        Type y;
    };

    /*!
     * \brief Subtraction operator.
     * \tparam T Type that is used be vector.
     * \tparam IsAtomic Flag that defines if vector is atomic or not.
     * \param vector Const reference to a vector.
     * \return New vector with same but negative values as result of math operation.
     */
    template <typename T, bool IsAtomic>
    constexpr Vector2<T, false> operator-(const Vector2<T, IsAtomic>& vector);

    /*!
     * \brief Multiplication operator.
     * \tparam U Type of a scalar.
     * \tparam T Type that is used be vector.
     * \tparam IsAtomic Flag that defines if vector is atomic or not.
     * \param scalar Value of a scalar.
     * \param vector Const reference to a vector.
     * \return New vector as result of math operation.
     */
    template <typename U, typename T, bool IsAtomic>
    constexpr Vector2<T, false> operator*(U scalar, const Vector2<T, IsAtomic>& vector);

#include <Utility/Math/Vector2.inl>

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