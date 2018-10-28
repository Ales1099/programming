#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define NO -1

int commit(const std::vector<std::string>& v, const std::string& val);
void show(const std::vector<std::string>& v);
void insertToFile(const std::vector<std::string>& v, const char * filename);

int main(int argc, char ** argv)
{
	if(argc <= 2)
	{
		std::cout<<"fatal error :: file input and output is not OK!!! Please, try again:)"<<std::endl;
		return(-1);
	}

	std::vector<std::string> toFile;
	std::vector<std::string> repeated;

	FILE * fileInput = fopen(argv[1],"r+");

	if(fileInput == NULL)
	{
		std::cout<<"fatal error :: file input is not open!!! Please, try again:)"<<std::endl;
		return(-1);
	}
	
	std::string test;
	char input[1000];
	int error = 0;
	int cap = 0;

	while(true)
	{
		if(fgets(input,1000,fileInput) != NULL)
		{
			cap++;

			test = std::string((const char*)input);
			
			error = commit(repeated,test);

			if(error != NO)
				continue;

			error = commit(toFile,test);

			if(error != NO)
			{
				toFile.erase(toFile.begin() + error, toFile.begin() + (error+1));
				repeated.push_back(test);
			}
			else
			{
				toFile.push_back(test);
			}
		} 
		else
		{
			break;
		}
	}

	fclose(fileInput);

	if(cap == 0)
	{
		std::cout<<"fatal error :: file "<<argv[1]<<" is empty!!!"<<std::endl;
		return(-1);
	}

	insertToFile(toFile,(const char*)argv[2]);

	std::cout<<"END!!! File "<<argv[2]<<" create!!!"<<std::endl;

	return(0);
}

int commit(const std::vector<std::string>& v, const std::string& val){

	const int sz = v.size();

	for(int i=0; i<sz; ++i)
	{
		if(v[i] == val)
		{
			return(i);
		}
	}
	return(NO);
}

void show(const std::vector<std::string>& v){

	const int sz = v.size();

	for(int i=0; i<sz; ++i)
		std::cout<<v[i];

	return;
}

void insertToFile(const std::vector<std::string>& v, const char * filename){

	FILE * fileOutput = fopen(filename,"w+");

	const int sz = v.size();
	
	for(int i=0; i<sz; ++i)
	{
		fputs(v[i].c_str(),fileOutput);
	}
	fclose(fileOutput);
	return;
}