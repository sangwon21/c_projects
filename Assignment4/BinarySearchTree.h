#pragma once

#include <memory>
#include <vector>
#include <stack>

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		std::shared_ptr<TreeNode<T>> mRoot;
	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::move(data));
			return;
		}

		std::shared_ptr<TreeNode<T>> cmp = mRoot;
		std::shared_ptr<TreeNode<T>> rightPlace = nullptr;

		while (cmp != nullptr)
		{
			rightPlace = cmp;

			if (*(cmp->Data) > * data)
			{
				cmp = cmp->Left;
			}
			else
			{
				cmp = cmp->Right;
			}
		}

		if (*(rightPlace->Data) > * data)
		{
			rightPlace->Left = std::make_shared<TreeNode<T>>(std::move(data));
			rightPlace->Left->Parent = rightPlace;
		}
		else
		{
			rightPlace->Right = std::make_shared<TreeNode<T>>(std::move(data));
			rightPlace->Right->Parent = rightPlace;
		}
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		std::shared_ptr<TreeNode<T>> start = mRoot;

		while (start != nullptr)
		{
			if (*(start->Data) == data)
			{
				return true;
			}

			if (*(start->Data) > data)
			{
				start = start->Left;
			}
			else
			{
				start = start->Right;
			}
		}

		return false;
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		bool bJudge = false;


		std::shared_ptr<TreeNode<T>> current = mRoot;

		while (current != nullptr)
		{
			if (*(current->Data) > data)
			{
				current = current->Left;
			}
			else if (*(current->Data) < data)
			{
				current = current->Right;
			}
			else
			{
				bJudge = true;
				if (current->Left == nullptr && current->Right == nullptr)
				{
					if (current == mRoot)
					{
						mRoot = nullptr;
						current = nullptr;
						return bJudge;
					}
					// �ڽ� ��ġ ã��
					if (current->Parent.lock() != nullptr)
					{
						if (current->Parent.lock()->Right == current)
						{
							current->Parent.lock()->Right = nullptr;
						}
						else if (current->Parent.lock()->Left == current)
						{
							current->Parent.lock()->Left = nullptr;
						}
					}
					current = nullptr;
				}
				else if (current->Right == nullptr)
				{
					// �θ� -> �ڽ� ����
					if (current->Parent.lock() != nullptr)
					{
						if (current->Parent.lock()->Right == current)
						{
							current->Parent.lock()->Right = current->Left;
						}
						else if (current->Parent.lock()->Left == current)
						{
							current->Parent.lock()->Left = current->Left;
						}
					}
					current->Left->Parent = current->Parent;
					if (current == mRoot)
					{
						mRoot = current->Left;
					}
					current = nullptr;
				}
				else
				{
					// �İ��� �θ�
					std::shared_ptr<TreeNode<T>> succParent = current->Right;

					// �İ���
					std::shared_ptr<TreeNode<T>> succ = current->Right;

					// �İ��� ã��
					while (succ->Left != nullptr)
					{
						succParent = succ;
						succ = succ->Left;
					}

					if (succ == succParent)
					{

						// �θ� -> �İ���
						if (current->Parent.lock() != nullptr)
						{
							if (current->Parent.lock()->Left == current)
							{
								current->Parent.lock()->Left = succ;
							}
							else
							{
								current->Parent.lock()->Right = succ;
							}
						}
						// �İ��� -> �θ�
						succ->Parent = current->Parent;
						// ������ �� �ڽ� ����
						succ->Left = current->Left;
						if (current->Left != nullptr)
						{
							current->Left->Parent = succ;
						}
						if (current == mRoot)
						{
							mRoot = succ;
						}
						current = nullptr;
						return bJudge;
					}
					// succ�θ�� -> succ Right ����
					succParent->Left = succ->Right;
					if (succ->Right != nullptr)
					{
						succ->Right->Parent = succParent;
					}

					succ->Left = current->Left;
					succ->Right = current->Right;

					if (current->Left != nullptr)
					{
						current->Left->Parent = succ;
					}
					if (current->Right != nullptr)
					{
						current->Right->Parent = succ;
					}


					// �θ� -> �İ���
					if (current->Parent.lock() != nullptr)
					{
						if (current->Parent.lock()->Left == current)
						{
							current->Parent.lock()->Left = succ;
						}
						else
						{
							current->Parent.lock()->Right = succ;
						}
					}
					// �İ��� -> �θ�
					succ->Parent = current->Parent;


					if (current == mRoot)
					{
						mRoot = succ;
					}
					current = nullptr;
				}
			}
		}
		return bJudge;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		if (startNode == nullptr)
		{
			return v;
		}

		std::stack<std::shared_ptr<TreeNode<T>>> s;
		std::shared_ptr<TreeNode<T>> current = startNode;

		while (current != nullptr || s.empty() == false)
		{
			while (current != nullptr)
			{
				s.push(current);
				current = current->Left;
			}

			current = s.top();
			s.pop();

			v.push_back(*(current->Data));

			current = current->Right;
		}

		return v;
	}
}