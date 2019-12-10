package Pylot_BT; 

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;

public class Test 
{

	public static void main(String[] args) 
	{
		List<Collect> l = new LinkedList<>(); 
		
		Collect c = null; 
		for(String s: readData("Input"))
		{
			if(((s.split(" "))[0]).equals("Movimento"))
			{
				c = new Collect(Integer.parseInt((s.split(" "))[1])); 
				l.add(c); 
			}
			else
			{
				c.add(s); 
			}
		}
		
		List<Collect> errori = new LinkedList<>(); 
		for(Collect coll: l)
		{
			float valorePrec = Float.MIN_VALUE; 
			for(String s: coll.getLista())
			{
				if(((s.split(" "))[0]).equals("Cella"))
				{
					String str = s.replaceAll("[^.?0-9]+", " "); 
					String[] sp = str.split(" "); 
					float valore = Float.parseFloat(sp[2]); 
					if(valore > valorePrec)
					{
						valorePrec = valore;
					}
					else
					{
						errori.add(coll); 
						break; 
					}
				}
			}
		}
		
		if(errori.size()==0)
		{
			System.out.println("Test superato"); 
		}
		else
		{
			System.out.println("Test non superato"); 
			System.out.println("Movimenti errati:");
			for(Collect coll: errori)
			{
				System.out.println(coll); 
				System.out.println("\n"); 
			}
		}
		
	}
	
	public static List<String> readData(String file)
	{
		List<String> lines = null;
		try(BufferedReader in = new BufferedReader(new FileReader(file)))
		{
			lines = in.lines().collect(Collectors.toList());
			return lines;
		}
		catch(IOException e) 
		{ 
			System.err.println(e.getMessage()); 
			return null; 
		}
	}
}
