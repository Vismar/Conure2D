#Code convention

General rules:
* Indents are 4 spaces. No tabs should be used anywhere.
* Each line must be at most 120 characters long.
* Comments within the code can be // or /*.
* For documentation puproses comments should be in Qt Doxygen style.
* File names should be PascalCase.hpp for header files and PascalCase.cpp for source files.

Macros:
* Use ALL_CAPS separated by underscore:
  ```cpp
  #define I_AM_MACRO 0x0
  ```
* If macro is replacement is not just literal, encolse it in paramtheses
  ```cpp
  #define I_AM_COOL_MACRO (0x1 << 3)
  ```
  
Type names:
* Structs, enumerations and clases should be in PascalCase
  ```cpp
  struct SomeStruct
  enum SomeEnum
  class SomeClass 
  ```
* Enum values also should be in PascalCase
  ```cpp
  enum SomeEnum
  {
      EnumValue1,
	  EnumValue2,
	  EnumValue3
  };
  ```

Member names:
* Any public member should be in camelCase
  ```cpp
  class ClassName
  {
  public:
      int publicMember;
  };
  ```
* Any protected or private member should be in _camelCase with underscore in the front
  ```cpp
  class ClassName
  {
  protected:
      int _protectedMember;
  private:
      int _privateMember;
  };
  ```

Function names:
* Public functions should be in PascalCase
  ```cpp
  void FunctionName();
  ```
* Protected and private functions should be in _PascalCase with underscore in the front
  ```cpp
  class ClassName
  {
  private:
      void _PrivateFunctionName();
  };
  ```

Braces:
* Any opening or closing brace should come at the start of the next line

Local variables:
* Local variables should be only in camelCase
  ```cpp
  void FunctionName()
  {
      int localVariable;
  }
  ```

Multiple lines:
* Statements that span multiple lines, break after the logical operator 
  and align each line with the start of the first line
  ```cpp
  if (left1 == right1 &&
      left2 == right2 &&
      left3 == right3 &&
      left4 == right4 &&
      left5 == right5) 
  ```
* For function declarations that span multiple lines, align subsequent lines with the first parameter
  ```cpp
  void FunctionName(int param1,
                    bool param2,
                    float param3,
                    double param4,
                    char param5)
  ```
* For function calls that span multiple lines, align each subsequent line.
  ```cpp
  FunctionName(1,
               true,
               0.5f,
               0.99,
               'q');
  ```

else statement:
* else and else if comes on the next line
