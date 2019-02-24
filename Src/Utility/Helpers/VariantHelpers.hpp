#pragma once
#include <variant>
#include <fstream>

// ---------------------------------------------------------------------------------------------------------------------

/*!
 * \brief Simple structure that helps stream variant data.
 * \tparam T Variant that should be streamed.
 */
template <class T>
struct VariantStreamer { const T& value; };

/*! Straightforward deduction guide for a VariantStreamer. */
template <class T> VariantStreamer(T) -> VariantStreamer<T>;

// ---------------------------------------------------------------------------------------------------------------------

/*!
 * \brief Streams a VariantStreamer.
 * \tparam T Type of variant within the VariantStreamer.
 * \param stream Stream to which VariantStreamer will be streamed.
 * \param variantStreamer VariantStreamer from which variant will be streamed.
 * \return Reference to provided stream.
 */
template <class T>
std::ostream& operator<<(std::ostream& stream, const VariantStreamer<T>& variantStreamer)
{
    stream << variantStreamer.value;
    return stream;
}

// ---------------------------------------------------------------------------------------------------------------------

/*!
 * \brief Streams a VariantStreamer which can contain recursive variants.
 * \tparam Ts Type of variant within the VariantStreamer.
 * \param stream Stream to which VariantStreamer will be streamed.
 * \param variantStreamer VariantStreamer from which variant will be streamed.
 * \return Reference to provided stream.
 */
template<class ... Ts>
std::ostream& operator<<(std::ostream& stream, const VariantStreamer<std::variant<Ts...>>& variantStreamer)
{
    std::visit([&stream](const auto& variant) { stream << VariantStreamer{variant}; }, variantStreamer.value);
    return stream;
}

// ---------------------------------------------------------------------------------------------------------------------

/*!
 * \brief Streams a variant.
 * \tparam T Type within the variant.
 * \param stream Stream to which variant will be streamed.
 * \param variant Variant from which value will be streamed.
 * \return Reference to provided stream.
 */
template <class T>
std::ostream& operator<<(std::ostream& stream, const std::variant<T>& variant)
{
    stream << VariantStreamer{variant};
    return stream;
}

// ---------------------------------------------------------------------------------------------------------------------

/*!
 * \brief Streams a variant with multiple values within it.
 * \tparam T Type within the variant.
 * \tparam Ts Types within the variant.
 * \param stream Stream to which variant will be streamed.
 * \param variant Variant from which value will be streamed.
 * \return Reference to provided stream.
 */
template <class T, class ... Ts>
std::ostream& operator<<(std::ostream& stream, const std::variant<T, Ts...>& variant)
{
    stream << VariantStreamer{variant};
    return stream;
}

// ---------------------------------------------------------------------------------------------------------------------
