#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include "MLX90640_I2C_Driver.h"
#include "MLX90640_API.h"
#include "mlx90640_driver_register.h"
// #include "MLX90640_I2C_Driver_mcp2221.h"
// #include "MLX90640_I2C_Driver_devtree.h"

#define MLX_I2C_ADDR 0x33

int main(void){

    // mlx90640_register_driver(MLX90640_get_register_mcp2221());
    // mlx90640_register_driver(MLX90640_get_register_devtree());

    MLX90640_I2CInit("mcp://mcp:2221/0");
    //MLX90640_I2CInit("/dev/i2c-1");

    // int state = 0;
    printf("Starting...\n");
    static uint16_t eeMLX90640[832];
    float emissivity = 1;
    uint16_t frame[834];
    // static float image[768];
    float eTa;
    // static uint16_t data[768*sizeof(float)];

    int r = MLX90640_SetRefreshRate(MLX_I2C_ADDR, 2);
    printf("Configured...%d\n", r);

    printf("refresh = %d\n", MLX90640_GetRefreshRate (MLX_I2C_ADDR));

    paramsMLX90640 mlx90640;
    MLX90640_DumpEE(MLX_I2C_ADDR, eeMLX90640);
    MLX90640_ExtractParameters(eeMLX90640, &mlx90640);

    int refresh = MLX90640_GetRefreshRate(MLX_I2C_ADDR);
    printf("EE Dumped...\n");
    printf("Refresh Rate = %d\n", refresh);

    static float mlx90640To[768];
    int counter =0;
    while(1){
        MLX90640_GetFrameData(MLX_I2C_ADDR, frame);
        eTa = MLX90640_GetTa(frame, &mlx90640)-5.0;

        printf("TA = %0.2f    -- %d\n", eTa, counter);
        counter++;
        MLX90640_CalculateTo(frame, &mlx90640, emissivity, eTa, mlx90640To);

        for(int i=0; i<12; i++){
            for(int j=0; j<16; j++){
                if(j!=19)
                    printf("%0.2f,", mlx90640To[i*16+j]);
                else
                    printf("%0.2f\n", mlx90640To[i*16+j]);
            }   
        }
        printf("\n");


    }


    /*
    uint16_t data[4];

    MLX90640_I2CInit();
    MLX90640_I2CRead(0x33, 0x800D, 4, data);

    for (int i=0; i<4; i++){
        printf("%d\n", data[i]);
       // printf("\n");
    }

    MLX90640_I2CWrite(0x33, 0x800D, 0);
    MLX90640_I2CRead(0x33, 0x800D, 4, data);

    for (int i=0; i<4; i++){
        printf("%d\n", data[i]);
       // printf("\n");
    }

    MLX90640_I2CWrite(0x33, 0x800D, 6401);
    MLX90640_I2CRead(0x33, 0x800D, 4, data);

    for (int i=0; i<4; i++){
        printf("%d\n", data[i]);
       // printf("\n");
    }

    MLX90640_I2CClose();
    */
}
