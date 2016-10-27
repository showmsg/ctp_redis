# CIniFile

[CIniFile Class for C++ - A robust cross platform INI file class][url]
[url]: http://www.codeproject.com/Articles/8342/CIniFile-Class-for-C-A-robust-cross-platform-INI-f "原文链接"

# Introduction
My language of choice is VB.NET, because I like its ease of use and rapid development. But neither VB nor the .NET runtime are overly cross-platform friendly. Also, I just like to keep my language proficiencies up to snuff. When I started to dabble in game programming, I quickly realized that I'd need some way to handle *.ini and *.cfg files. I looked around online for a good INI file handling library, but didn't find much. And when I asked around on the programmers' forums, everyone replied that I should just use the built-in GetVal/SetVal functions of the Windows API. This isn't cross-platform friendly programming however, and that just irks me. Besides, those functions are awfully weak and limited - I hate weak and limited.

To be honest, this wasn't my first foray into the world of INI files. I wrote an INI class for VB as well (INI Class using VB.NET). I wanted that same power and flexibility in my C++ programs. And since no one else seemed to be stepping up to the plate, well... here we go.

# Background #
I thought that coding this class would be a breeze - after all, we are only dealing with text files. But the implementation turned out to be tricky. At first, I tried to read and analyze the file in one fell swoop, but I quickly realized that wasn't going to work. Some INI files are modified by hand, and can be poorly formed. Also, keeping comments and their respective Sections/Keys together was difficult at best. When all was said and done, I realized it would be best to read the file into memory, and keep the various "parts" of the file stored in a struct for easy access and manipulation.

I also had to decide between one of two classic class models - one way to build the class would be to have one **CIniFile** object represent one file, read all the data in, and do all the operations in memory, and then have the developer call **Save()** when ready. This is a common way to do things, and does use less overhead. It would look something like this:
	
	// Create an instance of the CIniFile class
	CIniFile IniFile;
	// Create a new file called test.ini
	IniFile.Create("test.ini");
	// Create a key
	IniFile.SetValue("MyKey","MyValue","MySection",FileName);
	// Save the changes
	IniFile.Save();

I didn't like that approach however, for several reasons. First, it puts the responsibility on the programmer to remember to call **Save(),** or else all the changes would be lost. Second, it could increase the overhead, if several files were opened, and stayed open for the life of the application. Third, in the event of a crash, all changes again, would be lost. And finally, if changes were made to the file from another source before you called **Save()**, those changes would be lost. Not good.

The other approach was to use a "fire and forget" model. In that model, all the functions are static - you simply accomplish your mission and exit. That is the model I chose to use, and you can see the code for it below. While this model can create some extra traffic from repeated open/close events, I believe that very few programs access this kind of information so frequently as to make this a concern.

# Using the code #
I won't paste too much code here, as the class file is heavily commented throughout, and the accompanying demo application contains a demo of every function in the class. But, here is the basic usage of the CIniFile class:

	#include "CIniFile.h"
	#include <string.h>
	..
	// Create a new file called test.ini
	CIniFile::Create("test.ini");
	// Create a Section called MySection, and a key/value of MyKey=MyValue
	CIniFile::SetValue("MyKey","MyValue","MySection",FileName);
	// Get the value of MyKey in section MySection and store it in s
	std::string s = CIniFile::GetValue("MyKey","MySection",FileName);
	// Sort the sections and records
	CIniFile::Sort("test.ini");
	..

# Features #
- Create, Rename, Edit and Delete Sections and Keys with ease
- Comment and Uncomment Sections or Keys
- Add comment lines (such as instructions) to any Section or Key
- Sort entire files
- Can handle multiple comment lines, and comments stay with their targets even through a sort
- Retrieve Section Names
- Retrieve file contents as a string
- Verify that Sections and Keys exist

# Limitations #
There were a few features I really wanted to add to this class that aren't there yet. First, be aware that this class is case sensitive! I wanted to add an option to ignore case, but was having a tough time implementing it smoothly. My initial solution was to read in the file and convert it all to uppercase for comparison, but this then saved out the file as all uppercase. If you can figure out a way to make it work smoothly, please let me know.

Another option I really wanted to add was the ability to convert INI files to/from XML. While I could technically add this to some degree, it would have either taken an enormous amount of coding on my part, or dependence on another class or library. In the interests of keeping this class cross platform friendly and easily distributable, I decided not to include this feature. If you like, you can probably throw this in using TinyXML or a similar XML parser. Then again, if you are using INI files, then why worry about XML anyway?

Finally, while full featured, this class isn't as robust as it could be. There is almost no error catching. No try/catch blocks, no asserts. The only error checking done is to make sure that the file loads and saves. If it does not, the function gracefully fails, but no error is reported. This code is not heavily tested, there may be bugs.

If you find a bug, or would like to submit enhancements to the code, please contact me.

# Update - Sept 23, 2004 #
I made a few changes to the code and this article. First, I made all the functions static. You no longer need to create an object from the CIniFile class first in order to call the functions. Also, I realized that Record.Commented was being declared as a string - however, it should only ever store either a "#" or a ";". So I made it a char, and then added an enum in order to set the comment character, like this:

	CIniFile::CommentRecord(CIniFile::CommentChar::Pound, "MyKey","YourSection",FileName)

Finally, I repacked the zip file - instead of zipping up the entire VS project, I just included the source code files, and a (Windows only) executable of the demo project. This took the file size down to 68k, which should be easier for those with slower connection speeds to stomach.

# License #
This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)

# About the Author #
[**Todd Davis**](http://www.codeproject.com/Members/Todd-Davis)  
Systems Engineer Virtual RadioLogic  
United States  

Todd Davis has been working in web and application development for several years, using Silverlight, ASP.NET, VB.NET, C#, C++ and Javascript, as well as a great deal of work with SQL server and IIS. 
 
He currently works for Virtual Radiologic in Eden Prairie, MN, however he is better known for his varied work in the open source community, especially the DotNetNuke project for which he provided several world-renowned training videos and modules. A huge advocate of open source and open knowledge sharing, everything on his website (www.SeaburyDesign.com) is always offered for free. 
 
Whenever he is not actively coding at his laptop (a rarity to be sure), he can be found woodworking, walking with his wife and kids, or motoring along the back roads of MN on his Harley Davidson Fatboy.