// DP_serializate.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include "traj.h"
#include "DP.h"
#include "iomanip" 
#include "time.h"
#include "proj_api.h"

void split(std::string& s, std::string& delim,std::vector< std::string >* ret)  
{  
	size_t last = 0;  
	size_t index=s.find_first_of(delim,last);  
	while (index!=std::string::npos)  
	{  
		ret->push_back(s.substr(last,index-last));  
		last=index+1;  
		index=s.find_first_of(delim,last);  
	}  
	if (index-last>0)  
	{  
		ret->push_back(s.substr(last,index-last));  
	}  
}  

int _tmain(int argc, _TCHAR* argv[])
{
	projPJ pj_merc, pj_latlong;

	if (!(pj_merc = pj_init_plus("+proj=merc +lon_0=0 +k=1 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs")))
		exit(1);
	if (!(pj_latlong = pj_init_plus("+proj=longlat +datum=WGS84 +no_defs")))
		exit(1);

	using namespace std;
	ifstream fin("C:\\Users\\Constantine\\Desktop\\out2.txt",ios::in);
	if(!fin)
	{
		cout<<"Cannot open input file!"<<endl;
		system("pause");
		return 1;
	}

	vector<Traj> trajs;

	string line;
	string delim=" ";
	int num=0;
	while(getline(fin,line)) {
		vector<string> result;
		split(line,delim,&result);

		Traj* traj = new Traj;
		traj->id = result.at(0);
		for ( vector<string>::iterator it = result.begin()+1;it != result.end(); it++) {
			double lng = atof(&(*it->c_str()));
			it++;
			double lat = atof(&(*it->c_str()));

			lat *= DEG_TO_RAD;
			lng *= DEG_TO_RAD;
			pj_transform(pj_latlong, pj_merc, 1, 1, &lng, &lat, NULL);

			UTMCoor xy = {lng,lat,false};
			traj->points.push_back(xy);
		}

		trajs.push_back(*traj);
		delete traj;
		if(trajs.size() == 10)
			break;
	}

	clock_t starttime = clock();
	for (int i = 0; i < trajs.size();i++)
	{
		DP(trajs.at(i).points,0,trajs.at(i).points.size()-1,50);
	}
	clock_t endtime = clock();

	ofstream fout("C:\\Users\\Constantine\\Desktop\\100.txt",ios::out);
	for (int j = 0;j < trajs.size();j++)
	{
		for ( vector<UTMCoor>::iterator it = trajs.at(j).points.begin();it != trajs.at(j).points.end();it++) {

			if (it->flag == true) {
				double x = (double)it->x;
				double y = (double)it->y;
				pj_transform(pj_merc, pj_latlong, 1, 1, &x, &y, NULL);
				x /= DEG_TO_RAD;
				y /= DEG_TO_RAD;
				fout<<fixed<<setprecision(6)<<trajs.at(j).id<<","<<x<<","<<y<<endl;
			}
		}
	}

	printf("totals time is %lf s\n",(double)(endtime-starttime)/CLOCKS_PER_SEC);

	system("pause");
	return 0;
}

