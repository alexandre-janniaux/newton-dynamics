/* Copyright (c) <2003-2016> <Julio Jerez, Newton Game Dynamics>
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "dgNewtonPluginStdafx.h"
#include "dgWorldBase.h"


char dgWorldBase::m_libPath[256];


// This is an example of an exported function.
dgWorldPlugin* GetPlugin(dgWorld* const world, dgMemoryAllocator* const allocator)
{
	VkInstance instance = dgVulkanContext::CreateInstance(allocator);
	if (instance == 0) {
		return NULL;
	}

	static dgWorldBase module(world, allocator);
	module.m_score = 10;
	//module.InitDevice(instance, &vkAllocators);
	dgVulkanContext& context = module.GetContext();
	context.InitDevice(instance);

#ifdef _DEBUG
	sprintf (module.m_hardwareDeviceName, "NewtonVK_d %s", context.m_gpu_props.deviceName);
#else
	sprintf(module.m_hardwareDeviceName, "NewtonVK %s", context.m_gpu_props.deviceName);
#endif

	return &module;
}

dgWorldBase::dgWorldBase(dgWorld* const world, dgMemoryAllocator* const allocator)
	:dgWorldPlugin(world, allocator)
	,dgSolver(world, allocator)
{
}

dgWorldBase::~dgWorldBase()
{
	Cleanup();
	dgVulkanContext& context = GetContext();
	context.DestroyDevice();
}

const char* dgWorldBase::GetId() const
{
	return m_hardwareDeviceName;
}

dgInt32 dgWorldBase::GetScore() const
{
	return m_score;
}

void dgWorldBase::CalculateJointForces(const dgBodyCluster& cluster, dgBodyInfo* const bodyArray, dgJointInfo* const jointArray, dgFloat32 timestep)
{
	dgSolver::CalculateJointForces(cluster, bodyArray, jointArray, timestep);
}