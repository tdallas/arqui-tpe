# TPE -  Arquitectura de Computadoras 2018
Sistema Basado en x64BareBones para la arquitectura Intel 64.

## Para ejecutar el proyecto:

1- Instalar los siguientes paquetes antes de armar el Toolchain y Kernel:

```
sudo apt-get install nasm qemu gcc make
```

2- Armar la Toolchain

Ejecutar los siguientes comandos desde el directorio del repositorio:
```
cd Toolchain
make all
```

3- Armar el Kernel

Desde el directorio del repositorio realizar:
```
make all
```

4- Ejecutar el Kernel

Desde el directorio del repositorio realizar:
```
./run.sh
```

## Desde el sistema ejecutar el siguiente comando para ver sus utilidades:
```
help
```

## Collaborators
* Dorado, Tomas
* Dallas, Tomas