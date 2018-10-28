#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <exception>
#include <map>
#include <iterator>
#include <algorithm>

typedef std::vector<std::string> Strings;

void add_in_the_map(std::map<char, Strings>& map, const std::string& s);
void show_screen(std::map<char, Strings>::iterator ptr);
void sort_alf(std::map<char, Strings>::iterator ptr);
bool alpha_sort(std::string first, std::string second);

int main(int argc, char ** argv)
{
	try
	{
		if(argc < 2)
		{
			throw std::runtime_error("exception of arguments main()");
		}
	

	std::map<char, Strings> Text;

	FILE * fileInput = fopen((const char*)argv[1],"r+");

	
		if(fileInput == NULL)
		{
			throw std::runtime_error("exception of file");
		}

	char error[256];
	std::string str;

	while(true)
	{
		if(fgets(error,256,fileInput)==NULL)
			break;

		str=std::string((char*)error);

		add_in_the_map(Text,str);
	}

	fclose(fileInput);

	for(std::map<char,Strings>::iterator i = Text.begin(); i != Text.end(); ++i)
	{
		sort_alf(i);
	}

	char userAnswer;

	std::cout<<"Please enter a synmbol of ABC(small symbol) - ";
	std::cin>>userAnswer;

	if((userAnswer > 'A' ) && (userAnswer < 'Z'))
	{
		userAnswer = char(userAnswer+32);
	}

	std::map<char,Strings>::iterator it = Text.find(userAnswer);

	
		if(it == Text.end())
		{
			throw std::runtime_error("exception of map this is symbol is not declarated");
		}
	
		show_screen(it);

	}
	catch(std::runtime_error e)
	{
		std::cout<<"fatal error :: "<<e.what()<<std::endl;
	}
	return(0);
}

void add_in_the_map(std::map<char, Strings>& map, const std::string& s)
{
	try
	{
		if(((char)s[0] < 'A' && (char)s[0] > 'Z') || ( char(s[0]) < 'a' && char(s[0]) > 'z' ))
		{
			throw std::runtime_error("exception of first simbol is not a character");
		}
	} 
	catch(std::runtime_error e)
	{
		std::cout<<"fatal error :: function add_in_the_map :: "<<e.what()<<std::endl;
		return;
	}

	int c = 0;
	char sim = (char)s[0];

	sim = ((sim > 'A' ) && (sim < 'Z') ? char(sim+32) : char(sim));

	std::map<char, Strings>::iterator i = map.find(sim);

	if(i != map.end())
	{
		i->second.push_back(s);
		c++;
	}
	else
	{
		c = 0;
	}

	if(c == 0)
	{
		Strings buffer;
		buffer.push_back(s);
		map.insert(std::pair<char, Strings>(sim,buffer));
		buffer.pop_back();
	}

	return;
}

void show_screen(std::map<char, Strings>::iterator ptr)
{
	std::cout<<ptr->first<<" : ";
	for(Strings::iterator i = ptr->second.begin(); i != ptr->second.end(); ++i)
	{
		std::cout<<(*i)<<"    ";
	}
	std::cout<<std::endl;
}

bool alpha_sort(std::string first, std::string second)
{
	return(first<second);
}

void sort_alf(std::map<char, Strings>::iterator ptr)
{
	std::sort(ptr->second.begin(), ptr->second.end(), alpha_sort);
	return;
}