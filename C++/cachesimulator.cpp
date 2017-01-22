/*
Cache Simulator
Level one L1 and level two L2 cache parameters are read from file (block size, line per set and set per cache).
The 32 bit address is divided into tag bits (t), set index bits (s) and block offset bits (b)
s = log2(#sets)   b = log2(block size)  t=32-s-b
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>

using namespace std;
//access state:
#define NA 0 // no action
#define RH 1 // read hit
#define RM 2 // read miss
#define WH 3 // Write hit
#define WM 4 // write miss




struct config{
       int L1blocksize;
       int L1setsize;
       int L1size;
       int L2blocksize;
       int L2setsize;
       int L2size;
       };

/* you can define the cache class here, or design your own data structure for L1 and L2 cache
class cache {
      
      }
*/       
class cL1{
	public:
		int L1offset, L1tag, L1index;
	void cacheL1(int L1block_size,int L1set_size,int L1_size)
	{
		L1offset = log2(L1block_size);
		if(L1set_size==0)
		{
		L1index = log2((L1_size*1024)/(L1block_size));
		L1tag = 32 - L1offset;
		}
		else
		{
		L1index = log2((L1_size*1024)/(L1set_size*L1block_size));
		L1tag = 32 - L1offset - L1index;
		}
	}	
};

class cL2{
	public:
		int L2offset, L2tag, L2index;
	void cacheL2(int L2block_size,int L2set_size,int L2_size)
	{
		L2offset = log2(L2block_size);
		if(L2set_size==0)
		{
		L2index = log2((L2_size*1024)/(L2block_size));
		L2tag = 32-L2offset; 
		}
		else
		{
		L2index = log2((L2_size*1024)/(L2set_size*L2block_size));
		L2tag = 32 - L2offset - L2index;
		}
	}
};

int main(int argc, char* argv[]){


    cL1 mycL1;
    cL2 mycL2;
    int dataL1,dataL2;
    config cacheconfig;
    ifstream cache_params;
    string dummyLine;
    cache_params.open(argv[1]);
    while(!cache_params.eof())  // read config file
    {
      cache_params>>dummyLine;
      cache_params>>cacheconfig.L1blocksize;
      cache_params>>cacheconfig.L1setsize;              
      cache_params>>cacheconfig.L1size;
      cache_params>>dummyLine;              
      cache_params>>cacheconfig.L2blocksize;           
      cache_params>>cacheconfig.L2setsize;        
      cache_params>>cacheconfig.L2size;
      }
   // Implement by you: 
   // initialize the hirearch cache system with those configs
   // probably you may define a Cache class for L1 and L2, or any data structure you like
   
    mycL1.cacheL1(cacheconfig.L1blocksize, cacheconfig.L1setsize, cacheconfig.L1size);
    mycL2.cacheL2(cacheconfig.L2blocksize, cacheconfig.L2setsize, cacheconfig.L2size);
    cout << "-----Properties of cache L1----- " << "\n";
    cout << "Offset bits- " << mycL1.L1offset << "\n";
    cout << "Index bits- " << mycL1.L1index << "\n";
    cout << "Tag bits- " << mycL1.L1tag << "\n";
    cout << "----Properties of cache L2----- " << "\n";
    cout << "Offset bits- " << mycL2.L2offset << "\n";
    cout << "Index bits- " << mycL2.L2index << "\n";
    cout << "Tag bits- " << mycL2.L2tag << "\n";

if(cacheconfig.L1setsize!=0){
if(log2(cacheconfig.L1setsize)!=floor(log2(cacheconfig.L1setsize))){
return 0;
}
}
if( cacheconfig.L2setsize!=0){
if(log2(cacheconfig.L2setsize)!=floor(log2(cacheconfig.L2setsize)))
{
return 0;
}
}

   
if(cacheconfig.L1setsize==0){
dataL1 = 2;
}
else{ 
    dataL1 = pow(2,mycL1.L1index);}

if(cacheconfig.L2setsize==0){
dataL2 = 2;}
else{
    dataL2 = pow(2,mycL2.L2index);}

   if(cacheconfig.L1setsize==0)
    {
     cacheconfig.L1setsize=pow(2,mycL1.L1index);
     mycL1.L1index = 0;

}
   if(cacheconfig.L2setsize==0)
{
     cacheconfig.L2setsize=pow(2,mycL2.L2index);
     mycL2.L2index = 0;

}


   int tagarrL1[dataL1-1][cacheconfig.L1setsize];

  int tagarrL2[dataL2-1][cacheconfig.L2setsize];
    int validarrL1[dataL1-1][cacheconfig.L1setsize];
    int validarrL2[dataL2-1][cacheconfig.L2setsize];
	cout << "data L1 i.e rows is " <<dataL1 <<"\n";
    int dataarr[dataL1-1][cacheconfig.L1blocksize-1];  
  int L1AcceState =0; // L1 access state variable, can be one of NA, RH, RM, WH, WM;
  int L2AcceState =0; // L2 access state variable, can be one of NA, RH, RM, WH, WM;
   
   
    ifstream traces;
    ofstream tracesout;
    string outname;
    outname = string(argv[2]) + ".out";
    
    traces.open(argv[2]);
    tracesout.open(outname.c_str());
    
    string line;
    string accesstype;  // the Read/Write access type from the memory trace;
    string xaddr;       // the address from the memory trace store in hex;
    unsigned int addr;  // the address from the memory trace store in unsigned int;        
    bitset<32> accessaddr; // the address from the memory trace store in the bitset;
    int countL1[dataL1-1];
for(int i=0;i<(dataL1);i++){
countL1[i]=0;
}
    int countL2[dataL2-1];
for(int i=0;i<(dataL2);i++){
countL2[i]=0;
}
    int j=0;
    int k=0;



    if (traces.is_open()&&tracesout.is_open()){    
        while (getline (traces,line)){   // read mem access file and access Cache
            
            istringstream iss(line); 
            if (!(iss >> accesstype >> xaddr)) {break;}
            stringstream saddr(xaddr);
            saddr >> std::hex >> addr;
            accessaddr = bitset<32> (addr);
cout << xaddr << "\n";          
cout << accessaddr << "\n"; 
          int offL1 = bitset<32> (accessaddr.to_string().substr((mycL1.L1tag+mycL1.L1index),mycL1.L1offset)).to_ulong();
	  int tgL1 = bitset<32> (accessaddr.to_string().substr(0,mycL1.L1tag)).to_ulong();
	  int indL1 = bitset<32> (accessaddr.to_string().substr(mycL1.L1tag,mycL1.L1index)).to_ulong();
	 cout << "offset bitsL1 - " << offL1 << "\n";
	 cout << "tag bitsL1 - " << tgL1 << "\n";
	 cout << "index bitsL1 -" << indL1 << "\n";
	  int offL2 = bitset<32> (accessaddr.to_string().substr((mycL2.L2tag+mycL2.L2index),mycL2.L2offset)).to_ulong();
          int tgL2 = bitset<32> (accessaddr.to_string().substr(0,mycL2.L2tag)).to_ulong();
          int indL2 = bitset<32> (accessaddr.to_string().substr(mycL2.L2tag,mycL2.L2index)).to_ulong();
	  cout << "offset bitsL2 - " << offL2 << "\n";
         cout << "tag bitsL2 - " << tgL2 << "\n";
         cout << "index bitL2 -" << indL2 << "\n";
           // access the L1 and L2 Cache according to the trace;
              if (accesstype.compare("R")==0) 
             {    
                 //Implement by you:
                 // read access to the L1 Cache, 
                 //  and then L2 (if required), 
                 //  update the L1 and L2 access state variable;
                for(int i=0;i<cacheconfig.L1setsize;i++)
                  {
                        if((tagarrL1[indL1][i] == tgL1) && (validarrL1[indL1][i] == 1))
                        {
                           L1AcceState=1;
                           L2AcceState=0;
			   break;
                        }
                 }
                 if(L1AcceState==0)
                  {
		   L1AcceState=2;
		   for(int i=0;i<cacheconfig.L2setsize;i++)
		   {
		   if((tagarrL2[indL2][i] == tgL2) && (validarrL2[indL2][i] == 1))
		   {		
		   L2AcceState=1;
		   
		   j=countL1[indL1];
		   // cout << "the value of j1 is " << j << "\n"; 
		   tagarrL1[indL1][j]=tgL1;
		   validarrL1[indL1][j]=1;
		   countL1[indL1]=countL1[indL1]+1;
		   if(countL1[indL1]==cacheconfig.L1setsize){
		   countL1[indL1]=0;
		   }
		   
		   break;
		   }
		   }		
		   if(L2AcceState == 0)
		   {
		   L2AcceState=2;

                   k=countL2[indL2];

                   tagarrL2[indL2][k]=tgL2;
		   validarrL2[indL2][k]=1;
                   countL2[indL2]=countL2[indL2]+1;
                   if(countL2[indL2]==cacheconfig.L2setsize){
                   countL2[indL2]=0;
                   }
                  


                  cout << countL1[indL1] << "\n";
		   tagarrL1[indL1][countL1[indL1]]=tgL1;
		   validarrL1[indL1][countL1[indL1]]=1;
                   countL1[indL1]=countL1[indL1]+1;
                   if(countL1[indL1]==cacheconfig.L1setsize){
                   countL1[indL1]=0;
                   }
                   
		   } 
		  }   
                 }
             else 
             {    
		  for(int i=0;i<cacheconfig.L1setsize;i++)
		  {
			if((tagarrL1[indL1][i] == tgL1) && (validarrL1[indL1][i] == 1)) 		
		 	{
		           L1AcceState=3;
			   L2AcceState=0;
			   break;
			}	
}
                   //Implement by you:
                  // write access to the L1 Cache, 
                  //and then L2 (if required), 
                  //update the L1 and L2 access state variable;
 if (L1AcceState == 0)
{
L1AcceState=4;
for(int i=0;i<cacheconfig.L2setsize;i++)
{
if((tagarrL2[indL2][i] == tgL2) && (validarrL2[indL2][i] == 1))
{
L2AcceState=3;
break;
}
}
if(L2AcceState == 0)
{
L2AcceState=4;
}
}                 
                  }
              
cout << L1AcceState << " " << L2AcceState << "\n";               
             
            tracesout<< L1AcceState << " " << L2AcceState << endl;  // Output hit/miss results for L1 and L2 to the output file;
            L1AcceState=0;
	    L2AcceState=0;  
             
        }
        traces.close();
        tracesout.close(); 
    }
    else cout<< "Unable to open trace or traceout file ";


   
    
  

   
    return 0;


}
