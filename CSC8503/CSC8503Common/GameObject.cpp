#include "GameObject.h"
#include "CollisionDetection.h"

using namespace NCL::CSC8503;

GameObject::GameObject(string objectName)	{
	name			= objectName;
	worldID			= -1;
	isActive		= true;
	toDelete = false;
	boundingVolume	= nullptr;
	useGravity = true;
	physicsObject	= nullptr;
	renderObject	= nullptr;
	collisionLayer  = CollisionLayer::Default;
	lockFlags = 0;
	colour = Vector4(1, 1, 1, 1);
}

GameObject::~GameObject()	{
	delete boundingVolume;
	delete physicsObject;
	delete renderObject;
}

bool GameObject::GetBroadphaseAABB(Vector3&outSize) const {
	if (!boundingVolume) {
		return false;
	}
	outSize = broadphaseAABB;
	return true;
}

void GameObject::UpdateBroadphaseAABB() {
	if (!boundingVolume) {
		return;
	}
	if (boundingVolume->type == VolumeType::AABB) {
		broadphaseAABB = ((AABBVolume&)*boundingVolume).GetHalfDimensions();
	}
	else if (boundingVolume->type == VolumeType::Sphere) {
		float r = ((SphereVolume&)*boundingVolume).GetRadius();
		broadphaseAABB = Vector3(r, r, r);
	}
	else if (boundingVolume->type == VolumeType::OBB) {
		Matrix3 mat = Matrix3(transform.GetOrientation());
		mat = mat.Absolute();
		Vector3 halfSizes = ((OBBVolume&)*boundingVolume).GetHalfDimensions();
		broadphaseAABB = mat * halfSizes;
	}
	else if (boundingVolume->type == VolumeType::Capsule) {
		// Implement capsule ABB
	}
}

void GameObject::ConstrainLinearVelocity() {
	Vector3 linearVel = physicsObject->GetLinearVelocity();
	if (lockFlags & AxisLock::LINEAR_X) {
		physicsObject->SetLinearVelocity(Vector3(0, linearVel.y, linearVel.z));
		linearVel = physicsObject->GetLinearVelocity();
	}
	if (lockFlags & AxisLock::LINEAR_Y) {
		physicsObject->SetLinearVelocity(Vector3(linearVel.x, 0, linearVel.z));
		linearVel = physicsObject->GetLinearVelocity();
	}
	if (lockFlags & AxisLock::LINEAR_Z) {
		physicsObject->SetLinearVelocity(Vector3(linearVel.x, linearVel.y, 0));
	}
}

void GameObject::ConstrainAngularVelocity() {
	Vector3 angularVel = this->physicsObject->GetAngularVelocity();
	if (lockFlags & AxisLock::ANGULAR_X) {
		this->physicsObject->SetAngularVelocity(Vector3(0, angularVel.y, angularVel.z));
		angularVel = this->physicsObject->GetAngularVelocity();
	}
	if (lockFlags & AxisLock::ANGULAR_Y) {
		this->physicsObject->SetAngularVelocity(Vector3(angularVel.x, 0, angularVel.z));
		angularVel = this->physicsObject->GetAngularVelocity();
	}
	if (lockFlags & AxisLock::ANGULAR_Z) {
		this->physicsObject->SetAngularVelocity(Vector3(angularVel.x, angularVel.y, 0));
	}
}

void GameObject::Update(float dt) {
	
}