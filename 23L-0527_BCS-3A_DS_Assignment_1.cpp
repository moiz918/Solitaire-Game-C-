#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <string>
#include <windows.h>
#include <cstdlib>
using namespace std;

//static variables to initialise the value of each suit and decksize
static int heart = 1;
static int diamond = 2;
static int club = 3;
static int spade = 4;
static int deckSize = 52;



class Command
{
private:
	bool FlipTail;
	string data; //string to store the whole command
	char action; // can be s or m or w
	char dest; 
	char src;
	int destIndex;
	int srcIndex;
	int count; //number of cards to be moved



public:

	Command() //default constructor setting everything to 0 initially
	{
		FlipTail = false;
		data = "0";
		action = 0;
		dest = 0;
		src = 0;
		destIndex = 0;
		srcIndex = 0;
		count = 0;
	}

	Command(string s) //overloaded constructor used to store the string at the initialisation of command
	{
		FlipTail = false;
		data = s;
		action = 0;
		dest = 0;
		src = 0;
		destIndex = 0;
		srcIndex = 0;
		count = 0;
	}

	friend ostream& operator<<(std::ostream& out, const Command& c) //output operator to display data of cards
	{
		out << c.data;
		return out;
	}

	bool ParseCommand() //parsing command and setting all command variables accordingly
	{
		int i = 0;
		while (data[i] == ' ') //removes space before command is entered if any exists
		{ 
			i++;
		}

		if (data[i] != 's' && data[i] != 'z' && data[i] != 'm' && data[i] != 'S' && data[i] != 'Z' && data[i] != 'M' && data[i] != 'q' && data[i] != 'Q') //if action is not equal
			                                                                                                           //then it is invalid commmand
		{
			return false;
		}

		if (data[i] == 's' || data[i] == 'z' || data[i] == 'S' || data[i] == 'Z' || data[i] == 'q' || data[i] == 'Q') //in the instance of s or z ony action needs to be initialised
		{
			char c = data[i];
			i++;
			while (data[i] == ' ') 
			{
				i++;
			}
			if (data[i] != 0)
			{
				return false;
			}
			else 
			{
				action = c;
				return true;
			}
		}

		else if (data[i] == 'm' || data[i] == 'M') //in the instance command is of move condition
		{
			i++;
			while (data[i] == ' ')
			{
				i++;
			}
			if (data[i] != 'w' && data[i] != 'c' && data[i] != 'f' && data[i] != 'W' && data[i] != 'C' && data[i] != 'F') //command is invalid if source or destination
			{                                                                                                             //does not match the valid values
				return false;
			}
			else
			{
				src = data[i];
				if (src == 'c' || src == 'C')
				{
					i++;
					if (data[i] <= '7' && data[i] >= '1') //columns can only be in between 1 or 7 inclusive
					{
						srcIndex = data[i] - '0';
						srcIndex--;
					}
					else
					{
						src = 0;
						return false;
					}

				}
				else if (src == 'f' || src == 'F')
				{
					i++;
					if (data[i] <= '4' && data[i] >= '1') //foundations can only be in between 1 or 4 inclusive
					{
						srcIndex = data[i] - '0';
						srcIndex--; //subtract to adhere to pointer index values
					}
					else
					{
						src = 0;
						return false;
					}
				}
				i++;
				while (data[i] == ' ')
				{
					i++;
				}
				if (data[i] != ',') //to check if source and destination have been seperated by a comma
				{
					return false;
				}
				else
				{
					i++;
					while (data[i] == ' ')
					{
						i++;
					}
					if (data[i] != 'f' && data[i] != 'c' && data[i] != 'F' && data[i] != 'C') //same procedure repeated for destination
					{
						return false;
					}
					else
					{
						dest = data[i];
						i++;
						if (dest == 'c' || dest == 'C')
						{
							if (data[i] <= '7' && data[i] >= '1')
							{
								destIndex = data[i] - '0';
								destIndex--;
							}
							else 
							{
								src = 0;
								dest = 0;
								return false;
							}
						}
						else if (dest == 'f'|| dest == 'F')
						{
							if (data[i] <= '4' && data[i] >= '1')
							{
								destIndex = data[i] - '0';
								destIndex--;
							}
							else 
							{
								src = 0;
								dest = 0;
								return false;

							}
						}
					}
					if ( (dest == 'f'|| dest == 'F') && ( src == 'F' || src == 'f')) //source and destination can both not be foundation as their suits are different
					{
						src = 0;
						dest = 0;
						srcIndex = 0;
						destIndex = 0;
						return false;
					}
					if ( (dest == 'c' || dest == 'C') && ( src == 'c' || src == 'C') && srcIndex == destIndex) //cannot move from the same column
					{
						src = 0;
						dest = 0;
						srcIndex = 0;
						destIndex = 0;
						return false;
					}
					i++;

					while (data[i] == ' ')
					{
						i++;
					}

					if (data[i] != ',')
					{
						return false;
					}
					i++;

					while (data[i] == ' ')
					{
						i++;
					}

					if (data[i] <= '9' && data[i] >= '1')  //to store the count of number of cards to move
					{
						if (data[i + 1] <= '3' && data[i + 1] >= '0' && data[i] == '1')
						{
							count = count + 10;
							count += data[i] - '0';
						}

						else
						{
							count = data[i] - '0';
						}

						if (src != dest) //the only scenario where cards can be more than 1 are if movement is column to column else it can only be 1
						{
							if (count != 1)
							{
								return false;
							}
						}
					}

					else
					{
						src = 0;
						dest= 0;
						srcIndex = 0;
						destIndex = 0;
						return false;
					}

					i++;
					while (data[i] == ' ')
					{
						i++;
					}

					if (data[i] != 0)
					{
						src = 0;
						dest = 0;
						srcIndex = 0;
						destIndex = 0;
						count = 0;
						return false;
					}

				}
			}
		}
			action = 'm';
			return true;
	}


	//getters used to access the variables stored in command class elsewhere in the program mainly in the process command fnction in game class
	char getAction() 
	{
		return action;
	}

	char getDest()
	{
		return dest;
	}

	char getSrc()
	{
		return src;
	}

	int getDestIndex()
	{
		return destIndex;
	}

	int getSrcIndex()
	{
		return srcIndex;
	}

	int getCount()
	{
		return count;
	}

	bool getFlipColTail()
	{
		return FlipTail;
	}

	void setFlipColTail()
	{
		FlipTail = true;
	}

	~Command()
	{

	}


};

//card class to store the data of each solitaire card
class card
{
private:
	int rank;
	bool show; //to determine whether card shoud be hidden [ ] or shown
	int suit;
public:

	card(int r = 0, int h = 0, bool s = false)
	{
		rank = r;
		show = s;
		suit = h;
	}

	friend ostream& operator<<(std::ostream& out, const card& c) //output operator to display data of cards
	{
		string h = "\u2665"; //considering symbols are not able to be printed opted for strings instead
		string d = "\u2666";
		string C = "\u2663";
		string s = "\u2660";
		if (c.show)
		{
			if (c.suit == heart || c.suit == diamond )
			{
				if (c.suit == 1)
				{
					string color = "\033[31m"; //if a card is of type diamond or heart which is checked
					string reset = "\033[37m"; //set the color to red and after output reset it
					if (c.rank == 1) //rank of 1 is A and 11 is J and 12 is Q and 13 is K in solitaire
					{
						out << color << 'A' << h << " " << reset;
					}
					else if (c.rank == 11)
					{
						out << color << 'J' << h << " " << reset;
					}
					else if (c.rank == 12)
					{
						out << color << 'Q' << h << " " << reset;
					}
					else if (c.rank == 13)
					{
						out << color << 'K' << h << " " << reset;
					}
					else
					{
						out << color << c.rank << h << " " << reset;
					}
				}
				else
				{
					string color = "\033[31m";
					string reset = "\033[37m";
					if (c.rank == 1)
					{
						out << color << 'A' << d << " " << reset;
					}
					else if (c.rank == 11)
					{
						out << color << 'J' << d << " " << reset;
					}
					else if (c.rank == 12)
					{
						out << color << 'Q' << d << " " << reset;
					}
					else if (c.rank == 13)
					{
						out << color << 'K' << d << " " << reset;
					}
					else
					{
						out << color << c.rank << d << " " << reset;
					}
				}
			}
			else
			{
				if (c.suit == 3) //default color printing for cards with suit type spades or clubs
				{
					if (c.rank == 1)
					{
						out << 'A' << C << " ";
					}
					else if (c.rank == 11)
					{
						out << 'J' << C << " ";
					}
					else if (c.rank == 12)
					{
						out << 'Q' << C << " ";
					}
					else if (c.rank == 13)
					{
						out << 'K' << C << " ";
					}
					else
					{
						out << c.rank << C << " ";
					}
				}
				else
				{
					if (c.rank == 1)
					{
						out << 'A' << s << " ";
					}
					else if (c.rank == 11)
					{
						out << 'J' << s << " ";
					}
					else if (c.rank == 12)
					{
						out << 'Q' << s << " ";
					}
					else if (c.rank == 13)
					{
						out << 'K' << s << " ";
					}
					else
					{
						out << c.rank << s << " ";
					}
				}
			}
		}
		else 
		{
			out << "[ ]";
		}
		return out;
	}


	void flipShow() //to set the card to be displayed
	{
		show = true;
	}

	void HideShow() //to set the card to be hidden or [ ] 
	{
		show = false;
	}

	int getRank() //return rank of card
	{
		return rank;
	}

	int getSuit() //return suit of card
	{
		return suit;
	}

	~card()
	{

	}
};

//This is the list clas which i set the name to tableau as it comprises the tableau columns and also elements of all stacks
template<class T> //type T as list can be both card and command
class Tableau
{
private:

	template<class T> //type T as Node can have card data or command data
	class Node
	{
	public:
		T data;
		Node<T>* next; //nature is doubly link list with next and previous pointers
		Node<T>* prev; // thismakes it easier to traverese and access nodes with efficent time complexity

		Node() //default constructor
		{
			next = 0;
			prev = 0;
		}

		Node(T x , Node<T>* NextPtr = 0, Node<T>* PrevPtr = 0) //overloaded constructor
		{
			data = x;
			next = NextPtr;
			prev = PrevPtr;
		}

		~Node()
		{

		}
	};

	//class terator used to access nodes outside of list class for card and command movement without deletion or creation of new nodes
	//type T as it can store both cards and command type nodes
	template <class T>
	class ListIterator
	{
	private:
		Node<T>* current;
	public:

		ListIterator(Node<T>* curr = 0)
		{
			current = curr;
		}

		ListIterator& operator++()  //Pre-fix increment
		{
			if (current)
			{
				current = current->next;
			}
			return *this;
		}

		ListIterator operator++(int)   //Post-fix increment
		{
			ListIterator old(current);
			if (current)
			{
				current = current->next;
			}
			return old;
		}

		ListIterator& operator--()   //Pre-fix decrement
		{
			if (current)
			{
				current = current->prev;
			}
			return *this;
		}

		ListIterator operator--(int)   //Post-fix decrement
		{
			ListIterator old(current);
			if (current)
			{
				current = current->prev;
			}
			return old;;
		}

		T& operator*() //used to get and also display node datas
		{

			return current->data;

		}

		bool operator==(const ListIterator& l) const
		{

			return current == l.current;

		}

		bool operator!=(const ListIterator& l) const
		{

			return !(current == l.current);

		}
		
		~ListIterator()
		{

		}


		Node<T>* getData() //used to access the node within the iterator
		{
			return current;
		}

	};

	Node<T>* head; //start of list
	Node<T>* tail; //end of list
	int size; //size of list

public:

	typedef ListIterator<T> Iterator; //defining iterator to access in the program

	Iterator begin() //to get the head of the list in this case since list is made with dummy head and tail it will be head->next
	{
		Iterator I(head->next);
		return I;
	}

	Iterator end() //to get the tail of the lisr
	{
		Iterator I(tail->prev);
		return I;
	}

	Tableau()
	{
		head = new Node<T>(); //default initialisation of dummy head and tail,
		tail = new Node<T>(); //this helps to not need to do boundary checks
		size = 0;
	}

	void printForward() //printing the list from head to tail to display cards in a tableau column
	{
		cout << "( " << size << " cards ) ";
		for (Node<T>* temp = head->next; temp != tail; temp = temp->next)
		{
			cout << temp->data << " ";
		}
		cout << endl;
	}

	void InsertAtEnd(T const element) //this is used in the instance of tableau columns as instea dof stacks they do not have a LIFO nature
	{
		if (size != 0)
		{
			tail->prev->next = new Node<T>(element, tail, tail->prev); //only used before the making of stock hence creation of nodes
			tail->prev = tail->prev->next;
		}
		else
		{
			head->next = tail->prev = new Node<T>(element, tail, head); //if empty list we set a card in betweem head and tail
		}
		size++;
	}

	void InsertAtStart(T const element) //this is used for the stacks pushing and popping as top is uodated
	{                                   //only used at the start when no nodes exist hence creation of nodes is inevitable
		if (head->next != 0)
		{

			Node<T>* temp = new Node<T>(element, head->next, 0);
			head->next = temp;

		}
		else
		{
			head->next = new Node<T>(element); //since stacks do not have a dummy head , we update the head node
		}
		size++;
	}

	void DeleteFromEnd() //used to remove a card from the end of the node , however not used in the program directly since deletion occurs
	{
		Node<T>* temp = tail->prev;
		tail->prev = temp->prev;
		temp->prev->next = tail;
		delete temp;
		size--;
	}

	void DeleteFromStart() //used in stack popping however since deletion occurs not used in program directly
	{
		if (size > 1)
		{
			Node<T>* temp = head->next;
			head->next = temp->next;
			temp->next->prev = head;
			delete temp;
			size--;
		}
		else if (size == 1)
		{
			delete head->next;
			head->next = 0;
			size--;
		}
	}

	void fliptail() //this is used to change determine whether the last card in the tableau column is to be shown
	{
		tail->prev->data.flipShow(); //we update the show variable in the card
	}

	void Hidetail() //this is used to change determine whether the last card in the tableau column is to be shown
	{
		tail->prev->data.HideShow(); //we update the show variable in the card
	}

	int getRank() //return the rank of the card within the tail
	{
		card d = tail->prev->data;
		return d.getRank();
	}

	int getSuit() //return the suit of the card within the tail
	{
		card d = tail->prev->data;
		return d.getSuit();
	}

	int getIndexRank( int inx) //return the rank of the card at the start of sublist
	{
		Node<T>* temp = tail->prev;
		for (int i = 0; i < inx - 1; i++)
		{
			temp = temp->prev;
		}
		card d = temp->data;
		return d.getRank();
	}

	int getIndexSuit( int inx) //return the suit of the card at the start of the sublist
	{
		Node<T>* temp = tail->prev;
		for (int i = 0; i < inx - 1; i++)
		{
			temp = temp->prev;
		}
		card d = temp->data;
		return d.getSuit();
	}

	int getSize() //function used to get the size of list
	{
		return size;
	}

	T getHeadData() //function used to get the card stored at the start of the list head->next as it is a dummy node
	{
		return head->next->data;
	}

	//function used to store a card or command at the top of the stack by pushing it
	//iterator used as we cannot create or delete nodes
	void pushVal(Iterator& ptr)
	{
		if (head->next != 0)
		{
			Node<T>* temp = head->next;
			head->next = ptr.getData();
			head->next->next = temp;
			temp->prev = head->next;
			head->next->prev = head;
		}
		else
		{
			Node<T>* temp = head->next;
			head->next = ptr.getData();
			head->next->next = 0;
			head->next->prev = head;
		}
		size++;
	}

	//function used to remove a card or command at the top of the stack by popping it
	//iterator used as we cannot create or delete nodes
	Iterator popVal()
	{
		if (!isEmpty())
		{
			Iterator ret = head->next;
			Node<T>* temp = head->next;
			head->next = temp->next;
			temp->prev = head->next;
			size--;
			return ret;
		}
		else if (size == 1)
		{
			Iterator ret = head->next;
			head->next = 0;
			size--;
			return ret;
		}
	}

	//this function shifts a card from the waste pile to the chosen tableau column by updating the tail
    //an iterator is used as we cannot create or delete nodes so we access it through iterator
	void MoveWasteToCol(Iterator& W)
	{
		Node<T>* temp = W.getData(); //get the node stored in iterator
		temp->next = tail;
		tail->prev->next = temp;
		temp->prev = tail->prev;
		tail->prev = temp;
		size++;
	}

	//function used to remove a card or command at the end of column through iterator
	//iterator used as we cannot create or delete nodes
	Iterator MoveFromEnd()
	{
		if (!isEmpty())
		{
			Iterator ret = tail->prev;
			Node <T>* temp = tail->prev;
			tail->prev = temp->prev;
			temp->prev->next = tail;
			size--;
			return ret;
		}
		else if (size == 1)
		{
			Iterator ret = tail->prev;
			tail->prev = 0;
			size--;
			return ret;
		}
	}

	//this function shifts a card from the chosen foundation to the chosen tableau column by updating the tail
    //an iterator is used as we cannot create or delete nodes so we access it through iterator
	void MoveFoundationToCol(Iterator& W)
	{
		Node<T>* temp = W.getData(); //get the node stored in iterator
		temp->next = tail;
		tail->prev->next = temp;
		temp->prev = tail->prev;
		tail->prev = temp;
		size++;
	}

	//function used to remove sublist of cards from the desired column through an iterator
	//iterator used as we cannot create or delete nodes
	Iterator MoveSubList(int index )
	{
		if (index == 1)
		{
			if (!isEmpty())
			{
				Iterator ret = tail->prev;
				Node <T>* temp = tail->prev;
				tail->prev = temp->prev;
				temp->prev->next = tail;
				size--;
				return ret;
			}
			else if (size == 1)
			{
				Iterator ret = tail->prev;
				tail->prev = 0;
				size--;
				return ret;
			}
		}
		else
		{
			if (!isEmpty())
			{
				Node<T>* temp = tail->prev;
				for (int i = 0; i < index - 1; i++) //inx - 1 so it moves the rquired number of nodes back an not 1 extra
				{
					temp = temp->prev; //used to access the start of the sublist's Node

				}
				size = size - index;
				Iterator ret = temp;
				tail->prev = temp->prev; //linking after removing sublist
				temp->prev->next = tail;
				return ret;
			}
		}
	}

	//this function shifts a sublist of cards from a chosen tableau column to another chosen tableau column
	//by linking the sublist to the end of the end of the column which calls the fuunction
	//an iterator is used as we cannot create or delete nodes so we access it through iterator
	void MoveColToCol(Iterator& W , int count)
	{
		if (count == 1)
		{
			Node<T>* temp = W.getData(); //get the node stored in iterator
			temp->next = tail;
			tail->prev->next = temp;
			temp->prev = tail->prev;
			tail->prev = temp;
			size++;
		}
		else
		{
			Node<T>* temp = W.getData(); //get the node stored in iterator
			tail->prev->next = temp;
			temp->prev = tail->prev;
			for (int i = 0; i < count - 1; i++)
			{
				temp = temp->next;
			}
			temp->next = tail;
			tail->prev = temp;
			size += count;
		}
	}


	bool isEmpty() //function used to check whether list is empty or not
	{
		return head->next == 0;
	}

	T getData() //retrieve the data stored at the head
	{
		return head->next->data;
	}

	~Tableau() //Tableau destructor to clear list of all commands or cards
	{
		if (head->next != 0)
		{
			Node<T> * temp = head->next;
			Node<T> * temp2 = temp->next;
			while (temp2 != 0)
			{
				Node<T> * temp3 = temp2->next;
				delete temp2;
				temp2 = temp3;
			}

			head->next = 0;
			tail->prev = 0;
		}
	}
};

//Stack class used to implement stock , waste and foundation piles
template <class T>
class Stack
{
private:
	Tableau<T> head; //stacks have been made through stack implementation
public:
	Stack() //Default constructor
	{
		
	}

	void push(T element) //pushing element by calling the InsertAtSTart function in list to add a node at the start of list
	{
		head.InsertAtStart(element);
	}

	void pop() //pushing element by calling the DeleteFromSTart function in list to remove a node at the start of list
	{
		head.DeleteFromStart();
	}

	//function used to print the stock pile
	void printStock()
	{
		cout << "[ ]" << "\t\t\t"; //displaying [ ] as all cards are hidden in stock pile
	}

	//function used to print the waste pile
	void printWaste()
	{
		if (head.getSize() != 0) //if waste is empty display [ ] else show top most card in waste pile
		{
			cout << head.getHeadData();
		}
		else
		{
			cout << "[ ]";
		}
	}

	//function used to print the command list
	void printCommandList()
	{
		if (head.getSize() != 0) //if command list is empty display [ ]
		{
			cout << head.getHeadData();
		}
		else
		{
			cout << "[ ]";
		}
	}

	//push a card or command in a stack without creating or deleting nodes hence the use of iterators
	void pushElem(Tableau<card>::Iterator& ptr)
	{
		head.pushVal(ptr); //function made in tableau class
	}

	//pop a card or command in a stack without creating or deleting nodes hence the use of iterators
	Tableau<card>::Iterator popElem()
	{
		return head.popVal(); //function made in tableau class
	}

	//used to print the foundation stacks
	void printForward()
	{
		if (head.getSize() != 0) //to show the size of stack head is the name of list not a node
		{
			cout << head.getHeadData();
			cout << endl;
			cout << "( " << head.getSize() << " cards ) " << endl;
			cout << endl;
		}
		else
		{
			cout << "[  ]" << endl; //if stack is empty show [ ]
			cout << "( " << head.getSize() << " cards ) " << endl;
			cout << endl;
		}
	}

	int getRank() //return the rank of a card stored in stack
	{
		card d = head.getData();
		return d.getRank();
	}

	int getSuit() //return the suit of a card stored in stack
	{
		card d = head.getData();
		return d.getSuit();
	}

	bool isEmpty() //checks whether stack is empty or not
	{
		return head.isEmpty();
	}

	T getCommandData()
	{
		return head.getData();
	}

	~Stack()
	{

	}
};

//game class which holds all stacks and lists
class game
{
private:
	Stack<card> Stock; //stock pile
	Stack<card> Waste; //waste pile
	Stack<card> Foundation[4]; //foundation piles statically set to 4 as there are 4 foundation piles
	Stack<Command> commandList; //list of commands to store them for use in undo
	Tableau<card> col[7]; //Array of Tableau columns set statically to 7 as there are 7 Tableau columns
	card deck[52]; //deck of cards
	int StockSize; //number of cards in stock pile
	int WasteSize; //number of cards in waste pile
	int colSize; //number of columns
	int commandSize; //number of commands
	int foundationSize; //number of foundation piles
	int FoundationSizes[4]; //number of cards in each foundation
	int TableauSize[7]; //total number of cards in each column
	int TableauHidden[7]; //number of hidden cards in each column
	int TableauShown[7]; //number of visible cards in each column
	bool FlipColTail;
public:
	game() //default constructor
	{
		foundationSize = 4;
		colSize = 7;
		StockSize = 0;
		WasteSize = 0;
		commandSize = 0;
		FlipColTail = false;

		for (int i = 0; i < 7; i++)
		{
			TableauSize[i] = i + 1;
		}

		for (int i = 0; i < 7; i++)
		{
			TableauHidden[i] = 0;
		}

		for (int i = 0; i < 7; i++)
		{
			TableauShown[i] = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			FoundationSizes[i] = 0;
		}

	}

	//this function is used to create cards and put them in a deck then shuffling them
	void shuffle()
	{

		for (int i = 0; i < 13; i++) //creating heart cards
		{
			card x(i + 1, 1, false);
			deck[i] = x;
		}
		for (int i = 13, j = 0 ; i < 26; j++,i++) //creating diamond cards
		{
			card x(j + 1, 2, false);
			deck[i] = x;
		}
		for (int i = 26 , k = 0; i < 39; k++,i++) //creating club cards
		{
			card x(k + 1, 3, false);
			deck[i] = x;
		}
		for (int i  = 39 , l = 0; i < 52; l++,i++) //creating spade cards
		{
			card x(l + 1, 4, false);
			deck[i] = x;
		}

		srand(static_cast<unsigned int>(time(0))); //shuffling them through srand
		{
			for (int i = 51 ; i >= 0; i--)
			{
				int rdm = rand() % (i + 1); //this shuffles the index of the card and stores it 
				card temp = deck[i];  //after that the card is swapped using basic swapping algorithm
				deck[i] = deck[rdm];
				deck[rdm] = temp;
			}
		}
	}

	//Display all piles and all columns
	void Display()
	{
		cout << "Stock \t\t\tWaste " << endl;
		Stock.printStock();
		Waste.printWaste();
		cout << endl;

		cout << "(" << StockSize << ") cards" << "\t\t" << "(" << WasteSize << ") cards " << endl;
		cout << endl;

		cout << "Previous Command" << endl;
		commandList.printCommandList();
		cout << endl << "(" << commandSize << ") commands" << endl << endl;

		for (int i = 0; i < foundationSize; i++)
		{
			cout << "Foundation " << i + 1 << " ";
			Foundation[i].printForward();
		}

		for (int i = 0; i < colSize; i++)
		{
			cout << "Column " << i + 1 << " ";
			col[i].printForward();
		}
	}

	//Function to determine whether game is won or not
	bool GameWon()
	{
		if (FoundationSizes[0] != 0 && FoundationSizes[1] != 0 && FoundationSizes[2] != 0 && FoundationSizes[3] != 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (Foundation[i].getRank() != 13)
				{
					return false; //if all foundations are not full
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	void GameWonOutro() //Used To Display that Game is won
	{
		string color = "\033[34m"; //if a card is of type diamond or heart which is checked
		string reset = "\033[37m";
		string colorSub = "\033[32m";

		cout << color << "  []          []      [][][][][][]     []          []       []            []     []     []                  []" << reset << endl;
		cout << color << "  []          []      []        []     []          []       []            []     []     [][]                []" << reset << endl;
		cout << color << "  []          []      []        []     []          []       []            []     []     []  []              []" << reset << endl;
		cout << color << "  []          []      []        []     []          []       []            []     []     []    []            []" << reset << endl;
		cout << color << "  [][][][][][][]      []        []     []          []       []            []     []     []      []          []" << reset << endl;
		cout << color << "        []            []        []     []          []       []            []     []     []        []        []" << reset << endl;
		cout << color << "        []            []        []     []          []       []  [][][][]  []     []     []          []      []" << reset << endl;
		cout << color << "        []            []        []     []          []       []  []    []  []     []     []            []    []" << reset << endl;
		cout << color << "        []            []        []     []          []       []  []    []  []     []     []              []  []" << reset << endl;
		cout << color << "        []            [][][][][][]     [][][][][][][]       [][][]    [][][]     []     []                [][]" << reset << endl;

		cout << colorSub;
		cout << "--------------------------------------------------------------------------------------------------------------" << endl;
		printLine("\t\t\t\t\tTHANK YOU FOR PLAYING SOLITAIRE! :)");
		printLine("");
		cout << reset;

		printCardsHorizontallyWon();
		
	}

	void GameLoseOutro() //Used To Display that Game is won
	{
		string color = "\033[33m"; //if a card is of type diamond or heart which is checked
		string reset = "\033[37m";
		string colorSub = "\033[32m";

		cout << color << "  [][][][][][][]      [][][][][][]     [][][]    [][][]       [][][][][][][][]" << reset << endl;
		cout << color << "  []          []      []        []     []  []    []  []       []              " << reset << endl;
		cout << color << "  []          []      []        []     []  []    []  []       []              " << reset << endl;
		cout << color << "  []          []      []        []     []  []    []  []       []              " << reset << endl;
		cout << color << "  []                  []        []     []  [][][][]  []       [][][][][][][][]" << reset << endl;
		cout << color << "  []                  [][][][][][]     []            []       []              " << reset << endl;
		cout << color << "  []    [][][][]      []        []     []            []       []              " << reset << endl;
		cout << color << "  []          []      []        []     []            []       []              " << reset << endl;
		cout << color << "  []          []      []        []     []            []       []              " << reset << endl;
		cout << color << "  [][][][][][][]      []        []     []            []       [][][][][][][][]" << reset << endl;
		cout << endl;
		cout << color << "  [][][][][][][]  []                  []  [][][][][][][][][]  [][][][][][][][]" << reset << endl;
		cout << color << "  []          []   []                []   []                  []            []" << reset << endl;
		cout << color << "  []          []    []              []    []                  []            []" << reset << endl;
		cout << color << "  []          []     []            []     []                  []            []" << reset << endl;
		cout << color << "  []          []      []          []      [][][][][][][][][]  [][][][][][][][]" << reset << endl;
		cout << color << "  []          []       []        []       []                  []  [][]        " << reset << endl;
		cout << color << "  []          []        []      []        []                  []    [][]      " << reset << endl;
		cout << color << "  []          []         []    []         []                  []      [][]    " << reset << endl;
		cout << color << "  []          []          []  []          []                  []        [][]  " << reset << endl;
		cout << color << "  [][][][][][][]            []            [][][][][][][][][]  []          [][]" << reset << endl;

		cout << colorSub;
		cout << "---------------------------------------------------------------------------------------" << endl;
		printLine("\t\t\tTHANK YOU FOR PLAYING SOLITAIRE! :)");
		printLine("");
		cout << reset;

		printCardsHorizontally();


	}

	void printLine(const string& line)
	{
		cout << line << endl;
	}

	void printCardsHorizontally()
	{
		string red = "\033[31m";
		string reset = "\033[37m";
		cout << "\t\t\t  +-----+   +-----+   +-----+   +-----+" << endl;
		cout << "\t\t\t  | A   |   | A   |   | A   |   | A   |" << endl;
		cout << "\t\t\t  |  \u2660  |   |  "<< red << "\u2665" << reset <<"  |   |  \u2666  |   |" << red <<  "  \u2663"  << reset << "  | " << endl;
		cout << "\t\t\t  +-----+   +-----+   +-----+   +-----+" << endl;
	}

	void printCardsHorizontallyWon()
	{
		string red = "\033[31m";
		string reset = "\033[37m";
		cout << "\t\t\t\t\t  +-----+   +-----+   +-----+   +-----+" << endl;
		cout << "\t\t\t\t\t  | A   |   | A   |   | A   |   | A   |" << endl;
		cout << "\t\t\t\t\t  |  \u2660  |   |  " << red << "\u2665" << reset << "  |   |  \u2666  |   |" << red << "  \u2663" << reset << "  | " << endl;
		cout << "\t\t\t\t\t  +-----+   +-----+   +-----+   +-----+" << endl;
	}


	//game is started and we can now play it
	void play()
	{
		//initialises the hidden cards in all 7 Tableau columns
		int count = 0;
		for (int i = 0; i < colSize; i++)
		{
			TableauShown[i] = 0;
			for (int j = 0; j < TableauSize[i]; j++)
			{
				TableauHidden[i]++;
				col[i].InsertAtEnd(deck[count++]);
			}
		}

		//flips the last card in each column so it can be seen
		for (int i = 0; i < colSize; i++)
		{
			TableauHidden[i]--;
			TableauShown[i]++;
			col[i].fliptail();

		}

		//puts the remaining cards in the stock pile
		StockSize = deckSize - count;

		for (int i = 0 , j = count ; i < StockSize; j++, i++)
		{
			Stock.push(deck[j]);
		}

		//initislly displays all piles and columns at the start of the game
		Display();

		int QuitFlag = 0;
		while (!GameWon() && QuitFlag == 0)
		{
			string command;
			cout << endl << "ENTER COMMAND  s FOR DRAW , m FOR MOVEMENT ( m c1 , c2 , 1 ) , z FOR UNDO , q TO QUIT " << endl;
			getline(cin, command); //command sent to the process command fuunction
			cout << endl << endl << endl << endl;
			int x = processCommand(command);
			if (x == 0)
			{
				cout << "INVALD COMMAND " << endl << endl; //if the command sent is invalid 
			}
			else if (x == 1)
			{
				system("cls"); //clear the screen after  every successful command execution
				Display(); //display if the command is valid
			}
			else
			{
				QuitFlag = 1;
			}
			
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl << endl << endl;

		if (GameWon())
		{
			GameWonOutro();
		}
		else
		{
			GameLoseOutro();
		}

	}

	//This function is used to move a card from waste pile to a chosen column
	bool MoveWasteToColumn(int destIndex) //index of column
	{
		int Index = destIndex;
		int InxSize = TableauSize[Index];
		if (WasteSize != 0) //if there are cards in waste pile
		{
			if (TableauSize[Index] == 0) //if the column is empty
			{
				int rank = Waste.getRank(); //check whether card in waste is a king as new column can only be initialised through a king
				if (rank == 13)
				{
					Tableau<card>::Iterator W = Waste.popElem(); //function call to pop card from waste pile
					col[Index].MoveWasteToCol(W);
					TableauSize[Index]++; //increase number of cards of tableau column
					TableauShown[Index]++;//increase number of shhiwn cards in tableau column
					WasteSize--; //reduce size of waste pile
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				//get ranks and suits of both cards to compare
				int rankW = Waste.getRank();
				int suitW = Waste.getSuit();
				int rankC = col[Index].getRank();
				int suitC = col[Index].getSuit();

				if (suitC == 1 || suitC == 2) //if card at the bottom of tableau column is diamond or heart then card in waste must be club or spade
				{
					if (suitW == 3 || suitW == 4)
					{
						if (rankC - rankW == 1) //the difference in rank can only be 1 to make the movement
						{
							Tableau<card>::Iterator W = Waste.popElem();
							col[Index].MoveWasteToCol(W);
							TableauSize[Index]++;
							TableauShown[Index]++;
							WasteSize--;
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else if (suitC == 3 || suitC == 4) //if card at the bottom of tableau column is club or spade then card in waste must be diamond or heart
				{
					if (suitW == 1 || suitW == 2)
					{
						if (rankC - rankW == 1)
						{
							Tableau<card>::Iterator W = Waste.popElem();
							col[Index].MoveWasteToCol(W);
							TableauSize[Index]++;
							TableauShown[Index]++;
							WasteSize--;
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

		}
		else
		{
			return false;
		}
	}

	//This function is used to move a card from waste pile to a chosen foundation
	bool MoveWasteToFoundation(int destIndex)
	{
		int Index = destIndex;
		int InxSize = FoundationSizes[Index];
		if (WasteSize != 0 && InxSize < 13) //if there are cards in waste pile and the max number of cards in foundation have not been reached
		{
			if (FoundationSizes[Index] == 0) //if the foundation is empty
			{
				int rank = Waste.getRank(); //check whether card in waste is an Ace as foundation can only be initialised through an Ace
				if (rank == 1)
				{
					Tableau<card>::Iterator W = Waste.popElem(); //function call to pop card from waste pile
					Foundation[Index].pushElem(W);
					FoundationSizes[Index]++; //increase number of cards of desired foundation pile
					WasteSize--; //reduce size of waste pile
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				//get ranks and suits of both cards to compare
				int rankW = Waste.getRank();
				int suitW = Waste.getSuit();
				int rankF = Foundation[Index].getRank();
				int suitF = Foundation[Index].getSuit();

				if (suitF == suitW) //if card at the top of foundation suit matches the suit of card to be moved from waste pile
				{
					if (rankW - rankF == 1) //the difference in rank can only be 1 to make the movement
					{
						Tableau<card>::Iterator W = Waste.popElem(); //function call to pop card from waste pile
						Foundation[Index].pushElem(W);
						FoundationSizes[Index]++; //increase number of cards of desired foundation pile
						WasteSize--; //reduce size of waste pile
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
		}
		else
		{
			return false;
		}
	}

	//This function is used to move a card from a chosen column to a chosen foundation
	bool MoveColumnToFoundation(int srcIndex, int destIndex , bool &FlipCol)
	{
		int Cindex = srcIndex;
		int Findex = destIndex;
		int FinxSize = FoundationSizes[Findex];
		int CinxSize = TableauSize[Cindex];
		if (CinxSize != 0 && FinxSize < 13) //if there are cards in column and the max number of cards in foundation have not been reached
		{
			if (FoundationSizes[Findex] == 0) //if the foundation is empty
			{
				int rank = col[Cindex].getRank(); //check whether card in column tail is an Ace as foundation can only be initialised through an Ace
				if (rank == 1)
				{
					if (TableauShown[Cindex] > 1)
					{
						Tableau<card>::Iterator W = col[Cindex].MoveFromEnd(); //function call to remove card from end of Tableau column
						Foundation[Findex].pushElem(W);
						FoundationSizes[Findex]++; //increase number of cards of desired foundation pile
						TableauSize[Cindex]--; //reduce size of waste pile
						TableauShown[Cindex]--; //reduce the number of displayed cards in the tableau
						return true;
					}
					else
					{
						Tableau<card>::Iterator W = col[Cindex].MoveFromEnd(); //function call to remove card from end of Tableau column
						if (TableauHidden[Cindex] > 0)
						{
							col[Cindex].fliptail(); //if only 1 shown card is in the deck and it is moved then flip the next card to display
							TableauShown[Cindex]++; //increase number of shown cards
							TableauHidden[Cindex]--; // decrease number of hidden cards
						}
						FlipCol = true;
						Foundation[Findex].pushElem(W);
						FoundationSizes[Findex]++; //increase number of cards of desired foundation pile
						TableauSize[Cindex]--; //reduce size of column
						TableauShown[Cindex]--; //reduce the number of displayed cards in the tableau
						return true;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				//get ranks and suits of both cards to compare
				int rankC = col[Cindex].getRank();
				int suitC = col[Cindex].getSuit();
				int rankF = Foundation[Findex].getRank();
				int suitF = Foundation[Findex].getSuit();

				if (suitF == suitC) //if card at the top of foundation suit matches the suit of card to be moved from the column
				{
					if (rankC - rankF == 1) //the difference in rank can only be 1 to make the movement
					{
						if (TableauShown[Cindex] > 1)
						{
							Tableau<card>::Iterator W = col[Cindex].MoveFromEnd(); //function call to remove card from end of Tableau column
							Foundation[Findex].pushElem(W);
							FoundationSizes[Findex]++; //increase number of cards of desired foundation pile
							TableauSize[Cindex]--; //reduce size of waste pile
							TableauShown[Cindex]--; //reduce the number of displayed cards in the tableau
							return true;
						}
						else
						{
							Tableau<card>::Iterator W = col[Cindex].MoveFromEnd(); //function call to remove card from end of Tableau column
							if (TableauHidden[Cindex] > 0)
							{
								col[Cindex].fliptail(); //if only 1 shown card is in the deck and it is moved then flip the next card to display
								TableauShown[Cindex]++; //increase number of shown cards
								TableauHidden[Cindex]--; // decrease number of hidden cards
							}
							FlipCol = true;
							Foundation[Findex].pushElem(W);
							FoundationSizes[Findex]++; //increase number of cards of desired foundation pile
							TableauSize[Cindex]--; //reduce size of column
							TableauShown[Cindex]--; //reduce the number of displayed cards in the tableau
							return true;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
		}
		else
		{
			return false;
		}
	}

	//This function is used to move a card from a chosen foundation to a chosen column
	bool MoveFoundationToColumn(int srcIndex, int destIndex)
	{
		int Findex = srcIndex;
		int Cindex = destIndex;
		int CinxSize = TableauSize[Cindex];
		int FinxSize = FoundationSizes[Findex];


		if (FinxSize != 0) //if there are cards in foundation 
		{
			if (TableauSize[Cindex] == 0) //if the column is empty
			{
				int rank = Foundation[Findex].getRank(); //check whether card in foundation is a king as new column can only be initialised through a king
				if (rank == 13)
				{
					Tableau<card>::Iterator W = Foundation[Findex].popElem(); //function call to pop card from waste pile
					col[Cindex].MoveFoundationToCol(W);
					TableauSize[Cindex]++; //increase number of cards of tableau column
					TableauShown[Cindex]++;//increase number of shown cards in tableau column
					FoundationSizes[Findex]--; //reduce size of waste pile
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				//get ranks and suits of both cards to compare
				int rankF = Foundation[Findex].getRank();
				int suitF = Foundation[Findex].getSuit();
				int rankC = col[Cindex].getRank();
				int suitC = col[Cindex].getSuit();

				if (suitC == 1 || suitC == 2) //if card at the bottom of tableau column is diamond or heart then card in foundation must be club or spade
				{
					if (suitF == 3 || suitF == 4)
					{
						if (rankC - rankF == 1) //the difference in rank can only be 1 to make the movement
						{
							Tableau<card>::Iterator W = Foundation[Findex].popElem();
							col[Cindex].MoveFoundationToCol(W);
							TableauSize[Cindex]++;
							TableauShown[Cindex]++;
							FoundationSizes[Findex]--;
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else if (suitC == 3 || suitC == 4) //if card at the bottom of tableau column is club or spade then card in foundation must be diamond or heart
				{
					if (suitF == 1 || suitF == 2)
					{
						if (rankC - rankF == 1)
						{
							Tableau<card>::Iterator W = Foundation[Findex].popElem();
							col[Cindex].MoveFoundationToCol(W);
							TableauSize[Cindex]++;
							TableauShown[Cindex]++;
							FoundationSizes[Findex]--;
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

		}
		else
		{
			return false;
		}
	}

	//This function is used to move a sublist of cards from a chosen column to another desired column
	bool MoveColumnToColumn(int srcIndex, int destIndex, int count , bool &FlipCol)
	{
		int Col1index = srcIndex;
		int Col2index = destIndex;
		int Col1Size = TableauSize[Col1index];
		int Col2Size = TableauSize[Col2index];

		//if there are cards in source column
		if (Col1Size != 0) 
		{
			if (TableauSize[Col2index] == 0) //if the column is empty
			{
				if (TableauShown[Col1index] > count)
				{
					//check whether card in column sublist head is a king
					//as new column can only be initialised through a king
					int rank = col[Col1index].getIndexRank(count);
					if (rank == 13)
					{
						Tableau<card>::Iterator W = col[Col1index].MoveSubList(count); //function call to pop card from waste pile
						col[Col2index].MoveColToCol(W ,count);
						TableauSize[Col2index]+= count; //increase number of cards of destination tableau column
						TableauShown[Col2index]+= count;//increase number of shown cards in destination tableau column
						TableauSize[Col1index] -= count; //decreasee number of cards of sourcetableau column
						TableauShown[Col1index] -= count;//decrease number of shown cards in source  tableau column
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (TableauShown[Col1index] == count)
				{
					//check whether card in column sublist head is a king
					//as new column can only be initialised through a king
					int rank = col[Col1index].getIndexRank(count);
					if (rank == 13)
					{
						Tableau<card>::Iterator W = col[Col1index].MoveSubList(count); //function call to pop card from waste pile
						col[Col2index].MoveColToCol(W, count);
						TableauSize[Col2index] += count; //increase number of cards of destination tableau column
						TableauShown[Col2index] += count;//increase number of shown cards in destination tableau column
						TableauSize[Col1index] -= count; //decreasee number of cards of sourcetableau column
						TableauShown[Col1index] -= count;//decrease number of shown cards in source  tableau column
						if (TableauHidden[Col1index] > 0)
						{
							col[Col1index].fliptail(); //if only 1 shown card is in the deck and it is moved then flip the next card to display
							TableauShown[Col1index]++; //increase number of shown cards
							TableauHidden[Col1index]--; // decrease number of hidden cards
						}
						FlipCol = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				//get ranks and suits of both cards to compare
				int rankCol1 = col[Col1index].getIndexRank(count);
				int suitCol1 = col[Col1index].getIndexSuit(count);
				int rankCol2 = col[Col2index].getRank();
				int suitCol2 = col[Col2index].getSuit();

				if (suitCol2 == 1 || suitCol2 == 2) //if card at the bottom of tableau column is diamond or heart then card in at start of sublist must be club or spade
				{
					if (suitCol1 == 3 || suitCol1 == 4)
					{
						if (rankCol2 - rankCol1 == 1) //the difference in rank can only be 1 to make the movement
						{
							if (TableauShown[Col1index] > count)
							{
								Tableau<card>::Iterator W = col[Col1index].MoveSubList(count); //function call to pop card from waste pile
								col[Col2index].MoveColToCol(W, count);
								TableauSize[Col2index] += count; //increase number of cards of destination tableau column
								TableauShown[Col2index] += count;//increase number of shown cards in destination tableau column
								TableauSize[Col1index] -= count; //decreasee number of cards of sourcetableau column
								TableauShown[Col1index] -= count;//decrease number of shown cards in source  tableau column
								return true;
							}
							else if (TableauShown[Col1index] == count)
							{
								Tableau<card>::Iterator W = col[Col1index].MoveSubList(count); //function call to pop card from waste pile
								col[Col2index].MoveColToCol(W, count);
								TableauSize[Col2index] += count; //increase number of cards of destination tableau column
								TableauShown[Col2index] += count;//increase number of shown cards in destination tableau column
								TableauSize[Col1index] -= count; //decreasee number of cards of sourcetableau column
								TableauShown[Col1index] -= count;//decrease number of shown cards in source  tableau column
								if (TableauHidden[Col1index] > 0)
								{
									col[Col1index].fliptail(); //if only 1 shown card is in the deck and it is moved then flip the next card to display
									TableauShown[Col1index]++; //increase number of shown cards
									TableauHidden[Col1index]--; // decrease number of hidden cards
								}
								FlipCol = true;
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else if (suitCol2 == 3 || suitCol2 == 4) //if card at the bottom of tableau column is club or spade then card at the top of the sublist must be diamond or heart
				{
					if (suitCol1 == 1 || suitCol1 == 2)
					{
						if (rankCol2 - rankCol1 == 1)
						{
							if (TableauShown[Col1index] > count)
							{
								Tableau<card>::Iterator W = col[Col1index].MoveSubList(count); //function call to pop card from waste pile
								col[Col2index].MoveColToCol(W, count);
								TableauSize[Col2index] += count; //increase number of cards of destination tableau column
								TableauShown[Col2index] += count;//increase number of shown cards in destination tableau column
								TableauSize[Col1index] -= count; //decreasee number of cards of sourcetableau column
								TableauShown[Col1index] -= count;//decrease number of shown cards in source  tableau column
								return true;
							}
							else if (TableauShown[Col1index] == count)
							{
								Tableau<card>::Iterator W = col[Col1index].MoveSubList(count); //function call to pop card from waste pile
								col[Col2index].MoveColToCol(W, count);
								TableauSize[Col2index] += count; //increase number of cards of destination tableau column
								TableauShown[Col2index] += count;//increase number of shown cards in destination tableau column
								TableauSize[Col1index] -= count; //decreasee number of cards of sourcetableau column
								TableauShown[Col1index] -= count;//decrease number of shown cards in source  tableau column
								if (TableauHidden[Col1index] > 0)
								{
									col[Col1index].fliptail(); //if only 1 shown card is in the deck and it is moved then flip the next card to display
									TableauShown[Col1index]++; //increase number of shown cards
									TableauHidden[Col1index]--; // decrease number of hidden cards
								}
								FlipCol = true;
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

		}
		else
		{
			return false;
		}
	}

	//Function used to draw a card from stock pile and place it in waste pile
	bool Draw()
	{
		if (!Stock.isEmpty()) //if stock has cards
		{
			Tableau<card>::Iterator d = Stock.popElem(); //use iterator for card movement without deleting or creating nodes
			(*(d)).flipShow(); //show the card as in waste pile all cards are displayed
			Waste.pushElem(d);
			StockSize--; //decrease stock size
			WasteSize++; //increase waste size
			return true;
		}
		else
		{
			while (!Waste.isEmpty()) // if stock is empty move all waste cards in stock through a loop
			{ 
				Tableau<card>::Iterator d = Waste.popElem();
				(*(d)).HideShow(); //hide card as all cards in stock are hidden
				Stock.pushElem(d);
				StockSize++;
				WasteSize--;
			}
			return false;
		}
	}
	
	//Function used to draw a card from waste pile and place it in atock pile
	void UndoDraw()
	{
		if (!Waste.isEmpty())
		{
			Tableau<card>::Iterator d = Waste.popElem();
			(*(d)).HideShow(); //hide card as all cards in stock are hidden
			Stock.pushElem(d);
			StockSize++;
			WasteSize--;
		}
	}

	//This function is used to move a card from foundation pile to waste pile
	void UndoMoveWasteToFoundation(int srcIndex)
	{
		int Index = srcIndex;
		Tableau<card>::Iterator W = Foundation[Index].popElem(); //function call to pop card from foundation pile
		Waste.pushElem(W);
		FoundationSizes[Index]--; //decrease number of cards of desired foundation pile
		WasteSize++; //increase size of waste pile
	}

	//This function is used to move a card from the column back to waste pile by undoing the command
	void UndoMoveWasteToColumn(int destIndex)
	{
		int Index = destIndex;
		Tableau<card>::Iterator W = col[Index].MoveFromEnd(); //get card from end of columns
		Waste.pushElem(W); //push card back into waste pile
		TableauSize[Index]--;
		TableauShown[Index]--;
		WasteSize++;
	}

	//This function is used to move a card from a chosen column to a chosen foundation by through undo
	void UndoMoveFoundationToColumn(int srcIndex, int destIndex)
	{
		int Findex = srcIndex;
		int Cindex = destIndex;
		Tableau<card>::Iterator W = col[Cindex].MoveFromEnd(); //function call to remove card from end of Tableau column
		Foundation[Findex].pushElem(W);
		FoundationSizes[Findex]++; //increase number of cards of desired foundation pile
		TableauSize[Cindex]--; //reduce size of waste pile
		TableauShown[Cindex]--; //reduce the number of displayed cards in the tableau
	}

	//This function is used to undo the move column to foundation command
	void UndoMoveColumnToFoundation(int srcIndex , int destIndex , bool FlipSet)
	{
		int Cindex = srcIndex;
		int Findex = destIndex;
		if (FlipSet == true)
		{
			if (TableauSize[Cindex] > 0)
			{
				col[Cindex].Hidetail(); //hide the card at the tail of the index before the movement if it was previoously hidden
				TableauHidden[Cindex]++;
				TableauShown[Cindex]--;
				Tableau<card>::Iterator W = Foundation[Findex].popElem(); //send card back to its source
				col[Cindex].MoveFoundationToCol(W);
				TableauSize[Cindex]++;
				TableauShown[Cindex]++;
				FoundationSizes[Findex]--;
			}
			else
			{
				Tableau<card>::Iterator W = Foundation[Findex].popElem();
				col[Cindex].MoveFoundationToCol(W);
				TableauSize[Cindex]++;
				TableauShown[Cindex]++;
				FoundationSizes[Findex]--;
			}
		}
		else
		{
			Tableau<card>::Iterator W = Foundation[Findex].popElem();
			col[Cindex].MoveFoundationToCol(W);
			TableauSize[Cindex]++;
			TableauShown[Cindex]++;
			FoundationSizes[Findex]--;
		}
	}

	//This function is used to undo the move column to column command
	void UndoMoveColumnToColumn(int srcIndex, int destIndex, int count , bool FlipSet)
	{
		int Col1index = srcIndex;
		int Col2index = destIndex;
		if (FlipSet == true)
		{
			if (TableauSize[Col1index] > 0)
			{
				col[Col1index].Hidetail();
				TableauHidden[Col1index]++;
				TableauShown[Col1index]--;
				Tableau<card>::Iterator W = col[Col2index].MoveSubList(count); //function call to pop card from column
				col[Col1index].MoveColToCol(W, count);
				TableauSize[Col1index] += count; //increase number of cards of destination tableau column
				TableauShown[Col1index] += count;//increase number of shown cards in destination tableau column
				TableauSize[Col2index] -= count; //decreasee number of cards of source tableau column
				TableauShown[Col2index] -= count;//decrease number of shown cards in source  tableau column
			}
			else
			{
				Tableau<card>::Iterator W = col[Col2index].MoveSubList(count); //function call to pop card from column
				col[Col1index].MoveColToCol(W, count);
				TableauSize[Col1index] += count; //increase number of cards of destination tableau column
				TableauShown[Col1index] += count;//increase number of shown cards in destination tableau column
				TableauSize[Col2index] -= count; //decreasee number of cards of sourcetableau column
				TableauShown[Col2index] -= count;//decrease number of shown cards in source  tableau column
			}
		}
		else
		{
			Tableau<card>::Iterator W = col[Col2index].MoveSubList(count); //function call to pop card from column
			col[Col1index].MoveColToCol(W, count);
			TableauSize[Col1index] += count; //increase number of cards of destination tableau column
			TableauShown[Col1index] += count;//increase number of shown cards in destination tableau column
			TableauSize[Col2index] -= count; //decreasee number of cards of sourcetableau column
			TableauShown[Col2index] -= count;//decrease number of shown cards in source  tableau column
		}
	}

	//Function used to process all Undo Commands
	void UndoCommand( Command& P)
	{
		//if the command is movement
		if (P.getAction() == 'm' || P.getAction() == 'M')
		{

			if (P.getSrc() == 'w' || P.getSrc() == 'W')
			{
				//if the moement is undo from waste to column
				if (P.getDest() == 'c' || P.getDest() == 'C')
				{
					UndoMoveWasteToColumn(P.getDestIndex());
				}
				//if the movement is undo from waste to foundation
				else if (P.getDest() == 'f' || P.getDest() == 'F')
				{
					UndoMoveWasteToFoundation(P.getDestIndex());
				}
			}
			else if (P.getSrc() == 'c' || P.getSrc() == 'C')
			{
				//if the movement is udno from column to foundation
				if (P.getDest() == 'f' || P.getDest() == 'F')
				{
					UndoMoveColumnToFoundation(P.getSrcIndex(), P.getDestIndex(), P.getFlipColTail());
				}
				//if the movement is undo from column to column
				else if (P.getDest() == 'c' || P.getDest() == 'c')
				{
					UndoMoveColumnToColumn(P.getSrcIndex(), P.getDestIndex(), P.getCount(), P.getFlipColTail());
				}
			}
			else if (P.getSrc() == 'f' || P.getSrc() == 'F')
			{
				//if the movement is undo from foundation to column
				if (P.getDest() == 'c' || P.getDest() == 'C')
				{
					UndoMoveFoundationToColumn(P.getSrcIndex(), P.getDestIndex());
				}
			}
		}
		//if command is to undo draw a card
		else if (P.getAction() == 's' || P.getAction() == 'S')
		{
			UndoDraw();
		}
	}

	//Function used to process command sent from play function
	int processCommand(string com)
	{
		Command P(com);
		bool Valid = P.ParseCommand(); //parse command and check whether it is valid

		if (Valid)
		{
			//if the command is movement
			if (P.getAction() == 'm' || P.getAction() == 'M')
			{
				
				if (P.getSrc() == 'w' || P.getSrc() == 'W')
				{
					//if the moement is from waste to column
					if (P.getDest() == 'c' || P.getDest() == 'C')
					{
						bool WTC = MoveWasteToColumn(P.getDestIndex());
						if (WTC) //if the command is carried out , store it in command list
						{
							commandList.push(P);
							commandSize++;
							return 1;
						}
						else
						{
							return 0;
						}
					}
					//if the movement is from waste to foundation
					else if (P.getDest() == 'f' || P.getDest() == 'F')
					{
						bool WTF = MoveWasteToFoundation(P.getDestIndex());
						if (WTF) //if the command is carried out , store it in command list
						{
							commandList.push(P);
							commandSize++;
							return 1;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						return 0;
					}
				}
				else if (P.getSrc() == 'c' || P.getSrc() == 'C')
				{
					//if the movement ix from column to foundation
					if (P.getDest() == 'f' || P.getDest() == 'F')
					{
						bool CTF = MoveColumnToFoundation(P.getSrcIndex() , P.getDestIndex() , FlipColTail);
						if (CTF) //if the command is carried out , store it in command list
						{
							if (FlipColTail)
							{
								P.setFlipColTail();
							}
							FlipColTail = false;
							commandList.push(P);
							commandSize++;
							return 1;
						}
						else
						{
							return 0;
						}
					}
					//if the movement is from column to column
					else if (P.getDest() == 'c' || P.getDest() == 'c')
					{
						bool CTC = MoveColumnToColumn(P.getSrcIndex(), P.getDestIndex() , P.getCount() , FlipColTail);
						if (CTC) //if the command is carried out , store it in command list
						{
							if (FlipColTail)
							{
								P.setFlipColTail();
							}
							FlipColTail = false;
							commandList.push(P);
							commandSize++;
							return 1;
						}
						else
						{
							return 0;
						}
					}
				}
				else if (P.getSrc() == 'f' || P.getSrc() == 'F')
				{
					//if the movement is from foundation to column
					if (P.getDest() == 'c' || P.getDest() == 'C')
					{
						bool FTC = MoveFoundationToColumn(P.getSrcIndex(), P.getDestIndex());
						if (FTC) //if the command is carried out , store it in command list
						{
							commandList.push(P);
							commandSize++;
							return 1;
						}
						else
						{
							return 0;
						}
					}
				}
			}
			//if command is to draw a card
			else if (P.getAction() == 's' || P.getAction() == 'S')
			{
				bool d = Draw();
				if (d)
				{
					commandList.push(P);
					commandSize++;
					return 1;
				}
				else
				{
					return 0;
				}
			}
			//if command is to undo
			else if (P.getAction() == 'z' || P.getAction() == 'Z')
			{
				if (!commandList.isEmpty())
				{
					Command P = commandList.getCommandData();
					UndoCommand(P);
					commandList.pop();
					commandSize--;
					return 1;
				}
				else
				{
					return 0;
				}
			}
			//if the command is to quit the game
			else if (P.getAction() == 'q' || P.getAction() == 'Q')
			{
				return 2;
				}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}

	}

	~game()
	{

	}

};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	game solitaire; //game class object
	solitaire.shuffle(); //shuffling cards at initialisation
	solitaire.play(); //start of game

	system("pause");
	return 0;
}