/* 
 * File:   main.cpp
 * Author: Hailey Campbell 
 * Created on 3/22/2024
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Random Function Library
#include <ctime>     //Time Library 
#include <cmath>
using namespace std;

//Global Constants
enum CrdCard {AmericanExpress, Visa, MasterCard, Discover, ALL};

//Function Prototypes
char rndDgit();           //Randomly generates digit characters
void prpLuhn(char[],int, int); //Prepares the Luhn Sequence
int  cnvrt(char);         //Convert 1 digit char to integer
char cnvrt(int);          //Convert 1 digit integer to a char
void output(char[],int);  //Output the sequence as integers
//Function you are to create
void Luhn(char[],int);    //Calculate and append the Luhn Digit
void genCC(CrdCard,char []);    //Add digits to card
void flipDig(char []);    // flips a digit
void transpose(char[]);   // transposes digits
bool validCC(char[], int);     // checks if new card number is valid

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //counts valid and invalid
    int valid = 0, invalid=0;
    
    //Generate card type and number
    
    int size;
    CrdCard cardType;
    //One larger than needed for the null terminator
    
    for (int i=0; i<10000; i++){
        switch (rand()%5){
            case 0:
                cardType = AmericanExpress;
                size = 17;
                break;
            case 1:
                cardType = Visa;
                size = 18; 
                break;
            case 2:
                cardType = MasterCard;
                size = 18;
                break;
            case 3:
                cardType = Discover;
                size = 18;
                break;
            case 4:
                cardType = ALL;
                size = 18;
                break;
        }
    
        char crdCard[size];
    
        //Prepare for Luhn encoding
        genCC(cardType,crdCard);
        
        //Now create a function that fills the last digit
        //using the Luhn Algorithm
        Luhn(crdCard,size);
    
        flipDig(crdCard);
        flipDig(crdCard);
        transpose(crdCard);
    
        if(validCC(crdCard, size))
            valid++;
        else
            invalid++;
    }
    cout << "Valid: " << valid << endl;
    cout << "Invalid: " << invalid << endl;
    
    //Exit Stage Right
    return 0;
}

void genCC(CrdCard ct,char cc[]){
    int start=0;
    int size;
    if (ct==AmericanExpress){
        cc[0] = '3';
        if ((rand()%2)==0)
            cc[1]= '4';
        else 
            cc[1]= '7';
        start = 2;
        size = 17;
    }
    else if(ct==Visa){
        cc[0]='4';
        start = 1;
        size =18;
    }
    else if(ct==MasterCard){
        cc[0]='5';
        cc[1]= (((rand()%5)+1)+'0');
        start=2;
        size = 18;
    }
    else if(ct==Discover){
        //6011
        cc[0]='6';
        cc[1]='0';
        cc[2]='1';
        cc[3]='1';
        start=4;
        size = 18;
    }
    else{
        start=0;
        size = 18;
    }
    
    prpLuhn(cc,(size-2), start);
}

//Calculate and append the Luhn Digit
void Luhn(char ccc[],int n){
    int sum=0, num=0;
    for (int i=0; i<n-2; i++){
        int temp=0, temp1=0;
        temp = cnvrt(ccc[i]);
        if ((i%2) == 0){
            temp=temp*2;
            if (temp>=10){
                temp1 = (temp%10);
                temp = (static_cast<int>(temp/10));
                temp += temp1;
            }
        }
        sum = sum+temp;
    }
    num = (sum * 9) % 10;
    ccc[n-2]=cnvrt(num);
}

void output(char cc[],int n){
    cout<<"The char array output as each integer digit"<<endl;
    for(int i=0;i<n;i++){
        cout<<cnvrt(cc[i]);
    }
    cout<<endl;
}

char  cnvrt(int digit){
    if(digit<0||digit>9){
        cout<<"You don't know what you are doing "<<endl;
        exit(0);
    }
    return digit+'0';
    //return digit+48;
}

int  cnvrt(char digit){
    if(digit<'0'||digit>'9'){
        cout<<"You don't know what you are doing"<<endl;
        exit(0);
    }
    return digit-'0';
}

void prpLuhn(char cc[],int n, int start){
    //Create a random cc in prep for Luhn checksum
    for(int i=start;i<n;i++){
        cc[i]=rndDgit();
    }
    //Put null terminator at the end
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
}

char rndDgit(){
    return rand()%10+'0';//Ascii Code for numbers '0'=48 and '9'=57
    //return rand()%10+48;//Ascii Code for numbers '0'=48 and '9'=57
}

void flipDig(char cc[]){
    cc[rand()%15] = rndDgit();
}

void transpose(char cc[]){
    // choosing random positions
    int pos1 = (rand()%15), pos2 = (rand()%15);
    char num1, num2;
    
    //storing the values in the those locations
    num1 = cc[pos1];
    num2 = cc[pos2];
    
    //switch the values
    cc[pos1] = num2;
    cc[pos2] = num1;
}

bool validCC(char cc[], int size){
    char temp = cc[size-2];
    Luhn(cc, size);
    if(temp==cc[size-2])
        return true;
    else 
        return false;
}