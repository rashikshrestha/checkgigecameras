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
    UINT32 timestampModulo = 1000000000;
    UINT32 ptpMode = 0;
    int type;

    status = GevGetCameraList(pCamera, MAX_CAMERAS, &numCamera);

	printf("%d camera(s) on the network\n", numCamera);
	for (int i = 0; i < numCamera; i++)
	{
        
	}

    for (int i = 0; i < numCamera; i++)
	{
        status = GevOpenCamera(&pCamera[i], GevExclusiveMode, &handle[i]);
        std::cout << status << std::endl;
	}

    printf("\n\nCamera details: \n");

    for (int i = 0; i < numCamera; i++)
	{
        printf("\n");
        printf("Index: %d\tGUID: %d (%X)\n\n",i,pCamera[i].macLow,pCamera[i].macLow);

        GevSetFeatureValue(handle[i], "timestampModulo", sizeof(UINT32), &timestampModulo);
        // GevGetFeatureValue(handle[i], "timestampModulo", &type, sizeof(UINT32), &timestampModulo);
	    std::cout << "timestampModulo = " << timestampModulo << std::endl;

        GevGetFeatureValue(handle[i], "ptpMode", &type, sizeof(UINT32), &ptpMode);
	    std::cout << "ptpMode = " << ptpMode << std::endl;

        printf("----------------------------------------------------------------\n");
	}

    // Close all the Cameras
    for (int i = 0; i < numCamera; i++)
	{
        GevCloseCamera(&handle[i]);
	}

    
    std::cout << "End of program !! " << std::endl;
    return 0;
}