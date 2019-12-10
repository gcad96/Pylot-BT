package Pylot_BT; 

import java.util.LinkedList;
import java.util.List;

public class Collect
{
	private List<String> l;
	private int id; 

	public Collect(int id) 
	{
		this.l = new LinkedList<>(); 
		this.id = id;
	} 
	
	public void add(String s)
	{
		this.l.add(s); 
	}
	
	public List<String> getLista()
	{
		return this.l; 
	}
	
	@Override
	public String toString()
	{
		String s = "Movimento "; 
		s+=this.id+"\n"; 
		for(String t: this.l)
		{
			s+=t+"\n"; 
		}
		return s; 
	}
}
