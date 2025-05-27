# Minishell 🐚 - Nuestra Propia Shell (Proyecto en Equipo)

![Minishell GIF](URL_DEL_GIF_AQUI) ## Introducción

Minishell es un proyecto emblemático de [42 School](https://www.42.fr/) cuyo objetivo es **crear una shell simple**, nuestra propia versión reducida de `bash`. Este proyecto representa una inmersión profunda en el funcionamiento interno de los sistemas Unix, proporcionando un **conocimiento extensivo sobre procesos y descriptores de archivo**.

Fue desarrollado por un equipo de dos personas, permitiéndonos abordar la complejidad del proyecto de manera colaborativa y especializada.

---

## El Desafío

Construir una shell, incluso una "mini", implica superar varios desafíos técnicos clave:

1.  **Parsing:** Interpretar correctamente la línea de comandos, manejando comillas simples (`'`) y dobles (`"`), y caracteres especiales como pipes (`|`) y redirecciones (`<`, `>`, `<<`, `>>`).
2.  **Ejecución:** Lanzar los comandos, ya sean *built-ins* o programas externos (buscándolos en el `PATH` o mediante rutas).
3.  **Gestión de Procesos:** Utilizar `fork` para crear nuevos procesos, `execve` para ejecutar comandos externos, y `wait`/`waitpid` para gestionar la finalización de los procesos hijos.
4.  **Redirección de E/S:** Manipular descriptores de archivo con `dup`/`dup2` para implementar las redirecciones y los pipes.
5.  **Expansión:** Manejar la expansión de variables de entorno (`$VAR`) y el código de salida (`$?`).
6.  **Manejo de Señales:** Implementar el comportamiento esperado para `ctrl-C`, `ctrl-D` y `ctrl-\`, usando `signal` o `sigaction`.

---

## Nuestro Enfoque y Mi Contribución ⚙️

Abordamos el proyecto dividiéndolo funcionalmente:

* Mi compañero, **[jeandrad1](https://github.com/jeandrad1)**, fue el arquitecto del **Parsing**. Se encargó de:
    * Analizar la entrada del usuario y **tokenizarla**.
    * Construir un **Árbol Sintáctico Abstracto (AST)** que representara fielmente la estructura y prioridades de los comandos.
    * Implementar un **autómata** para realizar comprobaciones previas y detectar errores de sintaxis *antes* de intentar la ejecución, mejorando la robustez de nuestra shell.

* Mi rol se centró en dar vida a ese árbol: la **Ejecución**. Fui responsable de:
    * **Recorrer el AST** generado por el parser para interpretar la secuencia de comandos.
    * Implementar la lógica de **`fork`** para crear nuevos procesos.
    * Utilizar **`execve`** para lanzar los ejecutables, incluyendo la búsqueda en el `PATH`.
    * Gestionar **`pipes` (`|`)** para conectar comandos.
    * Implementar las **redirecciones (`<`, `>`, `<<`, `>>`)** usando `dup2`.
    * Manejar la ejecución de los comandos **`built-in`**.
    * Controlar los **estados de salida (`$?`)**.
    * Coordinar la espera de procesos hijos con **`waitpid`**.

Esta división nos permitió especializarnos y, al mismo tiempo, mantener una comunicación constante para asegurar una integración perfecta entre el análisis y la ejecución.

---

## Características Implementadas (Parte Obligatoria)

Nuestra Minishell implementa las siguientes funcionalidades:

* **Prompt Interactivo:** Muestra un prompt cuando espera un nuevo comando.
* **Historial Funcional:** Permite navegar por comandos anteriores.
* **Ejecución de Comandos:** Busca y lanza ejecutables basándose en `PATH` o rutas.
* **Manejo de Comillas:**
    * `'` (comillas simples) previenen la interpretación de metacaracteres.
    * `"` (comillas dobles) previenen la interpretación, excepto para `$`.
* **Redirecciones:**
    * `<`: Redirección de entrada.
    * `>`: Redirección de salida.
    * `<<`: Here-document.
    * `>>`: Redirección de salida en modo *append*.
* **Pipes (`|`):** Conecta la salida de un comando con la entrada del siguiente.
* **Variables de Entorno:** Expande variables (`$VAR`) y el estado de salida (`$?`).
* **Manejo de Señales:** `ctrl-C`, `ctrl-D`, y `ctrl-\` se comportan como en `bash`.
* **Built-ins:**
    * `echo` con la opción `-n`.
    * `cd` con rutas relativas o absolutas.
    * `pwd` sin opciones.
    * `export` sin opciones.
    * `unset` sin opciones.
    * `env` sin opciones o argumentos.
    * `exit` sin opciones.

---

## Parte Bonus (Opcional)

* Implementación de `&&` y `||` con paréntesis para prioridades.
* Soporte para *wildcards* (`*`) en el directorio actual.

*(Nota: La parte bonus solo se evalúa si la parte obligatoria es perfecta.)*

---

## Cómo Usar

### Requisitos

* Un compilador C (como `gcc` o `clang`).
* `make`.
* La librería `readline`.

### Compilación

1.  **Clona el repositorio:**
    ```bash
    git clone [https://github.com/tu_usuario/tu_repositorio.git](https://github.com/tu_usuario/tu_repositorio.git)
    cd tu_repositorio
    ```
2.  **(Opcional) Si usas `libft`, asegúrate de que esté presente y tu `Makefile` la compile.**
3.  **Compila el proyecto:**
    * Para la parte obligatoria:
        ```bash
        make
        ```
    * Para compilar con los bonus:
        ```bash
        make bonus
        ```
    El `Makefile` debe usar las flags `-Wall`, `-Wextra`, y `-Werror` y debe contener las reglas `$(NAME)`, `all`, `clean`, `fclean` y `re`.

### Ejecución

Una vez compilado, ejecuta la shell con:

```bash
./minishell

