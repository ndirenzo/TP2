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
         - 1. Identificar la secuencia de funciones invocadas durante la ejecución del ejemplo de aplicación, en qué archivo se encuentran, su descripción detallada,  qué efecto tiene la aplicación sobre el hardware (identificar circuitos, puertos, pines, niveles, etc.) así como la interacción entre las mismas (tanto en ResetISR() como en main()).  
             
          **Adasdas**
         - 3. Idem c pero con datos (definiciones, constantes, variables, estructuras, etc.) (tanto en ResetISR() como en main())
           
          **Adasdasdas**
          
2. El objetivo a continuación es crear las funciones gpioInit, gpioWrite y gpioRead, las cuales implementan completamente el uso de los
GPIOs de la placa en una manera simple y general: 
