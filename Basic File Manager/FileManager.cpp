#include "FileManager.h"

FileManager::FileManager() : _currentPath(fs::current_path())
{}

void FileManager::changeDirectory(const string& strDestPath)
{
	// Get the input path from the user
	// Use a try-catch block in case an error arises
	try
	{
		// For special cases such as ".." for the parent directory
		if (strDestPath == "..")
		{
			if (_currentPath.has_parent_path())
			{
				_currentPath = fs::canonical(_currentPath.parent_path());
			}
			return;
			
		}
		int intCounter = 2;
		while (intCounter < vecCommand.size())
		{
			vecCommand[1] = vecCommand[1] + " " + vecCommand[intCounter];
			intCounter++;
		}

		fs::path newPath = _currentPath / vecCommand[1];

		// Check to see if the new path exists
		if (fs::exists(newPath) && fs::is_directory(newPath))
		{
			_currentPath = fs::canonical(newPath);
		}
		else
		{
			cout << "Directory does not exist!!!" << endl;
		}			
		
				
	}
	catch (const fs::filesystem_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}

void FileManager::listContents()
{
	try
	{
		cout << endl;
		for (const auto& entry : fs::directory_iterator(_currentPath))
		{

			if (fs::is_directory(entry))
			{
				cout << "<DIR> " << entry.path().filename() << endl;
			}
			else
			{
				cout << "<FILE> " << entry.path().filename() << endl;
			}
		}
		cout << endl;
	}
	catch (const fs::filesystem_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}

void FileManager::createDirectory(const string& strName)
{
	try
	{
		fs::create_directory(strName);
	}
	catch (const fs::filesystem_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}

void FileManager::copyFile(const string& strSource, const string& strDestination)
{
	try
	{
		fs::path from = strSource;
		fs::path to = strDestination;

		fs::copy(from, to);

	}
	catch (const fs::filesystem_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}

// Remember to use FILE HANDLING for this part
void FileManager::viewFiles()
{
	try
	{
		int intCounter = 2;
		while (intCounter < vecCommand.size())
		{
			vecCommand[1] = vecCommand[1] + " " + vecCommand[intCounter];
			intCounter++;
		}
		// Open the file
		ifstream inFile(vecCommand[1], ios::in);

		// Check if file opened successfully
		if (!inFile.is_open())
		{
			throw ios_base::failure("Failed to open file...");
		}

		// Perform operations
		stringstream ssBuffer;
		/*while (inFile >> strFileContents)
		{
			
		}*/

		ssBuffer << inFile.rdbuf();
		string strFileContent = ssBuffer.str();

		// Close the file
		inFile.close();

		cout << strFileContent << endl;
	}
	catch (const ios_base::failure& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	

}

// This function handles cases where the user enters a path that is more than 1 word, separated by space(s)
void FileManager::inputEdgeCase()
{
	int counter = 3;
	
	if (vecCommand.size() > 2)
	{
		while (counter < vecCommand.size())
		{
			vecCommand[2] = vecCommand[2] + " " + vecCommand[counter];
			counter++;
		}
	}
	
}

void FileManager::moveFiles(const string& strSource, const string& strDestination)
{
	try
	{
		fs::path from = strSource;
		fs::path to = strDestination;

		fs::rename(from, to);

	}
	catch (const fs::filesystem_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

}

void FileManager::runApplication()
{
	bool blnTerminate = false;

	do
	{
		cout << _currentPath << "> ";
		try
		{
			// Clear the previous commands
			vecCommand.clear();
			string tempWord;

			// Store the user commands
			while (cin >> tempWord)
			{
				vecCommand.push_back(tempWord);
				if (std::cin.get() == '\n') break;
			}

			// Evaluate the users input
			if (vecCommand[0] == "cd")
			{
				changeDirectory(vecCommand[1]);
			}
			else if (vecCommand[0] == "cat")
			{
				// Use file handling for this
				viewFiles();
			}
			else if (vecCommand[0] == "mkdir")
			{
				createDirectory(vecCommand[1]);
			}
			else if (vecCommand[0] == "dir")
			{
				listContents();
			}
			else if (vecCommand[0] == "cp")
			{
				if (vecCommand[1] == "" || vecCommand[2] == "")
				{
					throw ("No destination/source has been provided for the file to be copied to...");
				}
				
				inputEdgeCase();
				copyFile(vecCommand[1], vecCommand[2]);
			}
			else if (vecCommand[0] == "mv")
			{
				if (vecCommand[1] == "" || vecCommand[2] == "")
				{
					throw ("No destination/source has been provided for the file to be moved to...");
				}
				
				inputEdgeCase();
				moveFiles(vecCommand[1], vecCommand[2]);
			}
			else if (vecCommand[0] == "exit")
			{
				cout << "\nEXITING...\n";
				blnTerminate = true;
			}
			else // Display the available options
			{
				cout << "\nPlease only select from the options below: \n"
					<< "cd : To change the directory [cd path OR cd .. (for parent directory)] \n"
					<< "dir : To display all the folders/files in the current directory [dir]\n"
					<< "cat : To display the contents of a file [cat fileName.ext]\n"
					<< "mkdir : To create a new directory [mkdir directoryName]\n"
					<< "cp : To copy a file [cp filename.ext destination/filename.ext]\n"
					<< "mv : To move a file [mv filename.ext destination/filename.ext]\n"
					<< "exit : To stop the program [exit]\n\n";
			}
		}
		catch (const char* e)
		{
			cout << "Error: " << e << endl;
		}
		catch (...)
		{
			cout << "Input error occured." << endl;
		}
		

	} while (blnTerminate == false);
}

fs::path FileManager::getPath() const
{
	return _currentPath;
}