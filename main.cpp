//
//  main.cpp
//  DES2
//
//  Created by Mohammed Dabbah on 12/05/2023.
//  Id:324262476.

#include <iostream>
using namespace std;
string strToBinary(string);
string shiftLeft(string k,int shifts);
string permute(string k,int *arr,int n);
string Xor(string a,string b);
int binaryToDecimal(string);
string decimalToBinary(int n);
string encryption(string message,string*key);
string binTohex(string s);
int main(int argc, const char * argv[]) {
    // insert code here...
    int keyp[] = {57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4};
    //======================================
    int shift_table[]= {1, 1, 2, 2,
        2, 2, 2, 2,
        1, 2, 2, 2,
        2, 2, 2, 1};
    //======================================
    int key_comb[]= {14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32};
    //======================================
    string m,k;
    cout<<"Enter message:";
    cin>>m;
    cout<<"Enter Key:";
    cin>>k;
    m=strToBinary("thoughts");
    k=strToBinary("nonsense");
    cout<<"message in binary: "<<m<<endl;
    cout<<"key in binary: "<<k<<endl;
    k=permute(k,keyp, 56);
    cout<<"Key after PC-1 (56-bit):"<<k<<endl;
    string lKey="0000000000000000000000000000",rKey="0000000000000000000000000000";
    for(int i=0;i<28;i++){
        lKey[i]=k[i];
        rKey[i]=k[i+28];
    }
    cout<<"left key: "<<lKey<<endl<<"right key: "<<rKey<<endl;
    string sHK[32];
    cout<<"\n";
    for(int i=0;i<16;i++){
        lKey=shiftLeft(lKey,shift_table[i]);
        rKey=shiftLeft(rKey,shift_table[i]);
        sHK[i*2]=lKey;
        sHK[i*2+1]=rKey;
        cout<<"left key"<<i+1<<": "<<sHK[i*2]<<"\n"<<"right key"<<i+1<<": "<<sHK[i*2+1]<<endl;
        
    }
    cout<<"\n";
    string comb[16];
    for(int i=0;i<16;i++)
        comb[i]=sHK[i*2]+sHK[i*2+1];
    for(int i=0;i<16;i++)
        cout<<"combine key"<<i+1<<": "<<comb[i]<<endl;
    cout<<"\n";
    for(int i=0;i<16;i++)
        comb[i]=permute(comb[i], key_comb, 48);
    for(int i=0;i<16;i++)
        cout<<"combine key"<<i+1<<" 48bits: "<<comb[i]<<endl;
    cout<<"\n";
    string cipher_text=encryption(m, comb);
    cout<<"\n\nmessage after encryption in binary: "<<cipher_text<<endl<<"message after encryption in hex: "<<binTohex(cipher_text)<<endl<<"===============================================================\n";
    //======================================
    string revcomb[16];
    for(int i=0;i<16;i++)
        revcomb[i]=comb[15-i];
    cipher_text=encryption(cipher_text, revcomb);
    cout<<"\n\nmessage after decryption in binary: "<<cipher_text<<endl<<"message after decryption in hex: "<<binTohex(cipher_text)<<endl;
    return 0;
}
//======================================
int final_perm[] = {40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};
//======================================
int initial_perm[] = {58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};
//======================================
int exp_d[] = {32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1};
//======================================
int per []= {16,  7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25};
//======================================
int sbox[8][4][16] = {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};


//=========================================
string strToBinary(string s)
{
    int n = (int)s.length();
    string bin = "",c="";
    for (int i = 0; i < n; i++)
    {
        // convert each char to
        // ASCII value
        int val = int(s[i]);
        bin="";
        // Convert ASCII value to binary
        while (val > 0)
        {
            if(val % 2)
                bin.push_back('1');
            else
                bin.push_back('0');
            val /= 2;
        }
        if(bin.length()==7){
            bin.push_back('0');
        }
        if(bin.length()==6){
            bin.push_back('0');
            bin.push_back('0');
        }
        reverse(bin.begin(), bin.end());
        c+=bin;
    }
    return c;
}
//======================================
string shiftLeft(string k, int shifts){
    string s="000000000000000000000000000";
    int i,j,size=(int)k.length(),c;
    for(i=0;i<shifts;i++){
        c=1;
        for(j=0;j<size;j++,c++)
            s[j]=k[c];
        s+=k[0];
        k=s;
        s="000000000000000000000000000";
    }
    return k;
}
//======================================
string permute(string k,int*arr,int n){
    string permutation="";
    for(int i=0;i<n;i++)
        permutation=permutation+k[arr[i]-1];
    return permutation;
}
//======================================
string Xor(string a,string b){
   string s="";
    for(int i=0;i<a.length();i++)
        if(a[i]==b[i])
            s+='0';
        else
            s+='1';
    return s;
    
}
//======================================
int binaryToDecimal(string s)
{
    int n=0,size=(int)s.length(),p=0;
    for(int i=size-1;i>=0;i--){
        if(s[i]=='1')
            n+=1*pow(2, p);
        p++;
    }
    return n;
}
//======================================
string decimalToBinary(int decimal){
    int binary = 0, remainder, product = 1;
    string s="",g="";
      while (decimal != 0) {
        remainder = decimal % 2;
        binary = binary + (remainder * product);
        decimal = decimal / 2;
        product *= 10;
      }
    s=to_string(binary);
    int n=(int)s.length();
    while (n%4!=0) {
        g+='0';
        n++;
    }
    g+=s;
        
    return g;
}
//======================================
string encryption(string message,string*key){
    cout<<"Original message (64-bit): "<<message<<endl;
    string m=permute(message, initial_perm, 64);
    cout<<"Message after IP (64-bit): "<<m<<endl;
    string left="00000000000000000000000000000000",right="00000000000000000000000000000000";
    for(int i=0;i<32;i++){
        left[i]=m[i];
        right[i]=m[i+32];
    }
    cout<<"left: "<<left<<endl<<"right: "<<right<<endl;
    for(int i=0;i<16;i++){
        string rightEX=permute(right, exp_d, 48);
//        if(i==0)
//            cout<<"test: "<<rightEX<<endl;
        string rxor=Xor(rightEX, key[i]);
        cout<<"xor: "<<rxor<<endl;
        string box_str="";
        for(int j=0;j<8;j++){
            string r="00";
            r[0]=rxor[j*6];
            r[1]= rxor[j * 6 + 5];
//            cout<<"R: "<<r<<endl;
//            row = binaryToDecimal(r);
            string c="0000";
            c[0]=rxor[j * 6 + 1] ;
            c[1]=rxor[j * 6 + 2] ;
            c[2]=rxor[j * 6 + 3];
            c[3]=rxor[j * 6 + 4];
//            cout<<"L: "<<c<<endl;
//            int col=binaryToDecimal(c);
//            cout<<"row: "<<binaryToDecimal(r)<<"\n"<<"col: "<<binaryToDecimal(c)<<"\n";
            int val=sbox[j][binaryToDecimal(r)][binaryToDecimal(c)];
//            cout<<"value: "<<val<<endl;
//            string t=(decimalToBinary(val));
            box_str+=decimalToBinary(val);
            
        }
        cout<<box_str<<"\n==============================================\n";
        
//        box_str = permute(box_str, per, 32);
//        string result = Xor(left, box_str);
        string result = permute(box_str, per, 32);
//        cout<<"box test: "<<result<<endl;
//        result=Xor(result, left);
        if(i != 16){
            string temp=left;
            left = right;
            right=Xor(result,temp);
        cout<<"left: "<<left<<"\nright: "<<right<<endl;
       
        cout<<"box test: "<<result<<endl;
        }
//        cout<<"box test: "<<result<<endl;
//        left=result;
        
    }
    string combine=right+left;
    string cipherText=permute(combine, final_perm, 64);
    
    return cipherText;
}
string binTohex(string s){
    string a="0000",b="";
    for(int i=0;i<16;i++){
        a="0000";
        a[0]=s[i*4];
        a[1]=s[i*4+1];
        a[2]=s[i*4+2];
        a[3]=s[i*4+3];
        if(a=="0000")
            b+='0';
        else if(a=="0001")
            b+='1';
        else if(a=="0010")
            b+='2';
        else if(a=="0011")
            b+='3';
        else if(a=="0100")
            b+='4';
        else if(a=="0101")
            b+='5';
        else if(a=="0110")
            b+='6';
        else if(a=="0111")
            b+='7';
        else if(a=="1000")
            b+='8';
        else if(a=="1001")
            b+='9';
        else if(a=="1010")
            b+='A';
        else if(a=="1011")
            b+='B';
        else if(a=="1100")
            b+='C';
        else if(a=="1101")
            b+='D';
        else if(a=="1110")
            b+='E';
        else if(a=="1111")
            b+='F';
    }
    return b;
}
