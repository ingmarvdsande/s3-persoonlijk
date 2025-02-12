#include <iostream>
#include <array>
#include <cmath>
#include <chrono>
#include <iomanip>

// Constante voor pi
constexpr double pi = 3.14159265358979323846;

// Functie om graden naar radialen om te zetten
constexpr double degreesToRadians(int degrees) {
    return degrees * (pi / 180.0);
}

// Eigen constexpr sinus functie met behulp van de Taylor-reeks
constexpr double constexprSin(double x) {
    double term = x;
    double result = x;
    constexpr int iterations = 13; // Aantal termen voor de Taylor-reeks
    // De Taylorreeks van een sinus is:
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...

    for (int i = 1; i < iterations; ++i) {
        term *= -x * x / ((2 * i) * (2 * i + 1));
        result += term;
    }

    return result;
}

// Eigen constexpr cosinus functie met behulp van de Taylor-reeks
constexpr double constexprCos(double x) {
    double term = 1.0;
    double result = 1.0;
    constexpr int iterations = 13; // Aantal termen voor de Taylor-reeks
    // De Taylorreeks van een cosinus is:
    // cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ...

    for (int i = 1; i < iterations; ++i) {
        term *= -x * x / ((2 * i - 1) * (2 * i));
        result += term;
    }

    return result;
}

// Constexpr functie om de sinuswaarden voor 0 tot 359 graden te berekenen
constexpr std::array<double, 360> generateSinTable() {
    std::array<double, 360> sinTable{};
    for (int i = 0; i < 360; ++i) {
        sinTable[i] = constexprSin(degreesToRadians(i));
    }
    return sinTable;
}

// Constexpr functie om de cosinuswaarden voor 0 tot 359 graden te berekenen
constexpr std::array<double, 360> generateCosTable() {
    std::array<double, 360> cosTable{};
    for (int i = 0; i < 360; ++i) {
        cosTable[i] = constexprCos(degreesToRadians(i));
    }
    return cosTable;
}

// Sinustabel gegenereerd tijdens compile-tijd
constexpr auto sinTable = generateSinTable();

// Cosinustabel gegenereerd tijdens compile-tijd
constexpr auto cosTable = generateCosTable();

// Functie om de sinuswaarde te krijgen voor een gegeven graad
double sinDegrees(int degrees) {
    return sinTable[degrees];
}

// Functie om de cosinuswaarde te krijgen voor een gegeven graad
double cosDegrees(int degrees) {
    return cosTable[degrees];
}

// Functie om de maximum afwijking tussen sinDegrees en constexprSin te berekenen
double maxDifferenceSinSinDegrees() {
    double maxDifference = 0.0;
    for (int i = 0; i < 360; ++i) {
        double resultSinDegrees = sinDegrees(i);
        double constExprSinDifference = constexprSin(degreesToRadians(i));
        double difference = std::abs(resultSinDegrees - constExprSinDifference);
        if (difference > maxDifference) {
            maxDifference = difference;
        }
    }
    return maxDifference;
}

// Functie om de maximum afwijking tussen cosDegrees en constexprCos te berekenen
double maxDifferenceCosCosDegrees() {
    double maxDifference = 0.0;
    for (int i = 0; i < 360; ++i) {
        double resultCosDegrees = cosDegrees(i);
        double constExprCosDifference = constexprCos(degreesToRadians(i));
        double difference = std::abs(resultCosDegrees - constExprCosDifference);
        if (difference > maxDifference) {
            maxDifference = difference;
        }
    }
    return maxDifference;
}

// Functie om de snelheid van std::sin te meten
double measureStdSinSpeed() {
    auto start = std::chrono::high_resolution_clock::now();
    
    double result = 0.0;
    for (int i = 0; i < 360; ++i) {
        result += std::sin(degreesToRadians(i)); // Gebruik std::sin in radialen
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "std::sin computation took: " << elapsed.count() << " ms\n";
    return result; // Zodat de compiler de berekening niet wegoptimaliseert
}

// Functie om de snelheid van std::cos te meten
double measureStdCosSpeed() {
    auto start = std::chrono::high_resolution_clock::now();
    
    double result = 0.0;
    for (int i = 0; i < 360; ++i) {
        result += std::cos(degreesToRadians(i)); // Gebruik std::cos in radialen
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "std::cos computation took: " << elapsed.count() << " ms\n";
    return result; // Zodat de compiler de berekening niet wegoptimaliseert
}

// Functie om de snelheid van sinDegrees te meten
double measureSinDegreesSpeed() {
    auto start = std::chrono::high_resolution_clock::now();

    double result = 0.0;
    for (int i = 0; i < 360; ++i) {
        result += sinDegrees(i); // Gebruik sinDegrees
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "sinDegrees computation took: " << elapsed.count() << " ms\n";
    return result; // Zodat de compiler de berekening niet wegoptimaliseert
}

// Functie om de snelheid van cosDegrees te meten
double measureCosDegreesSpeed() {
    auto start = std::chrono::high_resolution_clock::now();

    double result = 0.0;
    for (int i = 0; i < 360; ++i) {
        result += cosDegrees(i); // Gebruik cosDegrees
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "cosDegrees computation took: " << elapsed.count() << " ms\n";
    return result; // Zodat de compiler de berekening niet wegoptimaliseert
}

int main() {
    std::cout << std::fixed << std::setprecision(8);

    // Maximum verschil tussen sinDegrees en constexprSin
    std::cout << "Max difference (sin): " << maxDifferenceSinSinDegrees() << std::endl;

    // Maximum verschil tussen cosDegrees en constexprCos
    std::cout << "Max difference (cos): " << maxDifferenceCosCosDegrees() << std::endl;

    // Snelheidsmetingen
    double resultStdSin = measureStdSinSpeed();
    double resultSinDegrees = measureSinDegreesSpeed();

    double resultStdCos = measureStdCosSpeed();
    double resultCosDegrees = measureCosDegreesSpeed();

    // Resultaten gebruiken zodat de compiler ze niet wegoptimaliseert
    std::cout << "Result std::sin: " << resultStdSin << std::endl;
    std::cout << "Result sinDegrees: " << resultSinDegrees << std::endl;

    std::cout << "Result std::cos: " << resultStdCos << std::endl;
    std::cout << "Result cosDegrees: " << resultCosDegrees << std::endl;

    return 0;
}
