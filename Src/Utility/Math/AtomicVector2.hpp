#pragma once
#include <atomic>

namespace Utility
{
    /*!
     * \brief Simple 2d vector with atomic parameters.
     * 
     * Because of nature of atomic data type this 2d vector was created.
     * Atomic type cannot be directly copied or applied to typical math operations (i.e. T == float || T == double),
     * so this class was created for some places where thread-safe 2d vector is required.
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
        AtomicVector2(const T xValue, const T yValue);

        /*!
         * \brief Copy constructor.   
         * \param other - const reference to other atomic vector with the same template type.
         * 
         * The same type of atomic vector as a parameter.
         */
        AtomicVector2(const AtomicVector2& other);

        /*!
         * \brief Move constructor. 
         * \param other - double reference to other atomic vector value with the same template type.
         * 
         * The same type of atomic vector as a parameter.
         */
        AtomicVector2(AtomicVector2&& other) noexcept;

        /*! 
         * \brief Copy constructor.
         * \param other - const reference to other atomic vector with a different template type.
         * 
         * A different type of atomic vector as a parameter.
         */
        template <typename U>
        explicit AtomicVector2(const AtomicVector2<U>& other);

        /*!
         * \brief Move constructor. 
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
         * \param other - const reference to other atomic vector with a different template type.
         * \return Reference to atomic vector after assignment.
         * 
         *  A different type of atomic vector as a parameter.
         */
        template <typename U>
        AtomicVector2& operator=(const AtomicVector2<U>& other);

        /*!
         * \brief Move assignment operator. 
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
        AtomicVector2 operator*(const T scalar) const;

        /*!
         * \brief Division operator.
         * \param scalar - scalar value with the same template type.
         * \return New atomic vector as result of math operation.
         */
        AtomicVector2 operator/(const T scalar) const;

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
        AtomicVector2& operator/=(const T scalar);

        /*!
         * \brief Multiplication and assignment operator.
         * \param scalar - scalar value with the same template type.
         * \return Reference to atomic vector after math operation and assignment.
         */
        AtomicVector2& operator*=(const T scalar);

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
     * \param right - const reference to other atomic vector with the same template type.
     * \return New atomic vector with same but negative values as result of math operation.
     */
    template <typename T>
    AtomicVector2<T> operator-(const AtomicVector2<T>& right);

    /*!
     * \brief Multiplication operator.
     * 
     * \param scalar - scalar value with the same template type.
     * \param right - const reference to other atomic vector with the same template type.
     * \return New atomic vector as result of math operation.
     */
    template <typename T>
    AtomicVector2<T> operator*(const T scalar, const AtomicVector2<T>& right);

#include "AtomicVector2.inl"

    /*! Atomic vector for float type. */
    using AtomicVector2F = AtomicVector2<float>;
    /*! Atomic vector for int type. */
    using AtomicVector2I = AtomicVector2<int>;
}