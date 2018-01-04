#include "InputHandler.hpp"
#include "Managers/InputDeviceManager.hpp"
#include "Managers/InputMapManager.hpp"
#include "SFML/Window/Event.hpp"

using namespace Input;

InputDeviceManager DeviceManager;
InputMapManager MapManager;

/*****************************************/
/*             DeviceManager             */
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputHandler::HandleInputEvent(const sf::Event& event)
{
    DeviceManager.HandleInputEvent(event);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputHandler::FinishHandle()
{
    DeviceManager.FinishUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
