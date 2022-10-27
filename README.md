# FdF | Filsdefer | "wire frame"
<i>A skeletal three-dimensional model in which only lines and vertices are represented.</i><br><br>
This C project is about creating a simplified graphic “wireframe” (“fils de fer”) representation of a relief landscape linking various points (x, y, z) via segments. The coordinates of this landscape are stored in a file passed as a parameter to the program.  This C program is tagged with my school's "42" user account "aviholai".

MiniLibraryX (MLX) is a 42School graphical library used in the graphics branch projects, such as this one, and is included in the files. For more information regarding MLX and understanding it, I recommend checking out this guide by <a href="https://github.com/harm-smits">@harm-smits</href>: <a href="https://harm-smits.github.io/42docs/libs/minilibx/introduction.html">42 Docs: MiniLibX</href><br><br>

# How to use.
1. Compile the binary in the repository with command <i>make</i> 
2. Apply a simple text map file as a parameter with <i>./fdf \<name of file> </i>
3. If the map is viable the graphic window should open, otherwise you should get an error message in the standard output. <br><br> 
<b>Controls for MAC:</b> <br> 
• Press `TAB` to toggle projection modes (Parallel Mode, Isometric Mode). <br>
• Press `ESC` to quit the program. <br>
• Press `*` or `/` to adjust height peaks scale. <br>
• Press `+` or `-` to zoom in or out. <br>
• Press `↑`, `←`, `→` or `↓` to move the map.<br><br>
As the program was initially planned for school computer use, the keyboard controls may not be hooked properly to other than MacOS.

![fdf_video](https://user-images.githubusercontent.com/70949716/198287968-788d3880-bcd1-4b39-b190-efe02644fe42.gif)


# To do. | Future capacities.

• Compatibility with different OS (with MiniLibraryX and keyboard controls) <br>
• Automatic scaling the graphical projection's width to the window resolution <br>
• Automatic scaling the peaks (altitude) of the graphical projection to the window resolution <br>
• Scaling the color hue in-between altitudes (coordinates) for better visual representation <br>
• HEX color value parsing in the map coordinate data <br>
<strike>• Zoom in feature (keyboard or mouse) </strike><br>
<strike>• Movable map plane feature. </strike><br>
• Rotatable map plane feature. <br>
• Tiltable map plane feature. <br>
• Rotation feature (keyboard) <br>
• Etc. <br>
