#pragma once
#include "Constraint.h"

namespace NCL {
	namespace CSC8503 {
		class GameObject;

		class HingeConstraint : public Constraint {
		public:
			HingeConstraint(GameObject* a, GameObject* b) {
				object = a;
				hinge = b;
			}
			~HingeConstraint() {}

			void UpdateConstraint(float dt) override;

		protected:
			GameObject* object;
			GameObject* hinge;
		};
	}
}

