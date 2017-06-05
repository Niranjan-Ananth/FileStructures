#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;

string buffer = "";
class Student{
    public:
        string USN;
        string name;
        string branch;
        string semester;


        void readData(){

            cout << "Enter the student record :\n";
            cout << "USN: ";
            cin >> USN;
            cout << "Name: ";
            cin >> name;
            cout << "Semester: ";
            cin >> semester;
            cout << "Branch: ";
            cin >> branch;
        }

        void pack(){
            string temp = USN + "|" + name + "|" + semester + "|" + branch;
            while(temp.size() < 99){
                temp += "$";
            }
            buffer += temp + "\n";
        }

        static void writeData(){
            fstream f1;
            f1.open("studentRecords.txt",ios::app);
            f1 << buffer;
            buffer.erase();
            f1.close();
        }

        int search(string key){
            ifstream f1;
            int pos = 0;
            bool flag = false;
            f1.open("studentRecords.txt",ios::in);
            while(!f1.eof()){
                getline(f1,buffer);
                unpack();
                if(USN==key){
                    pos = f1.tellg();
                    flag = true;
                    break;
                }
            }
            if(flag){
                display();
            }
            else{
                cout << "No record found\n";
            }
            return pos;
        }

        void unpack(){
            int i=0;
            string u, n, b, s;
            while(buffer[i]!='|'){
                u += buffer[i];
                i++;
            }
            i++;
            while(buffer[i]!='|'){
                n += buffer[i];
                i++;
            }
            i++;
            while(buffer[i]!='|'){
                s += buffer[i];
                i++;
            }
            i++;
            while(buffer[i]!='$'){
                b += buffer[i];
                i++;
            }
            USN = u;
            name = n;
            branch = b;
            semester = s;
        }
        
        void display(){
            cout << "USN: " << USN << endl; 
            cout << "Name: " << name << endl;
            cout << "Semester: " << semester << endl;
            cout << "Branch: " << branch << endl;
        }

        int deleteFromFile(string key){
            fstream f1;
            bool flag = false;
            int pos = search(key);
            if(pos){
                f1.open("studentRecords.txt",ios::out);
                pos -= 101;
                f1.seekp(pos,ios::beg);
                f1 << "*"; //Deleted  
                flag = true;
            }
            f1.close();
            if(flag){
                cout << "Deleted\n";
            }
            else{
                cout << "No record found\n";
            }
            return pos;
        }

        void modify(string key){
            if(deleteFromFile(key)){
                buffer.erase();
                readData();
                pack();
                writeData();
            }
        }
};

int main(){
    int n, i;
    int ch;
    string temp, key;
    Student s1;
    while(true){
        cout << "1. Insert\n2. Delete\n3. Modify\n4. Search\n";
        cin >> ch;
        switch(ch){
            case 1:
                cout << "Enter the number of records\n";
                cin >> n;
                buffer.erase();
                while(n--){
                    s1.readData();
                    s1.pack();
                }
                Student::writeData();
                break;
            case 2:
                cout << "Enter the USN to delete\n";
                cin >> key;
                s1.deleteFromFile(key);
                break;
            case 3:
                cout << "Enter the USN to modify\n";
                cin >> key;
                s1.modify(key);
                break;
            case 4:
                cout << "Enter the USN for searching\n";
                cin >> key;
                i = s1.search(key);
                break;
            default:
                return 0;
        }
        
    }
    return 0;
}


