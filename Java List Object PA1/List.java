package pa1;

public class List extends Lex {

	private class Node {
		private int item;
		private Node next;
		private Node pre;

		Node(int data) {
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


		int getItem() {
			return item;
		}
	}

	public <T> void cout(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}

	private Node head = null;
	private Node back = null;
	private Node cursor = null;
	private int length = 0;
	private int index = -1;

	// Constructor
	List()// Creates a new empty list.
	{
//		cout("Default Constructor Initiated x1");
	};

	// Access functions
	int length() {
		// Returns the number of elements in this List.
		return length;
	};

	int index() {
		cout("index():: print cursor : " + cursor );
		if (cursor != null)
			return index;
		else
			return -1;
	};// If cursor is defined, returns the index of the cursor element,
		// otherwise returns -1.

	int front() {
		return head.getItem();
	}; // Returns front element. Pre: length()>0

	int back() {
		return back.getItem();
	}; // Returns back element. Pre: length()>0

	int get() {
		if (length() <= 0 || index() < 0) {
			cout("get()::length() <= 0 || index() < 0");
			return -1;
		}
		return cursor.getItem();
	}; // Returns cursor element. Pre: length()>0, index()>=0

	boolean equals(List L) {
		// Returns true if and only if this List and L are the same
		// integer sequence. The states of the cursors in the two Lists
		// are not used in determining equality.
		return false;
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
			// throw new RuntimeException(
			// "List is Empty");
			//
			cout("moveFront: Error: Empty List");
			return;
		}
		cout("cursor = head now");
		cursor = head;
		index = 0;
	}

	void moveBack() {
		// If List is non-empty, places the cursor under the back element,
		// otherwise does nothing.
		if (length == 0) {
			// throw new RuntimeException(
			// "List is Empty");
			//
			cout("moveBack: Error: Empty List");
			return;
		}
		//cout("cursor = head now");
		cursor = back;
		index = length - 1;
	}

	void movePrev() {
		// If cursor is defined and not at front, moves cursor one step toward
		// front of this List, if cursor is defined and at front, cursor becomes
		// undefined, if cursor is undefined does nothing.
		if (cursor == null) {

			cout("cursor == null");
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

	void prepend(int data) {
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
		}
	}

	void append(int data) {
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

	void insertBefore(int data) {
		// Insert new element before cursor.
		// Pre: length()>0, index()>=0
		if (length() <= 0 || index() < 0) {
			cout("length() <= 0 || index() < 0");
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
	}

	void insertAfter(int data) {
		// Inserts new element after cursor.
		// Pre: length()>0, index()>=0
		if (length() <= 0 || index() < 0) {
			cout("length() <= 0 || index() < 0");
			return;
		}
		Node node = new Node(data);
		if (cursor.getNext() != null) {
			node.setNext(cursor.getNext());
			cursor.getNext().setPre(node);
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
		}
	}

	void deleteBack() {
		// Deletes the back element. Pre: length()>0
		if (length > 0) {
			back = back.getPre();
			length--;
		}
	}

	void delete() {
		// Deletes cursor element, making cursor undefined.
		// Pre: length()>0, index()>=0
		if (length() <= 0 || index() < 0) {
			cout("length() <= 0 || index() < 0");
			return;
		}

		cursor = null;
		index = -1;
	}
	
	void print()  // use to test list, delete later.
	{
		if(length() == 0)
			return;
		Node temp = head;
		while(temp != null)
		{
			cout(temp.getItem());
			temp = temp.getNext();
		}
	}

}
