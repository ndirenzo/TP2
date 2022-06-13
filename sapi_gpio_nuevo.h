

#ifndef _SAPI_GPIO_NUEVO_H_
#define _SAPI_GPIO_NUEVO_H_

/*==================[inclusions]=============================================*/

#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"
#include "sapi_gpio.h"

/*==================[c++]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif


/*==================[external functions declaration]=========================*/

bool_t gpioInitNew( gpioMap_t pin, gpioInit_t config );
bool_t gpioReadNew( gpioMap_t pin );
bool_t gpioWriteNew( gpioMap_t pin, bool_t value );
bool_t gpioToggleNew( gpioMap_t pin );

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SAPI_GPIO_NUEVO_H_ */
