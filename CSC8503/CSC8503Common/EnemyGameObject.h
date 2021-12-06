#pragma once
#include "../CSC8503Common/GameObject.h"
namespace NCL {
	namespace CSC8503 {
		class StateMachine;
		class NavigationGrid;
		class EnemyGameObject : public GameObject {
		public:
			EnemyGameObject(NavigationGrid* grid, GameObject* target);
			~EnemyGameObject();

			GameObject* GetTarget() {return target;}
			void SetTarget(GameObject* target) { this->target = target; }
			void MoveToTarget(float dt);
			void CalculatePath();
			vector<Vector3> GetPath() { return pathToTarget; }

			virtual void Update(float dt);
		protected:
			GameObject* target;
			NavigationGrid* grid;
			vector <Vector3 > pathToTarget;
			float counter;

			StateMachine* stateMachine;
		};
	}
}

