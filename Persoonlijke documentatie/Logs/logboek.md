# Logboek van Ingmar van de Sande 

### September

##### 2 September 2024
Afwezig op eerste collegedag ivm ziekenhuisafspraak

##### 3 september 2024
Eerste collegedag, groepje ontmoet en start gemaakt aan functionele requirements, non functionele requirements, key drivers en voornemens voor het komende semester.

##### 4 september 2024
Later op college ivm fysio, functionele en non functionele requirements afgemaakt

##### 5 september 2024
In de groep de Functionele, Non functionele requirements + key drivers samengevoegd en besproken

##### 6 september 2024
Bedrijfsbezoek Exner

##### 9 september 2024
Use Case beschrijving + diagram gemaakt

##### 10 september 2024
Activity Diagram + Use cases besproken

##### 11 september 2024
Begonnen met IDF installatie, zie [IDF logboek](https://github.com/2024-TICT-TV2SE3-24/s3-personal-ingmarvdsande/blob/main/Persoonlijke%20documentatie/Logs/idf_installatie.md)

##### 12 september 2024
Verder met IDF, key drivers, functionele en non functionele requirements verbeterd na meeeting met Bart en Harm

##### 13 september 2024
IDF installatie afgemaakt

##### 16 september 2024
Gesprek Lucy voorbereid en gehad, zie [gesprek_lucy](https://github.com/2024-TICT-TV2SE3-24/s3-personal-ingmarvdsande/blob/main/Persoonlijke%20documentatie/gesprek_lucy.md)

##### 17 september 2024
Networking basics

##### 18 september 2024
Object model snoepautomaat gemaakt

##### 19 september 2024
Show and tell gehad, multithreaded programming start

##### 20 september 2024
Persoonlijke dag

##### 21 september 2024
Mutex oefening gemaakt, alle programmatjes op ESP gerund tot Webserver opdracht, deze files niet kunnen vinden. Ik heb hierbij geleerd dat ik in de accesspoint en internet access opdrachten de wifi intellingen in menuconfig moest aanpassen. Hierbij kon ik ook lol hebben door mijn AP de naam "Michiel de Router" te geven.

##### 26 september
Feedback Activity Diagram: Swimlanes overbodig en onoverzichtelijk

Scorebord langs Lucy runnen, designs maken en checken of zij dit goed vindt.

##### Maandag 21 oktober
Raspberry Pi 4 ontvangen van Harm, ivm werk geen tijd gehad om direct mee aan de slag te gaan

##### Woensdag 23 oktober
Eerste keer aan de slag met de Pi, geprobeerd Ubuntu te flashen naar de SD kaart via Pi Imager. Error "Port 22 refused" en "Secret key" errors. Geprobeerd opnieuw te flashen en bleef dezelfde error krijgen. Geprobeerd zelf de files in de boot folder aan te passen om SSH met wachtwoord toe te staan, niet gelukt

##### Donderdag 24 oktober
Zelfde secret key error, niet lang aan kunnen werken ivm werk en college.

##### Vrijdag 25 oktober
Erachter gekomen dat je de SSH instellingen in de imager kan veranderen, hier SSH gebruikersnaam + wachtwoord geprobeerd in te stellen. "Port 22 refused" errors gekregen. Verder de eerste opdracht van Fourier gemaakt

##### Maandag 28 oktober
Nog een laatste keer geprobeerd met de Pi Ubuntu werkende te krijgen, niet gelukt. Geschakeld naar een VM voor MacOS: UTM. Eerste keer niet goed de virtual boot drive ingesteld, 2e keer alle settings standaard gelaten en geduld gehad bij het "Try or Install Ubuntu", daarna **niet vergeten de Boot volgorde aan te passen in UEFI**, zorg dat "Ubuntu" als eerste staat. Docker geïnstalleerd en de Git gecloned, echter krijg ik bij "localhost:5000" en localhost:5001" allebei lege pagina's te zien. Zowel de MongoDB Docker container als de Gomoku container runnen, echter werkt de game nog niet.

##### Dinsdag 29 oktober
Tweede opdracht van Fourier afgemaakt en ingeleverd, opnieuw geprobeerd Gomoku werkende te krijgen. Niet gelukt, nog steeds hetzelfde issue. Plan is om maandag eerst met peers proberen het op te lossen, daarna evt docent om hulp vragen

##### Maandag 18 november
Start gemaakt aan leaderboard pagina, styling gemaakt in CSS en een index.html pagina gemaakt, ook een simpele Flask applicatie gemaakt om de website te runnen

##### Dinsdag 19 november
Leaderboard omgezet naar een React website, hierbij de styling omgezet naar Tailwind CSS styling en de pagina's in JS gemaakt. Ook een JS script gemaakt om de data uit de Database API te halen. Deze API en Database zijn er nog niet, maar moeten er wel komen deze week. Zodra deze er zijn hoef ik alleen maar een API key in mijn programma te pluggen en dan is het leaderboard ready om live te updaten. 

##### Dinsdag 2 december Docker 
Eerst React app in Docker container gezet, hierbij gebruik gemaakt van [deze tutorial](https://www.freecodecamp.org/news/how-to-dockerize-a-react-application/).\
Aan de hand van deze tutorial heb ik [deze Dockerfile](https://github.com/2024-TICT-TV2SE3-24/s3-project-flitsmeister/blob/main/Dashboard/app/Dockerfile) gemaakt.

Hierna heb ik de volgende command gerund: \
``docker build -t web-app .`` \

Vervolgens heb ik de image gerund met deze command: \
``docker run -d -p 8000:3000 web-app`` \

Zo kon ik via 'localhost:8000' bij mijn website. \
Niet vergeten de image te 'taggen', door het volgende: \
``docker tag web-app ingmarvdsande/flitsmaister:v1`` \

Zo heb ik mijn repo 'flitsmaister' genoemd op Docker hub. 
Daarna 'docker login' gedaan en 
``docker push ingmarvdsande/flitsmaister:v1`` \
gedaan. \

Daarna Flask API in Docker gezet, gebruik gemaakt van [deze tutorial](https://www.digitalocean.com/community/tutorials/how-to-build-and-deploy-a-flask-application-using-docker-on-ubuntu-20-04)
Dezelfde stappen als hierboven gebruikt, alleen heb ik de image en repo uiteraard een andere naam gegeven. 

##### Maandag 9 december
Pong debugging
---------------
Error 1: Een lege functiebody in SceneDisplay, de Enable body had geen "flagEnable.set()" erin. Deze heb ik erin geschreven
Error 2: in Pong2_ino.h stond in line 32 2 keer "buttonLeft", terwijl 1 daarvan buttonRight moet zijn.
Error 3: in PaddleControl stond onder "void ButtonPressed" in de functie by buttonRight "flagLeftPressed" terwijl dat uiteraard "flagRightPressed" moet zijn.
Error 4: in GameControl stond er geen start state onder STATE INITIAL. Deze heb ik toegevoegd. 

#### Dinsdag 17 december
Tailscale geinstalleerd op de Pi, dit zodat de Pi op een vaste plek kan blijven (nu bij mij thuis) en alle groepsgenoten remote bij de Pi kunnen via SSH om 
er bestanden op te zetten of dingen op te runnen. Hiervoor heb ik een [installatie handleiding gemaakt](https://github.com/2024-TICT-TV2SE3-24/s3-project-flitsmeister/tree/main/Business%20documentatie/Tailscale_installatie)