#include <iostream>
#include <cmath>

#define pi 3.14159265

using namespace std;

int main(){
	int test = 1.0;
    cout<<"asin(1) = "<<asin(test)*180/pi<<endl;
    cout<<"acos(1) = "<<acos(test)*180/pi<<endl;
    cout<<"atan(1) = "<<atan(test)*180/pi<<endl;

	/*
	设角度为A，弧度为B，则
	角度转弧度： B = A /180 * pi;
	弧度转角度： A = B /pi * 180.
	其中pi是圆周率。
	*/

	double angle = 30.0;
	cout<<"angle="<<angle<<endl;

	double radian = (angle/180.0)*pi;
	cout<<"弧度:"<<radian<<endl;
	cout<<"sin:"<<sin(radian)<<endl;
	cout<<"cos:"<<cos(radian)<<endl;
	cout<<"tan:"<<tan(radian)<<endl;


	double hole,com,a,b,upper_R,lower_r;

	cout<<"孔数:";
	cin>>hole;
	cout<<"编法(1.5/2.5/3.5):";
	cin>>com;
	cout<<"a,b,R,r:";
	cin>>a>>b>>upper_R>>lower_r;
	cout<<endl;

	double beta,theta,fai;
	beta = ((360.0/hole)/180.0)*pi;
	theta = com*beta;
	fai = atan(b/(upper_R-lower_r));

	cout<<beta<<endl;
	cout<<theta<<endl;
	cout<<fai<<endl;

	double numSqrt;
	double tmp1 = pow((lower_r-lower_r*pow(cos(theta),2)),2);
	double tmp2 = 2*cos(theta)-1;
	double tmp3 = lower_r*(2*cos(theta)-1);
	double tmp4 = cos(theta)-1;
	double tmp = pow((tmp1-tmp2)/(tmp3*tmp4),2);
	numSqrt = sqrt(pow(lower_r,2)*pow(sin(theta),2)+tmp);
	double strip = (1+(upper_R*sin(beta/2))/lower_r*sin(theta))*numSqrt;
	cout<<"条长:"<<strip<<endl;
	double vaStrip = strip/cos(fai);
	cout<<"真空中条长:"<<vaStrip<<endl;

	return 0;
}