#include <iostream>
#include <string>

class Flag {
public:
    Flag(VerjaagController* controller) : controller(controller), state(false) {}
    bool get() const { return state; }
    void set() { state = true; }
    void reset() { state = false; }

private:
    VerjaagController* controller;
    bool state;
};

class Instellingen{
    public:
        Instellingen(){
            // Constructor
        }
        bool setAlarmEnabled(bool enabled){
            // Set alarm enabled
        }
        bool getAlarmEnabled(){
            // Get alarm enabled
        }
        bool setLightEnabled(bool enabled){
            // Set light enabled
        }
        bool getLightEnabled(){
            // Get light enabled
        }
        bool setServoEnabled(bool enabled){
            // Set servo enabled
        }
        bool getServoEnabled(){
            // Get servo enabled
        }
        bool setSoundEnabled(bool enabled){
            // Set sound enabled
        }
        bool getSoundEnabled(){
            // Get sound enabled
        }
};
class LichtController{
    public:
        LichtController(){
            // Constructor
        }
        void maakLichtEffect(){
            // Maak licht effect
        }
};
class SoundController{
    public:
        SoundController(){
            // Constructor
        }
        void maakAfschrikGeluid(){
            // Afschrik geluid
        }
};
class ServoController{
    public:
        ServoController(){
            // Constructor
        }
        void maakWapperEffect(){
            // Maak wapper effect
        }
};

class VerjaagController {
    public:
        VerjaagController(): flagAan(this), flagUit(this), flagDuifKwam(this), flagDuifGing(this), flagLichtKlaar(this), flagWapperKlaar(this),
        flagGeluidKlaar(this), instellingen() {
            // Constructor
        }

    private:
        Instellingen instellingen;
        Flag flagAan;
        Flag flagUit;
        Flag flagDuifKwam;
        Flag flagDuifGing;
        Flag flagLichtKlaar;
        Flag flagWapperKlaar;
        Flag flagGeluidKlaar;
        LichtController lichtController;
        SoundController soundController;
        ServoController servoController;

        void startVerjagen() {
            while(true){
                if(flagAan.get()){
                    if(flagDuifKwam.get()){
                        if (!instellingen.getLightEnabled()){
                            lichtController.maakLichtEffect();
                            flagLichtKlaar.set();
                        }
                        else{
                            if (!instellingen.getServoEnabled()){
                                servoController.maakWapperEffect();
                                flagWapperKlaar.set();
                            }
                            else{
                                if (!instellingen.getSoundEnabled()){
                                    soundController.maakAfschrikGeluid();
                                    flagGeluidKlaar.set();
                                }
                            }
                        }
                    }
                }
            }
        }

        void zetAan()
        {
            flagAan.set();
        }
        void zetUit()
        {
            flagUit.set();
        }

        void meldDuifAanwezig()
        {
            flagDuifKwam.set();
        }

        void meldDuifVertrokken()
        {
            flagDuifGing.set();
        }

        void meldLichtEffectKlaar()
        {
            flagLichtKlaar.set();
        }

        void meldWapperEffectKlaar()
        {
            flagWapperKlaar.set();
        }

        void afschrikGeluidKlaar()
        {
            flagGeluidKlaar.set();
        }
};