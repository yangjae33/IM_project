#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <deque>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream inFile;
        
    inFile.open("/Users/mac/Desktop/project/Team_PrOJECT/SHM/Build/Products/Debug/TEXT.txt");
    deque<string> stk;
    deque<string> content;
    char inputString[255];
    
    if(inFile.is_open() == false){
            cout<<"파일이 없습니다"<<endl;
    }else{
        while(!inFile.eof()){
            inFile.getline(inputString, 255);
            content.push_back(inputString);
            memset(inputString,NULL,255);
        }
        inFile.close();
    }
    //=====LIST=====
    
    int astr_flag = 0;
    int sharp_flag = 0;
    char buf[255];
    //cout<<content.size()<<endl;
    
    for(int i = 0; i<content.size(); i++){
        
        string pStr = content[i];
        int k = 0;
        int astrcount = 0;
        int sharpcount = 0;
        
        for(int j = 0; j<=pStr.length(); j++){
            astrcount = 0;
            if(j == pStr.length()&&strlen(buf)>0){
                stk.push_back(buf);
                stk.push_back("</li>\n");
                memset(buf,NULL,255);
                break;
            }
            if(pStr[j] == '*'){
                if(strlen(buf)>0){
                    stk.push_back(buf);
                    memset(buf,NULL,255);
                }
                do{
                    //counting the number of astrs
                    astrcount++;
                    j++;
                }while(j<pStr.length() && pStr[j] == '*');
                j--;
                
                if(astrcount > astr_flag){   //overlapped
                    astr_flag++;
                    stk.push_back("<ul>\n");
                    stk.push_back("<li>");
                }
                else if(astrcount < astr_flag){  //return
                    stk.push_back("</ul>\n");
                    stk.push_back("<li>");
                    astr_flag--;
                }
                else{   //each row has same astr counts
                    stk.push_back("<li>");
                }
            }
            else if(pStr[j] =='#'){
                if(strlen(buf)>0){
                    stk.push_back(buf);
                    memset(buf,NULL,255);
                }
                do{
                    //counting the number of sharps
                    sharpcount++;
                    j++;
                }while(j<pStr.length() && pStr[j] == '#');
                j--;
                
                if(sharpcount > sharp_flag){   //overlapped
                    sharp_flag++;
                    stk.push_back("<ol>\n");
                    stk.push_back("<li>");
                }
                else if(sharpcount < sharp_flag){  //return
                    stk.push_back("</ol>\n");
                    stk.push_back("<li>");
                    sharp_flag--;
                }
                else{   //each row has same sharp counts
                    stk.push_back("<li>");
                }
            }
            else{
                buf[k++] = pStr[j];
            }
        }
    }
    while(astr_flag>0){
        stk.push_back("</ul>\n");
        astr_flag--;
    }
    //cout<<stk.size()<<endl;
    int size = (int)stk.size();
    for(int i = 0; i<size;i++){
        cout<<stk.front();
        stk.pop_front();
    }
    //==============
}
