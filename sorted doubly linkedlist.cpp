#include<iostream>
using namespace std;
 template <class T> class NodeList
{
private:
	//creating a node type struct
	template <class T> struct Node
	{
		T data;
		Node<T>* next;	// hold the address of next node
		Node<T>* prev;	//hold the address of previous node
		Node(T data)	//default constructor
		{
			this->data = data;
			this->next = NULL;
			this->prev = NULL;
		}

	};
	Node<T>* head; //start of the list
	Node<T>* last; //last item of the list
public:
	NodeList();//default constructor
	NodeList(const NodeList& list);
	void insert(T node);
	void showStructureForward() const;
	void showStructureReverse() const;
	void remove(T data);
	bool isEmpty() const;
	NodeList<T>& operator=(const NodeList& list2);
	 NodeList& merge(NodeList& list2);
	 void merge(NodeList& list1, NodeList& list2);
	 ~NodeList(); //destructor
	
};
template <class T>
//Default constructor
// intailising both last and head of list with NULL
 NodeList<T>::NodeList()
 {
		 head = NULL;
		 last = NULL;
 }
 //copy constructor of list
 //accepts another list as a parameter
 // and initialises the new list with param list
 template <class T>
 NodeList<T>::NodeList(const NodeList<T>& list)
 {
	 Node<T>* ptr = list.head;
	 if (ptr == NULL)
	 {
		 head = last = NULL;
	 }
	 else
	 {
		 Node<T>* ptr2;
		 Node<T>* ptr3;
		 ptr2 = new Node<T>(ptr->data);
		 head = ptr2;
		 ptr2->next = NULL;
		 ptr = ptr->next;
		 ptr3 = ptr2;
		 while (ptr != NULL)
		 {
			 ptr2 = new Node<T>(ptr->data);
			 ptr2->next = NULL;
			 ptr2->prev = ptr3;
			 ptr3->next = ptr2;
			 ptr3 = ptr2;
			 ptr = ptr->next;
		 }
		 last = ptr2;
	 }
 }
 //isempty funcyions accepts no parameters
 //checks if the list is empty or not
 //return true if list is empty and false otherwise
 template <class T>
 bool NodeList<T>::isEmpty() const
 {
	 if (head == NULL)
	 {
		 return true;
	 }
	 else return false;
 }
 template <class T>
 //showStructureForward takes no arguments
 // displays the data of all the nodes starting from head and end at last
 //returns no value
 void NodeList<T>::showStructureForward() const
 {
	 if (head == NULL)
	 {
		 cout << "    List Is Emptyyyyyyyyyy  " << endl;
	 }
	 else
	 {
		 Node<T>* ptr = head;
		 do
		 {
			 cout << ptr->data << endl;
			 ptr = ptr->next;
		 } while (ptr != NULL);
	 }
 }
 //showStructurereverse takes no arguments
 // displays the data of all the nodes starting from last and end at head
 //returns no value
 template <class T>
 void  NodeList<T>::showStructureReverse() const
 {
	 if (head == NULL)
	 {
		 cout << "    List Is Emptyyyyyyyyyy  " << endl;
	 }
	 else
	 {
		 Node<T>* ptr = last;
		 do
		 {
			 cout << ptr->data << endl;
			 ptr = ptr->prev;
		 } while (ptr != NULL);
	 }
 }
 //merge function takes two sorted lists as parameters
 //merge these two lists and stores it in the list which is calling this merge function
 //it merges the two lists so that resultant list is also sorted
 // it returns no value
 template <class T>
 void NodeList<T>::merge(NodeList& list1, NodeList& list2)
 {
	 if (&list1 == &list2)
	 {
		 *this = list2;
		 return;
	 }
	 if (list1.head == NULL)
	 {
		 *this = list2;
		 return;
	 }
	 if (list2.head == NULL)
	 {
		 *this = list1;
		 return;
	 }

	 Node<T>* list1Cursor = list1.head;	//to walk through param list1 list
	 Node<T>* list2Cursor = list2.head;	//to walk through param list2 list
	 Node<T>* fakeHead;	//to hold a merge list
	 Node<T>* mergeMe;	//to connect the nodes from the lists
	 Node<T>* fakeLast = NULL;	//to hold the last node of merge list
	 if (list2Cursor->data < list1Cursor->data)
	 {
		 fakeHead = list2Cursor;
		 list2Cursor = list2Cursor->next;
	 }
	 else if (list2Cursor->data > list1Cursor->data)
	 {
		 fakeHead = list1Cursor;
		 list1Cursor = list1Cursor->next;
	 }
	 else
	 {
		 list2Cursor = list2Cursor->next;
		 list2.remove(list2Cursor->prev->data);
		 fakeHead = list1Cursor;
		 list1Cursor = list1Cursor->next;
	 }
	 mergeMe = fakeHead;
	 while (list1Cursor != NULL && list2Cursor != NULL)
	 {
		 if (list1Cursor->data < list2Cursor->data)
		 {
			 list1Cursor->prev = mergeMe;
			 mergeMe->next = list1Cursor;
			 list1Cursor = list1Cursor->next;

		 }
		 else if (list2Cursor->data < list1Cursor->data)
		 {
			 list2Cursor->prev = mergeMe;
			 mergeMe->next = list2Cursor;
			 list2Cursor = list2Cursor->next;
		 }
		 else
		 {
			 if (list2Cursor->next == NULL)
			 {
				 list2Cursor = NULL;
			 }
			 else
			 {
				 list2Cursor = list2Cursor->next;
				 list2.remove(list2Cursor->prev->data);
			 }
			 list1Cursor->prev = mergeMe;
			 mergeMe->next = list1Cursor;
			 list1Cursor = list1Cursor->next;
		 }
		 mergeMe = mergeMe->next;
	 }
	 if (list1Cursor != NULL)
	 {
		 list1Cursor->prev = mergeMe;
		 mergeMe->next = list1Cursor;
		 fakeLast = list1.last;
	 }
	 else if (list2Cursor != NULL)
	 {
		 list2Cursor->prev = mergeMe;
		 mergeMe->next = list2Cursor;
		 fakeLast = list2.last;
	 }
	 list1.head = NULL;
	 list2.head = NULL;
	 list1.last = NULL;
	 list2.last = NULL;
	 this->head = fakeHead;
	 this->last = fakeLast;
 }
 //remove functions take a T type value as a parameter
 //search the node with that param T value and remove it from the list
 //it returns no value
 template <class T>
 void NodeList<T>::remove(T data)
 {
	 bool flag = false;//to check if the required data node existes or not
	 if (head == NULL)
	 {
		 cout << "Cant remove  List Is Emptyyyyyyyyyy  " << endl;
	 }
	 else
	 {
		 Node<T>* ptr = head;//to walk through the whole list
		 while (ptr != NULL)
		 {
			 if (ptr->data == data)
			 {
				 flag = true;
				 if (ptr == head && head->next == NULL)
				 {
					 delete head;
					 head = NULL; last = NULL;
				 }
				 else if (ptr->next == NULL)
				 {
					 ptr->prev->next = NULL;
					 delete ptr;
				 }
				 else if (ptr == head)
				 {
					 ptr->next->prev = NULL;
					 head = head->next;
					 delete ptr;
				 }
				 else
				 {
					 Node<T>* nextnode = ptr->next;
					 Node<T>* prevnode = ptr->prev;
					 nextnode->prev = prevnode;
					 prevnode->next = nextnode;
					 delete ptr;
				 }
				 break;
			 }
			 ptr = ptr->next;
		 }
		 if (!flag)
		 {
			 cout << "cannot remove " << data << " This is not the part of list!!!!!!!" << endl;
		 }
	 }

 }
 //= operator takes one list as a parameter
 //and assighn the values of param list to the caller list
 //returns the final changed list
 template <class T>
 NodeList<T>& NodeList<T>::operator=(const NodeList<T>& list2)
 {
	 Node<T>* ptr = list2.head;
	 if (ptr == NULL)
	 {
		 head = last = NULL;
	 }
	 else
	 {
		 Node<T>* ptr2;
		 Node<T>* ptr3;
		 ptr2 = new Node<T>(ptr->data);
		 head = ptr2;
		 ptr2->next = NULL;
		 ptr = ptr->next;
		 ptr3 = ptr2;
		 while (ptr != NULL)
		 {
			 ptr2 = new Node<T>(ptr->data);
			 ptr2->next = NULL;
			 ptr2->prev = ptr3;
			 ptr3->next = ptr2;
			 ptr3 = ptr2;
			 ptr = ptr->next;
		 }
		 last = ptr2;
	 }
	 return *this;
 }
 //insert function takes T type value 
 //it creates a node the param value and insert the node in the list
 //this functions find the appropriate place for that value so that list remains sorted
 //it returns no value
 template <class T>
 void NodeList<T>::insert(T node)
 {
	 Node<T>* ptr = new Node<T>(node);//creates a new node with param value

	 if (head == NULL)
	 {
		 ptr->next = NULL;
		 ptr->prev = NULL;
		 last = ptr;
		 head = ptr;
	 }
	 else if (head->next == NULL)
	 {
		 if (head->data < ptr->data)
		 {
			 ptr->next = NULL;
			 ptr->prev = head;
			 head->next = ptr;
			 last = ptr;
		 }
		 else
		 {
			 head->prev = ptr;
			 head->next = NULL;
			 ptr->prev = NULL;
			 ptr->next = head;
			 head = ptr;
		 }
	 }
	 else
	 {
		 Node<T>* ptr2 = head;
		 if (ptr2->data > ptr->data)
		 {
			 ptr->next = ptr2;
			 ptr2->prev = ptr;
			 head = ptr;
			 return;
		 }
		 bool flag;
		 while (ptr2->next != NULL)
		 {
			 flag = false;
			 if ((ptr2->data < ptr->data) && (ptr2->next->data > ptr->data))
			 {
				 flag = true;
				 ptr->next = ptr2->next;
				 ptr->prev = ptr2;
				 ptr2->next->prev = ptr;
				 ptr2->next = ptr;
				 break;
			 }
			 ptr2 = ptr2->next;
		 }
		 if ((!flag) && ptr2->next == NULL)
		 {
			 ptr2->next = ptr;
			 ptr->prev = ptr2;
			 last = ptr;
		 }
	 }

 };
 //merge function takes one sorted list as parameter
 //merge and stores the param list in the list which is calling this merge function
 //it merges the two lists so that resultant list is also sorted
 //it returns the resultant merged sorted list
 template <class T>
 NodeList<T>& NodeList<T>::merge(NodeList<T>& list2)
 {
	 if (this == &list2)
	 {
		 return list2;
	 }
	 if (this->head == NULL)
	 {
		 return list2;
	 }
	 if (list2.head == NULL)
	 {
		 return *this;
	 }

	 Node<T>* thisCursor = this->head;	//to walk through current list
	 bool flag = false;
	 Node<T>* list2Cursor = list2.head;	//to walk through param list2 list
	 Node<T>* fakeHead;	//to hold a merge list
	 Node<T>* mergeMe;	//to connect the nodes from the lists
	 Node<T>* fakeLast = NULL;	//to hold the last node of merge list
	 if (list2Cursor->data < thisCursor->data)
	 {
		 fakeHead = list2Cursor;
		 list2Cursor = list2Cursor->next;
	 }
	 else if (list2Cursor->data > thisCursor->data)
	 {
		 fakeHead = thisCursor;
		 thisCursor = thisCursor->next;
	 }
	 else
	 {
		 list2Cursor = list2Cursor->next;
		 list2.remove(list2Cursor->prev->data);
		 fakeHead = thisCursor;
		 thisCursor = thisCursor->next;
	 }
	 mergeMe = fakeHead;
	 while (thisCursor != NULL && list2Cursor != NULL)
	 {
		 if (thisCursor->data < list2Cursor->data)
		 {
			 thisCursor->prev = mergeMe;
			 mergeMe->next = thisCursor;
			 thisCursor = thisCursor->next;

		 }
		 else if (list2Cursor->data < thisCursor->data)
		 {
			 list2Cursor->prev = mergeMe;
			 mergeMe->next = list2Cursor;
			 list2Cursor = list2Cursor->next;
		 }
		 else
		 {
			 if (list2Cursor->next == NULL)
			 {
				 list2Cursor = NULL;
			 }
			 else
			 {
				 list2Cursor = list2Cursor->next;
				 list2.remove(list2Cursor->prev->data);
			 }
			 thisCursor->prev = mergeMe;
			 mergeMe->next = thisCursor;
			 thisCursor = thisCursor->next;
		 }
		 mergeMe = mergeMe->next;
	 }
	 if (thisCursor != NULL)
	 {
		 thisCursor->prev = mergeMe;
		 mergeMe->next = thisCursor;
		 fakeLast = this->last;
	 }
	 else if (list2Cursor != NULL)
	 {
		 list2Cursor->prev = mergeMe;
		 mergeMe->next = list2Cursor;
		 fakeLast = list2.last;
	 }
	 this->head = NULL;
	 this->last = NULL;
	 list2.head = fakeHead;
	 list2.last = fakeLast;
	 return list2;
 }
 //destrctor of list
 //it deletes all the nodes in the list
 template <class T>
 NodeList<T>::~NodeList() //destructor
 {
	 Node<T>* ptr = head;
	 while (ptr != NULL)
	 {
		 head = ptr->next;
		 delete ptr;
		 ptr = head;
	 }
	 delete ptr;
 }
int main()
{
	
	NodeList<int> l1;
	l1.insert(67);
	//l1.showStructureForward();
	l1.insert(33);
	l1.insert(10);
	//l1.showStructureReverse();
	l1.insert(22);
	NodeList<int> l2;
	NodeList<int> l3;
	l2= l1;
	/*l2.insert(23);
	l2.insert(10);
	l2.insert(67);
	l2.insert(12);
	*/
	/*cout << "List 1\n" << endl;
	l1.showStructureForward();*/
	/*l1.remove(22);
	l1.remove(10);
	l1.remove(33);
	l1.remove(67);*/
	cout << "List 1\n" << endl;
	l1.showStructureForward();
	cout << "List 2\n" << endl;
	l2.showStructureForward();
	l3.merge(l1,l2);
	cout << "merged lists \n" << endl;
	l3.showStructureForward();

	
	//l1.search(3);
	//l1.replace(s3);
	//l1.gotoBeginning();
	//l1.gotoEnd();
	//l1.gotoPrior();
	//l1.gotoNext();
	//s2 = l1.getCursor();
	//l1.showStructureReverse();
	return 0;
}