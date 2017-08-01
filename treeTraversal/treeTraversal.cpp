// treeTraversal.cpp
// Adam Flammino 7/30 SDEV-345
// Builds and traverses a red black tree

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
		nil = new node;
		nil->red = false;
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
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
			root->left = nil;
			root->right = nil;
			root->red = false; // Root is always black
			root->parent = nil;
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
	node *temp;
	node *nil;
	// Recursively destroys tree
	void destroy(node *leaf)
	{
		if (leaf != nil)
		{
			if (leaf->left != nil)
			{
				destroy(leaf->left);
			}
			if (leaf->right != nil)
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
			if (leaf->right != nil)
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
				leaf->right->left = nil;
				leaf->right->right = nil;
				cleanUp(leaf->right);
			}
		}
		// Traverses left until it finds a spot for the leaf
		else
		{
			if (leaf->left != nil)
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
				leaf->left->left = nil;
				leaf->left->right = nil;
				cleanUp(leaf->left);
			}
		}
	}
	// Recolors and balances tree
	void cleanUp(node *newLeaf)
	{
		while (newLeaf->parent->red)
		{
			if (newLeaf->parent == newLeaf->parent->parent->left)
			{
				temp = newLeaf->parent->parent->right;
				if (temp->red)
				{
					newLeaf->parent->red = false;
					temp->red = false;
					newLeaf->parent->parent->red = true;
					newLeaf = newLeaf->parent->parent;
				}
				else 
				{
					if (newLeaf == newLeaf->parent->right)
					{
						newLeaf = newLeaf->parent;
						rotateLeft(newLeaf);
					}
					newLeaf->parent->red = false;
					newLeaf->parent->parent->red = true;
					rotateRight(newLeaf->parent->parent);
				}
			}
			else
			{
				temp = newLeaf->parent->parent->left;
				if (temp->red)
				{
					newLeaf->parent->red = false;
					temp->red = false;
					newLeaf->parent->parent->red = true;
					newLeaf = newLeaf->parent->parent;
				}
				else
				{
					if (newLeaf == newLeaf->parent->left)
					{
						newLeaf = newLeaf->parent;
						rotateRight(newLeaf);
					}
					newLeaf->parent->red = false;
					newLeaf->parent->parent->red = true;
					rotateLeft(newLeaf->parent->parent);
				}
			}
		}
		root->red = false;
	}

	// Rotates subtree right
	void rotateRight(node *subRoot)
	{
		temp = subRoot->left;
		subRoot->left = temp->right; // Left subtree to right subtree
		if (temp->right != nil)
		{
			temp->right->parent = subRoot;
		}
		temp->parent = subRoot->parent;
		if (subRoot->parent == nil)
		{
			root = temp;
		}
		else if (subRoot == subRoot->parent->right)
		{
			subRoot->parent->right = temp;
		}
		else
		{
			subRoot->parent->left = temp;
		}
		temp->right = subRoot;
		subRoot->parent = temp;
	}
	// Rotates subtree left
	void rotateLeft(node *subRoot)
	{
		temp = subRoot->right;
		subRoot->right = temp->left; // Left subtree to right subtree
		if (temp->left != nil)
		{
			temp->left->parent = subRoot;
		}
		temp->parent = subRoot->parent;
		if (subRoot->parent == nil)
		{
			root = temp;
		}
		else if (subRoot == subRoot->parent->left)
		{
			subRoot->parent->left = temp;
		}
		else
		{
			subRoot->parent->right = temp;
		}
		temp->left = subRoot;
		subRoot->parent = temp;
	}
	// Prints tree in order
	void inOrder (node *localRoot)
	{
		if (first)
		{
			std::cout << "Nodes traversed in order" << std::endl;
			first = false;
		}
		if (localRoot != nil)
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
		if (localRoot != nil)
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
		if (localRoot != nil)
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
	t.insert(30);
	t.insert(28);
	t.insert(21);
	t.insert(11);
	t.insert(17);
	t.insert(4);
	t.inOrder();
	std::cout << std::endl;
	t.preOrder();
	std::cout << std::endl;
	t.postOrder();
	std::cout << std::endl;
    return 0;
}
