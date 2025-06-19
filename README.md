# Mandelbrot visualizer  

## usage guide
- clone the repo to your system    

``` bash
git clone https://github.com/Reed-Broadhead/mandelbrot-set-visualizer.git
```

command to comile with gcc compiler  
 ``` bash
 gcc main.c -o main `sdl2-config --cflags --libs` -lSDL2_image -lm
```

- then run the file.  

command in unix
```bash
 ./main
```

probably command in windows  
```powershell
 main.exe
```


## args

The program default opens to 100 percent of the screen.  
if you'd like it to be less just enter the percent of the screen you want it to take up as an arg.  
_  
example:  
```bash
./main 20
```

**do not add** add a % sign. any incorrectly formated commands or extra ones will be ignored by the program. and screen will still defualt to 100%.
