#include <iostream>
#include <string>


int main(){
    std::string numbers("23746");
    std::string letters("abcdRE");
    std::string s("ab2c3d7R4E6");
    std::string::size_type pos = 0;
    //1、使用find_first_of
    // 查找数字
    // while((pos = s.find_first_of(numbers, pos)) != std::string::npos)
    // {
    //     std::cout << "found number at index " << pos << " " << "element is " << s[pos] << std::endl;
    //     ++pos;
    // }

    // 查找字母
    // while((pos = s.find_first_of(letters, pos)) != std::string::npos)
    // {
    //     std::cout << "found letter at index " << pos << " " << "element is " << s[pos] << std::endl;
    //     ++pos;
    // }

    //2、使用find_first_not_of
    //查找字母
    // while((pos = s.find_first_not_of(numbers, pos)) != std::string::npos)
    // {
    //     std::cout << "found letter at index " << pos << " " << "element is " << s[pos] << std::endl;
    //     ++pos;
    // }

    //查找数字
    while((pos = s.find_first_not_of(letters, pos)) != std::string::npos)
    {
        std::cout << "found number at index " << pos << " " << "element is " << s[pos] << std::endl;
        ++pos;
    }
}