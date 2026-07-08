# Instalación del entorno de desarrollo — Raylib + Visual Studio Code (Windows)

## Requisitos previos

Antes de comenzar a desarrollar nuestro videojuego, necesitaremos instalar las herramientas necesarias para programar videojuegos en C++ usando Raylib. Mediante esta guía conseguiremos instalar:

- Visual Studio Code
- Compilador C/C++ (MinGW mediante MSYS2 MINGW64)
- Raylib
- Extensiones de C++ para VS Code

---

## Paso 1 — Instalar Visual Studio Code

Descargar e instalar Visual Studio Code desde:

<https://code.visualstudio.com/>

![alt text](img/vscode.png)

Durante la instalación, se recomienda marcar:

- Add to PATH
- Register Code as editor
- Add "Open with Code"

### Comprobar instalación

1. Para abrir un terminal PowerShell, pulsamos la tecla de Windows (o pulsamos en inicio) o en la barra de busquedad inferior y escribimos "power".

![alt text](img/AbrirPowerWindows.png)

2. escribiendo esto en la terminal:

```powerShell
code
```

![imagen del terminal PowerShell](img/powerShell.png)

3. Si está instalado, se abrirá el programa **Visual Studio Code**.

![alt text](img/VsCodeOpen.png)

---

## Paso 2 — Instalar MSYS2

MSYS2 nos permitirá instalar el compilador de C++.

Descargar desde:

<https://github.com/msys2/msys2-installer/releases/download/2026-06-11/msys2-x86_64-20260611.exe>

Instalar en la ruta por **defecto**:

```text
C:\msys64
```

---

## Paso 3 — Actualizar MSYS2 MINGW64

### Abrir

Para abrir **MSYS2 MINGW64**, pulsamos la tecla de Windows (o pulsamos en inicio, o en la barra de busqueda inferior) y escribimos "MSYS2 MINGW64".

**NOTA**: Es importante fijarse en abrir la aplicación indicada, no otras con nombres similares.

![alt text](img/MSYS2_MINGW64.png)

**NOTA**: Para poder pegar el texto en este terminal, usamos click derecho y seleccionamos "paste".

### Ejecutar

```bash
pacman -Syu --noconfirm
```

![alt text](img/MSYS2_MINGW64_Terminal.png)

Ejecutar nuevamente, hasta que no queden actualizaciones pendientes.

![alt text](img/SyuComplete.png)

---

## Paso 4 — Instalar compilador C++, make y Raylib

### Instalar

En la terminal **MSYS2 MINGW64** ejecutar:

```bash
pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain
pacman -S --noconfirm --needed make
pacman -S --noconfirm --needed mingw-w64-x86_64-raylib
```

![alt text](img/InstallGcc.png)

Esto instala:

- g++
- gcc
- linker
- herramientas de compilación
- Makefile
- Raylib

### Comprobar instalación

```bash id="m2"
echo -e "\n=== G++ VERSION ===" && g++ --version
echo -e "\n=== MAKE VERSION ===" && make --version
echo -e "\n=== RAYLIB VERSION ===" && pkg-config --modversion raylib
```

devería aparecer algo como esto:

![alt text](img/TerminalCorrecto.png)

---

## Paso 5 — Añadir compilador al PATH de Windows

### Añadir al PATH del sistema

Para ello, abrimos una terminal de **PowerShell** tal y como se indicó anteriormente, **en modo administrador**:

![alt text](img/AbrirPowerWindows.png)

Y pegamos y pulsamos enter:

```powershell
[Environment]::SetEnvironmentVariable("Path", [Environment]::GetEnvironmentVariable("Path", [EnvironmentVariableTarget]::Machine) + ";C:\msys64\mingw64\bin", [EnvironmentVariableTarget]::Machine)
```

![alt text](img/PowerShellPath.png)

### Para comprobar que funciona correctamente

Escribimos en **PowerShell**:

```bash
g++ --version
```

---

## Paso 6 — Instalar extensiones de VS Code

Abrir **Visual Studio Code**.

Ir a extensiones e instalar:

### C/C++

Extensión oficial de Microsoft:

![alt text](img/cC++.png)

<https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools>

Opcional:

### Error Lens

Para visualizar errores directamente en el editor.

![alt text](<img/Error Lens.png>)

<https://marketplace.visualstudio.com/items?itemName=usernamehw.errorlens>

---

## Paso 7 - Añadir git a VSCode

### descargar e instalar git

<https://github.com/git-for-windows/git/releases/download/v2.55.0.windows.1/Git-2.55.0-64-bit.exe>

**Tras la instalación**, cerrar y volver a abrir Visual Studio Code. Nos debe aparecer estas opciones si está correctamente instalado:

![alt text](img/VisualStudioGit.png)

### Registrarse en Github

<https://docs.github.com/es/get-started/start-your-journey/creating-an-account-on-github#signing-up-for-a-new-personal-account>

### Hacer un fork del proyecto

Esto significa crear una copia que depende del proyecto principal (En este caso) sobre la que podemos trabajar por nuestra cuenta.

1. pulsamos en Fork
![alt text](img/fork/pulsarFork.png)

2. Completamos la creación en nuestra copia del repositorio en nuestra cuenta de github.
![alt text](img/fork/crearFork.png)

### Clonar el repositorio en VSCode

En Github, en nuestro nuevo fork del repositorio, copiamos la url:
![alt text](img/fork/copiarUrlFork.png)

vamos a **Visual Studio Code** y pulsamos en la opción de clonar

![alt text](img/VisualStudioGit.png)

---

## Paso 8 - Configurar para usar la terminal correcta en VSCode

vamos a [configurar](vscode://settings/terminal.integrated.profiles.windows) y pulsamos en el botón que indica la imagen:

![alt text](img/PerfilesTerminalWindows.png)

Ahí, añadimos al final el siguiente texto:

```JSON
, "MSYS2 MINGW64": {
    "path": "C:\\msys64\\usr\\bin\\bash.exe",
    "args": ["--login", "-i"],
    "env": {
        "MSYSTEM": "MINGW64",
        "CHERE_INVOKING": "1"
    }
}
```

![alt text](img/añadirRutaTerminal.png)

### Modificamos el terminal por defecto

Podemos modificar que terminal por defecto usará Visual Studio Code. Tenemos dos alternativas para configurarlo, de forma visual o manual.

#### De forma Visual

Abrimos la terminal, si no está ya abierta (Atajo: **Ctrl + ñ**)
![alt text](img/openTerminal.png)

Pulsamos en la flecha, para seleccionar la opción de "*select default profile*":

![alt text](img/openTerminalDefault.png)

Elegimos "*MSYS2 MINGW64*":

![alt text](img/selecTerminalDefault.png)

#### De forma Manual

![alt text](img/CambioNombreTerminalDefecto.png)

```JSON
,
    "terminal.integrated.defaultProfile.windows": "MSYS2 MINGW64"
```

---

## Paso 9 — Compilar

### Con Make

Para compilar directamente usando Make, en el terminar de **Visual Studio Code** (en la ruta del proyecto) escribimos:

```bash
make
```

![alt text](img/CompilarConMake.png)

![alt text](img/CompilarConMake_Resultado.png)

### Manualmente

Desde terminal :

```bash
g++ src/main.cpp -o bin/game -lraylib -lopengl32 -lgdi32 -lwinmm
```

![alt text](img/CompilacionManual_Resultado.png)

---

## Paso 10 — Ejecutar

Para ejecutar directamente usando Make, en el terminar de **Visual Studio Code** (en la ruta del proyecto) escribimos:

### Con Make

```bash
make run
```

![alt text](img/EjecutarConMake.png)

![alt text](img/Run_Resultado.png)

### Manualmente

Ejecutar:

```bash
./bin/game.exe
```

![alt text](img/EjecutarManualmente.png)

Si todo ha ido bien, aparecerá una ventana con:

---

## Problemas comunes

### Error: g++ no reconocido

Causa:

- PATH incorrecto

Solución:

- Añadir:

```text
C:\msys64\ucrt64\bin
```

---

### Error: raylib.h not found

Causa:

- Raylib no instalado

Comprobar:

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

---

### Error al enlazar librerías

Comprobar flags:

```bash
-lraylib -lopengl32 -lgdi32 -lwinmm
```

### Error al ejecutar el .exe

"*No se encuentra la libreria Raylib*"

Seguramente nos hemos añadido el PATH.

---

## Entorno listo

Si todo funciona correctamente, ya se puede comenzar a desarrollar videojuegos 2D y 3D con:

- C++
- Raylib
- Visual Studio Code

## Regla importante del curso

Durante este curso:

- Usaremos siempre la terminal de Visual Studio Code (MINGW64)
- Todo el código se compila y ejecuta con 'make run'
