#pragma once
#include <atomic>

namespace sf { template <typename T> class Vector2; }

namespace C2D
{
    template <typename T>
    class Vector2;

    /*!
     * \brief Simple 2d vector with atomic parameters.
     * \tparam T - type of used data.
     * 
     * This class was created for some places where thread-safe 2d vector is required.
     */
    template <typename T>
    class AtomicVector2
    {
    public:
        /*! Default destructor. */
        ~AtomicVector2() = default;

        /*! Default constructor with default values as zero. */
        AtomicVector2();
        
        /*! 
         * \brief Constructor to create the atomic vector from two values.
         * \param xValue - value for x parameter.
         * \param yValue - value for y parameter.
         */
        AtomicVector2(T xValue, T yValue);

        /*!
         * \brief Copy constructor.   
         * \param other - const reference to other atomic vector with the same template type.
         */
        AtomicVector2(const AtomicVector2& other);

        /*!
         * \brief Move constructor. 
         * \param other - double reference to other atomic vector value with the same template type.
         */
        AtomicVector2(AtomicVector2&& other) noexcept;

        /*!
         * \brief Copy constructor.
         * \param other - const reference to sf::Vector2 vector with the same template type.
         */
        AtomicVector2(const sf::Vector2<T>& other);

        /*!
         * \brief Move constructor.
         * \param other - double reference to sf::Vector2 value with the same template type.
         */
        AtomicVector2(sf::Vector2<T>&& other);

        /*!
         * \brief Copy constructor.
         * \param other - const reference to Vector2 with the same template type.
         */
        AtomicVector2(const Vector2<T>& other);

        /*!
         * \brief Move constructor.
         * \param other - double reference to Vector2 value with the same template type.
         */
        AtomicVector2(Vector2<T>&& other);

        /*! 
         * \brief Copy constructor.
         * \tparam U - different type of used data.
         * \param other - const reference to other atomic vector with a different template type.
         * 
         * A different type of atomic vector as a parameter.
         */
        template <typename U>
        explicit AtomicVector2(const AtomicVector2<U>& other);

        /*!
         * \brief Move constructor. 
         * \tparam U - different type of used data.
         * \param other - double reference to other atomic vector value with a different template type.
         * 
         * A different type of atomic vector as a parameter.
         */
        template <typename U>
        explicit AtomicVector2(AtomicVector2<U>&& other);

        /*! 
         * \brief Copy assignment operator. 
         * \param other - const reference to other atomic vector with the same template type.
         * \return Reference to atomic vector after assignment.
         * 
         * The same type of atomic vector as a parameter.
         */
        AtomicVector2& operator=(const AtomicVector2& other);

        /*! 
         * \brief Move assignment operator. 
         * \param other - double reference to other atomic vector value with the same template type.
         * \return Reference to atomic vector after assignment.
         * 
         * The same type of atomic vector as a parameter.
         */
        AtomicVector2& operator=(AtomicVector2&& other) noexcept;

        /*! 
         * \brief Copy assignment operator.
         * \tparam U - different type of used data.
         * \param other - const reference to other atomic vector with a different template type.
         * \return Reference to atomic vector after assignment.
         * 
         *  A different type of atomic vector as a parameter.
         */
        template <typename U>
        AtomicVector2& operator=(const AtomicVector2<U>& other);

        /*!
         * \brief Move assignment operator. 
         * \tparam U - different type of used data.
         * \param other - double reference to other atomic vector value with a different template type.
         * \return Reference to atomic vector after assignment.
         * 
         * A different type of atomic vector as a parameter.
         */
        template <typename U>
        AtomicVector2& operator=(AtomicVector2<U>&& other);

        /*!
         * \brief Equality operator.
         * 
         * \param right - const reference to other atomic vector with the same template type.
         * \return True if atomic vectors are equal. Otherwise - false.
         */
        bool operator==(const AtomicVector2& right);

        /*!
         * \brief Inequality operator.
         * 
         * \param right - const reference to other atomic vector with the same template type.
         * \return True if atomic vectors are unequal. Otherwise - false.
         */
        bool operator!=(const AtomicVector2& right);

        /*!
         * \brief Multiplication operator.
         * 
         * \param right - const reference to other atomic vector with the same template type.
         * \return Scalar of the same template type.
         */
        T operator*(const AtomicVector2& right) const;

        /*!
         * \brief Multiplication operator.
         * \param scalar - scalar value with the same template type.
         * \return New atomic vector as result of math operation.
         */
        AtomicVector2 operator*(T scalar) const;

        /*!
         * \brief Division operator.
         * \param scalar - scalar value with the same template type.
         * \return New atomic vector as result of math operation.
         */
        AtomicVector2 operator/(T scalar) const;

        /*!
         * \brief Addition operator.
         * \param right - const reference to other atomic vector with the same template type.
         * \return New atomic vector as result of math operation.
         */
        AtomicVector2 operator+(const AtomicVector2& right) const;

        /*!
         * \brief Subtraction operator.
         * \param right - const reference to other atomic vector with the same template type.
         * \return New atomic vector as result of math operation.
         */
        AtomicVector2 operator-(const AtomicVector2& right) const;

        /*!
         * \brief Addition and assignment operator.
         * \param right - const reference to other atomic vector with the same template type.
         * \return Reference to atomic vector after math operation and assignment.
         */
        AtomicVector2& operator+=(const AtomicVector2& right);

        /*!
         * \brief Subtraction and assignment operator.
         * \param right - const reference to other atomic vector with the same template type.
         * \return Reference to atomic vector after math operation and assignment.
         */
        AtomicVector2& operator-=(const AtomicVector2& right);

        /*!
         * \brief Division and assignment operator.
         * \param right - const reference to other atomic vector with the same template type.
         * \return Reference to atomic vector after math operation and assignment.
         */
        AtomicVector2& operator/=(const AtomicVector2& right);

        /*!
         * \brief Division and assignment operator.
         * \param scalar - scalar value with the same template type.
         * \return Reference to atomic vector after math operation and assignment.
         */
        AtomicVector2& operator/=(T scalar);

        /*!
         * \brief Multiplication and assignment operator.
         * \param scalar - scalar value with the same template type.
         * \return Reference to atomic vector after math operation and assignment.
         */
        AtomicVector2& operator*=(T scalar);

        /*!
         * \brief Sets each of atomic vector parameters to zero.
         */
        void Zero();

        /*! X value of vector. */
        std::atomic<T> x;
        /*! Y value of vector. */
        std::atomic<T> y;
    };    

    /*!
     * \brief Subtraction operator.
     * \tparam T - type of used data.
     * \param right - const reference to other atomic vector with the same template type.
     * \return New atomic vector with same but negative values as result of math operation.
     */
    template <typename T>
    AtomicVector2<T> operator-(const AtomicVector2<T>& right);

    /*!
     * \brief Multiplication operator.
     * \tparam T - type of used data.
     * \param scalar - scalar value with the same template type.
     * \param right - const reference to other atomic vector with the same template type.
     * \return New atomic vector as result of math operation.
     */
    template <typename T>
    AtomicVector2<T> operator*(T scalar, const AtomicVector2<T>& right);

#include "AtomicVector2.inl"

    /*! Atomic vector for float type. */
    using AtomicVector2F = AtomicVector2<float>;
    /*! Atomic vector for int type. */
    using AtomicVector2I = AtomicVector2<int>;
}