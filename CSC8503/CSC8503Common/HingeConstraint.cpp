#include "HingeConstraint.h"
#include "GameObject.h"

using namespace NCL;
using namespace CSC8503;

void HingeConstraint::UpdateConstraint(float dt) {

	Vector3 relativeRot =
		objectA->GetTransform().GetOrientation().ToEuler() -
		objectB->GetTransform().GetOrientation().ToEuler();

	float currentDistance = relativeRot.Length();

	Vector3 offsetDir = relativeRot.Normalised();

	PhysicsObject* physA = objectA->GetPhysicsObject();
	PhysicsObject* physB = objectB->GetPhysicsObject();

	Vector3 relativeAngularVelocity = physA->GetAngularVelocity() -
		physB->GetAngularVelocity();

	float constraintMass = physA->GetInverseMass() +
		physB->GetInverseMass();

	Vector3 offset = Vector3(1,0,0) - offsetDir;
	float margin = 0.0f;

	if (abs(offset.x) > margin && abs(offset.y) > margin && abs(offset.z) > margin) {
		if (constraintMass > 0.0f) {
			//how much of their relative force is affecting the constraint
			float velocityDot = Vector3::Dot(relativeAngularVelocity, offsetDir);
			float biasFactor = 0.1f;
			float bias = -(biasFactor / dt) * offset.Length();

			float lambda = -(velocityDot + bias) / constraintMass;

			Vector3 aImpulse = offsetDir * lambda;
			Vector3 bImpulse = -offsetDir * lambda;

			physA->ApplyAngularImpulse(aImpulse);// multiplied by mass here
			physB->ApplyAngularImpulse(bImpulse);// multiplied by mass here
		}
	}
}