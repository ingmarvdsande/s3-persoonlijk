# Upgrade-opdracht "Encryptie van datastroom"

Door Ingmar van de Sande

## Inhoudsopgave

1. [Inleiding](#inleiding)
2. [Vooronderzoek en Theoretisch kader](#vooronderzoek-en-theoretisch-kader)
3. [Hoofdvraag](#hoofdvraag)
4. [Deelvragen](#deelvragen)
5. [Methoden](#methoden)
6. [Bevindingen](#bevindingen)
7. [Beslissingstabel](#beslissingstabel)
8. [Conclusie](#conclusie)
9. [Implementatie](#implementatie)
10. [Aanbevelingen](#aanbevelingen)
11. [Bronvermelding](#bronvermelding)
---

## Inleiding
Het doel van dit onderzoek is om verbeterpunten op het gebied van encryptie en beveiliging van de website uit te werken. Op dit moment is de encryptie van inloggegevensuitwisseling tussen de API van de database en de frontend praktisch afwezig, waardoor onze website kwetsbaar is voor een man-in-the-middle (MITM) aanval. Bovendien worden wachtwoorden in plain text opgeslagen in de database, wat een groot beveiligingsrisico vormt.

De focus ligt op het onderzoeken en implementeren van veilige methoden voor end-to-end encryptie en gehashte wachtwoordopslag.

---

## Vooronderzoek en Theoretisch kader

Een lijst met relevante begrippen en bronnen:

- **API**: Application Programming Interface; het communicatiemechanisme tussen de frontend en backend.
- **End-to-End Encryptie (E2EE)**: Encryptie waarbij alleen de verzender en ontvanger toegang hebben tot de gedeelde informatie.
- **RSA**: Een bepaalde encryptie methode, hier wordt later in het onderzoek meer uitleg over gegeven
- **AES**: Een bepaalde encryptie methode, hier wordt later in het onderzoek meer uitleg over gegeven
- **Diffie-Hillman**: Een bepaalde encryptie methode, hier wordt later in het onderzoek meer uitleg over gegeven

**Bronnen:**
- [Implementing End-to-End Encryption in React](https://medium.com/@letscodefuture/implementing-end-to-end-encryption-in-a-react-application-a-beginners-guide-08b846353d19)
- [Basic End-to-End Encryption](https://dev.to/lambstar/basic-end-to-end-encryption-with-crypto-2gh7)
- [Password Hashing Guidelines](https://www.vaadata.com/blog/how-to-securely-store-passwords-in-database/)

---

## Hoofdvraag
Welke technologieën zijn er nodig om end-to-end encryptie te implementeren in de JavaScript-app en wachtwoorden gehashed op te slaan in de database?

---

## Deelvragen
1. Welke end-to-end encryptie technologieën zijn er beschikbaar?
2. Waar in de applicatie is het meest logische punt om deze encryptie te implementeren?
3. Wat zijn de beste methoden om wachtwoorden veilig in de database op te slaan?

---

## Methoden

### 1. Onderzoek naar end-to-end encryptie technologieën
Voor deze vraag raadpleegde ik literatuur en online bronnen om de meest gebruikte technologieën te identificeren. 

### 2. Analyse van de architectuur
Door de huidige architectuur van de applicatie te analyseren, bepaal ik waar encryptie het meest effectief kan worden toegepast.

---

## Bevindingen

### 1. Welke end-to-end encryptie technologieën zijn er en hoe werken ze?
De belangrijkste technologieën:
- **RSA**: Asymmetrisch encryptie-algoritme, geschikt voor veilige gegevensoverdracht. RSA-encryptie is een manier om informatie veilig te houden wanneer je het verstuurt. Het werkt met 2 sleutels: een openbare sleutel (die je met iedereen kunt delen) en een privésleutel (die je geheim houdt). De openbare sleutel wordt gebruikt door de tegenpartij om het bericht te versleutelen, zo kan jij met jouw prive-sleutel (de tegenhanger van de publieke, op een manier de sleutel en de "publieke sleutel" is eigenlijk meer een slot) het bericht weer ontsleutelen. Omdat alleen jij de prive-sleutel hebt is dit een zeer veilige methode van encryptie. Deze sleutels worden gegenereerd door een complex Wiskundig algoritme. 

- **AES**: Symmetrisch encryptie-algoritme dat hoge snelheid biedt voor grote datasets. AES encrypt de gegevens ook met een sleutel, echter gebruikt het maar één sleutel. Deze sleutel is dan hetzelfde aan beide kanten van de "lijn" om het zo maar te zeggen. Dit is veel sneller dan RSA. Hier is het lastige om de encryptie-sleutel door te geven aan de tegenpartij, hier zal je een andere beveiligsmethode voor moeten gebruiken, zoals RSA. Een effectieve en populaire manier om te beveiligen op grotere schaal is dus door de data zelf te beveiligen met een AES algoritme en de sleutel hiervan door te geven met het RSA algoritme.

- **Diffie-Hellman**: Voor veilige sleuteluitwisseling, echter werkt dit anders dan RSA. Beide partijen kiezen een groot priemgetal en een basisgetal die publiekelijk bekend zijn. Ze genereren elk een privégetal (dat geheim blijft) en gebruiken dit om een publieke waarde te berekenen. Ze wisselen deze publieke waarden uit. Vervolgens gebruiken beide partijen hun privégetallen en de ontvangen publieke waarde om een gezamenlijke geheime sleutel te berekenen. Omdat beide partijen hetzelfde proces gebruiken, hebben ze dezelfde geheime sleutel, die kan worden gebruikt om gegevens te versleutelen.

### 2. Waar in de applicatie is encryptie het meest logisch?
Na analyse van de architectuur blijkt dat de meest kritieke implementatiepunten zijn:
- **Frontend-API communicatie**: Hier voorkomt end-to-end encryptie dat gegevens tijdens de transmissie worden onderschept.
- **Database**: Encryptie beschermt gegevens wanneer deze in rust zijn. Hier kan je effectief Hashing inzetten (voornamelijk tussen de API en de Database) zodat de persoonsgegevens en inloggegevens veilig kunnen worden opgeslagen op de database.


---

## Beslissingstabel

| **Criteria**             | **Gewicht** | **RSA** | **AES** | **Diffie-Hillman** |
|--------------------------|-------------|---------|---------|---------|
| **Beveiligingsniveau**   | 5           | 9       | 8       | 8       |
| **Snelheid**             | 4           | 6       | 10      | 7       |
| **Schaalbaarheid**       | 4           | 8       | 9       | 7       |
| **Simpele implementatie**| 3           | 4       | 6       | 4       |

**Totaalscore:**

- **RSA**: 113
- **AES**: 134
- **Diffie-Hillman**: 108

## Conclusie
De hoofdvraag kan als volgt worden beantwoord:

1. De technologieën die nodig zijn om end-to-end encryptie te implementeren zijn RSA, AES en Diffie-Hellman.
2. Het meest logische punt om encryptie te implementeren is tussen de frontend en de API voor gegevensoverdracht, en in de database voor gegevens in rust.

---

## Implementatie

### Stap 1: End-to-End Encryptie tussen frontend en API
1. **Kies een encryptiemethode:**
   - Gebruik **AES** voor snelle symmetrische encryptie van de data.
   - Gebruik **RSA** of **Diffie Hillman** voor de veilige uitwisseling van sleutels. Ik zou kiezen voor RSA vanwege de hogere score in de tabel, dit zit vooral in dat RSA toch iets veiliger is en beter schaalbaar.

2. **Codeer encryptie in de frontend:**
   - Installeer een bibliotheek zoals [crypto-js](https://github.com/brix/crypto-js) of een moderne Web Crypto API.
   - Versleutel gevoelige data voordat deze via de API wordt verzonden.

3. **Decodeer encryptie in de backend:**
   - Gebruik een server-side bibliotheek zoals [Node.js Crypto module](https://nodejs.org/api/crypto.html).
   - Ontvang versleutelde gegevens en decodeer deze met de gedeelde sleutel.

4. **Voorkom MITM-aanvallen:**
   - Gebruik HTTPS met een geldig SSL-certificaat.

### Stap 2: Beveiliging van data in rust
1. **Encryptie van databasevelden:**
   - Gebruik AES om gevoelige velden zoals e-mail en andere persoonsgegevens te versleutelen.
2. **Gebruik sleutelbeheer:**
   - Gebruik een Key Management Service (KMS) zoals AWS KMS of Azure Key Vault.

---

## Aanbevelingen

Voor toekomstige verbeteringen stel ik het volgende voor:

1. **Performance-optimalisatie:**
   - Analyseer de impact van encryptie op de snelheid van de applicatie en optimaliseer de algoritmen indien nodig.
2. **Database encryptie:**
   - Onderzoek encryptiemethoden op database-niveau om gegevens in rust te beveiligen.
3. **Nieuwe technologieën:**
   - Houd nieuwe encryptiestandaarden en technologieën in de gaten, zoals Post-Quantum Cryptography.
4. **Audit en testen:**
   - Voer regelmatige beveiligingsaudits uit en gebruik penetratietesten om kwetsbaarheden te identificeren.

---

Met deze implementatie en aanbevelingen kunnen we de beveiliging van de applicatie aanzienlijk verbeteren en zorgen voor veilige verwerking van gevoelige gegevens.

## Bronvermelding

    Lakshminarayanan, A. (2019). Implementing end-to-end encryption in a React application: A beginner's guide. Medium. (Geraadpleegd op 19-12-2024) https://medium.com/@letscodefuture/implementing-end-to-end-encryption-in-a-react-application-a-beginners-guide-08b846353d19

    Lamb, S. (2020). Basic end-to-end encryption with crypto. DEV Community. (Geraadpleegd op 19-12-2024) https://dev.to/lambstar/basic-end-to-end-encryption-with-crypto-2gh7

    Vaadata. (2021). How to securely store passwords in database. (Geraadpleegd op 10-1-2024) https://www.vaadata.com/blog/how-to-securely-store-passwords-in-database/

    Bhattacharya, A. (2024, 13 november). What is RSA? How does an RSA work? | Encryption Consulting. Encryption Consulting. (Geraadpleegd op 10-1-2024)https://www.encryptionconsulting.com/education-center/what-is-rsa/ 
    
    MongoDB Data Encryption. (z.d.). MongoDB. (Geraadpleegd op 10-1-2024) https://www.mongodb.com/products/capabilities/security/encryption

    Awati, R., Bernstein, C., & Cobb, M. (2024, 20 februari). Advanced Encryption Standard (AES). Search Security. (Geraadpleegd op 10-1-2024) https://www.techtarget.com/searchsecurity/definition/Advanced-Encryption-Standard

    Gillis, A. S. (2022, 18 oktober). Diffie-Hellman key exchange (exponential key exchange). Search Security. (Geraadpleegd op 10-1-2024) https://www.techtarget.com/searchsecurity/definition/Diffie-Hellman-key-exchange 