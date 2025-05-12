#include "GameController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

  // If your program is having trouble finding the Assets directory,
  // replace the string literal with a full path name to the directory,
  // e.g., "Z:/CS32/IceMan/Assets" or "/Users/fred/cs32/IceMan/Assets"


const string assetDirectory = "Assets";
const int msPerTick = 10;  // 10ms per tick; increase this if game moves too fast

#ifdef _MSC_VER
#include <windows.h>
bool is_directory(string path)
{
    DWORD result = GetFileAttributesA(path.c_str());
    return result != INVALID_FILE_ATTRIBUTES  &&  (result & FILE_ATTRIBUTE_DIRECTORY);
}
#else
#include <sys/stat.h>
bool is_directory(string path)
{
    struct stat statbuf;
    return stat(path.c_str(), &statbuf) == 0  &&  S_ISDIR(statbuf.st_mode);
}
#endif
class GameWorld;

GameWorld* createStudentWorld(string assetDir = "");

int main(int argc, char* argv[])
{
    /*
    If you're building and running under Xcode and instead of the program
     starting with the welcome window, you get the message failed to open
     display '', do the following:

    1) In a Terminal window, type echo $DISPLAY and see if it writes one
       line like /private/tmp/com.apple.launchd.jyOB2CIw2y/org.xquartz:0
       although the text jyOB2CIw2y might be some other 10-character sequence.
    
    2) Insert the following line as the first statement of the main routine:
     
         setenv("DISPLAY", "/private/tmp/com.apple.launchd.jyOB2CIw2y/org.xquartz:0", 1);
     
     except that you should replace the jyOB2CIw2y with the 10-character you saw for step 1.
    */
    string assetPath = assetDirectory;
    if (!assetPath.empty())
    {
        if (!is_directory(assetPath))
        {
            cout << "Cannot find directory " << assetPath << endl;
            return 1;
        }
        assetPath += '/';
    }
	{
		string path = assetDirectory;
		if (!path.empty())
			path += '/';
		const string someAsset = "dig1.tga";
		ifstream ifs(path + someAsset);
		if (!ifs)
		{
			cout << "Cannot find " << someAsset << " in ";
			cout << (assetDirectory.empty() ? "current directory"
											: assetDirectory) << endl;
			return 1;
		}
	}

	srand(static_cast<unsigned int>(time(nullptr)));

	GameWorld* gw = createStudentWorld(assetDirectory);
	Game().run(argc, argv, gw, "IceMan", msPerTick);
}
