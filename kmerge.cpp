#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

/*Function to trim a string.
Parameters : the string to be trimmed.
Return value : Trimmed string.
*/
string trim(const string& str){
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main(){
    cout<<"Enter the number of files to merge\n";
    int n, i;
    cin>>n;

    //Array of input filestreams.
    fstream myfile[n];
    
    //Output file stream.
    fstream outfile;
    outfile.open("kmergeout");
    cout<<"Enter the file names\n";
    
    //Take 'n' files as input, from the user. 
    for(i=0; i<n; i++){
        cout<<"File "<<i<<": ";
        string s;
        cin>>s;
        myfile[i].open(s, ios::in);
    }

    //Display the files first, in order.
    for(i=0; i<n; i++){
        string line;
        cout<<"File "<<i<<": "<<endl;
        
        while(!myfile[i].eof()){
            getline(myfile[i],line);
            trim(line);
            cout<<line<<endl;            
        }

    }
    
    //Seek the get pointer to the first character,for each file.
    for(i=0; i<n; i++){
        myfile[i].seekg(0, ios::beg);
    }
    
	cout<<endl<<endl<<endl;
	
    int num = n;
    int a[n], pos[n], closed[n]={0};
    int min;
    string line;
    
    //Do the following until the number of files whose content is not processed is 0
    while(num > 0){
    //Iterate over each file.
        for(i=0; i<n; i++){
            //Get the current position of the seek pointer for the file.
            pos[i] = myfile[i].tellg();
            //If not end of file, and file not closed
            if(!myfile[i].eof() && !closed[i]){
                //Get the curent line from file and trim it
                getline(myfile[i],line);
                trim(line);
                /*Convert the line to an integer, store it in an array, corresponding to
                the index of the file*/
           	    a[i] = stoi(line);
            }
            else{
                //If end of file, reduce the number of files to be processed, and close the file
                num--;
                myfile[i].close();
                /*Change value of a[i] to show that the file is closed 
                and that the value cannot be considered for finding minimum
                Hence value is set to the max value, say 99999.*/
                a[i]=99999;
                //Change the status of the file in the closed array, to reflect that it is closed
                closed[i]=1;
            }
        }
        
        //Get the minimum from the array, and put it in the output file
        min = *std::min_element(a,a+n);
        outfile<<min<<endl;
    
        //Iterate over each file
        for(i=0; i<n; i++){
            //If the current input file element is not the minimum, change it's seek pointer
            //position back to the previous element
            if(a[i]!=min){
                myfile[i].seekg(pos[i], ios::beg);
            }
        }
    }

    return 0;
}
