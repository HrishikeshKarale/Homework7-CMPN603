/**
* main.cpp
*
* @version   $Id: main.cpp,v_1.0 2014/12/07 13:20:00
*
* @author    hhk9433 (Hrishikesh Karale)
*
* Revisions:
*      Initial revision
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <cstddef>

using namespace std;

/**
 * This is the main function which accepts two parameters: int argc and pointer
 * [] argv where argc stores no of command line parameters and *argv stores
 * those individual command line parameter values.
 * This function reads the file sent as command line parameter and then gives
 * us the unique words and their count as output.
 */
int main (int argc,char *argv[]) 
{
  /*
   * This block of code checks if no of parameters given on command line and 
   * if not found to be 2 then std error msg is shown and program is exited 
   * with exit code as 2.  
   */
  if(argc!=2)
  {
    cerr<<"usage:"<<endl;
    cerr<<argv[0];
    for(int i=1; i<=argc; i++)
    {
      cerr<<" "<<argv[i];
    }
    exit(2);
  }

  //stores start of word
  int start;
  //stores length of line
  int linelength; 
  //stores length or word
  int wordlength; 
  //stores line and respective words
  string line, word;
  //used to store unique word as key and their count as value 
  map<string, int> final_list;
  //iterator is initialized
  map<string, int>::iterator it;
  //ifstream instance variable is initialized to command line parameter
  ifstream myfile (argv[1]);
  
  /*
   * This block of code checks if file could be open, if the file opens 
   * then it is read and words are stored in map and their count is calculated. 
   */
  if (myfile.is_open())
  {
    //This block of code loads a line from the file in line variable.
    while(getline(myfile, line)) 
    {
      //length of line is calculated
      linelength= line.length();
      //initialized to zero for every new line
      start=0;

      /*
       * This block of code parses through the line character by character and
       * then stores word and their count in the stl container of map.
       */
      for(int i=0; i<linelength+1; i++ )
      {
        //This block of code splits words from the line using whitespace as splitter.
        if(i==linelength-1 || isspace(line[i]) || line[i]=='\0' )
        {
          if(i==linelength)
          {
            word=line.substr(start, i-start+1);
          }
          else
          {
            word=line.substr(start, i-start);
          }  
          //wordlength is calculated and stored
          wordlength= word.length();
          
          /*
           * this block of code looks for characters and neglects them
           */
          if(word[wordlength-1]== ',' || word[wordlength-1]== '.' 
              || word[wordlength-1]== '?' || word[wordlength-1]== '!'
              || word[wordlength-1]== '|' || word[wordlength-1]== '-'
              || word[wordlength-1]== ':' || word[wordlength-1]== ';')
          {
            
            if(i==linelength)
            {
              word=word.substr(0, wordlength-1); 
            }
            else
            {
              word= word.substr(0, wordlength-1);
            }
          }
      	  if(word[0]=='\'' && word[wordlength-1]=='\'')
      	  {
      	     word= word.substr(1,wordlength-1);
      	  }
          //stores iterator index of the particular word in our map
          it= final_list.find(word);
          
          //checks if word is found or not
	        if(it==final_list.end())
          {
      	    int b=1;
            final_list[word]=b;
          }
          else
          {
            int b=(int)(it->second);
            final_list[word]=(int)(b+1);
          }
          start= i+1;
        }
      }
    }

    //prints the content of our map.
    for (it=++(final_list.begin()); it!=final_list.end(); it++)
    {
      std::cout << (string)it->first << ": " << (int)it->second << "\n";
    }

    myfile.close();
    exit(0);
  }
  //error is shown if file cannot be read.
  else
  {
    cerr<<argv[0]<<": "<<argv[1]<<": No such file.\n"; 
    exit(2);
  }

  return 0;
}
