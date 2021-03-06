#pragma once
#include "../../Common/Vector2.h"
#include "../CSC8503Common/CollisionDetection.h"
#include "Debug.h"
#include <list>
#include <functional>

namespace NCL {
	using namespace NCL::Maths;
	namespace CSC8503 {
		template<class T>
		class QuadTree;

		template<class T>
		struct QuadTreeEntry {
			Vector3 pos;
			Vector3 size;
			T object;

			QuadTreeEntry(T obj, Vector3 pos, Vector3 size) {
				object		= obj;
				this->pos	= pos;
				this->size	= size;
			}
		};

		template<class T>
		class QuadTreeNode	{
		public:
			typedef std::function<void(std::list<QuadTreeEntry<T>>&)> QuadTreeFunc;
		protected:
			friend class QuadTree<T>;

			QuadTreeNode() {}

			QuadTreeNode(Vector3 pos, Vector3 size) {
				children		= nullptr;
				this->position	= pos;
				this->size		= size;
			}

			~QuadTreeNode() {
				delete[] children;
			}

			void Insert(T& object, const Vector3& objectPos,
				const Vector3 & objectSize, int depthLeft, int maxSize) {
				if (!CollisionDetection::AABBTest(objectPos,
					position, objectSize,
					size)) {
					return;	
				}
				if (children) { //not a leaf node , just descend the tree
					for (int i = 0; i < 8; ++i) {
						children[i].Insert(object, objectPos, objectSize,
							depthLeft - 1, maxSize);
					}
				}
				else { // currently a leaf node , can just expand
					contents.push_back(QuadTreeEntry <T>(object, objectPos, objectSize));
					if ((int)contents.size() > maxSize && depthLeft > 0) {
						if (!children) {
							Split();
							//we need to reinsert the contents so far!
								for (const auto& i : contents) {
									for (int j = 0; j < 8; ++j) {
										auto entry = i;
										children[j].Insert(entry.object, entry.pos,
										entry.size, depthLeft - 1, maxSize);
								}
							}
							contents.clear(); // contents now distributed!
						}
					}
				}
			}

			void Split() {
				Vector3 halfSize = size / 2.0f;
				children = new QuadTreeNode <T >[8];
				children[0] = QuadTreeNode <T>(position +
					Vector3(-halfSize.x, halfSize.y, halfSize.z), halfSize);
				children[1] = QuadTreeNode <T>(position +
					Vector3(halfSize.x, halfSize.y, halfSize.z), halfSize);
				children[2] = QuadTreeNode <T>(position +
					Vector3(-halfSize.x, -halfSize.y, halfSize.z), halfSize);
				children[3] = QuadTreeNode <T>(position +
					Vector3(halfSize.x, -halfSize.y, halfSize.z), halfSize);
				children[4] = QuadTreeNode <T>(position +
					Vector3(-halfSize.x, halfSize.y, -halfSize.z), halfSize);
				children[5] = QuadTreeNode <T>(position +
					Vector3(halfSize.x, halfSize.y, -halfSize.z), halfSize);
				children[6] = QuadTreeNode <T>(position +
					Vector3(-halfSize.x, -halfSize.y, -halfSize.z), halfSize);
				children[7] = QuadTreeNode <T>(position +
					Vector3(halfSize.x, -halfSize.y, -halfSize.z), halfSize);
			}

			void DebugDraw() {

			}

			void OperateOnContents(QuadTreeFunc& func) {
				if (children) {
					for (int i = 0; i < 8; ++i) {
						children[i].OperateOnContents(func);
					}
				}
				else {
					if (!contents.empty()) {
						func(contents);
					}
				}
			}

		protected:
			std::list< QuadTreeEntry<T> >	contents;

			Vector3 position;
			Vector3 size;

			QuadTreeNode<T>* children;
		};
	}
}


namespace NCL {
	using namespace NCL::Maths;
	namespace CSC8503 {
		template<class T>
		class QuadTree
		{
		public:
			QuadTree(Vector3 size, int maxDepth = 6, int maxSize = 5){
				root = QuadTreeNode<T>(Vector3(), size);
				this->maxDepth	= maxDepth;
				this->maxSize	= maxSize;
			}
			~QuadTree() {
			}

			void Insert(T object, const Vector3& pos, const Vector3& size) {
				root.Insert(object, pos, size, maxDepth, maxSize);
			}

			void DebugDraw() {
				root.DebugDraw();
			}

			void OperateOnContents(typename QuadTreeNode<T>::QuadTreeFunc  func) {
				root.OperateOnContents(func);
			}

		protected:
			QuadTreeNode<T> root;
			int maxDepth;
			int maxSize;
		};
	}
}