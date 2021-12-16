#pragma once
#include "Transform.h"
#include "CollisionVolume.h"

#include "PhysicsObject.h"
#include "RenderObject.h"

#include <vector>

using std::vector;

namespace NCL {
	namespace CSC8503 {
		enum class CollisionLayer {
			Default = 1,
			Wall = 2,
			Player = 4,
			Enemy = 8,
			Coins = 16,
			Floor = 32,
			UI = 256,
			Finish = 512
		};

		enum AxisLock {
			LINEAR_X = (1 << 0),
			LINEAR_Y = (1 << 1),
			LINEAR_Z = (1 << 2),
			ANGULAR_X = (1 << 3),
			ANGULAR_Y = (1 << 4),
			ANGULAR_Z = (1 << 5)
		};

		class GameObject	{
		public:
			GameObject(string name = "");
			~GameObject();

			void SetBoundingVolume(CollisionVolume* vol) {
				boundingVolume = vol;
			}

			const CollisionVolume* GetBoundingVolume() const {
				return boundingVolume;
			}

			bool IsActive() const {
				return isActive;
			}

			bool ToDelete() const {
				return toDelete;
			}

			Transform& GetTransform() {
				return transform;
			}

			RenderObject* GetRenderObject() const {
				return renderObject;
			}

			PhysicsObject* GetPhysicsObject() const {
				return physicsObject;
			}

			void SetRenderObject(RenderObject* newObject) {
				renderObject = newObject;
			}

			void SetPhysicsObject(PhysicsObject* newObject) {
				physicsObject = newObject;
			}

			const string& GetName() const {
				return name;
			}

			virtual void OnCollisionBegin(GameObject* otherObject) {
				
			}

			virtual void OnCollisionEnd(GameObject* otherObject) {
				if (otherObject->GetCollisionLayer() == CollisionLayer::Player) {
					toDelete = true;
				}
			}

			bool GetBroadphaseAABB(Vector3&outsize) const;

			void UpdateBroadphaseAABB();

			void SetWorldID(int newID) {
				worldID = newID;
			}

			int		GetWorldID() const {
				return worldID;
			}

			CollisionLayer GetCollisionLayer() {
				return collisionLayer;
			}

			void SetCollisionLayer(CollisionLayer layer) {
				collisionLayer = layer;
			}

			void SetLockFlags(int lf) {
				lockFlags = lf;
			}

			int	GetLockFlags() const {
				return lockFlags;
			}

			void SetColour(Vector4 c) {
				colour = c;
				if (renderObject) {
					renderObject->SetColour(colour);
				}
			}

			Vector4	GetColour() const {
				return colour;
			}

			void ConstrainLinearVelocity();
			void ConstrainAngularVelocity();

			virtual void Update(float dt);

		protected:
			Transform			transform;

			CollisionVolume*	boundingVolume;
			PhysicsObject*		physicsObject;
			RenderObject*		renderObject;

			bool	isActive;
			bool toDelete;
			int		worldID;
			string	name;

			CollisionLayer collisionLayer;

			Vector3 broadphaseAABB;

			Vector4 colour;

			int lockFlags;
		};
	}
}

