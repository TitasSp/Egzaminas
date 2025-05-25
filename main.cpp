#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <cctype>
#include <regex>

// Patikrina ar žodis yra URL
bool isUrl(const std::string& token) {
    std::regex url_regex(R"(^(https?:\/\/)?(www\.)?[a-zA-Z0-9\.-]+\.[a-z]{2,}(\/\S*)?$)");
    return std::regex_match(token, url_regex);
}

// Funkcija URL'ų suradimui ir išvedimui į failą
bool extractUrls(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input(input_filename);
    std::ofstream output(output_filename);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Nepavyko atidaryti failu URL." << std::endl;
        return false;
    }

    std::string line;
    std::set<std::string> found_urls;

    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            if (isUrl(token)) {
                found_urls.insert(token);
            }
        }
    }

    output << "Rasti URL adresai:\n";
    output << "-------------------\n";
    for (const auto& url : found_urls) {
        output << url << "\n";
    }

    input.close();
    output.close();

    std::cout << "URL issaugoti faile: " << output_filename << std::endl;
    return true;
}

// Funkcija žodžio išvalymui ir normalizavimui
std::string normalizeWord(const std::string& token) {
    std::string cleaned;
    for (char c : token) {
        char lower = std::tolower(c);
        if (std::isalpha(lower)) {
            cleaned += lower;
        }
    }
    return cleaned;
}

// Funkcija failo nuskaitymui ir žodžių analizei
bool analyzeTextFile(const std::string& filename, 
                     std::map<std::string, int>& word_counts,
                     std::map<std::string, std::set<int>>& word_lines) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Klaida atidarant faila: " << filename << std::endl;
        return false;
    }

    std::string line;
    int line_number = 0;

    // Nuskaitome failą eilutė po eilutės
    while (std::getline(input_file, line)) {
        ++line_number;
        std::istringstream iss(line);
        std::string token;

        // Skaidome eilutę į žodžius
        while (iss >> token) {
            std::string normalized = normalizeWord(token);
            
            if (!normalized.empty()) {
                word_counts[normalized]++;
                word_lines[normalized].insert(line_number);
            }
        }
    }
    
    input_file.close();
    return true;
}

// Funkcija kryžminių nuorodų failo sukūrimui
bool createCrossReferenceFile(const std::string& filename,
                              const std::map<std::string, int>& word_counts,
                              const std::map<std::string, std::set<int>>& word_lines) {
    std::ofstream output_cr(filename);
    if (!output_cr.is_open()) {
        std::cerr << "Nepavyko sukurti isvesties failo: " << filename << std::endl;
        return false;
    }

    output_cr << "Pasikartojantys zodziai ir ju eiluciu numeriai:\n";
    output_cr << "--------------------------------------------------\n";

    for (const auto& pair : word_counts) {
        if (pair.second > 1) {
            output_cr << pair.first << " (" << pair.second << " kartai): eilutes ";
            for (int ln : word_lines.at(pair.first)) {
                output_cr << ln << " ";
            }
            output_cr << "\n";
        }
    }

    output_cr.close();
    return true;
}

// Funkcija pagrindinių rezultatų failo sukūrimui
bool createOutputFile(const std::string& filename,
                      const std::map<std::string, int>& word_counts) {
    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
        std::cerr << "Klaida: Nepavyko sukurti/atidaryti isvesties failo '" << filename << "'" << std::endl;
        return false;
    }

    output_file << "Zodziai, kurie tekste pasikartojo daugiau nei viena karta:\n";
    output_file << "--------------------------------------------------------------\n";

    int unique_words_total = 0;
    int frequent_words_count = 0;

    // std::map saugo elementus surūšiuotus pagal raktą (žodį)
    for (const auto& pair : word_counts) {
        unique_words_total++;
        if (pair.second > 1) {
            output_file << pair.first << ": " << pair.second << "\n";
            frequent_words_count++;
        }
    }

    output_file.close();
    
    std::cout << "Rasta unikaliu zodziu: " << unique_words_total << std::endl;
    std::cout << "Daugiau nei karta pasikartojanciu zodziu: " << frequent_words_count << std::endl;
    
    return true;
}

int main() {
    const std::string input_filename = "input.txt";
    const std::string output_filename = "output.txt";
    const std::string cross_ref_filename = "cross_reference.txt";
    const std::string url_output_file = "urls.txt";

    // Duomenų struktūros žodžių saugojimui
    std::map<std::string, int> word_counts;          // žodis → pasikartojimų skaičius
    std::map<std::string, std::set<int>> word_lines; // žodis → eilučių numeriai

    // Analizuojame įvesties failą
    if (!analyzeTextFile(input_filename, word_counts, word_lines)) {
        return 1;
    }

    // Kuriame cross reference faila
    if (createCrossReferenceFile(cross_ref_filename, word_counts, word_lines)) {
        std::cout << "Cross-reference issaugotas faile: " << cross_ref_filename << std::endl;
    }

    // Kuriame pagrindiniu rezultatu faila
    if (createOutputFile(output_filename, word_counts)) {
        std::cout << "Rezultatai issaugoti faile: " << output_filename << std::endl;
    }

    if(extractUrls(input_filename, url_output_file)){
        std::cout << "URL adresai issaugoti faile: " << url_output_file << std::endl;
    }


    return 0;
}