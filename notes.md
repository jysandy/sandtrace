This file is here for me to note down things about the project's design and so forth. I jot down my thoughts here. It helps me keep myself organized, since I often have to take breaks from working on sandtrace due to college/other commitments.

####Changing the primitive interface
The texcoord field is not really needed. What clients really need is the color of the vertex itself. So add or replace this with another class called color_vertex which has the actual vertex color rather than the texcoords. primitive::vertex_at() should return a color_vertex. Implementations of this method should sample the texture to get the color.  
Current status: Need to add texture members to the other primitives (sphere, plane). Also need to look up formulae to generate texcoords for spheres and planes. I'll implement those in a private texcoords_at() method.

####texture: where to put it?
It should be possible for a primitive to be associated with a texture, so that vertex_at() can sample it. However all triangles in a mesh should share the same texture. It's probably best not to have the texture as a member variable of primitive. This way, vector surfaces like spheres/planes can keep their texture as a member variable since they don't really have any subcomponents as such. Triangles on the other hand have a pointer to their parent mesh itself which in turn contains the texture. It doesn't make sense to me to allow triangles in a single mesh to have different textures. If you want a different texture you should make a new mesh.

####Shading with colors from a texture
The texture color should be multiplied with the diffuse and ambient components of the calculated Phong lighting color of the pixel. This means I'll have to change intersection_data to have a texture color field apart from the material field. The Phong lighting functions will also need to be modified accordingly. Maybe I have to change nearerst_intersection too.

####try_intersects for triangle
I'll have to make the triangle class implement the primitive interface, including the try_intersects function.

####Loading a texture from disk
The scene's from_fbx_file function should be able to load a texture and attach it to a mesh. FBX files often don't specify the texture filenames, so this is a task which probably needs some kind of ugly hack(passing the filename to the loading function or something like that). Maybe I should ditch this stupid format and try COLLADA instead. The loading function is ugly enough as it is.

####Monochrome textures
I ought to develop a texture interface. One class could implement the sample method to always return the same color. This is a simple way to assign a single color to a primitive.
