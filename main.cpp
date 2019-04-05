#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream inFile;
        
    inFile.open("/Users/mac/Desktop/project/Team_PrOJECT/SHM/Build/Products/Debug/TEXT.txt");
    
    vector<string> temp;
    char inputString[255];
    
    if(inFile.is_open() == false){
            cout<<"파일이 없습니다"<<endl;
    }else{
        while(!inFile.eof()){
            
            inFile.getline(inputString, 255);
            
            temp.push_back(inputString);
            memset(inputString,NULL,255);
        }
        inFile.close();
    }
    int size = (int)temp.size();
    for(int i = 0; i<size; i++){
        cout<<temp[i]<<endl;
    }
    //=====LIST=====
    
    for(int i = 0; i<temp.size();i++){
        string pStr = temp[i];
        
    }
    
    //==============
}
