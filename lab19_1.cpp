#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream s(filename.c_str());
    int a,b,c;
    char na[30];
    string text;
    while(getline(s,text)){
    const char * x = text.c_str();
    char format[] = "%[^:]: %d %d %d";
    sscanf(x,format,na,&a,&b,&c);
    names.push_back(na);
    scores.push_back(a+b+c);
    grades.push_back(score2grade(a+b+c));
    }

}

void getCommand(string &command, string &key){
    string line;
    cout << "Please input your command: ";
    getline(cin,line);
    int idx = line.find_first_of(" ");
    command = line.substr(0,idx);
    key = line.substr(idx+1,line.size()-idx-1);
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------\n";
    bool f = false;
    int N = scores.size();
    for(int i = 0;i < N;i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s " << "score = ";
            cout << scores[i] << endl;
            cout << names[i] << "'s " << "grade = ";
            cout << grades[i]<< endl;
            f = true;
            break;
        }
        
    } 
    if(f == false) cout << "Cannot found.\n";
    
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------\n";
    bool f = false;
    int N = scores.size();
    for(int i = 0;i < N;i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")\n";    
        f = true;
        }
    }
    if(f == false) cout << "Cannot found.\n";
    
    cout << "---------------------------------\n";    
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}