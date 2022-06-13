#include "sapi_gpio_nuevo.h"
#include "sapi_gpio.h"

/*==================[external functions definition]==========================*/

bool_t gpioInitNew( gpioMap_t pin, gpioInit_t config )
{
   if( pin == VCC ){
	  return FALSE;
   }
   if( pin == GND ){
	  return FALSE;
   }

   bool_t ret_val     = 1;

   int8_t pinNamePort = 0;
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   gpioObtainPinInit( pin, &pinNamePort, &pinNamePin, &func,
                      &gpioPort, &gpioPin );

   switch(config) {

   case GPIO_ENABLE:
      /* Initializes GPIO */
      Chip_GPIO_Init(LPC_GPIO_PORT);
      break;

   case GPIO_INPUT:
      Chip_SCU_PinMux(
         pinNamePort,
         pinNamePin,
         SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
         func
      );
      Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );
      break;

   case GPIO_INPUT_PULLUP:
      Chip_SCU_PinMux(
         pinNamePort,
         pinNamePin,
         SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
         func
      );
      Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );
      break;

   case GPIO_INPUT_PULLDOWN:
      Chip_SCU_PinMux(
         pinNamePort,
         pinNamePin,
         SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
         func
      );
      Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );
      break;
   case GPIO_INPUT_PULLUP_PULLDOWN:
      Chip_SCU_PinMux(
         pinNamePort,
         pinNamePin,
         SCU_MODE_REPEATER | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
         func
      );
      Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );
      break;

   case GPIO_OUTPUT:
      Chip_SCU_PinMux(
         pinNamePort,
         pinNamePin,
         SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_INBUFF_EN,
         func
      );
      Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_OUTPUT );
      Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, 0);
      break;

   default:
      ret_val = 0;
      break;
   }

   return ret_val;

}


bool_t gpioWriteNew( gpioMap_t pin, bool_t value )
{
   if( pin == VCC ){
	  return FALSE;
   }
   if( pin == GND ){
	  return FALSE;
   }

   bool_t ret_val     = 1;

   int8_t pinNamePort = 0;
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   gpioObtainPinInit( pin, &pinNamePort, &pinNamePin, &func,
                      &gpioPort, &gpioPin );

   Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, value);

   return ret_val;
}


bool_t gpioToggleNew( gpioMap_t pin )
{
   return gpioWriteNew( pin, !gpioReadNew(pin) );
}


bool_t gpioReadNew( gpioMap_t pin )
{
   if( pin == VCC ){
      return TRUE;
   }
   if( pin == GND ){
      return FALSE;
   }

   bool_t ret_val     = OFF;

   int8_t pinNamePort = 0;
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   gpioObtainPinInit( pin, &pinNamePort, &pinNamePin, &func,
                      &gpioPort, &gpioPin );

   ret_val = (bool_t) Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, gpioPort, gpioPin );

   return ret_val;
}
