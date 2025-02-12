# Logboek van installatie van Gomoku webapp

### Problemen met Raspberry Pi
Eerst heb ik dagen geprobeerd het werkende te krijgen op een Raspberry Pi, echter liep ik veel tegen problemen met de SSH connectie op. Hierom heb ik besloten verder te gaan op een VM op mijn Macbook via UTM. 

### Installatie VM 
UTM heb ik geinstalleerd en hierop heb ik een Ubuntu Linux server gezet, hierbij moet je opletten dat je in de 'netwerk' instellingen het netwerk op 'bridged' zet, zo kan je namelijk vanaf je browser toegang krijgen tot dingen die op je VM runnen. 

Vervolgens de installatiestappen van [het log van Marius](https://github.com/HU-TI-DEV/TI-S3/blob/main/infrastructuur/ServerMetWebApplicatie/log_Opzetten_van_Server_en_Webapplicatie.md) gevolgd. Docker geinstalleerd en de github gecloned. Hierbij heb ik lang problemen gehad met het verbinden, omdat mijn netwerk instellingen niet goed stonden. Uiteindelijk heb ik uitgevogeld dat de netwerk instellingen op "bridged" moest staan. Toen kreeg ik een error ivm Eduroam (Server misbehaving), overgeschakeld naar data en toen docker-compose up --build -d gerund. Vervolgens heb ik 'ip a' gerund in de terminal om het IP adres van de VM te vinden onder 'Enp0s1'. Vervolgens verbonden met '172.20.10.7:5001', dit werkte niet. Toen gerealiseerd dat ik nog '/gomoku' eraan toe moest voegen. Toen werkte het! 

<img src="/media/Gomoku.jpg" alt="foto" width="400"/>


### MongoDB Compass
Op MongoDB compass een nieuwe connecte toegevoegd, eerst gedaan met mongodb://172.20.10.7:27017. Dit werkte niet, toen de docker-compose gecheckt en gezien dat de DB op 27018 staat, dit aangepast en de inloggegevens gezet onder "advanced" en "authentication" en toen werkte het! 

<img src="/media/MongoDb.jpg" alt="foto" width="400"/>

