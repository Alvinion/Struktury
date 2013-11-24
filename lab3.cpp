// BSTtree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node
{
	int key;
	Node *parent;
	Node *left;
	Node *right;
};

struct Tree
{
	Node *root;
	Node *sentinel;
};

Tree *start();
Node *node(Tree *tree, int key, Node *parent);
int add(Tree *tree, int key);
void addX(Tree *tree, int x);
Node *min(Tree *tree, Node *start);
Node *max(Tree *tree, Node *start);
Node *find(Tree *tree, int key);
int removen(Tree *tree, int key);
int removep(Tree *tree, int key);
void print(Tree *tree, Node *current);

int _tmain(int argc, _TCHAR *argv[])
{
	Tree *tree = start();

	
	add(tree, 50);
	add(tree, 20);
	add(tree, 70);
	add(tree, 69);
	add(tree,71);
	//add(tree,71);
	
	
	//addX(tree, 3);

	//remove(tree, 70);
	//remove2(tree, 50);

	
	
	print(tree, tree->root);
	cout << endl;	
	cout << endl <<tree->root->key << endl;
	system("pause");
	return 0;
}

Tree *start()
{
	Tree* tree = new Tree;
	tree->sentinel = node(tree, 0, NULL);
	
	tree->root = tree->sentinel;
	return tree;
}

Node *node(Tree *tree, int key, Node *parent)
{
	Node *node = new Node;
	node->key = key;
	node->parent = parent;
	node->left = tree->sentinel;
	node->right = tree->sentinel;
	return node;
}

int add(Tree *tree, int key)		
{
	if (tree->root == tree->sentinel)
	{
		tree->root = node(tree, key, tree->sentinel);		
		return 0;
	}

	Node 
		*i = tree->root,
		*parent = tree->sentinel;

	while ( i != tree->sentinel )
	{
		if (key == i->key){
			cout << "Element: "<<key<<" juz istnieje"<<endl;
			return 0;
		}
		parent = i;
		i = key < i->key ? i->left : i->right;
	}

	Node* newNode = node(tree, key, parent);
	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	return 0;
}

void addX(Tree *tree, int x)		
{
	srand((int)time(0));

	for (int i = 0; i < x; i++)
	{
		i -= add(tree, rand());
	}
}

Node *min(Tree *tree, Node *start)
{
	Node *i = start;
	while (i->left != tree->sentinel)
	{
		i = i->left;
	}
	return i;
}

Node *max(Tree *tree, Node *start)
{
	Node *i = start;
	while (i->right != tree->sentinel)
	{
		i = i->right;
	}
	return i;
}

Node *find(Tree *tree, int key) 
{
	tree->sentinel->key = key;

	Node *i = tree->root;
	while (i->key != key)
	{
		i = key < i->key ? i->left : i->right;
	}
	return i;
}

int removen(Tree *tree, int key)			//usuwanie następnika
{
	Node *target = find(tree, key);

	if (target == tree->sentinel)
		return 1;

	if (target->left == tree->sentinel && target->right == tree->sentinel)
	{
		if (target == tree->root)
		{
			tree->root = tree->sentinel;
		}
		else
		{
			if (target->parent->left == target)
			{
				target->parent->left = tree->sentinel;
			}
			else
			{
				target->parent->right = tree->sentinel;
			}
		}
	}
	else if (target->right == tree->sentinel)
	{
		target->left->parent = target->parent;

		if (target->parent->left == target)
			target->parent->left = target->left;
		else
			target->parent->right = target->left;

		if (target == tree->root)
			tree->root = target->left;
	}
	else if (target->left == tree->sentinel)
	{
		target->right->parent = target->parent;

		if (target->parent->left == target)
			target->parent->left = target->right;
		else
			target->parent->right = target->right;

		if (target == tree->root)
			tree->root = target->right;
	}
	else
	{
		Node *successor = min(tree, target->right);
		successor->left = target->left;
		target->left->parent = successor;

		if (target->parent->right == target)
		{
			target->parent->right = successor;
		}
		else
		{
			target->parent->left = successor;
		}

		if (target->right != successor)
		{
			successor->parent->left = successor->right;
			successor->right->parent = successor->parent;
			
			successor->right = target->right;

			target->right->parent = successor;
			target->left->parent = successor;
		}

		successor->parent = target->parent;

		if (target == tree->root)
		{
			tree->root = successor;
		}
	}

	delete target;
	return 0;
}

int removep(Tree *tree, int key)		// usuwanie poprzednika
{
	Node *target = find(tree, key);

	if (target == tree->sentinel)
		return 1;

	if (target->left == tree->sentinel && target->right == tree->sentinel)
	{
		if (target == tree->root)
		{
			tree->root = tree->sentinel;
		}
		else
		{
			if (target->parent->left == target)
			{
				target->parent->left = tree->sentinel;
			}
			else
			{
				target->parent->right = tree->sentinel;
			}
		}
	}
	else if (target->right == tree->sentinel)
	{
		target->left->parent = target->parent;

		if (target->parent->left == target)
			target->parent->left = target->left;
		else
			target->parent->right = target->left;

		if (target == tree->root)
			tree->root = target->left;
	}
	else if (target->left == tree->sentinel)
	{
		target->right->parent = target->parent;

		if (target->parent->left == target)
			target->parent->left = target->right;
		else
			target->parent->right = target->right;

		if (target == tree->root)
			tree->root = target->right;
	}
	else
	{
		Node *predecessor = max(tree, target->left);
		predecessor->right = target->right;
		target->right->parent = predecessor;

		if (target->parent->left == target)
		{
			target->parent->left = predecessor;
		}
		else
		{
			target->parent->right = predecessor;
		}

		if (target->left != predecessor)
		{
			predecessor->parent->right = predecessor->left;
			predecessor->left->parent = predecessor->parent;

			predecessor->left = target->left;

			target->left->parent = predecessor;
			target->right->parent = predecessor;
		}

		predecessor->parent = target->parent;

		if (target == tree->root)
		{
			tree->root = predecessor;
		}
	}

	delete target;
	return 0;
}

void print(Tree *tree, Node *current)		//wyświetlanie inorder
{
	
 	if (current != tree->sentinel)
	{
		print(tree, current->left);
		cout << current->key <<" ";
		print(tree, current->right);
	}
}
