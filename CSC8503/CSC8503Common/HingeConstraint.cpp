#include "HingeConstraint.h"
#include "GameObject.h"

using namespace NCL;
using namespace NCL::Maths;

using namespace NCL;
using namespace CSC8503;

void HingeConstraint::UpdateConstraint(float dt) {

	Vector3 relativePos =
		hinge->GetTransform().GetPosition() -
		object->GetTransform().GetPosition();

	Vector3 objectToHingeDir = relativePos.Normalised();
	Vector3 objectUpDir = (object->GetTransform().GetOrientation() * Vector3(0, 0, -1)).Normalised();
	float offset = Vector3::Dot(objectUpDir, objectToHingeDir);
	
	if (offset < 0.98f) {
		Vector3 offsetDir = objectToHingeDir;

		PhysicsObject* physA = hinge->GetPhysicsObject();
		PhysicsObject* physB = object->GetPhysicsObject();

		Vector3 relativeVelocity = physA->GetAngularVelocity() -
			physB->GetAngularVelocity();

		float constraintMass = physA->GetInverseMass() +
			physB->GetInverseMass();

		if (constraintMass > 0.0f) {
			//how much of their relative force is affecting the constraint
			float velocityDot = Vector3::Dot(relativeVelocity, offsetDir);
			float biasFactor = 0.1f;
			float normOffset = (offset / 2) + 0.5;
			float bias = -(biasFactor / dt) * (1- normOffset);

			float lambda = -(velocityDot + bias) / constraintMass;

			Vector3 aImpulse = offsetDir * lambda;
			Vector3 bImpulse = -offsetDir * lambda;

			//physA->ApplyAngularImpulse(aImpulse);// multiplied by mass here
			physB->ApplyAngularImpulse(bImpulse);// multiplied by mass here
		}
	}
}