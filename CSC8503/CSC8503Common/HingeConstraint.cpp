#include "HingeConstraint.h"
#include "GameObject.h"

using namespace NCL;
using namespace CSC8503;

void HingeConstraint::UpdateConstraint(float dt) {

	Vector3 relativePos =
		hinge->GetTransform().GetOrientation().ToEuler() -
		object->GetTransform().GetOrientation().ToEuler();

	float currentDistance = relativePos.Length();

	float offset = 0.0 - currentDistance;

	if (abs(offset) > 0.0f) {
		Vector3 offsetDir = relativePos.Normalised();

		PhysicsObject* physA = hinge->GetPhysicsObject();
		PhysicsObject* physB = object->GetPhysicsObject();

		Vector3 relativeVelocity = physA->GetAngularVelocity() -
			physB->GetAngularVelocity();

		float constraintMass = physA->GetInverseMass() +
			physB->GetInverseMass();

		if (constraintMass > 0.0f) {
			//how much of their relative force is affecting the constraint
			float velocityDot = Vector3::Dot(relativeVelocity, offsetDir);
			float biasFactor = 0.01f;
			float bias = -(biasFactor / dt) * offset;

			float lambda = -(velocityDot + bias) / constraintMass;

			Vector3 aImpulse = offsetDir * lambda;
			Vector3 bImpulse = -offsetDir * lambda;

			physA->ApplyAngularImpulse(aImpulse);// multiplied by mass here
			physB->ApplyAngularImpulse(bImpulse);// multiplied by mass here
		}
	}
}