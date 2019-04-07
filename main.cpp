#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <deque>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream inFile;
        
    inFile.open("/Users/mac/Desktop/project/Team_PrOJECT/SHM/Build/Products/Debug/TEXT.txt");
    deque<string> html_tag;
    deque<string> sub_list_tag;
    deque<string> content;
    char inputString[255];
    
    if(inFile.is_open() == false){
            cout<<"Error : file not found"<<endl;
    }else{
        while(!inFile.eof()){
            inFile.getline(inputString, 255);
            content.push_back(inputString);
            memset(inputString,NULL,255);
        }
        inFile.close();
    }
    
    //=====LIST=====
    
    int total_word_count = 0;
    char buf[255];
    
    for(int i = 0; i<content.size(); i++){
        string pStr = content[i];
        int list_word_count = 0;
        int k = 0;
        string sharp_star="";
        for(int j = 0; j<=pStr.length(); j++){
            list_word_count = 0;
            if(j == pStr.length()&&strlen(buf)>0){
                html_tag.push_back(buf);
                html_tag.push_back("</li>\n");
                memset(buf,NULL,255);
                break;
            }
            if(pStr[j] == '*'||pStr[j] == '#'){
                if(strlen(buf)>0){
                    html_tag.push_back(buf);
                    memset(buf,NULL,255);
                }
                while(j<pStr.length() && (pStr[j] == '*'||pStr[j] == '#')){
                    //counting the number of astrs,sharps
                    list_word_count++;
                    j++;
                }
                j--;
                if(pStr[j] == '*')
                    sharp_star = "<ul>\n";
                else if(pStr[j] == '#')
                    sharp_star = "<ol>\n";
                
                if(list_word_count > total_word_count){   //overlapped
                    total_word_count++;
                    html_tag.push_back(sharp_star);
                    html_tag.push_back("<li>");
                    sharp_star.insert(1,"/");
                    sub_list_tag.push_back(sharp_star);
                }
                else if(list_word_count < total_word_count){  //return
                    html_tag.push_back(sub_list_tag.back());
                    sub_list_tag.pop_back();
                    html_tag.push_back("<li>");
                    total_word_count--;
                }
                else{   //each row has same astr counts
                    html_tag.push_back("<li>");
                }
            }
            /*
            else if(pStr[j] == '{' && j+1 < pStr.length()){
                if(pStr[j+1] == '&'){
                    html_tag.push_back("<table>");
                    while(!(pStr[j] == '&' && j+1 < pStr.length())){
                        if(pStr[j+1] == '}'){
                            html_tag.push_back("</table>");
                            break;
                        }
                        if(j > pStr.length()){
                            cout<<"Error"<<endl;
                            return 0;
                        }
                        
                    }
                }
                else{
                    cout<<"Error"<<endl;
                    return 0;
                }
            }*/
            
            else if (pStr[j] == '{' &&(j + 2 < pStr.length())) {
                if (pStr[j + 1] == '!' &&pStr[j + 2] == '!') {
                    if(strcmp(buf,"") != 0){html_tag.push_back(buf);}
                    memset(buf, NULL, 255);
                    html_tag.push_back("<b>");
                    k=0; //buffer index init
                    j += 2;
                }
                else if (pStr[j + 1] == '_' &&pStr[j + 2] == '_') {
                    if(strcmp(buf,"") != 0){html_tag.push_back(buf);}
                    memset(buf, NULL, 255);
                    html_tag.push_back("<u>");
                    k=0;
                    j += 2;
                }
                else if (pStr[j + 1] == '/' && pStr[j + 2] == '/') {
                    if(strcmp(buf,"") != 0){html_tag.push_back(buf);}
                    memset(buf, NULL, 255);
                    html_tag.push_back("<i>");
                    k=0;
                    j += 2;
                }
                else{
                    cout<<"Error"<<endl;
                    return 0;
                }
            }
            else if (pStr[j] == '!' &&(j + 2 < pStr.length())) {
                if (pStr[j + 1] == '!' && pStr[j + 2] == '}') {
                    if(strcmp(buf,"") != 0){html_tag.push_back(buf);}
                    memset(buf, NULL, 255);
                    html_tag.push_back("</b>");
                    k=0;
                    j += 2;
                }
                else{
                    cout<<"Error"<<endl;
                    return 0;
                }
            }
            else if (pStr[j] == '_'&&(j + 2 < pStr.length())) {
                if (pStr[j + 1] == '_'&&pStr[j + 2] == '}') {
                    if(strcmp(buf,"") != 0){html_tag.push_back(buf);}
                    memset(buf, NULL, 255);
                    html_tag.push_back("</u>");
                    k=0;
                    j += 2;
                }
                else{
                    cout<<"Error"<<endl;
                    return 0;
                }
            }
            else if (pStr[j] == '/'&&(j + 2 < pStr.length())) {
                if (pStr[j + 1] == '/'&&pStr[j + 2] == '}') {
                    if(strcmp(buf,"") != 0){html_tag.push_back(buf);}
                    memset(buf, NULL, 255);
                    html_tag.push_back("</i>");
                    k=0;
                    j += 2;
                }
                else{
                    cout<<"Error"<<endl;
                    return 0;
                }
            }
            else{   //리스트의 데이터
                buf[k++] = pStr[j];
            }
        }
    }

            /*
                        if(th_chk == 1){
                            char *ptr = strtok(inputString, "/");      // "|" 공백 문자를 기준으로 문자열을 자름, 포인터 반환
                            html_tag.push_back("<tr>");
                            while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
                            {
                                ptr = strtok(NULL, "/");      // 다음 문자열을 잘라서 포인터를 반환
                                html_tag.push_back("<th>");
                                if(ptr != NULL){
                                    html_tag.push_back(string(ptr));
                                }
                                html_tag.push_back("</th>");
                            }
                            html_tag.pop_back();
                            html_tag.pop_back();
                            html_tag.push_back("</tr>");
                        
                        if(td_chk == 1){
                            char *ptr1 = strtok(inputString, "|");      // "|" 공백 문자를 기준으로 문자열을 자름, 포인터 반환
                            html_tag.push_back("<tr>");
                            while (ptr1 != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
                            {
                                ptr1 = strtok(NULL, "|");      // 다음 문자열을 잘라서 포인터를 반환
                                html_tag.push_back("<td>");
                                if(ptr1 != NULL){
                                    html_tag.push_back(string(ptr1));
                                }
                                html_tag.push_back("</td>");
                            }
                            html_tag.pop_back();
                            html_tag.pop_back();
                            html_tag.push_back("</tr>");
                        }
                    }
                }
            }
            else{
                buf[k++] = pStr[j];
            }
        }
    }
*/
    //==============
    
    ofstream outFile;
    
    outFile.open("/Users/mac/Desktop/project/Team_PrOJECT/SHM/Build/Products/Debug/result.html");
    if(outFile.is_open()){
        int size = (int)html_tag.size();
        for(int i = 0; i<size;i++){
            outFile<<html_tag.front();
            html_tag.pop_front();
        }
        size = (int)sub_list_tag.size();
        for(int i = 0; i<size;i++){
            outFile<<sub_list_tag.back();
            sub_list_tag.pop_back();
        }
    }
    else{
        cout<<"file not created"<<endl;
    }
}

