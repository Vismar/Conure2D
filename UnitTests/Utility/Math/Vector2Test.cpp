#include <Utility/Math/Vector2.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>

constexpr float xValue1(0.0f), yValue1(5.9f);
constexpr float xValue2(434.548f), yValue2(-245.1445f);

/*!
 * Testing constructors.
 */
TEST(Vector2, Constructors)
{
    // Default constructor with 0 value for x and y
    C2D::Vector2<float, false> zeroVector;
    EXPECT_EQ(zeroVector.x, zeroVector.y);
    EXPECT_EQ(0.0f, zeroVector.x);

    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    // Copy constructors from nonatomic and atomic vectors to nonatomic vector
    C2D::Vector2<float, false> vec3(vec1);
    EXPECT_EQ(xValue1, vec3.x);
    EXPECT_EQ(yValue1, vec3.y);
    C2D::Vector2<float, false> vec4(vec2);
    EXPECT_EQ(xValue2, vec4.x);
    EXPECT_EQ(yValue2, vec4.y);

    // Copy constructors from nonatomic and atomic vectors to atomic vector
    C2D::Vector2<float, true> vec5(vec1);
    EXPECT_EQ(xValue1, vec5.x.load());
    EXPECT_EQ(yValue1, vec5.y.load());
    C2D::Vector2<float, true> vec6(vec2);
    EXPECT_EQ(xValue2, vec6.x.load());
    EXPECT_EQ(yValue2, vec6.y.load());

    // Move constructors from nonatomic vectors to nonatomic and atomic vectors
    C2D::Vector2<float, false> vec7(std::move(vec1));
    EXPECT_EQ(xValue1, vec7.x);
    EXPECT_EQ(yValue1, vec7.y);
    C2D::Vector2<float, true> vec8(std::move(vec4));
    EXPECT_EQ(xValue2, vec8.x.load());
    EXPECT_EQ(yValue2, vec8.y.load());

    // Create sfml vectors
    sf::Vector2<float> sfmlVec1(xValue1, yValue1);
    sf::Vector2<float> sfmlVec2(xValue2, yValue2);

    // Copy constructor from sf::Vector2 to nonatomic and atomic vectors
    C2D::Vector2<float, false> vec9(sfmlVec1);
    EXPECT_EQ(xValue1, vec9.x);
    EXPECT_EQ(yValue1, vec9.y);
    C2D::Vector2<float, true> vec10(sfmlVec2);
    EXPECT_EQ(xValue2, vec10.x.load());
    EXPECT_EQ(yValue2, vec10.y.load());

    // Copy constructor from sf::Vector2 to nonatomic and atomic vectors
    C2D::Vector2<float, false> vec11(sf::Vector2(xValue1, yValue1));
    EXPECT_EQ(xValue1, vec11.x);
    EXPECT_EQ(yValue1, vec11.y);
    C2D::Vector2<float, true> vec12(sf::Vector2(xValue2, yValue2));
    EXPECT_EQ(xValue2, vec12.x.load());
    EXPECT_EQ(yValue2, vec12.y.load());
}

/*!
 * Testing assignment operators.
 */
TEST(Vector2, Assignments)
{
    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    // Copy constructors from nonatomic and atomic vectors to nonatomic vector
    C2D::Vector2<float, false> vec3;
    vec3 = vec1;
    EXPECT_EQ(xValue1, vec3.x);
    EXPECT_EQ(yValue1, vec3.y);
    C2D::Vector2<float, false> vec4;
    vec4 = vec2;
    EXPECT_EQ(xValue2, vec4.x);
    EXPECT_EQ(yValue2, vec4.y);

    // Copy constructors from nonatomic and atomic vectors to atomic vector
    C2D::Vector2<float, true> vec5;
    vec5 = vec1;
    EXPECT_EQ(xValue1, vec5.x.load());
    EXPECT_EQ(yValue1, vec5.y.load());
    C2D::Vector2<float, true> vec6;
    vec6 = vec2;
    EXPECT_EQ(xValue2, vec6.x.load());
    EXPECT_EQ(yValue2, vec6.y.load());

    // Move constructors from nonatomic vectors to nonatomic and atomic vectors
    C2D::Vector2<float, false> vec7;
    vec7 = C2D::Vector2<float, false>(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec7.x);
    EXPECT_EQ(yValue1, vec7.y);
    C2D::Vector2<float, true> vec8;
    vec8 = C2D::Vector2<float, false>(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec8.x.load());
    EXPECT_EQ(yValue2, vec8.y.load());

    // Create sfml vectors
    sf::Vector2<float> sfmlVec1(xValue1, yValue1);
    sf::Vector2<float> sfmlVec2(xValue2, yValue2);

    // Copy constructor from sf::Vector2 to nonatomic and atomic vectors
    C2D::Vector2<float, false> vec9;
    vec9 = sfmlVec1;
    EXPECT_EQ(xValue1, vec9.x);
    EXPECT_EQ(yValue1, vec9.y);
    C2D::Vector2<float, true> vec10;
    vec10 = sfmlVec2;
    EXPECT_EQ(xValue2, vec10.x.load());
    EXPECT_EQ(yValue2, vec10.y.load());

    // Copy constructor from sf::Vector2 to nonatomic and atomic vectors
    C2D::Vector2<float, false> vec11;
    vec11 = sf::Vector2(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec11.x);
    EXPECT_EQ(yValue1, vec11.y);
    C2D::Vector2<float, true> vec12;
    vec12 = sf::Vector2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec12.x.load());
    EXPECT_EQ(yValue2, vec12.y.load());
}

/*!
 * Testing equality operators.
 */
TEST(Vector2, Equality)
{
    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    // Copy constructors from nonatomic and atomic vectors to nonatomic vector
    C2D::Vector2<float, false> vec3(vec1);
    EXPECT_EQ(xValue1, vec3.x);
    EXPECT_EQ(yValue1, vec3.y);
    C2D::Vector2<float, true> vec4(vec2);
    EXPECT_EQ(xValue2, vec4.x);
    EXPECT_EQ(yValue2, vec4.y);

    // Copy constructors from nonatomic vectors to nonatomic and atomic vector
    C2D::Vector2<float, true> vec5(vec1);
    EXPECT_EQ(xValue1, vec3.x);
    EXPECT_EQ(yValue1, vec3.y);
    C2D::Vector2<float, false> vec6(vec2);
    EXPECT_EQ(xValue2, vec4.x);
    EXPECT_EQ(yValue2, vec4.y);

    // Nonatomic == nonatomic
    EXPECT_EQ(vec1, vec3);
    // Atomic == atomic
    EXPECT_EQ(vec2, vec4);
    // Nonatomic == atomic
    EXPECT_EQ(vec1, vec5);
    // Atomic == nonatomic
    EXPECT_EQ(vec2, vec6);

    // Nonatomic != nonatomic
    EXPECT_NE(vec1, vec6);
    // Atomic != atomic
    EXPECT_NE(vec2, vec5);
    // Nonatomic != atomic
    EXPECT_NE(vec1, vec4);
    // Atomic != nonatomic
    EXPECT_NE(vec2, vec3);
}

/*!
 * Testing multiplication.
 */
TEST(Vector2, Multiplication)
{
    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    // Nonatomic * atomic
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(-1446.3525f, result);
    // Atomic * nonatomic
    result = vec2 * vec1;
    EXPECT_FLOAT_EQ(-1446.3525f, result);
    // Nonatomic * nonatomic
    result = vec1 * vec1;
    EXPECT_FLOAT_EQ(34.81, result);
    // Atomic * atomic
    result = vec2 * vec2;
    EXPECT_FLOAT_EQ(248927.8f, result);

    // Nonatomic * scalar
    C2D::Vector2<float, false> zeroVector;
    C2D::Vector2<float, false> resultVector = vec1 * xValue1;
    EXPECT_EQ(zeroVector, resultVector);
    // Atomic * scalar
    resultVector = vec2 * xValue1;
    EXPECT_EQ(zeroVector, resultVector);

    // Nonatomic *= scalar
    C2D::Vector2<float, false> tempVector1 = vec1;
    tempVector1 *= xValue1;
    EXPECT_EQ(zeroVector, tempVector1);
    // Atomic *= scalar
    C2D::Vector2<float, true> tempVector2 = vec2;
    tempVector2 *= xValue1;
    EXPECT_EQ(zeroVector, tempVector2);

    // Scalar * nonatomic
    resultVector = xValue1 * vec1;
    EXPECT_EQ(zeroVector, resultVector);
    // Scalar * atomic
    resultVector = xValue1 * vec2;
    EXPECT_EQ(zeroVector, resultVector);
}

/*!
 * Testing division.
 */
TEST(Vector2, Division)
{
    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    C2D::Vector2<float, false> checkTempVec1(0.0f, 1.0f);
    C2D::Vector2<float, false> checkTempVec2(73.652206f, -41.549915f);

    // Nonatomic / scalar
    C2D::Vector2<float, false> resultVector = vec1 / yValue1;
    EXPECT_EQ(checkTempVec1, resultVector);
    // Atomic / scalar
    resultVector = vec2 / yValue1;
    EXPECT_EQ(checkTempVec2, resultVector);

    // Nonatomic /= scalar
    C2D::Vector2<float, false> tempVector1 = vec1;
    tempVector1 /= yValue1;
    EXPECT_EQ(checkTempVec1, tempVector1);
    // Atomic /= scalar
    C2D::Vector2<float, true> tempVector2 = vec2;
    tempVector2 /= yValue1;
    EXPECT_EQ(checkTempVec2, tempVector2);
}

/*!
 * Testing adding.
 */
TEST(Vector2, Adding)
{
    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    // Nonatomic + atomic
    C2D::Vector2<float, false> result = vec1 + vec2;
    EXPECT_EQ(xValue1 + xValue2, result.x);
    EXPECT_EQ(yValue1 + yValue2, result.y);
    // Atomic + nonatomic
    result = vec2 + vec1;
    EXPECT_EQ(xValue2 + xValue1, result.x);
    EXPECT_EQ(yValue2 + yValue1, result.y);
    // Nonatomic + nonatomic
    result = vec1 + vec1;
    EXPECT_EQ(xValue1 + xValue1, result.x);
    EXPECT_EQ(yValue1 + yValue1, result.y);
    // Atomic + atomic
    result = vec2 + vec2;
    EXPECT_EQ(xValue2 + xValue2, result.x);
    EXPECT_EQ(yValue2 + yValue2, result.y);

    C2D::Vector2<float, true> atomicResult;
    // Nonatomic += nonatomic
    result = vec1;
    result += vec1;
    EXPECT_EQ(xValue1 + xValue1, result.x);
    EXPECT_EQ(yValue1 + yValue1, result.y);
    // Nonatomic += atomic
    result = vec1;
    result += vec2;
    EXPECT_EQ(xValue1 + xValue2, result.x);
    EXPECT_EQ(yValue1 + yValue2, result.y);
    // Atomic += nonatomic
    atomicResult = vec2;
    atomicResult += vec1;
    EXPECT_EQ(xValue2 + xValue1, atomicResult.x.load());
    EXPECT_EQ(yValue2 + yValue1, atomicResult.y.load());
    // Atomic += atomic
    atomicResult = vec2;
    atomicResult += vec2;
    EXPECT_EQ(xValue2 + xValue2, atomicResult.x.load());
    EXPECT_EQ(yValue2 + yValue2, atomicResult.y.load());
}

/*!
 * Testing subtraction.
 */
TEST(Vector2, Subtraction)
{
    // Constructor from pair of parameters for nonatomic vector
    C2D::Vector2<float, false> vec1(xValue1, yValue1);
    EXPECT_EQ(xValue1, vec1.x);
    EXPECT_EQ(yValue1, vec1.y);

    // Constructor from pair of parameters for atomic vector
    C2D::Vector2<float, true> vec2(xValue2, yValue2);
    EXPECT_EQ(xValue2, vec2.x);
    EXPECT_EQ(yValue2, vec2.y);

    // Nonatomic - atomic
    C2D::Vector2<float, false> result = vec1 - vec2;
    EXPECT_EQ(xValue1 - xValue2, result.x);
    EXPECT_EQ(yValue1 - yValue2, result.y);
    // Atomic - nonatomic
    result = vec2 - vec1;
    EXPECT_EQ(xValue2 - xValue1, result.x);
    EXPECT_EQ(yValue2 - yValue1, result.y);
    // Nonatomic - nonatomic
    result = vec1 - vec1;
    EXPECT_EQ(xValue1 - xValue1, result.x);
    EXPECT_EQ(yValue1 - yValue1, result.y);
    // Atomic - atomic
    result = vec2 - vec2;
    EXPECT_EQ(xValue2 - xValue2, result.x);
    EXPECT_EQ(yValue2 - yValue2, result.y);

    C2D::Vector2<float, true> atomicResult;
    // Nonatomic -= nonatomic
    result = vec1;
    result -= vec1;
    EXPECT_EQ(xValue1 - xValue1, result.x);
    EXPECT_EQ(yValue1 - yValue1, result.y);
    // Nonatomic -= atomic
    result = vec1;
    result -= vec2;
    EXPECT_EQ(xValue1 - xValue2, result.x);
    EXPECT_EQ(yValue1 - yValue2, result.y);
    // Atomic -= nonatomic
    atomicResult = vec2;
    atomicResult -= vec1;
    EXPECT_EQ(xValue2 - xValue1, atomicResult.x.load());
    EXPECT_EQ(yValue2 - yValue1, atomicResult.y.load());
    // Atomic -= atomic
    atomicResult = vec2;
    atomicResult -= vec2;
    EXPECT_EQ(xValue2 - xValue2, atomicResult.x.load());
    EXPECT_EQ(yValue2 - yValue2, atomicResult.y.load());

    // -nonatomic
    C2D::Vector2<float, false> minusVec1(-xValue1, -yValue1);
    EXPECT_EQ(minusVec1, -vec1);
    // -atomic
    C2D::Vector2<float, true> minusVec2(-xValue2, -yValue2);
    EXPECT_EQ(minusVec2, -vec2);
}