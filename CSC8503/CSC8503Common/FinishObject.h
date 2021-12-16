#pragma once
#include "../CSC8503Common/GameObject.h"
namespace NCL {
	namespace CSC8503 {

		class FinishObject : public GameObject {
		public:
			FinishObject();
			~FinishObject();

			virtual void Update(float dt);

			virtual void OnCollisionBegin(GameObject* otherObject) {
				if (otherObject->GetCollisionLayer() == CollisionLayer::Player) {
					SetFinish(true);
				}
			}

			void SetFinish(bool s) { finish = s; }
			bool GetFinish() { return finish; }
		protected:
			bool finish = false;

		};
	}
}

