#include "state_receiver.h"

#include "receiver.h"
#include "channels.h"
#include "ui.h"
#include "buttons.h"
#include <string.h>
#include "settings_eeprom.h"
#include "timer.h"

using Ui::display;

static Timer displaySwapTimer = Timer(100);

void StateMachine::ReceiverStateHandler::onEnter() {
	displaySwapTimer.reset();
}
void StateMachine::ReceiverStateHandler::onUpdate() {
	if (displaySwapTimer.hasTicked()) {
		displaySwapTimer.reset();
		Ui::needUpdate();
	}
}
void StateMachine::ReceiverStateHandler::onInitialDraw() {
    Ui::clear();
    Ui::needDisplay();
}

void StateMachine::ReceiverStateHandler::onUpdateDraw() {
	Ui::clear();

	Ui::display.setTextColor(WHITE);
	Ui::display.setTextSize(1);
	Ui::display.setCursor(5,2);
	Ui::display.print(Receiver::rssiA);
	Ui::display.setCursor(5,10);
	Ui::display.print(Receiver::rssiARaw);
	Ui::display.setCursor(5,18);
	Ui::display.print(EepromSettings.rssiAMin);
	Ui::display.setCursor(5,26);
	Ui::display.print(EepromSettings.rssiAMax);
	Ui::display.setCursor(5,42);
	Ui::display.print(Receiver::sensor_read);
#ifdef USE_DIVERSITY
	Ui::display.setCursor(69,2);
	Ui::display.print(Receiver::rssiB);
	Ui::display.setCursor(69,10);
	Ui::display.print(Receiver::rssiBRaw);
	Ui::display.setCursor(69,18);
	Ui::display.print(EepromSettings.rssiBMin);
	Ui::display.setCursor(69,26);
	Ui::display.print(EepromSettings.rssiBMax);
#endif
    Ui::needDisplay();

}

void StateMachine::ReceiverStateHandler::onButtonChange(Button button, Buttons::PressType pressType){
	Ui::needUpdate();
	if (button == Button::MODE && pressType == Buttons::PressType::LONG){
		StateMachine::switchState(StateMachine::State::MENU);
	}
}

