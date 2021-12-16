#pragma once
#include "../CSC8503Common/GameObject.h"
namespace NCL {
	namespace CSC8503 {

		class ResetObject : public GameObject {
		public:
			ResetObject();
			~ResetObject();

			virtual void Update(float dt);

			virtual void OnCollisionBegin(GameObject* otherObject) {
				if (otherObject->GetCollisionLayer() == CollisionLayer::Player) {
					SetResetGame(true);
				}
			}

			void SetResetGame(bool s) { resetGame = s; }
			bool GetResetGame() { return resetGame; }
		protected:
			bool resetGame = false;

		};
	}
}

