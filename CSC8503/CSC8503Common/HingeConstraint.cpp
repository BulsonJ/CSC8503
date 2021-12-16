#include "HingeConstraint.h"
#include "GameObject.h"

using namespace NCL;
using namespace NCL::Maths;

using namespace NCL;
using namespace CSC8503;

void HingeConstraint::UpdateConstraint(float dt) {

	Vector3 relativePos =
		object->GetTransform().GetPosition() -
		hinge->GetTransform().GetPosition();

	Vector3 objectToHingeDir = relativePos.Normalised();
	Vector3 objectUpDir = (object->GetTransform().GetOrientation() * Vector3(0, 0, -1)).Normalised();
	float offset = Vector3::Dot(objectUpDir, objectToHingeDir);
	
	if (abs(offset) < 0.95f) {
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
			float bias = -(biasFactor / dt) * offset;

			float lambda = -(velocityDot + bias) / constraintMass;

			Vector3 aImpulse = offsetDir * lambda;
			Vector3 bImpulse = -offsetDir * lambda;

			physA->ApplyAngularImpulse(aImpulse);// multiplied by mass here
			physB->ApplyAngularImpulse(bImpulse);// multiplied by mass here
		}
	}
}