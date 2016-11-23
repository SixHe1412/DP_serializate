#pragma once
#ifndef TRAJ_H
#define TRAJ_H
#include<string>
#include <vector>
#include "Gps.h"
class Traj
{
public:
	std::string id;
	std::vector<UTMCoor> points;


public:
	Traj(void);
	~Traj(void);
};
#endif