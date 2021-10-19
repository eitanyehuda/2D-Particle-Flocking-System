C++ and OpenGL

type make to compile and run program.

![Screensht1](https://user-images.githubusercontent.com/23744162/137965600-70de9582-1dd1-4ad0-9ce1-87c9aa12444d.JPG)
![Screensht2](https://user-images.githubusercontent.com/23744162/137966109-da88b432-eff3-4b5f-9b62-d833e55d4217.JPG)
![Screensht3](https://user-images.githubusercontent.com/23744162/137966118-9c61a43a-c2e2-4bfc-82ee-227b29716071.JPG)

I used Windows 10 OS and completed this assignment in VSCode.

I compiled the code in MSYS2 MINGW-64 using the Makefile. Simply type make to remove past exe, compile program, and run.

List of commands:
- press or hold LMB to attract particles within range of mouse cursor
- press or hold RMB to repel particles within range of mouse cursor
- press "a" to add new particle at current cursor position
- press "d" to remove a particle closest to cursor position
- press "+" to globally increase the range of all particles 
- press "-" to globally decrease the range of all particles 
- press "up" arrow key to globally increase movment speed of particles
- press "down" arrow key to globally decrease movment speed of particles
- press "space bar" to stop/run annimation if it it running/stopped
- press "r" to wipe screen and re-generate a new set of particles
- press "q" or "Esc" to exit the program

Additional features:
- Improved particle physics with momuntum
- Particles bounce off the screen edges
- Press "f" to toggle friction on/off: particles will slow down if no force is applied to them 
- Press "e" to toggle evacuation on/off: predefined animation of particles evacuating to the bottom-left corner of the screen
- Press "h" to gather particles and create a heart: the more particles in range, the more detailed it will be :)
