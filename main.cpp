#include <iostream>
#include <fstream>

std::string family[8][2] = {{"злаковые", "0"},
                            {"бобовые", "1"},
                            {"лелейные", "2"},
                            {"крестоцветные", "3"},
                            {"розоцветные", "4"},
                            {"пасленовые", "5"},
                            {"сложноцветные", "6"},
                            {"лютиковые", "7"}
};


int required[8][2] = {
        {0, 4},
        {1, 4},
        {2, 3},
        {3, 4},
        {4, 4},
        {5, 3},
        {6, 4},
        {7, 3}
};

int current[9][2] = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0},
        {8, 0}
};


/*
 * required flowers for each type
 злаковые - 4
 бобовые - 4
 лелейные - 3
 крестоцветные - 4
 розоцветные - 4
 пасленовые - 3
 сложноцветные - 4
 лютиковые - 3
 **required
 */

int getid(std::string type){
    for(int i = 0; i < 8; ++i){
        if (family[i][0] == type)
            return std::stoi(family[i][1]);
        else
            continue;
    }
}


void create_file(std::string file_path){
    std::ofstream fout("herb_data.txt");
    if (!fout){
        perror("Error while creating file");
    }
    else{
        std::cout << "File created" << std::endl;
        fout.close();
    }

}



void add_plant(std::string plant_name, std::string plant_type){
    std::ofstream writer("herb_data.txt", std::ios_base::app);
    if (writer.bad()){
        std::cout << "Data file isn`t present yet" << std::endl;
        writer.close();
    }
    else{
        int id_for_type = getid(plant_type);
        writer << plant_name << ":" << id_for_type << std::endl;
        writer.close();
    }

}

void add_plant(std::string plant_name, int plant_id){
    std::ofstream writer("herb_data.txt", std::ios_base::app);
    if (writer.bad()){
        std::cout << "Data file isn`t present yet" << std::endl;
        writer.close();
    }
    else{
        writer << plant_name << ":" << plant_id << std::endl;
        writer.close();
    }

}



void printCurrentHerb(std::string file = "herb_data.txt"){
    std::ifstream reader(file);
    if (reader.bad()){
        std::clog << "Error while opening file" << std::endl;
        return;
    }
    else
        std::cout << "Your current collection includes:" << std::endl;
    std::string buffer;
    do {
        getline(reader, buffer, '\n');
        std::cout << buffer << std::endl;
    } while(!buffer.empty());
}

std::string* split(std::string source, char splitter){
    std::string first = source;
    std::string second = source;
    int temp_pos = source.find(splitter);
    first.erase(temp_pos);
    second.erase(0, temp_pos + 1);
    std::string* final = new std::string[2];
    final[0] = first;
    final[1] = second;
    return final;
}



void refresh(){
    std::string buffer;
    std::ifstream reader("herb_data.txt");
    std::string* temp = new std::string[2];
    if (reader.bad()){
        std::clog << "Error while opening file" << std::endl;
        delete[] temp;
        return;
    }
    else{
        std::clog << "File opened successful in refresh" << std::endl;

    }
    do{
        std::getline(reader, buffer, '\n');
        try {
            temp = split(buffer, ':');
        }
        catch (std::exception ex){
            break;
        }
        int temp_id = std::stoi(temp[1]);
        current[temp_id][1] += 1;
    } while(!buffer.empty());
    delete[] temp;
}



void checkAndPrint(){
    refresh();
    for (int i = 0; i < 8; ++i){
        if (current[i][1] >= required[i][1]){
            std::cout << "You have enough " << family[i][0] << " plants" << std::endl;
        }
        else {
            std::cout << "You need " << required[i][1] - current[i][1] << " more " << family[i][0] << " plants" << std::endl;
        }
    }
}

int main() {
    std::cout << "\t-==Welcome to the Herbarium 2.0!==-\n"
    << "If you want to enter selection mode input 'change'\n"
    "If you want to check your plants collection input 'check'\n"
    "Type 'close' to exit Herbarium 2.0"
    << std::endl;
    std::string command;
    while(true) {
        std::cin >> command;
        if (command == "change") {
            std::cout << "You are in adding mode now.\n\n" << "Id list for each type:" << std::endl;
            for (int i = 0; i < 8; ++i) {
                std::cout << family[i][0] << " - " << family[i][1] << std::endl;
            }
            std::cout
                    << "To add plant in collection type it in format ['plant_name:plant_id'].\n To exit adding mode type 'back'"
                    << std::endl;
            while (command != "back") {
                std::cin >> command;
                if (command == "back"){
                    break;
                }
                std::string* words = split(command,':');
                try {
                    add_plant(words[0], std::stoi(words[1]));
                }
                catch (std::exception ex) {
                    std::cout << "incorrect input" << std::endl;
                }
            }
            std::cout << "returning to main menu" << std::endl;
        } else if (command == "check") {
            checkAndPrint();
        } else if (command == "close") {
            break;
        } else {
            std::cout << "unknown command" << std::endl;;
        }
    }
    setlocale(LC_ALL, "rus");
    return 0;
}
