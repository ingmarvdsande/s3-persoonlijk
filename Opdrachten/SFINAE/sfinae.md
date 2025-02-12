# Opdracht Sfinae
## Inleiding
De voorbeeld casus is dat we in onze code van een bepaald object willen controleren of het een bepaalde memberfunctie heeft.

Dat kan compiletime, met SFINAE. Er zijn ook eenvoudiger runtime alternatieven.

Bij deze opdracht ga je SFINAE vergelijken met 2 runtime alternatieven.

## A: Snelheidsmeting van Sfinae
Neem als uitgangspunt de code [sfinae.cpp](./sfinae.cpp).
Ga voor jezelf na hoe de code werkt.
Test de code even, en pas het als volgt aan:

- Commentarieer de couts uit in foo() en callFooIfExists() (we zijn nu immers niet geinteresseerd in de snelheid van couting)
- Meet hoe lang het duurt om de volgende combi 100000 keer aan te roepen:
```c++
callFooIfExists(a);
callFooIfExists(b);
```
-> **0.209276 seconden**

## B: Snelheidsmeting van Sfinae alternatief 1
Doe hetzelfde voor [runtime_nosfinae](./runtime_nosfinae.cpp).

-> **0.685921 seconden**

## C: Snelheidsmeting van Sfinae alternatief 2
Doe hetzelfde voor [runtime_nosfinae_2](./runtime_nosfinae_2.cpp).

-> **0.72377 seconden**

## D: Vergelijking
Geef voor elk van de methoden aan wat het voordeel is ten opzichte van de andere methoden.

- -> **Voordeel van sfinae:** [Compileertijdcontrole en flexibiliteit]
- -> **Voordeel van alternatief 1:** [Veiligheid]
- -> **Voordeel van alternatief 2:** [Eenvoudig en leesbaar]