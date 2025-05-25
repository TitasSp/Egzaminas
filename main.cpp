#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <cctype>

int main()
{
    std::string filename = "input.txt";
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Klaida atidarant faila: " << filename << std::endl;
        return 1;
    }

    // Map: žodis → kiek kartų pasikartojo
    std::map<std::string, int> word_counts;

    // Map: žodis → eilučių numeriai, kur jis buvo paminėtas
    std::map<std::string, std::set<int>> word_lines;

    std::string line;
    int line_number = 0;

    // Nuskaitome failą eilutė po eilutės
    while (std::getline(input_file, line)) {
        ++line_number;
        std::istringstream iss(line); 
        std::string token; // Laikinas kintamasis žodžiams saugoti

        // Išvalome eilutę nuo nereikalingų simbolių ir skaidome į žodžius
        while (iss >> token) {
            std::string cleaned; 
            for (char c : token) {
                char lower = std::tolower(c); // Paverčiame simbolį į mažąsias raides
                if (std::isalpha(lower)) // Patikriname, ar simbolis yra raidė
                    cleaned += lower;

                else if (!cleaned.empty()) {
                    // Jei simbolis nėra raidė, bet jau turime surinktą žodį, įrašome jį
                    word_counts[cleaned]++;
                    word_lines[cleaned].insert(line_number);
                    cleaned.clear();
                }
            }
            // Jei po ciklo liko surinktas žodis, įrašome jį
            if (!cleaned.empty()) {
                word_counts[cleaned]++;
                word_lines[cleaned].insert(line_number);
            }
        }
    }
    input_file.close();

    std::string output_cr_name = "cross_reference.txt";
    std::ofstream output_cr(output_cr_name);
    if (!output_cr.is_open()) {
        std::cerr << "Nepavyko sukurti išvesties failo: " << output_cr_name << std::endl;
        return 1;
    }

    output_cr << "Pasikartojantys zodziai ir ju eiluciu numeriai:\n";
    output_cr << "--------------------------------------------------\n";

    for (const auto& pair : word_counts) {
        if (pair.second > 1) {
            output_cr << pair.first << " ("
                        << pair.second << " kartai): eilutes ";
            for (int ln : word_lines[pair.first]) {
                output_cr << ln << " ";
            }
            output_cr << "\n";
        }
    }

    output_cr.close();
    std::cout << "Rezultatai issaugoti faile: " << output_cr_name << std::endl;


    std::string output_filename = "output.txt";
    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Klaida: Nepavyko sukurti/atidaryti išvesties failo '" << output_filename << "'" << std::endl;
        return 1;
    }

    output_file << "Žodžiai, kurie tekste pasikartojo daugiau nei vieną kartą:\n";
    output_file << "--------------------------------------------------------------\n";

    int unique_words_total = 0;
    int frequent_words_count = 0;

    // std::map saugo elementus surūšiuotus pagal raktą (žodį)
    for (const auto& pair : word_counts) {
        // pair.first - žodis(raktas), paird.second - pasikartojimų skaičius
        unique_words_total++;
        if (pair.second > 1) { // Jei žodis pasikartojo daugiau nei 1 kartą

            output_file << pair.first << ": " << pair.second << "\n";
            frequent_words_count++;
        }
    }
    output_file.close();

    std::cout << "Rezultatai issaugoti faile: " << output_filename << std::endl;
    return 0;
}
