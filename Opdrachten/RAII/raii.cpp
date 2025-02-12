#include <iostream>
#include <fstream>
#include <cstdio> // Voor std::remove
#include <string>
using namespace std;

class TempFile {
private:
    string filename; // Naam van het tijdelijke bestand

public:
    // Constructor die een tijdelijk bestand aanmaakt
    TempFile(const string& prefix) {
        filename = prefix + ".tmp";
        ofstream file(filename);
        file.close();
        // ** vul deze body zelf in **
    }
        // Functie om de naam van het bestand te krijgen
    const string& getFilename() const {
        return filename;
    }
    // Destructor die het tijdelijke bestand verwijdert
    ~TempFile() {
        remove(filename.c_str());
        // ** vul deze body zelf in **
    }
    
    // Functie om naar het bestand te schrijven
    void writeData(const string& data) {
        ofstream file(filename);
        file << data;
        file.close();
        // ** vul deze body zelf in **
    }

    // Verwijder copy constructor en copy assignment operator
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;

};

// Hoofdprogramma om de RAII-klasse te testen
int main() {
    try {
        TempFile tempFile("example"); // Maak een tijdelijk bestand aan met prefix "example"

        tempFile.writeData("Hello, RAII!"); // Schrijf data naar het bestand
        cout << "Temporary file is: " << tempFile.getFilename() << endl;

    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    // Het tijdelijke bestand wordt hier automatisch verwijderd door de destructor van TempFile

    return 0;
}