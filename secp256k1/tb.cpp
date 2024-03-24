#include "fp.hpp"

using namespace std;

void scalormul()
{
	//ap_uint<256> n, show_x;

	Point result;
	//n= ap_uint<256>("0xF99527E2862042DBB66313F44C4C47B6C0259E16F63F000194C4D5BBE3BB3907");
	//n= ap_uint<256>("0x3");

	result=xMUL();
	cout << result.X << ", " << result.Z << endl;


	//div_fp(&show_x, result.X, result.Z);
	//cout << n << "P=" <<hex<< show_x << endl;
}


void test_fp()
{
	ap_uint<256> x, y, z;
	ap_uint<256> xx,yy, zz;
	x = "20812168509434597367146703229805575690060615791308155437936410982393987532344";
	y = "83782116748037935365699506031188859134879139933492690049904288907394911218224";
	//mul_fp(&xx,x,para.R2);
	//mul_fp(&yy,y,para.R2);
	/*
	for(int i=255;i>=0;--i){
		std::cout<<y[i]<<std::endl;
	}
	*/

	//div_fp(&z, x,y);
	mul_fp(yy,x,y);
	cout << yy << endl;
	//mul_fp(&zz,z,para.R2);
	//cout << zz << endl;
}

/*
void test_affine()
{
	Point x,y,z;
	x.X=24; x.Y=11;
	y.X=96; y.Y=34;
	z=add_affine(x,y,1);
	cout << z.X << endl;
	cout << z.Y << endl;
}
*/


int main()
{
	//test_fp();
	//test_affine();
	scalormul();
	return 0;
}
