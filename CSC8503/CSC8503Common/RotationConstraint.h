#pragma once
#pragma once
#include "Constraint.h"
#include "Transform.h"

namespace NCL {
	namespace CSC8503 {
		class GameObject;

		class RotationConstraint : public Constraint {
		public:
			RotationConstraint(GameObject* a, Vector3 axis) {
				object = a;
				axisToRotate = axis;
			}
			~RotationConstraint() {}

			void UpdateConstraint(float dt) override;

		protected:
			GameObject* object;
			Vector3 axisToRotate;
		};
	}
}

