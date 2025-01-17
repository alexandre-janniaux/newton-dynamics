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


// NewtonPlayerControllerManager.h: interface for the NewtonPlayerControllerManager class.
//
//////////////////////////////////////////////////////////////////////

#ifndef D_CUSTOM_PLAYER_CONTROLLER_MANAGER_H_
#define D_CUSTOM_PLAYER_CONTROLLER_MANAGER_H_

#include "dCustomJointLibraryStdAfx.h"
#include "dCustomListener.h"


#define PLAYER_PLUGIN_NAME				"__playerManager__"
#define PLAYER_CONTROLLER_MAX_CONTACTS	32
#define PLAYER_MIN_RESTRAINING_DISTANCE	1.0e-2f

class dCustomPlayerControllerManager;

class dCustomPlayerController
{
	class dContactSolver;
	class dImpulseSolver;

	public:
	dCustomPlayerController ()
		:m_localFrame(dGetIdentityMatrix())
		,m_impulse(0.0f)
		,m_mass(0.0f)
		,m_invMass(0.0f)
		,m_headingAngle(0.0f)
		,m_forwardSpeed(0.0f)
		,m_lateralSpeed(0.0f)
		,m_stepHeight(0.0f)
		,m_contactPatch(0.0f)
		,m_userData(NULL)
		,m_kinematicBody(NULL)
		,m_manager(NULL)
		,m_isAirbone(false)
		,m_isOnFloor(false)
	{
	}

	~dCustomPlayerController () 
	{
	}

	void* GetUserData () const {return m_userData;}
	NewtonBody* GetBody() {return m_kinematicBody;}
	void SetUserData(void* const userData) {m_userData = userData;}
	dCustomPlayerControllerManager* GetManager() const {return m_manager;}

	bool IsAirBorn () const {return m_isAirbone;}
	bool IsOnFloor () const {return m_isOnFloor;}
	const dFloat GetMass() const { return m_mass;}

	const dVector& GetImpulse() { return m_impulse; }
	void SetImpulse(const dVector& impulse) { m_impulse = impulse;}

	dFloat GetForwardSpeed() const { return -m_forwardSpeed; }
	void SetForwardSpeed(dFloat speed) {m_forwardSpeed = -speed; }

	dFloat GetLateralSpeed() const { return -m_lateralSpeed; }
	void SetLateralSpeed(dFloat speed) { m_lateralSpeed = -speed; }

	dFloat GetHeadingAngle() const { return m_headingAngle; }
	void SetHeadingAngle(dFloat angle) {m_headingAngle = dClamp (angle, dFloat (-dPi), dFloat (dPi));}

	dMatrix GetFrame() const { return m_localFrame; }
	CUSTOM_JOINTS_API void SetFrame(const dMatrix& frame);

	CUSTOM_JOINTS_API dVector GetVelocity() const;
	CUSTOM_JOINTS_API void SetVelocity(const dVector& veloc);

	private:
	enum dCollisionState
	{
		m_colliding,
		m_freeMovement,
		m_deepPenetration,
	};

	void PreUpdate(dFloat timestep);
	void ResolveStep(dFloat timestep, dContactSolver& contactSolver);
	void ResolveCollision(dContactSolver& contactSolver, dFloat timestep);
	dFloat PredictTimestep(dFloat timestep, dContactSolver& contactSolver);
	void ResolveInterpenetrations(dContactSolver& contactSolver, dImpulseSolver& impulseSolver);
	dCollisionState TestPredictCollision(const dContactSolver& contactSolver, const dVector& veloc) const;

	dMatrix m_localFrame;
	dVector m_impulse;
	dFloat m_mass;
	dFloat m_invMass;
	dFloat m_headingAngle;
	dFloat m_forwardSpeed;
	dFloat m_lateralSpeed;
	dFloat m_stepHeight;
	dFloat m_contactPatch;
	void* m_userData;
	NewtonBody* m_kinematicBody;
	dCustomPlayerControllerManager* m_manager;
	bool m_isAirbone;
	bool m_isOnFloor;

	friend class dCustomPlayerControllerManager;
};

class dCustomPlayerControllerManager: public dCustomParallelListener
{
	public:
	CUSTOM_JOINTS_API dCustomPlayerControllerManager(NewtonWorld* const world);
	CUSTOM_JOINTS_API ~dCustomPlayerControllerManager();
	CUSTOM_JOINTS_API virtual dCustomPlayerController* CreateController(const dMatrix& location, const dMatrix& localAxis, dFloat mass, dFloat radius, dFloat height, dFloat stepHeight);

	virtual void ApplyMove(dCustomPlayerController* const controller, dFloat timestep) = 0;
	virtual bool ProccessContact(dCustomPlayerController* const controller, const dVector& position, const dVector& normal, const NewtonBody* const otherbody) const { return true; }
	virtual dFloat ContactFriction(dCustomPlayerController* const controller, const dVector& position, const dVector& normal, int contactId, const NewtonBody* const otherbody) const {return 2.0f;}

	protected:
	void PostUpdate(dFloat timestep) {}
	CUSTOM_JOINTS_API virtual void PreUpdate(dFloat timestep, int threadID);

	private:
	dList<dCustomPlayerController> m_playerList;
	friend class dCustomPlayerController;
};

#endif 

