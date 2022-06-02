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
             5. boardconfig() incluida desde "sapi_board.h". Configura los pines como entrada o salida a través de la función gpioInit(), p.ej. gpioInit(TEC1, GPIO_INPUT) establece el pin de la placa de desarrollo llamado "TEC1" como entrada. 
             
      - iii. Idem c pero con datos (definiciones, constantes, variables, estructuras, etc.) (tanto en ResetISR() como en main())
           
          **Adasdasdas**
          
2. El objetivo a continuación es crear las funciones gpioInit, gpioWrite y gpioRead, las cuales implementan completamente el uso de los
GPIOs de la placa en una manera simple y general: 

