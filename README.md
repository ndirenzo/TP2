# TP2 - Sistemas Embebidos - Facultad de Ingeniería Universidad de Buenos Aires 10 de Mayo 2022

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
           >**1. En app.c, dentro de main() se definen: bool_t buttonValue = OFF;  En esta variable se copia el valor negado del pin conectado al pulsador 1 'TEC1', leído mediante gpioRead(), en el led correspondiente 'LEDB'. bool_t ledValue    = OFF;  En esta variable se almacena el estado del led 'LEDB', que se usa luego para imprimirlo con printf(). tick_t timeCount   = 0; En esta variable para contar el tiempo transcurrido en milisegundos.  
            2. Dentro del primer while() de la linea 27, el cual es un bucle infinito, la variable timeCount empieza a incrementar en una unidad y cuando esta llegue a 100, habran transcurrido 100 ciclos del bucle en donde cada uno tiene un delay de 100ms. Por lo tanto cuando timeCount=100, implica que se tiene un retardo de 100 ciclos * 100ms = 10segundos. Mientras el valor de esta variable sea menor a 100, se ejecuta la funcion gpioToggle() en donde el 'LEDB' modifica su estado por cada ciclo que transcurra. Por lo tanto se puede apreciar un "parpadeo" del led cada 100ms. Cuando timeCount es 100, se ingresa a otro bucle infinito con un while() en la linea 40, y ahora en cada ciclo se lee e invierte el valor del pin que corresponde a 'TEC1', y con ésta utiliza la funcion gpioWrite() para modificar el valor del 'LEDB', generando otro parpadeo pero ahora cada 250ms.**
                  
2. El objetivo a continuación es crear las funciones gpioInit, gpioWrite y gpioRead, las cuales implementan completamente el uso de los
GPIOs de la placa en una manera simple y general: 

   b. Estructras que representan los periféricos:
      1. SCU - System Control Unit pág. 405 User Manual:  "The system control unit contains the registers to configure the pin function of multiplexed digital pins, the EMC clock delays, and the GPIO pin interrupts." Las funciones implementadas por el fabricante para manejar el SCU se encuentran en el archivo "scu_18xx_43xx.h" y son:
            - Chip_SCU_PinMux que modifica los registros del SCU para asignar a un pin del microcontrolador - identidificado por uint8_t port y uint8_t pin - un modo y función a través de las máscaras uint16_t mode y uint8_t func.
            
                ```c
                STATIC INLINE void Chip_SCU_PinMux(uint8_t port, uint8_t pin, uint16_t mode, uint8_t func);
                ```
            
      2. GPIO - General-Purpose Input/Output. Los pines configurados por el SCU para funcionar como GPIO (FUNC0) son controlados por los registros de GPIO. 
      
            - Chip_GPIO_SetDir(LPC_GPIO_t *pGPIO, uint8_t portNum) que recibe la dirección en memoria del bloque de registros *pGPIO, el puerto GPIO y el pin GPIO y lo configura como entrada o salida según uint8_t sea una macro de entrada o salida (0 o 1) modificando los registros GPIO DIR.
                    
                ```c
                STATIC INLINE void Chip_GPIO_SetDir(LPC_GPIO_T *pGPIO, uint8_t portNum, uint32 bitvalue, uint8_t out)
                ```
      
            - ChipGPIO_SetPinState( LPC_GPIO_PORT *pGPIO, gpioPort, gpioPin, 0) que modifica el registro del valor de un puerto/pin configurado como salida. Recibe la dirección del bloque de registros de *pGPIO el puerto/pin y el estado alto (1) o bajo (0).
            
                 ```c
                STATIC INLINE void ChipGPIO_SetPinState( LPC_GPIO_PORT *pGPIO, gpioPort, gpioPin, 0)
                ```
                
     c. Configuraciones electricas de un pin GPIO: Los bits EPUN y EPD en los registros SFS permite seleccionar resistores de pull-up o pull-down integrados. Activando ambos pines se habilita el modo repetidor y desactivando ambos se deja el pin inerte.
      
   | Bit | Descripción |
   | ------ | ------ |
   | 2:0 MODE | Función |
   | 3 EPD | 0, Desactiva pull-down. 1, Activa pull-down |
   | 4 EPUN | 0, Activa pull-up. 1, Desactiva pull-up |
   | 5:32 | Otros |

      para trabajar con las confgiuraciones se crea un tipo enumerativo ** gpioInit_t ** con las posibles configuraciones que pasada como parámetro a una función de iniciación permitan recorrer distintos 'case' de un 'switch' para definir los parámetros de configuración.      
      
    ```c
    typedef enum gpioInit_t {
      GPIO_INPUT,
      GPIO_OUTPUT,
      ...
    }
    ```
    d. Para la asociación entre SCU y GPIO se usa una estructura de estructuras asociadas a nombre y puerto del pin y del GPIO
    
    ```c
    typedef struct gpioInitLPC4337_t {
      pinInitLpc4337_t pinName,
      int-8_t func,
      gpioInitLpc4337_t gpio
    }
    ```

    e. El vector global de estas estructuras con las configuraciones de GPIO que la función gpioInit utilizará para buscar como configurar cada pin.
    
               
    ```c
    const pinInitGpioLpc4337_t gpioPinsInitPropia[] = {
      ...
      { {2,10}, FUNC0, {0,14} },   // 40   LED1    LED1
      ...
    ```
             
     
