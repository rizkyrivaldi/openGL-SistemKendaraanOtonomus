# Untuk Kelas Sistem Kendaraan Otonomus

## Dependencies
Cygwin with the package listed as below:
1. gcc-g++
2. make
3. libGLU-devel
4. libGLU1
5. libglut-devel
6. libglut3
7. libGL-devel
8. libGL1
9. xinit (required, scripts for starting the X server: xinit, startx, startwin (and a shortcut on the Start Menu to run it), startxdmcp.bat )
10. xorg-server (required, the Cygwin/X X Server)

## How to run
compile the program using make
```
make
```
to run the program
```
make start
```

## Controls
w = move the camera +y axis\
a = move the camera -x axis\
s = move the camera -y axis\
d = move the camera +x axis\
up = move the camera +z axis\
down = move the camera -z axis