/*
Student Name: Nathan Cheshire
Student NetID: nvc29
Compiler Used: Visual Studio Community Edition 2019
Program Description:
This header file contains the code for the Binary Tree and the Node which the Tree utilizes
*/

#pragma once
#include <iostream>
#include <string>

//standard namespace
using namespace std;

//Node class implementation
class bstNode
{
	//Everything is public since we are not accessing node directly through our main program
	public:

		//each node in this case has data and a left and right child pointer
		string data;
		bstNode* leftChild;
		bstNode* rightChild;

		//Constructor
		bstNode(string data)
		{
			this->data = data;
			this->leftChild = nullptr;
			this->rightChild = nullptr;
		}

		//Empty constructor
		bstNode()
		{
			this->data = "";
			this->leftChild = nullptr;
			this->rightChild = nullptr;
		}
};

class binaryTree
{
	private:
		bstNode* root;

		//Private search method so that we don't have to pass a node originally
		bool Psearch(string search, bstNode*& start)
		{
			if (root == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start == nullptr)
			{
				return false;
			}

			else if (start->data == search)
			{
				return true;
			}

			else if (start->data > search)
			{
				return this->Psearch(search, start->leftChild);
			}

			else if (start->data < search)
			{
				return this->Psearch(search, start->rightChild);
			}
		}

		//Private insert so that we don't have to pass a node originally
		bool Pinsert(string insert, bstNode*& start)
		{
			if (start == nullptr)
			{
				start = new bstNode(insert);

				return true;
			}

			else if (start->data == insert)
			{
				cout << "Value already exists in tree. Consequently, nothing will happen." << endl;

				return false;
			}

			else if (start->data < insert)
			{
				return this->Pinsert(insert, start->rightChild);
			}

			else if (start->data > insert)
			{
				return this->Pinsert(insert, start->leftChild);
			}
		}

		//Private in order listing so that we don't have to pass a node originally
		string PinOrderList(bstNode*& start)
		{
			if (start == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return start->data;
			}

			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return start->data + "," + PinOrderList(start->rightChild);
			}

			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return PinOrderList(start->leftChild) + "," + start->data;
			}

			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return PinOrderList(start->leftChild) + "," + start->data + "," + PinOrderList(start->rightChild);
			}
		}
		//Private pre order listing so that we don't have to pass a node originally
		string PpreOrderList(bstNode*& start)
		{
			if (start == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return start->data;
			}

			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return start->data + "," + PpreOrderList(start->rightChild);
			}

			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return start->data + "," + PpreOrderList(start->leftChild);
			}

			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return start->data + "," + PpreOrderList(start->leftChild) + "," + PpreOrderList(start->rightChild);
			}
		}

		//Private post order listing so that we don't have to pass a node originally
		string PpostOrderList(bstNode*& start)
		{
			if (start == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return start->data;
			}

			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return PpostOrderList(start->rightChild) + "," + start->data;
			}

			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return PpostOrderList(start->leftChild) + "," + start->data;
			}

			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return PpostOrderList(start->leftChild) + "," + PpostOrderList(start->rightChild) + "," + start->data;
			}
		}

		//Private remove so that we don't have to pass a node originally
		bool Premove(string remove, bstNode*& start)
		{
			//If the tree is empty we definitely cannot remove anything from it
			if (root == nullptr)
			{
				return false;
			}
			//If we are at the end, we cannot traverse any farther and thus we cannot remove the node we wanted to
			else if (start == nullptr)
			{
				return false;
			}

			//If what we want to remove is less than the nodes data, go left
			else if (remove < start->data)
			{
				return this->Premove(remove, start->leftChild);
			}

			//If what we want to remove is greater than the nodes data, go right
			else if (remove > start->data)
			{
				return this->Premove(remove, start->rightChild);
			}

			//Now we have found the data
			else if (remove == start->data)
			{
				//Case 0: no kids: pass
				if (start->rightChild == nullptr && start->leftChild == nullptr)
				{
					//no kids so it is a leaf so we can simply delete it and point our pointer to null address.

					delete start;

					start = nullptr;

					return true;
				}

				//Case 1: only a left kid: pass
				else if (start->rightChild == nullptr && start->leftChild != nullptr)
				{
					//Steal left kid's data, its children, and then delete it

					bstNode* del = start->leftChild;

					start->data = del->data;

					start->leftChild = del->leftChild;

					start->rightChild = del->rightChild;

					delete del;

					del = nullptr;

					return true;
				}

				//Case 2: only a right kid: pass
				else if (start->rightChild != nullptr && start->leftChild == nullptr)
				{
					//Steal right kid's data, its children, and then delete it.

					bstNode* del = start->rightChild;

					start->data = del->data;

					start->leftChild = del->leftChild;

					start->rightChild = del->rightChild;

					delete del;

					del = nullptr;

					return true;
				}

				//Case 3 both a right kid and left kid: pass
				else if (start->rightChild != nullptr && start->leftChild != nullptr)
				{
					//Make a pointer to the node we are trying to delete's left child
					bstNode* swap = start->leftChild;

					//trailing pointer for swap to use for deletion later
					bstNode* swapTrail = start;

					//accumulator so that swapTrail can trail behind swap and skip an iteration
					int acc = 0;

					//Traverse to this child's right until we can't anymore
					//At this point there could be a left child or no children
					while (swap->rightChild != nullptr)
					{
						if (acc == 0)
						{
							swapTrail = start->leftChild;
						}

						else
						{
							swapTrail = swapTrail->rightChild;
						}

						swap = swap->rightChild;

						acc++;
					}

					//now we swap these two nodes data
					string tmp = swap->data;

					swap->data = start->data;

					start->data = tmp;

					//now we need to delete the node swap is pointing to

					//swap does not have a right child but does it have a left?
					if (swap->leftChild != nullptr)
					{
						//has a left child so we need to put it on the right or left of swaptrail depending on the size

						if (swapTrail->data > swap->data)
						{
							swapTrail->leftChild = swap->leftChild;
						}

						else
						{
							swapTrail->rightChild = swap->leftChild;
						}

						delete swap;

						swap = nullptr;

						swapTrail = nullptr;

						return true;
					}

					else
					{
						//does not have a left child so we can simply delete this node and set the trail that pointed to it to nullptr

						delete swap;

						swap = nullptr;

						if (acc == 0)
						{
							swapTrail->leftChild = nullptr;
						}

						else
						{
							swapTrail->rightChild = nullptr;
						}

						swapTrail = nullptr;

						return true;
					}
				}
			}
		}

		//Private program clean up method
		void Preset(bstNode* start)
		{
			if (start == nullptr)
			{
				return;
			}

			if (start->leftChild != nullptr)
			{
				Premove(start->leftChild->data, root);
			}

			if (start->rightChild != nullptr)
			{
				Premove(start->rightChild->data, root);
			}

			if (start == root)
			{
				root = nullptr;
			}
		}

		//Private node counter (beautiful code)
		int PnumNodes(bstNode* start)
		{
			//if the current node exists, we return one plus the recursive count of its right and left child
			return ((start == nullptr) ? 0 : 1 + ((start->leftChild == nullptr) ? 0 : PnumNodes(start->leftChild)) + ((start->rightChild == nullptr) ? 0 : PnumNodes(start->rightChild)));
		}

	public:

		//EmptyTreeExcpetion number
		static const int EmptyTreeException = 117;

		//Empty constructor
		binaryTree()
		{
			root = nullptr;
		}

		//Constructor with initial node data
		binaryTree(string data)
		{
			root = new bstNode(data);
		}

		//Public search method
		bool search(string search)
		{
			return Psearch(search, root);
		}

		//Public insert method
		bool insert(string insert)
		{
			return Pinsert(insert, root);
		}

		//Public remove method
		bool remove(string remove)
		{
			return Premove(remove, root);
		}

		//Public inorderlisting method
		string inOrderList()
		{
			return PinOrderList(root);
		}

		//Public preorderlisting method
		string preOrderList()
		{
			return PpreOrderList(root);
		}

		//Public postorderlisting method
		string postOrderList()
		{
			return PpostOrderList(root);
		}

		//Public reset method
		void reset()
		{
			return Preset(root);
		}

		//Public num nodes method
		int numNodes()
		{
			return PnumNodes(root);
		}
};