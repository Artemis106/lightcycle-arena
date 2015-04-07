
#include <Ogre.h>
#include "Rwindow.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

int main(void)
{
	int i;
	std::cout << "how many player(s) ? : ";
	std::cin >> i;
    Rwindow app(i);
    try {
		app.Winit();
		app.Run();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }
    return 0;
}