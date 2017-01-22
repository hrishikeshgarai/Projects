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
//branch prediction:
#define NT 0 // not taken
#define T 1 // taken 

int branchprediction =0;

class calc
{
	public:
	int rows;	
	int** calculate(int m)
	{
		rows = pow(2,m);
		int** SatC=0;
		SatC=new int*[rows];
		for(int i=0;i<rows;i++)
		{	
			SatC[i]=new int[2];
			for(int j=0;j<2;j++)
			{	
				SatC[i][j]=1;
		
			}
		} 
	return SatC;	
	}
	
 };

class branch
{
	public:
	int** t_predictor(int** arr,int bits)
	{
	if(arr[bits][0]==1 && arr[bits][1]==1)
	{
		arr[bits][0]=1;
		arr[bits][1]=1;
		branchprediction=1;
	}
	else if(arr[bits][0]==1 && arr[bits][1]==0)          
        {
                arr[bits][0]=1;
                arr[bits][1]=1;
                branchprediction=1;
        } 
	else if(arr[bits][0]==0 && arr[bits][1]==0)          
        {
                arr[bits][0]=0;
                arr[bits][1]=1;
                branchprediction=0;
        }       
        else if(arr[bits][0]==0 && arr[bits][1]==1)          
        {
                arr[bits][0]=1;
                arr[bits][1]=1;
                branchprediction=0;
        }
	return arr;       
	}
	
	 int** nt_predictor(int** arr,int bits)
        {
        if(arr[bits][0]==1 && arr[bits][1]==1)
        {
                arr[bits][0]=1;
                arr[bits][1]=0;
                branchprediction=1;
        }       
        else if(arr[bits][0]==1 && arr[bits][1]==0)
        {
                arr[bits][0]=0;
                arr[bits][1]=0;
                branchprediction=1;
        }
        else if(arr[bits][0]==0 && arr[bits][1]==0)
        {
                arr[bits][0]=0;
                arr[bits][1]=0;
                branchprediction=0;
        }
        else if(arr[bits][0]==0 && arr[bits][1]==1)
        {
                arr[bits][0]=0;
                arr[bits][1]=0;
                branchprediction=0;
        }
	return arr;
}
};




int main(int argc, char* argv[])
{


    calc mycalc;
    branch mybranch;
    int config;
    ifstream config_params;
    config_params.open(argv[1]);
    while(!config_params.eof())  // read config file
    {
      
        config_params >> config;
    }
    
   

   int** abc=mycalc.calculate(config);
   
 // int branchprediction =0;//0=not taken,1=taken
   
   
    ifstream traces;
    ofstream tracesout;
    string outname;
    outname = string(argv[2]) + ".out";
    
    traces.open(argv[2]);
    tracesout.open(outname.c_str());
    
    string line;
    string actualbranch;  // the actual state whether branch is taken or not from the memory trace;
    string xaddr;       // the address from the memory trace store in hex;
    unsigned int addr;  // the address from the memory trace store in unsigned int;        
    bitset<32> accessaddr; // the address from the memory trace store in the bitset;
 
    if (traces.is_open()&&tracesout.is_open()){    
        while (getline (traces,line)){   // read mem access file
            
            istringstream iss(line); 
            if (!(iss >> xaddr >> actualbranch)) {break;}
            stringstream saddr(xaddr);
	   
            saddr >> std::hex >> addr;
            accessaddr = bitset<32> (addr);
	  
		
	    int config_bits  = bitset<32> (accessaddr.to_string().substr((32-config),config)).to_ulong();


            if (actualbranch.compare("1") == 0)
            {	
		abc=mybranch.t_predictor(abc,config_bits);
		
            }
            else
            {
		
		abc=mybranch.nt_predictor(abc,config_bits);
            }
             
            tracesout<< branchprediction << endl;  // Output branch prediction in output file.
             
             
        }
        traces.close();
        tracesout.close(); 
    }
    else cout<< "Unable to open trace or traceout file ";
    return 0;
}
