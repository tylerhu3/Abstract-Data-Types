/*
Tyler Hu #1597112
qhu27
10/30/2017
Programming Assignment 3
List class - Data type used to stored Objects in a doubly queue with
some additional functions 
*/
public class List extends Matrix{

	public static <T> void cc(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}
	
	public static <T> void cx(T x) // / Easier to print out stuff this way
	{
		System.out.print(x);
	}


	private class Node {
		private Object item;
		private Node next;
		private Node pre;

		Node(Object data) {
			this.item = data;
			next = null;
			pre = null;
		}

		Node getPre() {
			return pre;
		}

		Node getNext() {
			return next;
		}

		void setPre(Node node) {
			pre = node;
		}

		void setNext(Node node) {
			next = node;
		}

		Object getItem() {
			return item;
		}

		public String toString(){
			
			return String.valueOf(item);
		}	

	}

	private Node head = null;
	private Node back = null;
	private Node cursor = null;
	private int length = 0;
	private int index = -1; 

	// Constructor
	List()// Creates a new empty list.
	{
		super();
		this.length = 0;
		this.index = -1;
	};

	// Access functions
	int length() {
//		if(length == 0)
//			throw new RuntimeException("List is empty");
		// Returns the number of elements in this List.
		return length;
	};

	int index() {
		if (cursor != null)
			return index;
		else
			return -1;
	};// If cursor is defined, returns the index of the cursor element,
		// otherwise returns -1.

	Object front() {
		if(length == 0)
			throw new RuntimeException("List is empty");
		return head.getItem();
		
	}; // Returns front element. Pre: length()>0

	Object back() {
		if(length == 0)
			throw new RuntimeException("List is empty");
		return back.getItem();
	}; // Returns back element. Pre: length()>0

	Object get() {
		if (length() <= 0 || index() < 0) {
			return -1;
		}
		return cursor.getItem();
	}; // Returns cursor element. Pre: length()>0, index()>=0

	boolean equals(List L) {
		// Returns true if and only if this List and L are the same
		// integer sequence. The states of the cursors in the two Lists
		// are not used in determining equality.
		if(this == L)
			return true;
		this.moveFront();
		L.moveFront();
		while (index() >= 0 || L.index() >=0) {
			
			if(!this.get().equals(L.get()))
			{
				return false;
			}
				
			this.moveNext();
			L.moveNext();
		}
		return true;
	}

	// Manipulation procedures:
	void clear() {
		// Resets this List to its original empty state.
		head = null;
		back = null;
		cursor = null;
		index = -1;
		length = 0;
	}

	void moveFront() {
		// If List is non-empty, places the cursor under the front element,
		// otherwise does nothing.
		if (length == 0) {
			return;
		}
		
		cursor = head;
		cursor.setPre(null);
		index = 0;
	}

	void moveBack() {
		// If List is non-empty, places the cursor under the back element,
		// otherwise does nothing.
		if (length == 0) {
			// throw new RuntimeException(
			// "List is Empty");
			//

			return;
		}
		cursor = back;
		index = length - 1;
	}

	void movePrev() {
		// If cursor is defined and not at front, moves cursor one step toward
		// front of this List, if cursor is defined and at front, cursor becomes
		// undefined, if cursor is undefined does nothing.
		if (cursor == null) {

			return;
		}
		cursor = cursor.getPre();
		index--;
//		cout("cursor != null and index: " + index + " cursor : " + cursor);

	}

	void moveNext() {
		// If cursor is defined and not at back, moves cursor one step toward
		// back of this List, if cursor is defined and at back, cursor becomes
		// undefined, if cursor is undefined does nothing.
		if (cursor == null) {
			return;
		}
		cursor = cursor.next;
		index++;

	}

	void prepend(Object data) {
		// Insert new element into this List. If List is non-empty,
		// insertion takes place before front element.
		Node node = new Node(data);
		if (length == 0) {
			head = node;
			back = node;
			length++;
		} else {
			head.setPre(node);
			node.setNext(head);
			head = node;
			length++;
			index++;
		}
	}

	void append(Object data) {
		// Insert new element into this List. If List is non-empty,
		// insertion takes place after back element.
		Node node = new Node(data);
		if (length() == 0) {

			head = node;
			back = node;
			length++;
		} else {
			back.setNext(node);
			node.setPre(back);
			back = node;
			length++;
		}
	}

	void insertBefore(Object data) {
		// Insert new element before cursor.
		// Pre: length()>0, index()>=0
		if (length() <= 0 || index() < 0) {
			return;
		}
		Node node = new Node(data);
		if (cursor.getPre() != null) // in case the cursor element is the head
		{
			node.setPre(cursor.getPre());
			cursor.getPre().setNext(node);
			
		} else {
			head = node;
		}
		cursor.setPre(node);
		node.setNext(cursor);
		length++;
		index++;
	}

	void insertAfter(Object data) {
		// Inserts new element after cursor.
		// Pre: length()>0, index()>=0
		if (length() <= 0 || index() < 0) {
			return;
		}
		Node node = new Node(data);
		if (cursor.getNext() != null) {

			cursor.getNext().setPre(node);
			node.setNext(cursor.getNext());
		} else {
			back = node;
		}
		cursor.setNext(node);
		node.setPre(cursor);
		length++;

	}

	void deleteFront() {
		// Deletes the front element. Pre: length()>0
		if (length > 0) {
			head = head.getNext();
			length--;
			index--;
		}
	}
	
	void printEntries()
	{
		this.moveFront();
		while(this.index()>= 0)
		{
			cx(this.get().toString());
			this.moveNext();
		}
		cc("");
	}
	
	@Override
	public String toString(){
		// Overrides Object's toString method. Returns a String
	    // representation of this List consisting of a space 
	    // separated sequence of integers, with front on left.
		String temp = "";
		if(this.length() == 0)
			return temp;
		this.moveFront();
		while (this.index() >= 0) {
			
			temp = temp += this.get().toString();
			if(index != length -1)
				temp = temp + " ";
			this.moveNext();
		}
		return temp; 
		
	}


	void deleteBack() {	
		// Deletes the back element. Pre: length()>0
		if (length == 1) {

			if(cursor == back)
				index = -1;
			back = null;
			length--;
		}
		else if(length > 1)
		{
			if(cursor == back)
				index = -1;
			back = back.getPre();
			back.setNext(null);
			length--;
		}
		
		
	}

	void delete() {
		// Deletes cursor element, making cursor undefined.
		// Pre: length()>0, index()>=0
		if (length() <= 0 || index() < 0) {
			return;
		}
		if(cursor != null)
		{
			if(cursor == head)
			{
				deleteFront();
				return;
			}
			if(cursor == back)
			{
				deleteBack();
				return;
			}
			cursor.getPre().setNext(cursor.getNext());
			cursor.getNext().setPre(cursor.getPre());
			length--;
			cursor = null;
			index = -1;
		}
	}
	


}

