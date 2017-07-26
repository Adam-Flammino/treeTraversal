// treeTraversal.cpp
// Adam Flammino 7/25 SDEV-345
// Builds and traverses a binary tree

#include "stdafx.h"
#include <iostream>

// Holds key and pointers to child nodes
struct node
{
	int value;
	node *left;
	node *right;
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
			leaf->right->left = nullptr;
			leaf->right->right = nullptr;
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
			leaf->left->left = nullptr;
			leaf->left->right = nullptr;
		}
	}
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