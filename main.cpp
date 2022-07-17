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
    std::ofstream writer("herb_data.txt");
    if (writer.bad() == true){
        std::cout << "Data file isn`t present yet" << std::endl;
        writer.close();
    }
    else{
        writer.fill(':');
        writer << plant_name << plant_type << std::endl;
        writer.close();
    }

}

int main() {

    setlocale(LC_ALL, "rus");

    return 0;
}
