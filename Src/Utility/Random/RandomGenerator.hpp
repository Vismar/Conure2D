#pragma once
#include <random>

namespace Utility
{
    /*!
     * \brief Random number generator.
     * 
     * This random number generator uses Mersenne Twister algorithm from <random> STL and
     * provides the simple interface to ease the use of it. This generator has static 
     * instance so it can be used anywhere without creating your own instance.
     * But Mersenne Twister algorithm is NOT thread-safe, so if this generator 
     * should be used from different threads, instantiate generator for every thread.
     */
    class RandomGenerator
    {
    public:
        RandomGenerator(const RandomGenerator& other) = delete;
        RandomGenerator(RandomGenerator&& other) = delete;
        RandomGenerator& operator=(const RandomGenerator& other) = delete;
        RandomGenerator& operator=(RandomGenerator&& other) = delete;
        ~RandomGenerator() = default;

        /*!
         * \brief Default constructor which defines random seed for generators.
         */
        RandomGenerator();

        /*!
         * \brief Gets an instance of a random generator.
         * \return The reference to the static instance of random generator.
         */
        static RandomGenerator& Instance();

        /*!
         * \brief Sets specified seed to generators.
         * \param seed - new seed which will be used by random number generators.
         */
        void SetSeed(uint32_t seed);

        /*!
         * \brief Gets seed which is in use by generators.
         * \return The seed which represented by 32-bit number.
         */
        uint32_t GetSeed() const;

        /*!
         * \brief Generates random 32-bit number in range [0, 2^32].
         * \return A random 32-bit number in range [0, 2^32].
         */
        uint32_t Get();

        /*!
         * \brief Generates random 64-bit number in range [0, 2^64].
         * \return A random 64-bit number in range [0, 2^64].
         */
        uint64_t Get64();

        /*!
         * \brief Generates random number in specified range.
         * \tparam T - type of number that will be generated.
         * \param from - min value that can be generated.
         * \param to - max value that can be generated.
         * \return A random number in specified range.
         * 
         * It is a template function, so it uses partial specialization for certain types:
         * - For 64-bit types (uin64_t, int64_t, double, size_t(on 64-bit platforms) it will use 64-bit generator.
         * - For 32-bit types will be used 32-bit generator.
         * - For real numbers will be used uniform_real_distribution.
         */
        template <typename T>
        T Get(T from, T to);

        /*!
         * \brief Generates random number by using specified uniform_int_distribution.
         * \tparam T - type of number that will be generated.
         * \param distribution - reference to uniform_int_distribution.
         * \return A random number generated in a range which was specified in uniform_int_distribution.
         */
        template <typename T>
        T Get(std::uniform_int_distribution<T>& distribution);

        /*!
         * \brief Generates random number by using specified uniform_real_distribution.
         * \tparam T - type of number that will be generated.
         * \param distribution - reference to uniform_real_distribution.
         * \return A random number generated in a range which was specified in uniform_real_distribution.
         */
        template <typename T>
        T Get(std::uniform_real_distribution<T>& distribution);

    private:
        /*! Seed that is used by number generators. */
        uint32_t _seed;
        /*! Mersenne Twister pseudo-random number generator for 32-bit numbers. */
        std::mt19937 _mtEngine;
        /*! Mersenne Twister pseudo-random number generator for 64-bit numbers. */
        std::mt19937_64 _mtEngine64;
    };

#include "RandomGenerator.inl"
}

#define RANDOM Utility::RandomGenerator::Instance()