#pragma once
#ifndef DP_H
#define DP_H

#include <vector>
#include "stack"
#include "deque"
#include "Gps.h"
using namespace std;

double perpendicularDistance(UTMCoor &pt,UTMCoor &spt,UTMCoor &ept) {

	double h = 0.0;
	double a = sqrt(pow(pt.y-spt.y,2)+pow(pt.x-spt.x,2));
	double b = sqrt(pow(pt.y-ept.y,2)+pow(pt.x-ept.x,2));
	double c = sqrt(pow(spt.y-ept.y,2)+pow(spt.x-ept.x,2));
	double p = (a+b+c)/2.0;
	double s = sqrt(p*(p-a)*(p-b)*(p-c));
	h = 2*s/c;
	return h;
}

//void FindSplit(std::vector<UTMCoor>& points,int start,int end,int &f,float &dist)
//{
//	float dtmp = 0.0;
//
//	for (int i=start+1;i<end;i++) {
//		dtmp = perpendicularDistance( points.at(i) , points.at(start) , points.at(end) );
//		if (dtmp > dist) {
//			dist = dtmp;
//			f = i;
//		}
//	}
//}

//void DouglasPeucker(std::vector<UTMCoor>& points,int &i,int &j,float e) 
//{  
//	//cout<<points.size()<<endl;
//	float dist = 0.0;
//	int f = 0;
//	stack<int> tempVertex;
//	tempVertex.push(j);
//
//	do 
//	{
//		cout<<"1"<<endl;
//		FindSplit(points,i,j,f,dist); 
//
//		if (dist > e)
//		{
//			points.at(f).flag = true;
//			j = f;
//			tempVertex.push(f);
//			continue;
//		}
//		else{
//			if (!tempVertex.empty()&&j!=tempVertex.top())
//			{
//				i = f;
//				j = tempVertex.top();
//				continue;
//			}
//			else{
//				if (j!=points.size())
//				{
//					i = j;
//					if (!tempVertex.empty())
//					{
//						deque<int> cont = tempVertex._Get_container();
//						if (cont.size() > 1)
//						{
//							j = cont[cont.size()-2];
//						}
//						else if (cont.size() == 1)
//						{
//							j = cont[cont.size() - 1];
//						}
//						tempVertex.pop();
//						continue;
//					}
//				}
//			}
//		}
//	} while (!tempVertex.empty());
//} 

void DP(std::vector<UTMCoor>& points,int start,int end,float tol) {

	points.at(start).flag  = true;
	points.at(end).flag  = true;

	float dmax = 0.0;
	float dtmp = 0.0;

	long index;

	for (int i=start+1;i<end;i++) {
		dtmp = perpendicularDistance( points.at(i) , points.at(start) , points.at( end ) );
		if (dtmp > dmax) {
			dmax = dtmp;
			index = i;
		}
	}

	if (dmax < tol) {
	}

	else {
		points.at(index).flag  = true;
		DP(points,start,index,tol);
		DP(points,index,end,tol);
	}
}
#endif