// treeTraversal.cpp
// Adam Flammino 7/25 SDEV-345
// Builds and traverses a binary tree

#include "stdafx.h"
#include <iostream>

// Holds key, pointers to child nodes, and color of node
struct node
{
	int value;
	node *left;
	node *right;
	node *parent;
	bool red; // Red if true, black if false
};

class tree
{
public:
	// Constructor
	tree()
	{
		root = nullptr;
	}
	// Destructor
	~tree()
	{
		destroy(root);
	}
	// Creates new tree if needed, otherwise calls private function so user doesn't need to know root
	void insert(int key)
	{
		if (root == nullptr)
		{
			root = new node;
			root->value = key;
			root->left = nullptr;
			root->right = nullptr;
			root->red = false; // Root is always black
			root->parent = nullptr;
		}
		else
		{
			insert(key, root);
		}
	}
	// Allows user to call inOrder without knowing root
	void inOrder()
	{
		first = true;
		inOrder(root);
	}
	// Allows user to call preOrder without knowing root
	void preOrder()
	{
		first = true;
		preOrder(root);
	}
	// Allows user to call postOrder without knowing root
	void postOrder()
	{
		first = true;
		postOrder(root);
	}
private:
	bool first; // Tracks if it's the first time through a traversal function for printing
	node *root;
	bool sibling1; // Used for checking if siblings are the same color
	bool sibling2;
	// Recursively destroys tree
	void destroy(node *leaf)
	{
		if (leaf != nullptr)
		{
			if (leaf->left != nullptr)
			{
				destroy(leaf->left);
			}
			if (leaf->right != nullptr)
			{
				destroy(leaf->right);
			}
			delete leaf;
		}
	}
	// Inserts nodes into existing tree
	void insert(int key, node *leaf)
	{
		// Traverses right until it finds a spot for the leaf
		if (key >= leaf->value)
		{
			if (leaf->right != nullptr)
			{
				insert(key, leaf->right); //Recursive call
			}
			// Creates leaf
			else
			{
				leaf->right = new node;
				leaf->right->value = key;
				leaf->right->parent = leaf;
				leaf->right->red = true; // New leaves start as red
				leaf->right->left = nullptr;
				leaf->right->right = nullptr;
				cleanUp(leaf->right);
			}
		}
		// Traverses left until it finds a spot for the leaf
		else
		{
			if (leaf->left != nullptr)
			{
				insert(key, leaf->left); //Recursive call
			}
			// Creates leaf
			else
			{
				leaf->left = new node;
				leaf->left->value = key;
				leaf->left->parent = leaf;
				leaf->left->red = true; // New leaves start as red
				leaf->left->left = nullptr;
				leaf->left->right = nullptr;
				cleanUp(leaf->left);
			}
		}
	}

	// Recolors and balances tree
	void cleanUp(node *newLeaf)
	{
		while (newLeaf->parent->red) {
			if (newLeaf->parent->red) // Red parents can't have red children
			{
				sibling1 = false; // Defaults siblings to black in case one doesn't exist
				sibling2 = false;
				if (newLeaf->parent->parent->left != nullptr) // Makes sure left sibling exists
				{
					sibling1 = newLeaf->parent->parent->left->red; // Get color of left sibling
					newLeaf->parent->parent->left->red = false; // Color left sibling black
				}
				if (newLeaf->parent->parent->right != nullptr) // Makes sure right sibling exists
				{
					sibling2 = newLeaf->parent->parent->right->red; // Get color of right sibling
					newLeaf->parent->parent->right->red = false; // Color right sibling black
				}
				newLeaf->parent->parent->red = true; // Recolor grandparent to red
				if (!(sibling1 && sibling2)) // If parent doesn't have a red sibling, rotate
				{
					if (newLeaf->parent->left != nullptr)
					{
						rotateRight(newLeaf->parent);
					}
					else
					{
						rotateLeft(newLeaf->parent);
					}
				}
			}
			newLeaf = newLeaf->parent; // Goes up a level
			root->red = false; // Keeping root black here prevents trying to find root's parent
		}
	}
	// Rotates subtree right
	void rotateRight(node *subRoot)
	{
		node *temp = subRoot->left;
		if (temp->right != nullptr)
		{
			subRoot->left->value = temp->right->value;
			temp->right = subRoot;
		}
		subRoot = temp;
		delete temp;
	}
	// Rotates subtree left
	void rotateLeft(node *subroot)
	{
		node *temp = subroot->right;
		if (temp->left != nullptr)
		{
			subroot->right->value = temp->left->value;
			temp->left = subroot;
		}
		subroot = temp;
		delete temp;
	}
	// Prints tree in order
	void inOrder (node *localRoot)
	{
		if (first)
		{
			std::cout << "Nodes traversed in order" << std::endl;
			first = false;
		}
		if (localRoot != nullptr)
		{
			inOrder(localRoot->left); // Goes left
			std::cout << localRoot->value << " "; // Prints current node
			inOrder(localRoot->right); // Goes right
		}
	}
	// Prints tree pre order
	void preOrder (node *localRoot)
	{
		if (first)
		{
			std::cout << "Nodes traversed pre order" << std::endl;
			first = false;
		}
		if (localRoot != nullptr)
		{
			std::cout << localRoot->value << " "; // Prints current node
			preOrder(localRoot->left); // Goes left
			preOrder(localRoot->right); // Goes right
		}
	}
	// Prints tree post order
	void postOrder (node *localRoot)
	{
		if (first)
		{
			std::cout << "Nodes traversed post order" << std::endl;
			first = false;
		}
		if (localRoot != nullptr)
		{
			postOrder(localRoot->left); // Goes left
			postOrder(localRoot->right); // Goes right
			std::cout << localRoot->value << " "; // Prints current node
		}
	}
};

int main()
{
	tree t;
	t.insert(2);
	t.insert(4);
	t.insert(1);
	t.insert(12);
	t.insert(8);
	t.insert(105);
	t.insert(6);
	t.inOrder();
	std::cout << std::endl;
	t.preOrder();
	std::cout << std::endl;
	t.postOrder();
	std::cout << std::endl;
    return 0;
}