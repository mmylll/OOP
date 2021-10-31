#include <iostream>
#include "FamilyMart.h"

// modify this file to test your logics
// TODO

int main() {

    FamilyMart *test_mart = new FamilyMart();
    string filename1,filename2;
    for (int i= 0; i<2; i++){
        std::cout << "Today is beginning" << std::endl;
        std::cout << "please input purchase list file name" << std::endl;
        std::cin>>filename1;
        test_mart->purchase_file(filename1);
        std::cout << "please input sell list file name" << std::endl;
        std::cin>>filename2;
        test_mart->sell_file(filename2);
        std::cout << "This day is over" << std::endl;
        std::cout << "turnover:" << test_mart->show_turnover() << std::endl;
    }
    delete test_mart;

    return 0;
}
