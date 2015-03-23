This file is here for me to note down things about the project's design and so forth. I jot down my thoughts here. It helps me keep myself organized, since I often have to take breaks from working on sandtrace due to college/other commitments.

####polygon_vertex -> color_vertex
The texcoord field is not really needed. What clients really need is the color of the vertex itself. So add or replace this with another class called color_vertex which has the actual vertex color rather than the texcoords. primitive::vertex_at() should return a color_vertex. Implementations of this method should sample the texture to get the color. Which brings me to...

####texture: where to put it?
It should be possible for a primitive to be associated with a texture, so that vertex_at() can sample it. However all triangles in a mesh should share the same texture. It's probably best not to have the texture as a member variable of primitive. This way, vector surfaces like spheres/planes can keep their texture as a member variable since they don't really have any subcomponents as such. Triangles on the other hand have a pointer to their parent mesh itself which in turn contains the texture. It doesn't make sense to me to allow triangles in a single mesh to have different textures. If you want a different texture you should make a new mesh.

####Shading with colors from a texture
The texture color should be multiplied with the diffuse and ambient components of the calculated Phong lighting color of the pixel. This means I'll have to change intersection_data to have a texture color field apart from the material field. The Phong lighting functions will also need to be modified accordingly. Maybe I have to change nearerst_intersection too. Gotta run...I'll write more about this later...
