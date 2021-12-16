#include "RotationConstraint.h"
#include "GameObject.h"

using namespace NCL;
using namespace CSC8503;

void RotationConstraint::UpdateConstraint(float dt) {
	Vector3 rot = object->GetTransform().GetOrientation().ToEuler();

	rot = rot * axisToRotate.Normalised();
	//object->GetTransform()
		//.SetOrientation(Quaternion::EulerAnglesToQuaternion(rot.x,rot.y,rot.z));
	//object->GetPhysicsObject()->SetAngularVelocity(object->GetPhysicsObject()->GetAngularVelocity() * axisToRotate.Normalised());
}