#include "mlx90640_driver_register.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DRIVER_LIST_LEN 10

static struct MLX90640DriverRegister_t *g_driver_list[DRIVER_LIST_LEN];
static int16_t g_active_driver_index = -1;


void
mlx90640_register_driver(struct MLX90640DriverRegister_t *driver)
{
  for (uint8_t i=0; i<DRIVER_LIST_LEN; i++)    
  {
    if (g_driver_list[i] == NULL)
    { // ok found empty slot!
      g_driver_list[i] = driver;
      return;
    }
  }
  printf("mlx90640_register_driver: ERROR, no free slot!\n");
}


struct MLX90640DriverRegister_t *
mlx90640_get_driver(const char *name)
{
  for (uint8_t i=0; i<DRIVER_LIST_LEN; i++)    
  {
    if (g_driver_list[i] != NULL)
    { // ok found empty slot!
      if (!strcmp(g_driver_list[i]->name_, name))
      {
        return g_driver_list[i];
      }
    }
  }
  return NULL;
}


struct MLX90640DriverRegister_t *
mlx90640_get_active_driver(void)
{
  if (g_active_driver_index < 0) return NULL;
  if (g_active_driver_index >= DRIVER_LIST_LEN) return NULL;

  return g_driver_list[g_active_driver_index];
}


int 
mlx90640_activate_driver(const char *name)
{
  for (uint8_t i=0; i<DRIVER_LIST_LEN; i++)    
  {
    if (g_driver_list[i] != NULL)
    { // ok found used slot!
      if (!strncmp(name, g_driver_list[i]->name_, strlen(g_driver_list[i]->name_)))
      { // ok, found driver with a name that starts the same way as <name> starts! (no exact match needed!)
        g_active_driver_index = i;
        return 0;
      }
    }
  }
  return -1;
}


void *
MLX90640_get_i2c_handle(void)
{
  if (g_active_driver_index < 0) return NULL;
  return g_driver_list[g_active_driver_index]->MLX90640_get_i2c_handle_();
}


void
MLX90640_set_i2c_handle(void *handle)
{
  if (g_active_driver_index < 0) return;
  g_driver_list[g_active_driver_index]->MLX90640_set_i2c_handle_(handle);
}


void
MLX90640_I2CInit(const char *port)
{ 
  mlx90640_activate_driver(port);
  if (g_active_driver_index < 0) return;
  g_driver_list[g_active_driver_index]->MLX90640_I2CInit_(port);
}


void
MLX90640_I2CClose(void)
{
  if (g_active_driver_index < 0) return;
  g_driver_list[g_active_driver_index]->MLX90640_I2CClose_();
}


int
MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddr, uint16_t nMemAddressRead, uint16_t *data)
{
  if (g_active_driver_index < 0) return -1;
  return g_driver_list[g_active_driver_index]->MLX90640_I2CRead_(slaveAddr, startAddr, nMemAddressRead, data);
}


void
MLX90640_I2CFreqSet(int freq)
{
  if (g_active_driver_index < 0) return;
  g_driver_list[g_active_driver_index]->MLX90640_I2CFreqSet_(freq);
}


int
MLX90640_I2CGeneralReset(void)
{
  if (g_active_driver_index < 0) return -1;
  return g_driver_list[g_active_driver_index]->MLX90640_I2CGeneralReset_();
}


int
MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data)
{
  if (g_active_driver_index < 0) return -1;
  return g_driver_list[g_active_driver_index]->MLX90640_I2CWrite_(slaveAddr, writeAddress, data);
}
