#include <iostream>
#include "rtos.hpp"

class SettingsControl : public rtos::task<> {
    enum state_t {IDLE, NOTILT, TILTEDLEFT, TILTEDRIGHT};

    private:
        state_t state = IDLE;

        rtos::flag flagAngleData();
        rtos::poll poolAngleData();

        TiltDuration& tiltDuration;
        Speaker& speaker;

        SettingsControl(TiltDuration& tiltDuration, Speaker& speaker) {
            this->tiltDuration = tiltDuration;
            this->speaker = speaker;
        }

        void main() {
            for (;;) {
                switch (state) {
                case IDLE:
                    auto evt = wait(flagAngleData);
                    if (evt == flagAngleData) {
                        int angle = poolAngleData.read();
                        if (angle > 25) {
                            state = TILTEDLEFT;
                    } 
                        else if (angle < -25) {
                            state = TILTEDRIGHT;
                    } 
                        else {
                            state = NOTILT;
                    }
                    }
                    break;
                case NOTILT:
                    tiltDuration.setDuration(10);
                    state = IDLE;
                    break;
                case TILTEDLEFT:
                    tiltDuration.setDuration(10);
                    speaker.playPingOnce();
                    state = IDLE;
                    break;
                case TILTEDRIGHT:
                    tiltDuration.setDuration(20);
                    speaker.playPingTwice();
                    state = IDLE;
                    break;
                }
            }
        }
    public:
        void setAngleData(int angle) {
            poolAngleData.write(angle);
            flagAngleData.set();
        }
};
