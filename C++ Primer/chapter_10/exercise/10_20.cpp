#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

void elimDups(std::vector<std::string> &s){
    sort(s.begin(), s.end());
    auto iter = unique(s.begin(), s.end());
    s.erase(iter, s.end());
}

std::string make_plural (size_t ctr, const  std::string& word, const std::string& ending)
{
    return (ctr>1) ? word + ending : word;
}
void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz){
    elimDups(words);
    stable_sort(words.begin(), words.end(), [](const std::string &a, const std::string &b){ return a.size() < b.size();});
    int count = count_if(words.begin(), words.end(), [sz](const std::string &s){ return (s.size() > sz);});   
    std::cout << count << " " << make_plural(count, "word", "s") << " of length" << sz << " or longer " << std::endl;
    for_each(words.end() - count, words.end(), [](const std::string &s) { std::cout << s << " ";});
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> words = {"nihao", "hello" ,"bye", "bec", "sfs","fasdfasdf", "f134dsgq"};
    biggies(words, 6);
    getchar();
    return 0;
}