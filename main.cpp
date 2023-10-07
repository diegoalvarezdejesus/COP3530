#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <cctype>
#include <algorithm>
#include <regex>
#include "BST.h"
#include "BST.cpp"

std::vector<std::string> methods{"insert", "remove", "search" , "printInorder", "printPreorder", "printPostorder", "printLevelCount", "removeInorder"};

bool numbersAndSpecial(const std::string& string){
    for (char ch : string)
    {
        if (std::isdigit(ch) || !std::isalpha(ch)){
            return true;
        }
    }
    return false;
}

int main(){
    std::string commands;
    std::getline(std::cin, commands);

    BST gatorBST;
    for (int i = 0; i < stoi(commands); i++)
    {
        std::string inputline;
        std::getline(std::cin, inputline);

        std::istringstream line(inputline);
        std::string method;
        line >> method;
        std::string name;
        line >> name;
        std::string IDstr;
        line >> IDstr;
        // regex for name
        std::regex nameR("^\"[A-Za-z]+\"$");
        // regex for id
        std::regex idR("^\\d{8}$");
        
        // find method
        if (method == "insert")
        {
            if (std::regex_match(name, nameR) && std::regex_match(IDstr, idR)) // checking name and ID
            {
                gatorBST.insert(std::stoi(IDstr), name.substr(1, name.size() - 2));
            }
            else{
                std::cout << "unsuccessful\n";
            }
        }
        else if (method == "remove")
        {
            if (std::regex_match(name, idR)) // use name cause its the second term
            {
                gatorBST.remove(std::stoi(name));
            }
            else{
                std::cout << "unsuccessful\n";
            }
        }
        else if (method == "search") // searchID and searchNAME
        {
            if (std::regex_match(name, idR)){ // use name cause its in second position
                gatorBST.searchID(std::stoi(name));
            }
            else if (std::regex_match(name, nameR))
            {
                std::string newname = name.substr(1, name.size() - 2);
                gatorBST.searchNAME(newname);
            }
            else{
                std::cout << "unsuccessful\n";
            }
            
        }
        else if (method == "printInorder")
        {
            gatorBST.inorder();
        }
        else if (method == "printPreorder")
        {
            gatorBST.preorder();
        }
        else if (method == "printPostorder")
        {
            gatorBST.postorder();
        }
        else if (method == "printLevelCount")
        {
            gatorBST.printlevelcount();
        }
        else if (method == "removeInorder")
        {
            gatorBST.removeInorder(std::stoi(name)); // use name cause in second
        }
        else{
            std::cout << "unsuccessful\n";
        }
    }
    return 0;
}



