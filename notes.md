This file is here for me to note down things about the project's design and so forth. I jot down my thoughts here. It helps me keep myself organized, since I often have to take breaks from working on sandtrace due to college/other commitments.

####Texcoord generation for planes
Need to implement texcoords generation for planes. Since plane texcoords need to be tiled, this involves moving the plane to coincide with the XZ plane and then generating the texcoords using the X and Z coordinates of the surface point.

####Shading with colors from a texture
The texture color should be multiplied with the diffuse and ambient components of the calculated Phong lighting color of the pixel. This means I'll have to change intersection_data to have a texture color field apart from the material field. The Phong lighting functions will also need to be modified accordingly. Maybe I have to change nearerst_intersection too.

####try_intersects for triangle
I'll have to make the triangle class implement the primitive interface, including the try_intersects function.

####Monochrome textures
I ought to develop a texture interface. One class could implement the sample method to always return the same color. This is a simple way to assign a single color to a primitive.
