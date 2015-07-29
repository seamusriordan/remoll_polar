#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	string data[51][802];
	string datal[51][802];
	float par1, par2, par3, par4, par5;
	
	ofstream outfile;
	outfile.open("/home/cameronc/gitdir/remoll_polar/Map.dat",ios::out | ios::trunc );

	if (!outfile.is_open() ) {cout<< "error1"<<endl; return 1;}
	ifstream infile;
	infile.open("/home/cameronc/gitdir/remoll_polar/SolenoidFieldmap.dat",ios::in );
	
	if (!outfile.is_open() || !infile.is_open()) {cout<< "error2"<<endl; return 1;}

	//               R       Z       B_r     B_phi   B_z
	while( infile >> par1 >> par2 >> par3 >> par4 >> par5 ){
		ostringstream buff;
		ostringstream buffl;
		ostringstream negbuff;
		ostringstream negbuffl;
		int indR = (int)par1;
		int indZ = (int)par2+401;
		int indnegZ = -1*(int)par2+401;
		buffl<<fixed<<par1/1000<<"\t-180.0\t"<<par2/1000<<scientific<<"\t"<<par3<<"\t"<<par4<<"\t"<<par5;
		buff<<fixed<<par1/1000<<"\t180.0\t"<<par2/1000<<scientific<<"\t"<<par3<<"\t"<<par4<<"\t"<<par5;
		negbuffl<<fixed<<par1/1000<<"\t-180.0\t"<<-1.*par2/1000<<scientific<<"\t"<<-1.*par3<<"\t"<<par4<<"\t"<<par5;
		negbuff<<fixed<<par1/1000<<"\t180.0\t"<<-1.*par2/1000<<scientific<<"\t"<<-1.*par3<<"\t"<<par4<<"\t"<<par5;
		data[indR][indZ]=buff.str();	
		datal[indR][indZ]=buffl.str();
		if (indnegZ != 0) {
			data[indR][indnegZ]=negbuff.str();	
			datal[indR][indnegZ]=negbuffl.str();
		}
	}
	outfile<<"26\t0.00\t0.05"<<endl;
	outfile<<"2\t-180.0\t180.0"<<endl;
	outfile<<"401\t-0.40\t0.40"<<endl;
	outfile<<"0.0\t0.0"<<endl;
	outfile<<"1"<<endl;
	outfile<<"74.0"<<endl;
	for (int j = 0; j<802; j++) {
		for (int k = 0; k<2; k++) {
			for (int i = 0; i<51; i++) {
				if (data[i][j]!=""){
					if (k == 0){
						outfile<<datal[i][j]<<endl;				
					}
					else {
						outfile<<data[i][j]<<endl;
					}
				}
			}
		}
	}
	infile.close();
	outfile.close();
	return 0;
}
