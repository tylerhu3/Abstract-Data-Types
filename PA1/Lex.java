package pa1;

import java.io.*;
import java.util.Scanner;
import static List.java;
public class Lex {

	public static <T> void cc(T x) // / Easier to print out stuff this way
	{
		System.out.println(x);
	}

	public static int findSize(Scanner input) // returns size of file
	{
		int n = 0; // stores number of lines from input file
		while (input.hasNextLine()) {
			input.nextLine();
			n++;
		}
		return n;
	}

	public static void main(String[] args) throws IOException {

		Scanner input = new Scanner(new File("input.txt"));
		int n = findSize(new Scanner(new File("input.txt"))); // gets array size

		String arr[] = new String[n];
		for (int i = 0; i < n; i++) // Create arr from input
		{
			arr[i] = input.nextLine();
			 cc(arr[i]);
		}
		// lets try out the List ADT
		List list = new List();

		// List Sorting:
		int x;
		list.prepend(0);
		for (int i = 1; i < n; i++) {
			cc("Print List:");
			list.print();
			list.moveBack(); // / put cursor to back end
			while (list.index() >= 0) {
				cc("List Index: " + list.index());
				x = list.get();
				cc("comparing arr[i]: " + arr[i] + " VS " + arr[x] + "\t\t x: "
						+ x);
				cc("XXX: " + arr[i].compareTo(arr[x]));
				if (arr[i].compareTo(arr[x]) >= 0) {
					list.insertAfter(i);
					break;
				}
				else if(arr[i].compareTo(arr[x]) < 0 && list.index() == 0 )
				{
					list.prepend(i);
					break;
				}
					list.movePrev();
			}
			cc("\n");
		}
		cc("Print List:");
		list.print();
		
		// 
// 		
// 		// List Sorting:
// 		int x;
// 		list.append(0);
// 		for (int i = 1; i < n; i++) {
// 			cc("Print List:");
// 			list.print();
// 			list.moveFront();// / put cursor to back end
// 			while (list.index() >= 0) {
// 				cc("List Index: " + list.index());
// 				x = list.get();
// 				cc("comparing arr[i]: " + arr[i] + " VS " + arr[x] + "\t\t x: "
// 						+ x);
// 				cc("XXX: " + arr[i].compareTo(arr[x]));
// 				
// 				if (arr[i].compareTo(arr[x]) <= 0) {
// 					list.insertBefore(i);
// 					break;
// 				}
// 				else if(arr[i].compareTo(arr[x]) > 0 && list.get() == list.index() -1)
// 				{
// 					cc("dick");
// 					list.append(i);
// 					break;
// 				}
// 					list.moveNext();
// 			}
// 			cc("\n");
// 		}
// 		cc("Print List:");
// 		list.print();
// 		input.close();
 	}

}
