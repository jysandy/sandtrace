This file is here for me to note down things about the project's design and so forth. I jot down my thoughts here. It helps me keep myself organized, since I often have to take breaks from working on sandtrace due to college/other commitments.

####Unit tests
Many tests are pending for all the new code. Especially try_intersects for the triangle.

####Reading textures
As of now I can only load PNG textures. I should switch on the file extension and call the appropriate GIL function to load instead.

####Texcoord generation for planes
Need to implement texcoords generation for planes. Since plane texcoords need to be tiled, this involves moving the plane to coincide with the XZ plane and then generating the texcoords using the X and Z coordinates of the surface point.

####Monochrome textures
I ought to develop a texture interface. One class could implement the sample method to always return the same color. This is a simple way to assign a single color to a primitive.

####build_sphere_scene
Wondering what to do with this function. Perhaps I'll get rid of it later.
