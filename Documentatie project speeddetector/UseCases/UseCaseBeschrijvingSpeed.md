# Beschrijving van de Use Case Leaderbord van de Speed Detector door Ingmar van de Sande

### Actor: Bejaarden
De bejaarden moeten de mogelijkheid hebben om, na een snelheid "neergezet" te hebben, dit te kunnen vergelijken ter bevordering van de competitie. Hiervoor moet er een leaderboard komen, waarop de gemeten snelheden uit de database gehaald worden en op volgorde van hoog naar laag getoond worden. Hierbij worden alleen de 20 snelste snelheden getoond, met naam en snelheid. Dit wordt vervolgens getoond op een scherm in de hal, zodat de ouderen hun snelheden onderling kunnen vergelijken.

### Voorwaarden
- De snelheid moet gemeten worden door een betrouwbare meter.
- De gemeten snelheid, naam en datum moeten correct naar de database gestuurd worden.
- De database moet toegankelijk zijn voor het leaderboard om gegevens op te halen.

### Stappen
1. De bejaarde meet zijn/haar snelheid met de speed detector.
2. De gemeten snelheid, naam en datum worden naar de SQL database gestuurd.
3. De database slaat de gegevens op.
4. Het leaderboard vraagt de gegevens op uit de database.
5. De gegevens worden gesorteerd op snelheid van hoog naar laag.
6. Het leaderboard toont de 20 snelste snelheden met naam en snelheid.

### Resultaat
- De bejaarden kunnen hun snelheden vergelijken op het leaderboard.
- De competitie wordt bevorderd door het tonen van de snelste snelheden.