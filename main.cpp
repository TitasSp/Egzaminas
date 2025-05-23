#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

int main()
{
    std::string filename = "input.txt";
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::map<std::string, int> word_counts; // Asociatyvus konteineris zodziu pasikartojimams
    std::string word; // Laikinas kintamasis kiekvienam nuskaitytam zodziui

    // Skaitome failą žodis po žodžio (atskirtus tarpais)
    while (input_file >> word) {
        std::string cleaned_word_segment;
        for (char raw_char : word) {
            char lower_char = std::tolower(raw_char);
            if (std::isalpha(lower_char)) {
                cleaned_word_segment += lower_char;
            } else {
                // Jei sutinkamas ne alphabetinis simbolis ir jau turime sukaupę dalį žodžio,
                // ją įrašome ir pradedame kaupti iš naujo.
                if (!cleaned_word_segment.empty()) {
                    word_counts[cleaned_word_segment]++;
                    cleaned_word_segment.clear();
                }
            }
        }
        // Po ciklo per tokeno simbolius, jei liko sukaupta žodžio dalis
        if (!cleaned_word_segment.empty()) {
            word_counts[cleaned_word_segment]++;
        }
    }
    input_file.close();

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

    std::cout << "Results saved in file: '" << output_filename << "'" << std::endl;
    std::cout << "Unique words in text: " << unique_words_total << std::endl;
    std::cout << "More than once repeated: " << frequent_words_count << std::endl;


    return 0;
}
