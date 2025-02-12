# Logboek installatie van IDF
Installatie voor MacOS, gebruik gemaakt van [de officiele handleiding](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html).

### Stappen volgens handleiding
De volgende commands moeten ingevuld worden in de terminal:
- brew install cmake ninja dfu-util
- mkdir -p ~/esp
- cd ~/esp
- git clone -b v5.3.1 --recursive https://github.com/espressif/esp-idf.git
- cd ~/esp/esp-idf
- ./install.sh esp32
- . $HOME/esp/esp-idf/export.sh
----------
Willen we ". $HOME/esp/esp-idf/export.sh" makkelijk toegankelijk maken, maken wij een alias. Dat doen we als volgt:
- nano ~/.zshrc

Voeg de volgende tekst toe in deze file: 
- alias get_idf='. $HOME/esp/esp-idf/export.sh'

Dan: ctrl + x, Y, Enter

- source ~/.zshrc \
Herstart de terminal, als je nu "alias" in de terminal zet, zie je "get_idf" ertussen staan. Vanaf nu hoef je alleen maar "get_idf" in een directory in de terminal te runnen om de hele omgeving op te zetten. 
----------

### Eerste test runnen op ESP
Vul de volgende commands in om de test files toe te voegen:
- cd ~/esp
- cp -r $IDF_PATH/examples/get-started/hello_world .

Verbind nu je ESP, je kan met */dev/cu.** zien welke devices er verbonden zijn. De ESP moet op een */dev/cu.usbserial* verbonden zijn.

Ga nu naar de hello_world directory en doe het volgende:
- cd esp/hello_world
- idf.py set-target esp32

Om in het menu te komen van idf, doe je het volgende:
- idf.py menuconfig

Om te starten met builden, vul je het volgende in
- idf.py build

Om vervolgens het bestand naar de ESP te flashen en direct te kijken wat de output is, doe je het volgende:
- idf.py -p /dev/cu.usbserial-*PORT* flash monitor

Bij *PORT* vul je uiteraard het port nummber in waar je ESP mee verbonden is, in mijn geval nu /dev/cu.usbserial-10.

Als het goed is krijg je de volgende output: \
<img src="/media/hello_world_idf.jpg" alt="foto" width="400"/>

### Wifi Scan runnen
Om de wifi scan te runnen, doen we dit in de ESP-IDF folder.
- cd ..
- cd esp-idf/examples/wifi/fast_scan
- idf_build
- idf.py -p /dev/cu.usbserial-10 flash monitor

Als het goed is, krijg je nu deze output: \
<img src="/media/wifi_scan_idf.jpg" alt="foto" width="400"/>