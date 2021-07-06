#include <iostream>

#include "GenApi/GenApi.h" //!< GenApi lib definitions.
#include "gevapi.h"		   //!< GEV lib definitions.

#define MAX_CAMERAS 256

int main()
{
    GEV_DEVICE_INTERFACE pCamera[MAX_CAMERAS] = {0};
	GEV_STATUS status;
    // GEV_CAMERA_HANDLE handle = NULL;
    GEV_CAMERA_HANDLE handle[MAX_CAMERAS];
    int numCamera = 0;
    UINT32 rectimestampModulo = 0;
    int type;

    status = GevGetCameraList(pCamera, MAX_CAMERAS, &numCamera);

	printf("%d camera(s) on the network\n", numCamera);
	for (int i = 0; i < numCamera; i++)
	{
        printf("%d : %d (%X)\n",i,pCamera[i].macLow,pCamera[i].macLow);
	}

    for (int i = 0; i < numCamera; i++)
	{
        status = GevOpenCamera(&pCamera[i], GevExclusiveMode, &handle[i]);
        std::cout << status << std::endl;
	}

    for (int i = 0; i < numCamera; i++)
	{
        GevGetFeatureValue(handle[i], "timestampModulo", &type, sizeof(UINT32), &rectimestampModulo);
	    std::cout << "get timestampModulo = " << rectimestampModulo << std::endl;
	}

    for (int i = 0; i < numCamera; i++)
	{
        GevCloseCamera(&handle[i]);
	}

    
    std::cout << "End of program !! " << std::endl;
    return 0;
}