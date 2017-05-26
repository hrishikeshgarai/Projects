
package glancy;
import java.io.*;


public class Calculate_Time {

public static void main(String args[])throws IOException
{
	int a,b,c,d;
	BufferedReader br= new BufferedReader (new InputStreamReader(System.in));
	System.out.println("Enter four digits");
	a=Integer.parseInt(br.readLine());
	b=Integer.parseInt(br.readLine());
	c=Integer.parseInt(br.readLine());
	d=Integer.parseInt(br.readLine());
	String answer= cal(a,b,c,d);
	System.out.println(answer);
}

static String cal(int a,int b,int c, int d)
{
	int i,j;
	int arr[]=new int[4];
	arr[0]=a;
	arr[1]=b;
	arr[2]=c;
	arr[3]=d;
	String ans = new String();
	int h1=100,h2=100,m1=100,m2=100;


	for(i=2;i>=0;i--)
	{
		for(j=0;j<arr.length;j++)
		{
			if(arr[j]==i)
			{
				h1=arr[j];
				arr[j]=arr[3];
				arr[3]=h1;
				break;
			}
		}
		if(h1!=100)
			break;
		if(i==0)
		{
			return "invalid string";
		}
	}

	if(h1==2)
	{
		for(i=3;i>=0;i--)
		{
			for(j=0;j<arr.length-1;j++)
			{
				if(arr[j]==i)
				{
					h2=arr[j];
					arr[j]=arr[2];
					arr[2]=h2;
					break;
				}
			}
			if(h2!=100)
				break;
			if(i==0)
			{
				return "invalid string";
			}
		}
	}
	else
	{
		for(i=9;i>=0;i--)
		{
			for(j=0;j<arr.length-1;j++)
			{
				if(arr[j]==i)
				{
					h2=arr[j];
					arr[j]=arr[2];
					arr[2]=h2;
					break;
				}
			}
			if(h2!=100)
				break;
			if(i==0)
			{
				return "invalid string";
			}
		}
	}
	for(i=5;i>=0;i--)
	{
		for(j=0;j<arr.length-2;j++)
		{
			if(arr[j]==i)
			{
				m1=arr[j];
				arr[j]=arr[1];
				arr[1]=m1;
				break;
			}
		}
		if(m1!=100)
			break;
		if(i==0)
		{
			return "invalid string";
		}
	}
	m2=arr[0];
	ans=""+h1+""+h2+":"+m1+""+m2+"";
	return ans;	
}
}
