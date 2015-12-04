#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

const std::string getterTime(){
    time_t currentTime = time(0);
    struct tm iTime;
    char buffer[80];
    iTime = *localtime(&currentTime);
    strftime(buffer,sizeof(buffer),"%Y%m%dT%H%M%S\n",&iTime);
    return buffer;
}

void wFHeader(ofstream* outputfile){
    outputfile->write("BEGIN:VNOTE\n",12);
    outputfile->write("VERSION:1.1\n",12);
    outputfile->write("BODY;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:",45);
}

void wFFooter(ofstream* outputfile, std::string tmr){
    outputfile->write("DCREATED:",9);
    outputfile->write(tmr.c_str(),16);
    outputfile->write("X-IRMC-LUID:137\n",16);
    outputfile->write("END:VNOTE",9);
    outputfile->close();
}

int main()
{
    ifstream myTxtVNT;
    ofstream myVNT;

    string path;
    char share_dir;
    string in_file;
    string out_file;
    string rFromFile;
    int execution_flag = 1;

    while(execution_flag)
    {
        cout<<"Type source dir"<<endl;
        getline(cin,path);

        cout<<"Type input text file like VNT name"<<endl;
        getline(cin,in_file);
        in_file = path + '/' + in_file;

        cout<<"Type output VNT name"<<endl;
        getline(cin,out_file);

        cout<<"Use shared dir?\nY/N"<<endl;
        cin >> share_dir;
        getchar();
        if(toupper(share_dir) == 'Y')
            out_file = path + '/' + out_file + ".vnt";
        else{
            cout<<"Set output dir now!"<<endl;
            getline(cin,path);
            out_file = path + '/' + out_file + ".vnt";
        }
        myTxtVNT.open(in_file.c_str(),ios::binary);
        myVNT.open(out_file.c_str(),ios::app);

        if( myTxtVNT.is_open())
        {
            if(myVNT.is_open())
            {
                //Get Header into VNT;
                /*for(int i=0; i< 2; ++i)
                {
                    getline(myTxtVNT,rFromFile);
                    rFromFile += '\n';
                    myVNT<<rFromFile;
                }
                getline(myTxtVNT,rFromFile,':');
                rFromFile +=':';
                myVNT<<rFromFile;*/
                wFHeader(&myVNT);

                //Get data from file
                while(getline(myTxtVNT,rFromFile))
                {
                    rFromFile += '\n';
                    for(unsigned int i = 0; i< rFromFile.size(); i++)
                    {
                        //Search for pseudo-EOF
                        if(rFromFile.at(i) == '/')
                        {
                            if(rFromFile.at(i+1) == '!' && rFromFile.at(i+2) == '#' && rFromFile.at(i+3) == '/'){
                                myVNT<<'\n';
                            /*for(int i=0; i<3; i++)
                            {
                                getline(myTxtVNT,rFromFile);
                                rFromFile += '\n';
                                myVNT<<rFromFile;
                            }
                            myVNT.close();*/
                            wFFooter(&myVNT,getterTime());
                            break;
                            }
                            else
                                myVNT<<'/';
                        }
                        else if(rFromFile.at(i) == '!'){
                                if(rFromFile.at(i+1) == '['){
                                    myVNT<<"=C2=BB";
                                    i++;
                                }
                                else if(rFromFile.at(i+1) == ']'){
                                    myVNT<<"=C2=AB=C2=BB";
                                    i++;
                                }
                                else{
                                    myVNT<<rFromFile.at(i);
                                }
                        }
                        else if(rFromFile.at(i) == '\n')
                        {
                            myVNT<<"=0A";
                        }
                        else if(rFromFile.at(i) == '=')
                        {
                            myVNT<<"=3D";
                        }
                        else if(rFromFile.at(i) == 'À'){
                            myVNT<<"=C3=80";
                        }
                        else if(rFromFile.at(i) == 'Á'){
                            myVNT<<"=C3=81";
                        }
                        else if(rFromFile.at(i) == 'Â'){
                            myVNT<<"=C3=82";
                        }
                        else if(rFromFile.at(i) == 'Ã'){
                            myVNT<<"=C3=83";
                        }
                        else if(rFromFile.at(i) == 'à'){
                            myVNT<<"=C3=A0";
                        }
                        else if(rFromFile.at(i) == 'á')
                        {
                            myVNT<<"=C3=A1";
                        }
                        else if(rFromFile.at(i) == 'â')
                        {
                            myVNT<<"=C3=A2";
                        }
                        else if(rFromFile.at(i) == 'ã')
                        {
                            myVNT<<"=C3=A3";
                        }
                        else if(rFromFile.at(i) == 'Ç'){
                            myVNT<<"=C3=87";
                        }
                        else if(rFromFile.at(i) == 'ç')
                        {
                            myVNT<<"=C3=A7";
                        }
                        else if(rFromFile.at(i) == 'Ó'){
                            myVNT<<"=C3=93";
                        }
                        else if(rFromFile.at(i) == 'Ô'){
                            myVNT<<"=C3=94";
                        }
                        else if(rFromFile.at(i) == 'Õ'){
                            myVNT<<"=C3=95";
                        }
                        else if(rFromFile.at(i) == 'ó')
                        {
                            myVNT<<"=C3=B3";
                        }
                        else if(rFromFile.at(i) == 'ô')
                        {
                            myVNT<<"=C3=B4";
                        }
                        else if(rFromFile.at(i) == 'õ')
                        {
                            myVNT<<"=C3=B5";
                        }
                        else if(rFromFile.at(i) == 'É'){
                            myVNT<<"=C3=89";
                        }
                        else if(rFromFile.at(i) == 'Ê'){
                            myVNT<<"=C3=8A";
                        }
                        else if(rFromFile.at(i) == 'é')
                        {
                            myVNT<<"=C3=A9";
                        }
                        else if(rFromFile.at(i) == 'ê')
                        {
                            myVNT<<"=C3=AA";
                        }
                        else if(rFromFile.at(i) == 'Í'){
                            myVNT<<"=C3=8D";
                        }
                        else if(rFromFile.at(i) == 'í')
                        {
                            myVNT<<"=C3=AD";
                        }
                        else if(rFromFile.at(i) == 'Ñ'){
                            myVNT<<"=C3=91";
                        }
                        else if(rFromFile.at(i) == 'ñ'){
                            myVNT<<"=C3=B1";
                        }
                        else if(rFromFile.at(i) == 'Ú'){
                            myVNT<<"=C3=9A";
                        }
                        else if(rFromFile.at(i) == 'Ü'){
                            myVNT<<"=C3=9C";
                        }
                        else if(rFromFile.at(i) == 'ú'){
                            myVNT<<"=C3=BA";
                        }
                        else if(rFromFile.at(i) == 'ü'){
                            myVNT<<"=C3=BC";
                        }
                        else
                        {
                            myVNT<<rFromFile.at(i);
                        }
                    }
                }
            }
            else
            {
                cout<<"Out file not open!"<<endl;
            }
            myTxtVNT.close();
        }
        else
            cout<<"Input file not open!"<<endl;

        cout<<"Do you want, create another VNT? Y: 1/N: 0"<<endl;
        scanf("%d", &execution_flag);

        in_file = "";
        out_file = "";
        share_dir = '\0';
        path = "";
        getchar();
    }
    return 0;
}
