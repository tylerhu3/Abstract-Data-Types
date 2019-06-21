/*
Tyler Hu #1597112
qhu27
10/30/2017
Programming Assignment 3
Sparse class - Main Driver of Matrix.java and List.java; this client will taken 2 parameters, one input one output;
it will output some basic capabilities of the Matrix class; multiply, add, subtract, transpose,etc  
*/

import java.io.*;
import java.util.Scanner;

public class Sparse {

	public static <T> void cc(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}

	public static <T> void cxx(T x) // / Easier to print out stuff this way
	{
		System.out.print(x);
	}

	public static void main(String[] args) throws IOException {

		if(args.length != 2){
		 cc("stderr");
		 return;
		 }
		
		 Scanner input = new Scanner(new File(args[0])); //Input File
		 PrintWriter out = new PrintWriter(new FileWriter(args[1])); //output file

		int n, a, b; // n holds size, a is number of lines to insert from text for matrix A, and b is
						// number of lines for Matrix B
		n = input.nextInt();
		a = input.nextInt();
		b = input.nextInt();

		input.nextLine();// get rid of white line
		// temp variables to hold each element processed for each matrix
		int i;
		int j;
		double x;
		Matrix A = new Matrix(n);

		for (int k = 0; k < a; k++) {
			i = input.nextInt();
			j = input.nextInt();
			x = input.nextDouble();
			A.changeEntry(i, j, x);

		}

		input.nextLine();// get rid of white line
		Matrix B = new Matrix(n);
		for (int l = 0; l < b; l++) {
			i = input.nextInt();
			j = input.nextInt();
			x = input.nextDouble();
			B.changeEntry(i, j, x);
		}

		// Operations
		Matrix X = A.scalarMult(1.5);
		Matrix Add = A.add(B);
		Matrix Add2 = A.add(A);
		Matrix Sub = B.sub(A);
		Matrix SubA = A.sub(A);
		Matrix AT = A.transpose();
		Matrix AxB = A.mult(B);
		Matrix BxB = B.mult(B);

		// For quick testing purposes for future tests:
		cc("A has " + A.getNNZ() + " non-zero entries: ");
		cc(A.toString());
		cc("B has " + B.getNNZ() + " non-zero entries: ");
		cc(B.toString());
		cc("(1.5)*A = ");
		cc(X.toString());
		cc("A+B = ");
		cc(Add.toString());
		cc("A+A = ");
		cc(Add2.toString());
		cc("B-A = ");
		cc(Sub.toString());
		cc("A-A = ");
		cc(SubA.toString());
		cc("Transpose(A) = ");
		cc(AT.toString());
		cc("A*B = ");
		cc(AxB.toString());
		cc("B*B = ");
		cc(BxB.toString());

		// output of each operation
		out.println("A has " + A.getNNZ() + " non-zero entries: ");
		out.println(A.toString());
		out.println("B has " + B.getNNZ() + " non-zero entries: ");
		out.println(B.toString());
		out.println("(1.5)*A = ");
		out.println(X.toString());
		out.println("A+B = ");
		out.println(Add.toString());
		out.println("A+A = ");
		out.println(Add2.toString());
		out.println("B-A = ");
		out.println(Sub.toString());
		out.println("A-A = ");
		out.println(SubA.toString());
		out.println("Transpose(A) = ");
		out.println(AT.toString());
		out.println("A*B = ");
		out.println(AxB.toString());
		out.println("B*B = ");
		out.println(BxB.toString());
		input.close();
		out.close();

	}
}
