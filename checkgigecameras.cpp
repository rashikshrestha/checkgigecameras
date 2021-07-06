#include <iostream>

#include "GenApi/GenApi.h" //!< GenApi lib definitions.
#include "gevapi.h"		   //!< GEV lib definitions.

#define MAX_CAMERAS 256

int main()
{
    GEV_DEVICE_INTERFACE pCamera[MAX_CAMERAS] = {0};
	GEV_STATUS status;
    GEV_CAMERA_HANDLE handle = NULL;
    int numCamera = 0;
    UINT32 rectimestampModulo = 0;
    int type;

    status = GevGetCameraList(pCamera, MAX_CAMERAS, &numCamera);

	printf("%d camera(s) on the network\n", numCamera);
	for (int i = 0; i < numCamera; i++)
	{
		std::cout << i << " : " << pCamera[i].macLow << std::endl;
	}

    status = GevOpenCamera(&pCamera[0], GevExclusiveMode, &handle);

    GevGetFeatureValue(handle, "timestampModulo", &type, sizeof(UINT32), &rectimestampModulo);
	std::cout << "get timestampModulo = " << rectimestampModulo << std::endl;



    GevCloseCamera(&handle);
    std::cout << "End of program !! " << std::endl;
    return 0;
}