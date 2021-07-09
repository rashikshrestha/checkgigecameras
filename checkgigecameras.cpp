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

    // ---------------------------------------------------------------------------
    // GEVLIB_CONFIG_OPTIONS config;

    // status = GevGetLibraryConfigOptions(&config);
    // if(status)
    //     std::cout << "Error getting config with status " << status << std::endl;

    // std::cout << "LOG level = " << config.logLevel << std::endl;

    // config.logLevel = GEV_LOG_LEVEL_TRACE;

    // status = GevSetLibraryConfigOptions(&config);
    // if(status)
    //     std::cout << "Error setting config with status " << status << std::endl;

    // ---------------------------------------------------------------------------


    int numCamera = 0;

    char recieved_string[100] = {0};

    char* feature[8] = {"timestampModulo",
                        "TriggerSource",
                        "TriggerMode",
                        "ptpMode",
                        "ptpStatus",
                        "ptpServoStatus",
                        "ptpMasterClockId",
                        "ChunkModeActive"};

    int feature_size = sizeof(feature)/sizeof(feature[0]);

    
    int type;

    status = GevGetCameraList(pCamera, MAX_CAMERAS, &numCamera);

	printf("%d camera(s) on the network\n", numCamera);

    for (int i = 0; i < numCamera; i++)
	{
        status = GevOpenCamera(&pCamera[i], GevExclusiveMode, &handle[i]);
        
        if(status)
            std::cout << "Error opening camera" << i << std::endl;
	}

    

    


    printf("\n\nCamera details: \n");

    for (int i = 0; i < numCamera; i++)
	{
        printf("\n");
        printf("Index: %d\tGUID: %d (%x)\n\n",i,pCamera[i].macLow,pCamera[i].macLow);
        

        // GevSetFeatureValueAsString( handle[i], "timestampModulo", "1000000000");
        // status = GevSetFeatureValueAsString( handle[i], "ChunkModeActive", "1");
        // if(status)
        //     std::cout << "Error Setting Trigger Source on " << i << std::endl;

        // status = GevSetFeatureValueAsString( handle[i], "turboTransferEnable", "True");
        // if(status)
        //     std::cout << "Error setting feature turboTransferEnable on Cam" << i << " with status " << status << std::endl;

        status = GevSetFeatureValueAsString( handle[i], "ptpMode", "Slave");
        if(status)
            std::cout << "Error setting feature ptpMode on Cam" << i << " with status " << status << std::endl;

        status = GevSetFeatureValueAsString( handle[i], "TriggerMode", "On");
        if(status)
            std::cout << "Error setting feature TriggerMode on Cam" << i << " with status " << status << std::endl;
        

        // Print the listed features of camera i
        for(int j=0;j<feature_size;j++)
        {
            status = GevGetFeatureValueAsString( handle[i], feature[j], &type, sizeof(recieved_string), recieved_string);
            if(status)
                std::cout << "Error reading feature \"" << feature[j] << "\" with status " << status << std::endl;
            else
                std::cout << feature[j] << " = " << recieved_string << std::endl;
            
        }

        printf("----------------------------------------------------------------\n");
	}

  
    // Close all the Cameras
    for (int i = 0; i < numCamera; i++)
	{
        GevCloseCamera(&handle[i]);
	}

    const char* logs;


    
    std::cout << "End of program !! " << std::endl;
    return 0;
}

// UINT32 timestampModulo = 1000000000;
// UINT32 ptpMode = 0;
// UINT32 ptpStatus = 0;

// timestampModulo = 1000000000;
// GevSetFeatureValue(handle[i], "timestampModulo", sizeof(UINT32), &timestampModulo);
// GevGetFeatureValue(handle[i], "timestampModulo", &type, sizeof(UINT32), &timestampModulo);
// std::cout << "timestampModulo = " << timestampModulo << std::endl;

// ptpMode = 2;
// GevSetFeatureValue(handle[i], "ptpMode", sizeof(UINT32), &ptpMode);
// GevGetFeatureValue(handle[i], "ptpMode", &type, sizeof(UINT32), &ptpMode);
// std::cout << "ptpMode = " << ptpMode << std::endl;