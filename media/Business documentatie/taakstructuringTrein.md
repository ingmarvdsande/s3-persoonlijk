# Taakstructurering van object model Trein

Taak|Objecten|Taaksoort|Periode|Deadline|Prioriteit|
-----|-----|-----|---|-----|-----|
Snelheidstaak|snelheidsSchuif,Snelheidscontrol|Intern, Demand Driven| |30ms|2
TreinTaak|treincontrol|Intern, Demand Driven| |30ms|2
Motortaak|motor|Geen| |30ms|2
NoodremTaak|noodrem, noodremControl|Intern, Demand Driven| |10ms|1
DisplayTaak|displayMachinist|IO, Demand Driven| |100 ms|4
ObstakelTaak|obstakelSensor|IO, Periodical|10ms|10ms|1
VerkeersTaak|verkeerControl, snelheidsLimietControl|Intern, Demand Driven| |30ms|2
LocatieTaak|locatieMeter|IO, Periodical|50ms|50ms|3
LichtTaak|roodLampje, roodLampjeControl, geelLampje, geelLampjeControl|IO, Periodical|30ms|30ms|2
LogTaak|blackBoxLog|Intern, Demand Driven| |30ms|2