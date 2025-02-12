# Taakstructurering van object model Broodrooster

Objecten|Taaksoort|Periode|Deadline|Prioriteit
-----|-----|---|-----|-----|
bruinteInstellenControl | Intern, Demand Driven | | 30ms | 1 
broodRoosterenControl | Intern, Demand Driven | | 30ms | 1 
knopUp | IO, Periodical | 60ms | 60ms | 2 
knopDown | IO, Periodical | 60ms | 60ms | 2 
lichtSensor | IO, Periodical | 100ms | 100ms | 3 
verwarmingsElement | IO, Demand Driven |  | 100ms | 3 
speaker | IO, Demand Driven |  | 200ms | 4 
solenoid | IO, Demand Driven |  | 200ms | 4 
Display | IO, Demand Driven | | 200ms | 4 
-------------------------------------------------------------

### Samenvoegen

Taak|Objecten|Taaksoort|Periode|Deadline|Prioriteit
-----|-----|---|-----|-----|
InstelTaak | bruinteInstellenControl | Intern, Demand Driven | | 30ms | 1 
RoosterTaak | broodRoosterenControl | Intern, Demand Driven | | 30ms | 1 
ButtonTaak | ButtonHandler, knopUp, knopDown | IO, Periodical | 60ms | 60ms | 2 
ControleTaak | lichtSensor | IO, Periodical | 100ms | 100ms | 3 
VerwarmingsTaak | verwarmingsElement | IO, Demand Driven |  | 100ms | 3 
AlertTaak | speaker | IO, Demand Driven |  | 200ms | 4 
EjectTaak | solenoid | IO, Demand Driven |  | 200ms | 4 
DisplayTaak | Display | IO, Demand Driven | | 200ms | 4 
-------------------------------------------------------------