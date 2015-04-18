This file is here for me to note down things about the project's design and so forth. I jot down my thoughts here. It helps me keep myself organized, since I often have to take breaks from working on sandtrace due to college/other commitments.

####Messed up colours
The model's colours are all screwed up. Need to debug this. First I'll try without texturing.

####Octree
I really need to use an octree to speed up the intersection testing.

####Randomized tests
Improve the randomized tests. Right now they are all failing left and right. Clearly there's some mathematical error.

####Unit tests
Wrote unit tests for the triangle's try_intersects, and it's passing the static tests.. Look into more testing strategies.

####Reading textures
As of now I can only load PNG textures. I should switch on the file extension and call the appropriate GIL function to load instead.

####Texcoord generation for planes
Need to implement texcoords generation for planes. Since plane texcoords need to be tiled, this involves moving the plane to coincide with the XZ plane and then generating the texcoords using the X and Z coordinates of the surface point.

####build_sphere_scene
Wondering what to do with this function. Perhaps I'll get rid of it later.
