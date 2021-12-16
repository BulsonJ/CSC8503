#pragma once
#include "..\CSC8503Common\GameObject.h"
namespace NCL {
	namespace CSC8503 {
		class StateMachine;
		class CoinObject : public GameObject {
		public:
			CoinObject();
			~CoinObject();
			
		virtual void Update(float dt);
		
		protected:
			void MoveLeft(float dt);
			void MoveRight(float dt);

			virtual void OnCollisionBegin(GameObject* otherObject) {
				if (otherObject->GetCollisionLayer() == CollisionLayer::Player) {
					toDelete = true;
				}
			}

			virtual void OnCollisionEnd(GameObject* otherObject) {
				
			}

			StateMachine * stateMachine;
			float counter;
		};
	}
}
