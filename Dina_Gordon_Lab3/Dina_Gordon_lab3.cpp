#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <bitset>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

//reads CSV file and grabs  the data
vector<string> readFromFIle(string file_name, string search_term){
    vector<string> record;
    ifstream file;
    file.open(file_name);

    bool found_record = false;

    string col1, col2, col3, col4, col5, col6;
    while(getline(file, col1, ',') && !found_record){
        getline(file, col2, ',');
        getline(file, col3, ',');
        getline(file, col4, ',');
        getline(file, col5, ',');
        getline(file, col6, '\n');

        if(col1 == search_term){
            found_record = true;
            record.push_back(col1);
            record.push_back(col2);
            record.push_back(col3);
            record.push_back(col4);
            record.push_back(col5);
            record.push_back(col6);
        }
    }

    /*
    for(string i: record){
        cout << i << " ";
    }
    */
   file.close();

    return record;

};


int main(){
    //base intruction to its decimal, used to get binary string
    map<string, int> baseX {{"x0", 0}, {"x1", 1}, {"x2", 2}, {"x3", 3}, {"x4", 4}, {"x5", 5}, {"x6", 6}, {"x7", 7}, {"x8", 8}, {"x9", 9}, {"x10", 10},
    {"x11", 11}, {"x12", 12}, {"x3", 13}, {"x14", 14}, {"x15", 15}, {"x16", 16}, {"x17", 17}, {"x18", 18}, {"x19", 19}, {"x20", 20},
    {"x21", 21}, {"x22", 22}, {"x23", 23}, {"x24", 24}, {"x25", 25}, {"x26", 26}, {"x27", 27}, {"x28", 28}, {"x29", 29}, {"x30", 30},{"x31", 31}}
    ;


    string intruc;


    while(intruc != "quit"){

    //the Instruction (ex: add, addi) will be grabbed first then will go to the correct format to enter the rest of the instructions
    cout << "Enter an Instruction: ";
    cin >> intruc;

    //grab data from csv file
    vector<string> data = readFromFIle("RISC-V_Instructions (2).csv", intruc);

    //get binary string for opcode, other data binary strings will be collected depending on the opcode
    //stoi will turn the binary string into a int, then will be turned back but in the right bits
    string opcode = bitset<7>(stoi(data[1], 0, 2)).to_string(); // 7 bits
    string func3 = data[2]; 
    string func7 = data[3];
    string type = data[4]; //R, I, S, B, J, U,
    string immVal = data[5];



    //depending on the opcode certain data will be used

    string rs2; //5 bits
    string rs1; //5 bits
    string rd; //5 bits

    //type I
    string Imm110; // 12 bits

    //type S
    string Imm115; //7 bits
    string Imm40; // 5 bits

    //type B
    string Imm12105; //7 bits
    string Imm4111; //5 bits

    //type U
    string Imm3212; //20 bits

    //type J
    string Imm2001111912; //20 bits

    //swtich statments didn't work with strings, had to resort to strings
    //each if statement follows the same pattern. Ask user to input intructions/code (different order for different types), then turn that data into binary strings adding them at the end

    //for type R opcode
    if (type == "R"){
       // func3 = bitset<3>(stoi(func3, 0, 2)).to_string();
        //func7 = bitset<7>(stoi(func7, 0, 2)).to_string();

        cout << "enter the base register names (ex:rd_rs1_rs2): ";
        cin >> rd >> rs1 >> rs2;

        rd = bitset<5>(baseX[rd]).to_string();
        rs1 = bitset<5>(baseX[rs1]).to_string();
        rs2 = bitset<5>(baseX[rs2]).to_string();

        //func7 + rs2 + rs1 + func3 + rd + opcode
        cout << func7 + rs2 + rs1 + func3 + rd + opcode << "\n";
    }

    //for type I opcode
    if (type == "I"){
        //func3 = bitset<3>(stoi(func3, 0, 2)).to_string();
        int imm;

        //since 'ebreak' and 'ecall' are special we know what to output
        if (intruc == "ebreak")
        {
            Imm110 = bitset<12>(1).to_string();
            rd = bitset<5>(0).to_string();
            rs1 = bitset<5>(0).to_string();
        }
        else if (intruc == "ecall")
        {
            Imm110 = bitset<12>(0).to_string();
            rd = bitset<5>(0).to_string();
            rs1 = bitset<5>(0).to_string();
        }

        //different type I opcode
        else if ((intruc == "lb") || (intruc == "lbu") || (intruc == "lh") || (intruc == "lhu") || (intruc == "lw"))
        {
           cout << "enter the base register names (ex:rd_imm_rs1): ";
            cin >> rd >> imm >> rs1;
            rd = bitset<5>(baseX[rd]).to_string();
            rs1 = bitset<5>(baseX[rs1]).to_string();
            Imm110 = bitset<12>(imm).to_string();
        }
        
        //default if instruction is neither 'ebreak'/'ecall' or a special I
        else{
            cout << "enter the base register names (ex:rd_rs1_imm): ";
            cin >> rd >> rs1 >> imm;

            rd = bitset<5>(baseX[rd]).to_string();
            rs1 = bitset<5>(baseX[rs1]).to_string();
            Imm110 = bitset<12>(imm).to_string();
        }

        //imm[11:0] + rs1 + func3 + rd + opcode
        cout << Imm110 + rs1 + func3 + rd + opcode << "\n";
    }

    //for type S opcode
    if (type == "S"){
        int imm;
        //func3 = bitset<3>(stoi(func3, 0, 2)).to_string();
        cout << "enter the base register names (ex:rs2_imm_rs1): ";
        cin >> rs2 >> imm >> rs1;
            rs2 = bitset<5>(baseX[rs2]).to_string();
            rs1 = bitset<5>(baseX[rs1]).to_string();

            string IMM = bitset<32>(imm).to_string();


            Imm115 = IMM.substr(20,7);
            
            Imm40 = IMM.substr(27,5);

        //imm[11:5] + rs2 + rs1 + func3 + imm[4:0] + opcode
        cout << Imm115 + rs2 + rs1 + func3 + Imm40 + opcode << "\n";
    }

    //for type B opcode
    if (type == "B"){
        int label;
        //func3 = bitset<3>(stoi(func3, 0, 2)).to_string();
        cout << "enter the base register names (ex:rs1_rs2_label): ";
        cin >> rs1 >> rs2 >> label;

        rs2 = bitset<5>(baseX[rs2]).to_string();
        rs1 = bitset<5>(baseX[rs1]).to_string();

        string IMM = bitset<32>(label).to_string();

        Imm12105 = IMM[19] + IMM.substr(21,6);

        Imm4111 =  IMM.substr(27,4) + IMM[20];

        //imm[12|10:5] + rs2 + rs1 + func3 + imm[4:1|11] + opcode
        cout << Imm12105 + rs2 + rs1 + func3 + Imm4111 + opcode << "\n";
    }


    //for type U opcode
    if (type == "U"){
        int label;
        cout << "enter the base register names (ex:rd_label): ";
        cin >> rd >> label;

        rd = bitset<5>(baseX[rd]).to_string();
        Imm3212 = bitset<20>(label).to_string();
        
        //imm[31:12] + rd + opcode
        cout << Imm3212 + rd + opcode << "\n";
    }

    //for type J opcode
    if (type == "J"){
        int imm;
        cout << "enter the base register names (ex:rd_imm): ";
        cin >> rd >> imm;

        rd = bitset<5>(baseX[rd]).to_string();

        string IMM = bitset<32>(imm).to_string();

        Imm2001111912 = IMM[11] + IMM.substr(21,10) + IMM[20] + IMM.substr(12,8);

        //imm[20|10:1|11|19:12] + rd + opcode
        cout << Imm2001111912 + rd + opcode << "\n";
    }
    }

    return 0;
} 