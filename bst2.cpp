// bst2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;



class node {

public:
	node();
	node(int);
	node(int, node*);
	~node();
	node* getparent();
	node* getleft();
	node* getright();
	int getkey();
	void setkey(int);
	void setleft(node*);
	void setright(node*);
	void setparent(node*);
	int child();

private:
	node * left;
	node * right;
	node * parent;
	int key;

};


node::~node(){;}

node::node()
{
	parent=left=right=key=NULL;	
}

node::node(int keyv)
{
	key=keyv;
	parent=right=left=NULL;
}

node::node(int keyv, node * _parent)
{
	key=keyv;
	parent=_parent;
	right=left=NULL;
}

int node::getkey(){return(key);}

node* node::getleft()
{
        return(left);
}

node* node::getright()
{
        return(right);
}

node* node::getparent()
{
        return(parent);
}

void node::setkey(int _key)
{
        key=_key;
}

void node::setleft(node* _left)
{
        left = _left;
}

void node::setright(node* _right)
{
        right = _right;
}

void node::setparent(node* _parent)
{
        parent = _parent;
}

int node::child()
{
	int a=0;
	if(getleft()!=NULL) a++;
	if(getright()!=NULL)a++;
	return(a);
}


class tree
{

public:
	tree();
	~tree();
	node * getroot();
	void add(int);
	void random(int);
	node * find(int);
	void inorder();
	node * min();
	node * max();
	node * next(node*);
	node * prev(node*);
	void erase(int);

private:
	node * root;
	void setroot(node*);
	void inorder(node*);
	node * min(node*);
	node * max(node*);
	void nextdel(node*);
	void prevdel(node*);

};

tree::~tree(){;}

tree::tree()
{
	root=NULL;
}


void tree::setroot(node * _root)
{
	root=_root;
}

node* tree::getroot()
{
        return(root);
} 

void tree::add(int key)
{
	node * last = new node(key);

	if(getroot()==NULL)
	{
		setroot(last);
	}

	else

	{
		bool chck(false);
		node * a=getroot();
		node * a_parent=NULL;
		while(!chck)
		{
			if (last->getkey() == a->getkey())
			{
				cout << "Podany element juz istnieje"<< endl;
				chck=true;
			}
			else if(last->getkey() > a->getkey())
			{
				if(a->getright() == NULL)
				{
					a->setright(last);
					last->setparent(a);
					chck=true;
				}
				else
				{
					a_parent=a;
					a=a->getright();
				}
			}
			else if(last->getkey() > a->getkey())
			{
				if(a->getleft() == NULL)
				{
					a->setleft(last);
					last->setparent(a);
					chck=true;
				}
				else
				{
					a_parent=a;
					a=a->getleft();
				}
			}
		}
	}
}

void tree::random(int a)
{
	for(int i=0;i<a;i++)
	{
		add((rand() % 100000 << 16)+rand() % 100000);
	}
}



void tree::inorder()
{
	node * tmp = getroot();
	if(tmp!=NULL)
	{
		inorder(tmp->getleft());
		cout << tmp->getkey() << endl;
		inorder(tmp->getright());
	}
}

void tree::inorder(node * _root)
{
	if(_root!=NULL)
	{
		inorder(_root->getleft());
		cout << _root->getkey() << endl;
		inorder(_root->getright());
	}
}

node * tree::find(int keyv)
{
	node * tmp = getroot();
	if(tmp!=NULL)
	{
		if(keyv < tmp->getkey())
		{
			tmp = tmp->getleft();
		}
		else if(keyv > tmp->getkey())
		{
			tmp = tmp->getright();
		}
		else if(keyv==tmp->getkey())
		{
			return(tmp);
		}
	}
	cout << "Brak podanego wezla";
	return(NULL);
}

node * tree::min()
{
	node* tmp = new node();
        tmp=getroot();
        while(tmp->getleft()!= NULL)
        {
                tmp=tmp->getleft();
        }
        return(tmp);
}

node * tree::min(node * a)
{
	while(a->getleft()!=NULL)
	{
		a=a->getleft();
	}
	return(a);
}

node * tree::max()
{
	node* tmp = new node();
        tmp=getroot();
        while(tmp->getright()!= NULL)
        {
                tmp=tmp->getright();
        }
        return(tmp);
}

node * tree::max(node * a)
{
	while(a->getright()!=NULL)
	{
		a=a->getright();
	}
	return(a);
}

node * tree::next(node * a)
{
	node * tmp = new node();
	if(a!=max())
	{
	if(a->getright()!=NULL)
	{
		return(min(a->getright()));
	}
	else
	{
		tmp = a->getparent();
		while((tmp!=NULL) && (a==tmp->getright()))
		{
			a=tmp;
			tmp=tmp->getparent();
		}
		return(tmp);
	}
}
	return(a);
}

node * tree::prev(node * a)
{
	node * tmp = new node();
	if(a!=min())
	{
	if(a->getleft()!=NULL)
	{
		return(min(a->getleft()));
	}
	else
	{
		tmp = a->getparent();
		while((tmp!=NULL) && (a==tmp->getright()))
		{
			a=tmp;
			tmp=tmp->getparent();
		}
		return(tmp);
	}
}
	return(a);
}

void tree::nextdel(node * del)
{
	node * nxt = new node();
	nxt=next(del);
	if(nxt->getright()!=NULL)
	{
		if(nxt==del->getright())
		{
			nxt->getparent()->setright(nxt->getright());
			nxt->getright()->setparent(nxt->getparent());
		}
		else
		{
			nxt->getparent()->setleft(nxt->getright());
			nxt->getright()->setparent(nxt->getparent());
		}
	}
	del->setkey(nxt->getkey());
	if(del->getright()==nxt) 
	{
		del->setright(NULL);
	}

	delete nxt;

}


void tree::prevdel(node * del)
{
	node * prv = new node();
	prv=prev(del);
	if(prv->getleft()!=NULL)
	{
		if(prv==del->getleft())
		{
			prv->getparent()->setleft(prv->getleft());
			prv->getleft()->setparent(prv->getparent());
		}
		else
		{
			prv->getparent()->setright(prv->getleft());
			prv->getleft()->setparent(prv->getparent());
		}
	}
	del->setkey(prv->getkey());
	if(del->getleft()==prv) 
	{
		del->setleft(NULL);
	}

	delete prv;

}


void tree:: erase(int keyv)
{
	node * a=new node();
	a=find(keyv);
	if(a!=NULL)
	{
		if(a->child()==0)
		{
			if(a->getparent()!=NULL)
			{
				if(a->getparent()->getleft()==a)
				{
					a->getparent()->setleft(NULL);
					delete a;
				}
				else if (a->getparent()->getright()==a)
				{
					a->getparent()->setright(NULL);
					delete a;
				}
			}
			else delete a;
		}
		else if(a->child()==1)
			if(a->getparent!=NULL)
			{
				if(a->getleft()!=NULL)
				{
					if((a->getparent()->getleft()) == a)
					{
						a->getparent()->setleft(a->getleft());
						delete a;
					}
					else if(a->getparent()->getright() == a)
					{
						a->getparent()->setright(a->getleft());
						delete a;
					}
					else if(a->getright()!=NULL)
					{
						if((a->getparent()->getleft())==a)
						{
							a->getparent()->setleft(a->getright());
							delete a;
						}
						else if ((a->getparent()->getright()) == a)
						{
							a->getparent()->setright(a->getright());
							delete a;
						}
					}
				}
			}
			else if (a->child()==2)
			{
				prevdel(a);
				//nextdel(a);
			}
	}
}







int _tmain(int argc, _TCHAR* argv[])
{
	int a;
        srand(time(NULL));
        
        tree * bst = new tree();

        bst->random(100);
        bst->inorder();
        cout<< endl<< endl;
        
        cout << endl;
        cout << "Usun: ";
        cin >> a ;

        bst->erase(a);
        
        bst->inorder();
        cout<< endl<< endl;

        cout << endl;
        system("pause");
        return 0;
}
