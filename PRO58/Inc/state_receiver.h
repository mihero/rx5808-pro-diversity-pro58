#ifndef STATE_RECEIVER_H
#define STATE_RECEIVER_H


#include "state.h"
#include "ui_state_menu.h"


#define PEAK_LOOKAHEAD 4


namespace StateMachine {
    class ReceiverStateHandler : public StateMachine::StateHandler {
        private:

            void onUpdateAuto();


        public:

            void onEnter();
            void onUpdate();

            void onInitialDraw();
            void onUpdateDraw();

            void onButtonChange(Button button, Buttons::PressType pressType);
            //void onFSPinsChange(uint8_t state);
    };
}


#endif
