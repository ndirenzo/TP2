# TP1 - Sistemas Embebidos - Facultad de Ingeniería Universidad de Buenos Aires 10 de Mayo 2022

## Integrantes Grupo 1 : N.Direnzo, G.Pintos, J.González, M.Pinto


1. Uso del IDE

   b. Migrar proyecto examples/c/app (parpadeo del LEDs c/sAPI) a: examples/c/projects/TP2
      - i. Documentar los pasos a seguir para concretar una migración exitosa.  
           >**1. Crear una nueva carpeta dentro de examples/c llamada projects.  
             2. Hacer click derecho en la carpeta app dentro de examples/c, opción "mover".  
             3. Seleccionar dentro del menu el path examples/c/projects.  
             4. Modificar el nombre de la carpeta examples/c/projects/app a TP2.  
             5. Eliminar la carpeta examples/c/projects/TP2/out.  
             6. Migración exitosa.**  
             
      - ii. Identificar funciones de librería sAPI útiles para el parpadeo de un led y printf (UART_DEBUG).
           >**1. delay() incluida desde sapi_delay.c.
             2. gpioRead() incluida desde "sapi_gpio.c". Devuelve TRUE o FALSE si en el pin de placa de desarrollo se lee un estado alto VCC o bajo GND, respectivamente.  
             3. gpioWrite() incluida desde "sapi_gpio.c". Escribe un valor 1 o 0 en un pin de la placa, p.ej. gpioWrite(CIAA_BOARD_LED, ON).
             4. gpioToggle() incluidad desde "sapi_gpio.c". Escribe en un pin de la placa de desarrollo - definido como salida - el valor inverso al presente actualmente en el pin, esto lo hace llamando a la función gpioWrite(pin, !gpioRead(pin)).  
             5. boardconfig() incluida desde "sapi_board.h". Configura los pines como entrada o salida a través de la función gpioInit(), p.ej. gpioInit(TEC1, GPIO_INPUT) establece el pin de la placa de desarrollo llamado "TEC1" como entrada.**
             
      - iii. Idem c pero con datos (definiciones, constantes, variables, estructuras, etc.) (tanto en ResetISR() como en main())
           
          
2. El objetivo a continuación es crear las funciones gpioInit, gpioWrite y gpioRead, las cuales implementan completamente el uso de los
GPIOs de la placa en una manera simple y general: 

   b. Estructras que representan los periféricos:
      1. SCU - System Control Unit pág. 405 User Manual:  "The system control unit contains the registers to configure the pin function of multiplexed digital pins, the EMC clock delays, and the GPIO pin interrupts." Las funciones implementadas por el fabricante para manejar el SCU se encuentran en el archivo "scu_18xx_43xx.h" y son:
            - Chip_SCU_PinMux que modifica los registros del SCU para asignar a un pin del microcontrolador - identidificado por uint8_t port y uint8_t pin - un modo y función a través de las máscaras uint16_t mode y uint8_t func.
            
                ```c
                STATIC INLINE void Chip_SCU_PinMux(uint8_t port, uint8_t pin, uint16_t mode, uint8_t func);
                ```
            - 
      2. GPIO - General-Purpose Input/Output. Los pines configurados por el SCU para funcionar como GPIO (FUNC0) son controlados por los registros de GPIO. 
      
            - Chip_GPIO_SetDir(LPC_GPIO_t *pGPIO, uint8_t portNum) que recibe la dirección en memoria del bloque de registros *pGPIO, el puerto GPIO y el pin GPIO y lo configura como entrada o salida según uint8_t sea una macro de entrada o salida (0 o 1). 
                    
                ```c
                STATIC INLINE void Chip_GPIO_SetDir(LPC_GPIO_T *pGPIO, uint8_t portNum, uint32 bitvalue, uint8_t out)
                ```
      
            - ChipGPIO_SetPinState( LPC_GPIO_PORT *pGPIO, gpioPort, gpioPin, 0) que modifica el registro del valor de un puerto/pin configurado como salida. Recibe la dirección del bloque de registros de *pGPIO el puerto/pin y el estado alto (1) o bajo (0).
            
                 ```c
                STATIC INLINE void ChipGPIO_SetPinState( LPC_GPIO_PORT *pGPIO, gpioPort, gpioPin, 0)
                ```
      
```c
bool_t gpioInit(gpioMap_t pin, gpioInit_t config)
--> gpioObtainPinInit(gpioMap_t pin, int8_t *pinNamePort, int8_t *pinNamePin, int8_t *func, int8_t *gpioPort, int8_t *gpioPin)
--> switch(config):
    case GPIO_OUTPUT:
        Chip_SCU_PinMux(pinNamePort, pinNamePin, func);
        Chip_GPIO_SetDir(...);
        Chip_GPIO_SetPinState(...);
```
