#pragma once
#include <initializer_list>
#include <type_traits>
#include <fstream>

// ---------------------------------------------------------------------------------------------------------------------

/*! A shorter name for a type that stores pairs of enum name as key and its string representation as value. */
template <class Enum>
using EnumNameMap = std::initializer_list<std::pair<Enum, const char*>>;

// ---------------------------------------------------------------------------------------------------------------------

/*!
 * \brief Gets a string representation out of the specified list for a specific enum value.
 * \tparam Enum Enum type.
 * \param enumValue Value of an enumeration.
 * \param map Initializer list for enumeration and its string representation.
 * \return String representation of specified enum value if it exists or the empty string.
 */
template <class Enum>
constexpr const char* GetEnumValueName(Enum enumValue, const EnumNameMap<Enum>& map)
{
    for (const auto& pair : map)
    {
        if (enumValue == pair.first)
        {
            return pair.second;
        }
    }

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

#define STREAM_ENUM_DECL(enumName) \
std::ostream& operator<<(std::ostream& stream, enumName enumeration);

/*!
 * \brief Generates function definition to overload operator<< for specified enumeration.
 * \param enumName Enum type.
 * \param enumNameMap Name of variable that contains string representation of specified enumeration type.
 */
#define STREAM_ENUM_DEF(enumName, enumNameMap)                                          \
std::ostream& operator<<(std::ostream& stream, enumName enumeration)                    \
{                                                                                       \
    static_assert(std::is_enum_v<enumName>, "Passed type is not an enumeration");       \
    static_assert(std::is_same_v<decltype(enumNameMap), const EnumNameMap<enumName>>,   \
                  "EnumNameMap is of wrong type. "                                      \
                  "Should be std::initializer_list<std::pair<enumName, const char*>>"); \
    stream << GetEnumValueName(enumeration, enumNameMap);                                    \
                                                                                        \
    return stream;                                                                      \
}

// ---------------------------------------------------------------------------------------------------------------------
