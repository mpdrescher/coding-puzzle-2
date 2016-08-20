use std::vec::Vec;
use std::fmt::Debug;
use std::fmt::Formatter;
use std::fmt::Result;

struct Article
{
	name: String,
	group: usize,
	price: f64
}

impl Debug for Article
{
	fn fmt(&self, f: &mut Formatter) -> Result
	{
		write!(f, "Name: {}, Group: {}, Price: {}\n", self.name, self.group, self.price)
	}
}

fn main() 
{
	let mut art_vec = Vec::new();
	art_vec.push(Article{name: String::from("AA"), group: 1, price: 100.0});
	art_vec.push(Article{name: String::from("BB"), group: 1, price: 50.0});
	art_vec.push(Article{name: String::from("CC"), group: 2, price: 75.0});
	art_vec.push(Article{name: String::from("AA"), group: 1, price: 20.0});
	art_vec.push(Article{name: String::from("AA"), group: 0, price: 100.0});
	art_vec.push(Article{name: String::from("BB"), group: 2, price: 75.0});
	art_vec.push(Article{name: String::from("CC"), group: 2, price: 80.0});
	art_vec.push(Article{name: String::from("AA"), group: 0, price: 20.0});

	println!("{:?}", shorten(art_vec));
}

fn shorten(list: Vec<Article>) -> Vec<Article>
{
	let mut new_list: Vec<Article> = Vec::new();
	for item in list
	{
		if item.group == 0
		{
			new_list.push(item);
		}
		else 
		{
		    let mut found = false;
		    for ref mut new_item in &mut new_list
		    {
		    	if new_item.group == item.group
		    	{
		    		if !new_item.name.contains(&item.name)
		    		{
		    			new_item.name = format!("{}, {}", item.name, new_item.name);
		    		}
		    		new_item.price = new_item.price + item.price;
		    		found = true;
		    	}
		    }
		    if !found
		    {
		    	new_list.push(item);
		    }
		}
	}
	new_list.sort_by(|a, b| {a.group.cmp(&b.group)});
	new_list
}