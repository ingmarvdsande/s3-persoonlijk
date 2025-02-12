# Oefenopdracht constexpr

## A. Eerste test
Opdracht:
- Test deze cpp code: [constexpr_sin.cpp](constexpr_sin.cpp)
- Vervang de functiebody van constexprSin tijdelijk door: return sin(x); en run opnieuw.
- Zet de functiebody met de Taylor-reeks implementatie terug. 

Vraag:
- Waarom gebruikten we een Taylor-reeks implementatie?
  - **-> Omdat wij geen match functies kunnen gebruiken in compiling, die library is namelijk runtime. Met de Taylorreeks kunnen we zelf de rekensom uitvoeren tijdens het compilen**

## B. Nauwkeurigheidstest
Opdracht:
- Voeg code toe die de maximale fout weergeeft tussen sin(x) en sinDegrees(x) voor integer hoeken in het bereik van 0..259 graden.

Vraag:
- Welke fout meet je? 
  - **-> 0**

Opdracht:
- Verklein die maximale fout eens met tenminste factor miljard. 

Vraag:
- Daarvoor hoefts slechts 1 getal aangepast te worden, welk getal en hoeveel?
  - **-> Het aantal iterations van de Taylorreeks, van 10 naar 13**

## C. Snelheidstest
Opdracht:
- Voeg code toe die het snelheidsverschil laat zien tussen sin() en sinDegrees(x).

Vragen:
- Verklaar het snelheidsverschil.
  - **-> Het berekenen van de Taylor reeks kost tijd**

- Verlaagt de eerder genoemde extra nauwkeurigheid de gemeten snelheid?
  - **-> Ja, de extra Taylor reeksen kost iets meer tijd**
- Waarom wel/niet?

## D. Cosdegrees
- Voeg ook een functie cosDegrees(x) toe, op dezelfde leest geschoeid.
- Voeg die ook toe aan de tests.
- Voeg onderstaand een link toe naar je resulterende cpp code:
  - **-> [code](https://github.com/2024-TICT-TV2SE3-24/s3-personal-ingmarvdsande/blob/main/Opdrachten/constExpr/constexpr_sin.cpp)**

## E. const
Je zou het ook kunnen oplossen zonder constexpr, door direct na start van het programma de tabellen uit te rekenen. Je kunt dan zelfs sin() en cos() gebruiken voor het invullen van de tabellen. Dus eenvoudiger code. Vervolgens heb je met sinDegrees en cosDegrees weer vergelijkbare performance. 

Vraag:
- Is het altijd het best om constexpr te gebruiken? Licht je antwoord toe. 
- **-> Nee, het gebruikt namelijk wel veel ram. Alleen als je echt die extra performance nodig hebt en de trade off het waard is**
