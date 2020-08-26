
#include <iostream>
#include<string.h>
#include<string>
#include <fstream>
#include <sstream>

using namespace std;
int ASCII2Sum(string str)
{
    int first=0;
    int last=0;
    int sum=0;
    if(str.length()>0)
    {
        sum=(int)str[0];
        if(str.length()>1)
        sum=(int)str[1]+sum;
        if(str.length()>2)
        sum=(int)str[str.length()-1]+sum;
        if(str.length()>3)
        sum=(int)str[str.length()-2]+sum;
    }
    return sum;
}

int ASCIINextSum(string str)
{
    string temp;
    int sum=0;
    for(int i=0;i<str.length();i++){
      int ascii=(int)str[i];
      if(ascii==122)ascii=97;
      else if(ascii==90)ascii=65;
      else ascii=ascii+1;
      str[i]=(char)ascii;
      sum=ascii+sum;
    }
    //cout<<str<<endl;
    return sum;
}
int main()
{
    string str="";
    string temp;
    int count=0;
    string* words;
    ofstream infile;
    infile.open ("infile.txt");
    cout<<"Enter word/s or press * to end\n";
    do{

    cin>>temp;
    if((temp.compare("*"))!=0)
        {
            str=str+temp+",";
            count=count+1;
            infile<< temp<<"\n";
        }
    else
        {
            break;
        }
    }while(true);
    
    infile.close();
    words=new string[count];
    stringstream wordstream (str);
    string one_wrd;
    
    int i=0;
    while (getline (wordstream, one_wrd, ',')) {
    words[i]=one_wrd;
    i=i+1;
    }
    
    /*for(int i=0;i<count;i++)
    cout<<words[i]<<endl;
    cout<<count<<endl;*/
    
    int htsize=2*count;
    string *Hashtable1=new string[htsize];
    string *Hashtable2=new string[htsize];
    string *Hashtable3=new string[htsize];
    
    for(int i=0;i<htsize;i++)
    {
        Hashtable1[i]="";
        Hashtable2[i]="";
        Hashtable3[i]="";
    }
    
    ofstream outfile;
    outfile.open ("outfile.txt");
    
    //Hashtable1
    int col=0;
    for(int i=0;i<count;i++)
    {
        int ind=((words[i].length()/3)*3)%htsize;
        
        while(true)
        {
            if(Hashtable1[ind]=="")
            {
                Hashtable1[ind]=words[i];
                break;
            }
            else
            {
                ind=(ind+1)%htsize;
                col=col+1;
            }
        }
    }
    for(int i=0;i<htsize;i++)
    {
        //cout<<"{"<<Hashtable1[i]<<"}"<<endl;
        outfile<<"{"<<Hashtable1[i]<<"}";
    }
    //cout<<col<<endl;
    outfile<<col;
    outfile<<"\n";
     //Hashtable2
    col=0;
    for(int i=0;i<count;i++)
    {
        int ind=(ASCII2Sum(words[i]))%htsize;
        
        while(true)
        {
            if(Hashtable2[ind]=="")
            {
                Hashtable2[ind]=words[i];
                break;
            }
            else
            {
                ind=(ind+1)%htsize;
                col=col+1;
            }
        }
    }
    for(int i=0;i<htsize;i++)
    {
        //cout<<"{"<<Hashtable2[i]<<"}"<<endl;
        outfile<<"{"<<Hashtable2[i]<<"}";
    }
    //cout<<col<<endl;
     outfile<<col;
    outfile<<"\n";
    
     //Hashtable3
    col=0;
    for(int i=0;i<count;i++)
    {
        int ind=(ASCIINextSum(words[i])-2*words[i].length())%htsize;
        if(ind<0) ind=ind+htsize;
        
        while(true)
        {
            if(Hashtable3[ind]=="")
            {
                Hashtable3[ind]=words[i];
                break;
            }
            else
            {
                ind=(ind+1)%htsize;
                col=col+1;
            }
        }
    }
    for(int i=0;i<htsize;i++)
    {
        //cout<<"{"<<Hashtable3[i]<<"}"<<endl;
        outfile<<"{"<<Hashtable3[i]<<"}";
    }
    //cout<<col<<endl;
     outfile<<col;
    outfile<<"\n";
    outfile.close();
    return 0;
}
