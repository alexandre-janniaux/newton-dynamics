/* Copyright (c) <2003-2016> <Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely
*/


#ifndef __D_VEHICLE_INTERFACE_H__
#define __D_VEHICLE_INTERFACE_H__

#include "dStdafxVehicle.h"
#include "dVehicleNode.h"

class dTireInfo;
class dVehicleTire;
class dVehicleChassis;

class dVehicleInterface: public dVehicleNode
{
	public:
	DVEHICLE_API dVehicleInterface(dVehicleChassis* const chassis);
	DVEHICLE_API virtual ~dVehicleInterface();

	DVEHICLE_API virtual dVehicleTire* AddTire (const dMatrix& locationInGlobalSpace, const dTireInfo& tireInfo) = 0;

	protected:
	dVehicleChassis* m_chassis;
};


#endif 
