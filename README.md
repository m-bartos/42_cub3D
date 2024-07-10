# 42_cub3D
This project is inspired by the world-famous Wolfenstein 3D game, the first FPS ever. It is the best opportunity to explore ray-casting. The goal is to make a dynamic view inside a maze where you’ll have to find your way.

Team project with [Orezek](https://github.com/orezek) at 42Prague.

## Configuration file - map, textures, floor and ceiling colors
As you can see from [intra_map.cub](https://github.com/m-bartos/42_cub3D/blob/main/maps/intra_map.cub) the config file must have these parameters:
* config file has to have .cub postfix
* 4 textures for north (NO), south (SO), west (WE) and east (EA) must be present in the file with the path to the texture
* 2 colours for the floor (F prefix) and ceiling (C prefix) have to be present in the file followed by 3 integers with values between 0-255 to represent R, G, B
* Map must be last in the config file
* Spaces are valid a part of the map
* Map must be closed (surrounded by walls)
* The player's starting position is represented by one of these characters N, S, E, or W in the map and the letter represents the side the player is looking at

## What we learned during coding cub3D
* Ray-casting
* Who John Carmack is - listen to 5 hours long Lex Frieman podcast with him [here](https://youtu.be/I845O57ZSy4?feature=shared), it is just fascinating!

## Contributors
* [m-bartos](https://github.com/m-bartos) - parser
* [orezek](https://github.com/orezek) - ray-casting, minimap ([minimap branch](https://github.com/m-bartos/42_cub3D/tree/minimap))

## Thanks and kudos
* Thanks for [MLX42](https://github.com/codam-coding-college/MLX42)
* [Ray-casting tutorial](https://lodev.org/cgtutor/raycasting.html)
