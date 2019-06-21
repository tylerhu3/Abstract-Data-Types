import java.io.IOException;

/*
Tyler Hu  #1597112
qhu27
10/30/2017
Programming Assignment 3
Simple tester to test the New List, mainly testing it with ints because it accepts Objects
*/
public class ListTest{
	public static <T> void cc(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}
	public static <T> void cx(T x) // / Easier to print out stuff this way
	{
		System.out.print(x);
	}

	
	public static void main(String[] args) throws IOException {
		List A = new List();
		List B = new List();
		cc("A == B : " + A.equals(B));
		cc("A appends 222");
		A.append(222);
		cc("A == B : " + A.equals(B));
		cc("A delete");
		A.clear();
		
		for(int i = 0; i < 50; i++)
		{
			A.append(i);
			B.prepend(i);
		}
		for(int i = 0; i < 50; i++)
		{
			A.prepend(i);
			B.append(i);
		}
		

		cc(A.toString());
		cc(B.toString());

		cc("A == B : " + A.equals(B));
		
		for(int i = 0; i < 15; i++)
		{
			A.deleteFront();
			B.deleteBack();
		}
		cc(A.toString());
		cc(B.toString());
		cc("A == B : " + A.equals(B));
		
		for(int i = 99; i < 115; i++)
		{
			A.insertAfter(i);
			B.insertBefore(i);
		}
		cc(A.toString());
		cc(B.toString());
		for(int i = 99; i < 115; i++)
		{
			A.delete();
			B.delete();
		}
		cc("cleared both:");
		cc(A.toString());
		cc(B.toString());
		
		cc("\nend of ListTest");
	
	}
	
}
