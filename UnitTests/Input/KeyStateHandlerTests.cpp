#include "CppUnitTest.h"
#include "Input/Utilities/KeyStateHandler.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Input;

namespace UnitTests
{		
    TEST_CLASS(KeyStateHandlerTests)
    {
    public:		
        TEST_METHOD(KeyStateHandlerDefaultValue)
        {
            KeyStateHandler keyStateHandler;

            Assert::IsTrue(keyStateHandler.State() == KeyState::NotTouched);
        }

        TEST_METHOD(KeyStateHandlerUpdateState)
        {
            KeyStateHandler keyStateHandler;
		    
            keyStateHandler.UpdateState(KeyState::NotTouched);
            Assert::IsTrue(keyStateHandler.State() == KeyState::NotTouched);

            // Button was pressed
            keyStateHandler.UpdateState(KeyState::Pressed);
            Assert::IsTrue(keyStateHandler.State() == KeyState::Pressed);
            // Held
            keyStateHandler.UpdateState(KeyState::NotTouched);
            Assert::IsTrue(keyStateHandler.State() == KeyState::HeldDown);
            // Released
            keyStateHandler.UpdateState(KeyState::Released);
            Assert::IsTrue(keyStateHandler.State() == KeyState::Released);
            // Immediately pressed again
            keyStateHandler.UpdateState(KeyState::Pressed);
            Assert::IsTrue(keyStateHandler.State() == KeyState::Pressed);
            // And released
            keyStateHandler.UpdateState(KeyState::Released);
            Assert::IsTrue(keyStateHandler.State() == KeyState::Released);

            keyStateHandler.UpdateState(KeyState::NotTouched);
            Assert::IsTrue(keyStateHandler.State() == KeyState::NotTouched);
        }
    };
}