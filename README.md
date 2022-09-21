# A Simple Uncompressed GIF to ICO converter

## Implementation methodology:

- Studied the gif format and created the appropriate data structures for a gif file.
- Studied and Created the appropriate data structures for ICO file.
- Read the gif file and populated the above-mentioned data structures.
- Extracted the image data which was in form of indexes and then converted it to the individual RGB values using the global colour table of the gif: this is the process of conversion of image data.
- Wrote the image data into a ICO file according to little endian format.
- Made the makefile.

## Instructions :
- Paste the source image file in the directory of the project.
- in the directory of the project, run the command:
```
$ make
```
- this will create the “.o”  files and the final executable.
- Now run the command:
```
$ ./my_program source-image destination-image.
```
