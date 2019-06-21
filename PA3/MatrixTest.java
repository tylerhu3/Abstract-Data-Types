import java.io.IOException;
import java.util.Random; // for a randomly generated Matrix

/*
Tyler Hu  #1597112
qhu27
10/30/2017
Programming Assignment 3
This is to test the actual matrix class, here i will just be using a 100x100 matrix; will be testing over Add, subtract, copy, equals, mult, sub and scalar mult.
Also the numbers are randomly generated which is why java.util.Random is imported.
*/
public class MatrixTest {
	public static <T> void cc(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}

	public static <T> void cx(T x) // / Easier to print out stuff this way
	{
		System.out.print(x);
	}

	
	public static void main(String[] args) throws IOException {
	
		int n = 100;

		Random rand = new Random();
		Matrix A = new Matrix(n);

		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				A.changeEntry(i, j, rand.nextInt(50) + 1);
			}
		}

		Matrix B = A.copy();

		cc("A:\n" + A.toString());

		cc("B:\n" + B.toString());
		cc("A == B: " + A.equals(B));

		A.changeEntry(9, 9, 1.0);
		cc("A:\n" + A.toString());

		cc("B:\n" + B.toString());
		cc("A == B: " + A.equals(B));

		cc("A - B :\n " + A.sub(B).toString());
		cc("A + B :\n " + A.add(B).toString());
		cc("A * B :\n " + A.mult(B).toString());
		cc("4.3 * B :\n " + B.scalarMult(4.6).toString());
		A.makeZero();
		B.makeZero();

		cc("A:\n" + A.toString());

		cc("B:\n" + B.toString());
	}
}
