/*
Tyler Hu #1597112
qhu27
10/30/2017
Programming Assignment 3
Matrix class - Data type used to represent a sparse matrix where elements with 0 as it's value are excluded
*/
public class Matrix extends Sparse {
	public static <T> void cc(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}

	class Entry {
		int col;
		double value;

		Entry(int col, double val) {
			this.col = col;
			this.value = val;
		}

		void set(int col, double val) {
			this.col = col;
			this.value = val;
		}

		void setValue(double x) {
			this.value = x;
		}
		
		
		 public boolean equals(Entry x) // overrides Object's equals() method
		 {
			 if(this == x)
				 return true;
			 if(this.col != x.col)
				 return false;
			 if(this.value != x.value)
				 return false;
			 return true;
		 }
		
		@Override
		public String toString() // overrides Object's toString() method
		{
			String temp = "(" + String.valueOf(col) + ", " + String.valueOf(value) + ")";
			return temp;
		}
	}

	List row[];
	int size;

	// Constructor

	Matrix(int n) // Makes a new n x n zero Matrix. pre: n>=1
	{
		size = n;
		this.row = new List[n + 1];
		for (int i = 1; i < n + 1; i++) {
			row[i] = new List();

		}

	}

	public Matrix() {
		// TODO Auto-generated constructor stub
	}

	// Access functions
	int getSize() // Returns n, the number of rows and columns of this Matrix
	{
		return size;
	}

	int getNNZ() // Returns the number of non-zero entries in this Matrix
	{
		int nnz = 0;
		for (int i = 1; i <= size; i++) {
			nnz += row[i].length();
		}
		return nnz;
	}

	@Override
	 public boolean equals(Object x) // overrides Object's equals() method
	 {
		 if(this == x)
			 return true;
		 Matrix X = (Matrix)x;
		 Entry Y = new Entry(0,0), Z = new Entry (0,0); //bad idea here
		 if(this.size != X.size)
			 return false;
		 for(int i = 1; i <= size; i++)
		 {
			 this.row[i].moveFront();
			 X.row[i].moveFront();
			 while(row[i].index() >= 0 || X.row[i].index()>=0)
			 {
				 if(row[i].index() >= 0)
				 Y = (Entry) row[i].get();
				 if(X.row[i].index() >= 0)
				 Z = (Entry) X.row[i].get();
				 if(!Y.equals(Z))
					 return false;
				 row[i].moveNext();
				 X.row[i].moveNext();
			 }
		 }
		 return true;
	 }
	// // Manipulation procedures
	void makeZero() // sets this Matrix to the zero state
	{
		for (int i = 1; i < size + 1; i++) {
			row[i].clear();
		}
	}

	Matrix copy()// returns a new Matrix having the same entries as this
	{
		Entry tempE;
		Matrix temp = new Matrix(size);
		for (int i = 1; i <= size; i++) {
			row[i].moveFront();
			while (row[i].index() >= 0) {
				tempE = (Entry) row[i].get();
				temp.changeEntry(i, tempE.col, tempE.value);
				row[i].moveNext();
			}
		}
		return temp;
	}

	// Matrix
	void changeEntry(int i, int j, double x) {
		
		if (row[i] == null) {
			cc("Null list; Exit.");
			return;
		}
		
		Entry temp = null;
		boolean jExist = false; // variable to check if this col exist in List
		boolean greaterJ = true; //variable to check if j belongs in the end of this list
		row[i].moveFront();
		while (row[i].index() >= 0) // Cycle through and find this element
		{
			
			temp = (Entry) row[i].get();
			if (temp.col > j) {
				greaterJ = false;
				break;
			}	
			if (temp.col == j) {
				jExist = true;
				break;
			}
			row[i].moveNext();
		}

		// / four possible cases
		if (jExist == false && x == 0) {
			return;
		}

		if (jExist == true && x == 0) {
			row[i].delete();
			return;
		}

		if (jExist == false && x != 0) {
//			row[i].print();
			Entry data = new Entry(j, x);
			if (row[i].length() == 0 || greaterJ) {
				row[i].append(data);
				return;
			}
			row[i].insertBefore(data);
			return;
		}

		if (jExist == true && x != 0) {
			temp.value = x;
			return;
		}

	}

	// // returns a new Matrix that is the scalar product of this Matrix with x

	Matrix scalarMult(double x) {
		Entry tempE;
		Matrix temp = new Matrix(this.size);
		for (int i = 1; i <= size; i++) {

			row[i].moveFront();
			while (row[i].index() >= 0) {
				tempE = (Entry) row[i].get();
				temp.changeEntry(i, tempE.col, x * tempE.value);
				row[i].moveNext();
			}
		}
		return temp;
	}

	Matrix add2(Matrix M)
	{
		// // returns a new Matrix that is the sum of this Matrix with M
		// // pre: getSize()==M.getSize()
		if (this.getSize() != M.getSize()) {
			throw new RuntimeException("Mismatch Matrix Size");
		}
		
		
		Matrix temp = new Matrix(size);
		Entry tempThis = new Entry(0, 0) , tempM = new Entry(0, 0);
		
		for(int i = 1; i <= size; i++)
		{
			row[i].moveFront();
			M.row[i].moveFront();
			while (row[i].index() >= 0 || M.row[i].index() >= 0)
			{
				if (row[i].index() >= 0) {
					tempThis = (Entry) row[i].get();
				} 
				if (M.row[i].index() >= 0) {
					tempM = (Entry) M.row[i].get();
				}
				
				if (tempThis.col == tempM.col) {
					temp.changeEntry(i, tempM.col, tempThis.value + tempM.value);
					row[i].moveNext();
					M.row[i].moveNext();
				}
				else if(tempThis.col > tempM.col)
				{
					temp.changeEntry(i, tempM.col,tempM.value);
				} 
			}
		}
		
		
		return temp;
	}
	
	Matrix add(Matrix M) {
		// // returns a new Matrix that is the sum of this Matrix with M
		// // pre: getSize()==M.getSize()
		if (this.getSize() != M.getSize()) {
			throw new RuntimeException("Mismatch Matrix Size");
		}

		Entry tempP = new Entry(0, 0), tempQ = new Entry(0, 0), temp1 = new Entry(0, 0), temp2 = new Entry(0, 0);
		Matrix temp = new Matrix(size);
		if (this == M) {
			return this.scalarMult(2);
		}
		
		for (int i = 1; i <= size; i++) {
			row[i].moveFront();
			M.row[i].moveFront();
			while (row[i].index() >= 0 || M.row[i].index() >= 0) {
				if (row[i].index() >= 0) {
					tempQ = (Entry) row[i].get();
				} 
				if (M.row[i].index() >= 0) {
					tempP = (Entry) M.row[i].get();
				}

//				cc("tempP.col = " + tempP.col + " tempQ.col = " + tempQ.col);
				if (tempQ.col == tempP.col) {
					temp.changeEntry(i, tempQ.col, tempQ.value + tempP.value);
					row[i].moveNext();
					M.row[i].moveNext();
				} else if (tempQ.col > tempP.col && M.row[i].index() >= 0) {
					temp.changeEntry(i, tempP.col, tempP.value);
					M.row[i].moveNext();
				} else if (tempQ.col < tempP.col && row[i].index() >= 0){
					temp.changeEntry(i, tempQ.col, tempQ.value);
					row[i].moveNext();
				} else if (tempQ.col > tempP.col && M.row[i].index() < 0) {
					temp.changeEntry(i, tempQ.col, tempQ.value);
					row[i].moveNext();
				} else if(tempQ.col < tempP.col && row[i].index() < 0)
				{
					temp.changeEntry(i, tempP.col, tempP.value);
					M.row[i].moveNext();
				}
				
//				cc("add::row:: "+ i);
//				cc("Q index: " + row[i].index() + " P index: " + M.row[i].index());
//				 cc("After Changes; tempP.col = " + tempP.col + " tempQ.col = " + tempQ.col);
//				cc("CX");
			}

			temp1.set(tempQ.col, 0);
			tempP = temp1;
			temp2.set(tempP.col, 0);
			tempQ = temp2;
		}

		return temp;
	}

	Matrix sub(Matrix M) {
		// returns a new Matrix that is the difference of this Matrix with M
		// // pre: getSize()==M.getSize()
		if (this.getSize() != M.getSize()) {
			throw new RuntimeException("Mismatch Matrix Size");
		}
		
		Matrix temp = new Matrix(size);
		if (this == M) {
			return temp;

		}

		Entry tempP = new Entry(0, 0), tempQ = new Entry(0, 0), temp1 = new Entry(0, 0), temp2 = new Entry(0, 0);
		for (int i = 1; i <= size; i++) {

			row[i].moveFront();
			M.row[i].moveFront();
			while (row[i].index() >= 0 || M.row[i].index() >= 0) {
				
				if (row[i].index() >= 0)
					tempQ = (Entry) row[i].get();
				if (M.row[i].index() >= 0)
					tempP = (Entry) M.row[i].get();
				
				if (tempQ.col == tempP.col) {
					temp.changeEntry(i, tempQ.col, tempQ.value - tempP.value);
					row[i].moveNext();
					M.row[i].moveNext();
				} else if (tempQ.col > tempP.col && M.row[i].index() >= 0) {
					temp.changeEntry(i, tempP.col, -tempP.value);
					M.row[i].moveNext();
				} else if (tempQ.col < tempP.col && row[i].index() >= 0){
					temp.changeEntry(i, tempQ.col, tempQ.value);
					row[i].moveNext();
				} else if (tempQ.col > tempP.col && M.row[i].index() < 0) {
					temp.changeEntry(i, tempQ.col, tempQ.value);
					row[i].moveNext();
				} else if(tempQ.col < tempP.col && row[i].index() < 0)
				{
					temp.changeEntry(i, tempP.col, -tempP.value);
					M.row[i].moveNext();
				}
//
//				cc("row: "+ i + " index check: " + row[i].index() + " M index: " + M.row[i].index());
//				 cc("After Changes; tempP.col = " + tempP.col + " tempQ.col = " + tempQ.col);
				
			}
			temp1.set(tempQ.col, 0);
			tempP = temp1;
			temp2.set(tempP.col, 0);
			tempQ = temp2;
		}

		return temp;
	}

	Matrix transpose()
	// returns a new Matrix that is the transpose of this Matrix
	{
		Entry tempE = null;
		Matrix temp = new Matrix(size);
		for (int i = 1; i <= this.size; i++) {
			this.row[i].moveFront();
			while (row[i].index() >= 0) {
				tempE = (Entry) row[i].get();
				temp.changeEntry(tempE.col, i, tempE.value);
				this.row[i].moveNext();
			}
		}
		return temp;
	}

	Matrix mult(Matrix M) {
		// returns a new Matrix that is the product of this Matrix with M
		// pre: getSize()==M.getSize()
		// Other functions
		if (this.getSize() != M.getSize()) {
			throw new RuntimeException("Mismatch Matrix Size");
		}

		Matrix temp = M.transpose();
		Matrix temp2 = new Matrix(this.size);

		for (int i = 1; i <= size; i++) {
			for (int j = 0; j <= size; j++) {
				temp2.changeEntry(i, j, dot(row[i], temp.row[j]));
			}

		}
		return temp2;
	}

	public String print() {
		Entry tempE;
		String temp = "";

		for (int i = 1; i <= size; i++) {
			temp += i + ": ";
			row[i].moveFront();
			while (row[i].index() >= 0) {
				tempE = (Entry) row[i].get();
				temp += tempE.toString();
				row[i].moveNext();
			}
			temp += "\n";
		}
		cc(temp);
		return temp;
	}

	// Other functions
	@Override
	public String toString() // overrides Object's toString() method
	{
		String temp = "";
		for (int i = 1; i <= size; i++) {
			if (row[i].length() != 0) {
				temp += i + ": " + row[i].toString() + System.getProperty("line.separator") ;
			}
		}
		return temp;
	}

	// /function to get the dot product between 2 List
	private static double dot(List P, List Q) {

		if (P == null || Q == null)
			return 0;
		if (P.length() == 0 || Q.length() == 0)
			return 0;

		P.moveFront();
		Q.moveFront();
		double x1 = 0;

		Entry tempP = null, tempQ = null;

		while (P.index() >= 0 && Q.index() >= 0) {
			if (P.index() >= 0)
				tempQ = (Entry) P.get();

			if (Q.index() >= 0)
				tempP = (Entry) Q.get();

			if (tempQ.col == tempP.col) {

				x1 += tempQ.value * tempP.value;
				Q.moveNext();
				P.moveNext();
			} else if (tempQ.col > tempP.col) { // this is probably the current problem b/c this will never be true
				Q.moveNext();

			} else {
				P.moveNext();
			}

		}
		return x1;
	}

}
