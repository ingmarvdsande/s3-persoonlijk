#include <iostream>
#include "rtos.hpp"

class PresenceControl : public rtos::task<> {
    enum state_t {IDLE, INUSE, CLEANING, SAVINGDATA};

    private: 
        state_t state = IDLE;

        rtos::flag flagCatDetected;
        rtos::flag flagNoCatDetected;
        rtos::flag flagWasteDetected;
        rtos::pool <string> poolCatDetected;
        rtos::pool <string> poolWasteDetected;

        Tiltcontrol& tiltcontrol;
        Server& server;
        WasteRecognitionSensor& wasteRecognitionSensor;
        {
            wasteRecognitionSensor.addWasteSensorListener(this);
        }
        
        PresenceControl(Tiltcontrol& tiltcontrol, Server& server, WasteRecognitionSensor& wasteRecognitionSensor)

            void main() {
                for (;;)
                {
                    switch (state)
                    {
                    case IDLE:
                        auto evt = wait(flagCatDetected);
                        if (evt == flagCatDetected);{
                            string catName = poolCatDetected.read();
                            state = INUSE;
                        }
                        break;
                    case INUSE:
                        auto evt = wait(flagNoCatDetected);
                        if (evt == flagNoCatDetected);
                        {
                            state = CLEANING;
                        }    
                        break;
                    case CLEANING:
                        tiltControl.startSieve();
                        wasteRecognitionSensor.startScanning();
                        auto evt = wait(flagWasteDetected);
                        if (evt == flagWasteDetected);
                        {
                            state = SAVINGDATA;
                        }
                        break;
                    case SAVINGDATA:
                        string waste = poolWasteDetected.read();
                        server.sendData(catName, waste);
                        state = IDLE;
                        break;
                    }
                }
            }

    public:
        void catDetected(string catName) {
            poolCatDetected.write(catName);
            flagCatDetected.set();
        }

        void noCatDetected() {
            flagNoCatDetected.set();
        }

        void wasteDetected(string waste) {
            poolWasteDetected.write(waste);
            flagWasteDetected.set();
        }
};
