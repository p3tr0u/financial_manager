#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>

typedef struct{
    double money;
    std::string person;   //Sender or receiver.
    int type;   //0 if expense, 1 if income.
    std::string date;
    std::string description;
} transaction;

std::vector<transaction> trans_array;

void print_menu(){
    std::cout << " [P]rint transaction history.\n\
 [A]dd transaction.\n\
 [E]rase transaction\n\
 [C]lose program\n\
 Show [B]alance\n\
 [S]ave to file\n\
 [L]oad to file\n\n";
}

void print_trans(){
    if(trans_array.size() == 0){
        std::cout << "No transactions.\n\n";
        return;
    }
    for(unsigned int i=0; i < trans_array.size(); i++){
        std::cout << "\n/#################[ " << i+1 << " ]#################/\n\n";
        std::cout << "          Amount:  " << trans_array[i].money << '$' << std::endl;
        if(trans_array[i].type){
            std::cout << "          Type:  Income" << std::endl;
            std::cout << "          Received by:  " << trans_array[i].person << std::endl;
        }
        else{
            std::cout << "          Type:  Expenditure" << std::endl;
            std::cout << "          Sent to:  " << trans_array[i].person << std::endl;
        }
        std::cout << "          Date:  " << trans_array[i].date << std::endl;
        std::cout << "          Description:  " << trans_array[i].description << std::endl;;

    }
    std::cout << "\n/#######################################/\n\n";
}

void add_trans(){
    std::cout << "\nAmount: ";
    double amount;
    std::cin >> amount;

    char type;
    do{
        std::cout << "[E]xpence / [I]ncome: ";
        std::cin >> type;
        if(type != 'e' and type != 'E' and type != 'i' and type != 'I'){
            std::cout << "Please only input 'E' or 'I'.\n";
        }
    }
    while(type != 'e' and type != 'E' and type != 'i' and type != 'I');

    int flag;
    if(type == 'e' or type == 'E'){
        flag = 0;
    }
    else{
        flag = 1;
    }

    std::string person;
    if(flag){
        std::cout << "By: ";
    }
    else{
        std::cout << "To: ";
    }

    std::cin.ignore();
    std::getline(std::cin, person);

    std::cout << "Date: ";
    std::string date;
    std::cin >> date;

    std::cout << "Description: ";
    std::cin.ignore();
    std::string desc;
    std::getline(std::cin, desc);

    trans_array.push_back({amount, person, flag, date, desc});
    std::cout << "Done! Transaction #" << size(trans_array) << " added.\n\n";
}

void remove_by_id(){
    unsigned int element;
    std::cout << "\nWhich # transaction would you like to erase? ";
    std::cin >> element;
    if(trans_array.size() < element){
        std::cout << "\nElement " << element << " doesn't exist.\n\n";
        return;
    }
    trans_array.erase(trans_array.begin() + element-1);
    std::cout << "\nDone! Transaction #" << element << " erased.\n\n";
}

void show_balance(){
    double total_bal = 0;
    for(unsigned int i=0; i < trans_array.size(); i++){
        if(trans_array[i].type){
            total_bal+=trans_array[i].money;
        }
        else{
            total_bal-=trans_array[i].money;
        }
    }
    std::cout << "Total balance: " << total_bal << "$\n" << std::endl;
}

void save_to_file(){
    std::cout << "File name: ";
    std::string filename;
    std::cin >> filename;
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "File not found.\n";
        return;
    }

    for(unsigned int i=0; i < trans_array.size(); i++){
        file << trans_array[i].money << '\n';
        file << trans_array[i].person << '\n';
        file << trans_array[i].type << '\n';
        file << trans_array[i].date << '\n';
        file << trans_array[i].description << '\n';
    }
    std::cout << "\n\nDone! Saved to " << filename << ".\n\n";
}

void load_from_file(){
    std::vector<transaction> temp_array;

    std::cout << "File name: ";
    std::string filename;
    std::cin >> filename;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "File not found.\n";
        return;
    }

    std::string line;
    int lines_count = 0;
    double money;
    std::string person;
    int type;
    std::string date;
    std::string description;

    while(std::getline(file, line)){
        lines_count++;
        switch(lines_count){
            case(1):
                money = std::stod(line);
                break;
            case(2):
                person = line;
                break;
            case(3):
                type = std::stod(line);
                break;
            case(4):
                date = line;
                break;
            case(5):
                description = line;
                temp_array.push_back({money, person, type, date, description});
                lines_count = 0;
        }
    }
    std::cout << "Done! Loaded from " << filename << ".\n\n";
    trans_array = temp_array;
}

int main(){
    std::cout << "\nWelcome to Financial Manager 3000! What would you like to do?\n\n";
    char choice;
    while(1){
        print_menu();
        std::cin >> choice;
        switch (choice){
            case 'p':
            case 'P':
                print_trans();
                break;
            case 'a':
            case 'A':
                add_trans();
                break;
            case 'e':
            case 'E':
                remove_by_id();
                break;
            case 'b':
            case 'B':
                show_balance();
                break;
            case 's':
            case 'S':
                save_to_file();
                break;
            case 'l':
            case 'L':
                load_from_file();
                break;
            case 'c':
            case 'C':
                std::cout << "Goodbye!\n\n";
                return 0;
        }
    }
}
