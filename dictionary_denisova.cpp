#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <unordered_map>

// Comparator to sort by greater number and word alphabetically
bool sortByVector(const std::pair<int,std::string>& a, 
                 const std::pair<int,std::string>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first > b.first;    
}

int main(int argc, char *argv[])
{
    using namespace std;
    if (argc < 3) {
        std::cout << "Please, add input.txt and output.txt files\n";
        std::cout << "Example: ./dict in.txt out.txt\n";
        return 0;
    }
    const char * in_puth = argv[1];
    const char * out_puth = argv[2];

    FILE * fin = fopen(in_puth, "r");
    if (fin == NULL) {
        std::cout << "Cannot open file: " << in_puth << "\n";
        return 0;
    }

    unordered_map<string, int> dictionary;
    int N = 100; // line size

    char str[N];
    string word = "";
    while (fgets(str, N, fin)!=NULL) {
        for (auto s : str) {
            if (s == '\0') {
                break;
            }
            if ((s >= 'A' && s <= 'Z')) {
                word+=tolower(s);
            }
            else if ((s >= 'a' && s <= 'z')) {
                word+=s;
            }
            else if (word != "") {
                dictionary[word]++;
                word = "";
            }
        }
    }    
    fclose(fin);

    vector<pair<int, string>> order_dict;
    for (auto line : dictionary) {
        order_dict.push_back({line.second, line.first});
    }
    sort(order_dict.begin(), order_dict.end(), sortByVector);

    FILE * fout = fopen(out_puth, "w");
    for (auto line : order_dict) {
         fprintf(fout, "%i %s\n", line.first, line.second.c_str());
    }

    fclose(fout);

    return 0;
}