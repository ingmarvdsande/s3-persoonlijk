#include <iostream>
#include "rtos.hpp"

class BruinteInstelling {
    public:
        int getBruinteInstelling() {
            return 0;
        }
};

class Soilenoid {
    public:
        void enable() {
        }

        void disable() {
        }
};

class Speaker {
    public:
        void beep(int freq, int dur) {
        }
};

class VerwarmingsElement {
    public:
        void enable() {
        }

        void disable() {
        }
};

class LichtSensorInterface {
    public:
        int getLichtIntensiteit() {
            return 0;
        }
};

class BroodRoosterControl : public rtos::task<> {
    enum state_t {IDLE, HEATING, DONE};

    private:
        state_t state = IDLE;
        
        rtos::flag flagLichtIntensiteit;
        rtos::flag flagBruinTeInstelling;
        rtos::pool<int> poolLichtIntensiteitGemeten;

        BruinteInstelling& bruinteInstelling;
        Soilenoid& soilenoid;
        Speaker& speaker;
        VerwarmingsElement& verwarmingsElement;
        LichtSensorInterface& lichtSensor;

        void main() {
            for(;;) {
                switch(state) {
                    case IDLE:
                        soilenoid.disable();
                        wait (flagBruinTeInstelling); {
                            state = HEATING;
                        }
                        break;
                   case HEATING:
                        verwarmingsElement.enable();
                        while (true) {
                            wait(flagLichtIntensiteit);
                            int currentLight = lichtSensor.getLichtIntensiteit();
                            int setBruinte = bruinteInstelling.getBruinteInstelling();
                            if (setBruinte == currentLight) {
                                state = DONE;
                                break;
                            }
                        }
                        break;
                    case DONE:
                        verwarmingsElement.disable();
                        soilenoid.enable();
                        speaker.beep(440, 500); // Added random hz and duration
                        state = IDLE;
                        break;
                }
            }
        }

    public:
            BroodRoosterControl(
            BruinteInstelling& bi,
            Soilenoid& s,
            Speaker& sp,
            VerwarmingsElement& ve,
            LichtSensorInterface& li
        ) :
            rtos::task<>("BroodRoosterControl"),
            bruinteInstelling(bi),
            soilenoid(s),
            speaker(sp),
            verwarmingsElement(ve),
            lichtSensor(li),
            lichtIntensiteit(this, "lichtIntensiteit"),
            poolLichtIntensiteitGemeten("lichtIntensiteitPool")
        {}
};
