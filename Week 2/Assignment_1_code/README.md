# GV Assignment 1
Victoria Yong 1004455

## Part 1: Load Input
This script required the file to be loaded in to two lists.
- verList: stores vertices and normals  with order (v.x, v.y, v.z, n.x, n.y, n.z)
- triList: store vertex indices

The obj file writes all vertex information first, followed by normals and then faces. Hence, in order to store the information in verList in the specified order, we must first extract the vertex, normal and face index information into 3 separate temporary lists (i.e. `normalIndices, temp_vertices, temp_normals`)

### Storing face indexes.
Related indexes is stored in face data in the format <vertice_index>/<>/<normal_index>
I iterate through the file and store the vertice_index and normal_index in a hash map so I know which vertice is related to which normal.
I also update triList with the vertice_index.

### Storing Vertices and Normals
Using the hash map of related vertice and normal indexes, I select the vertex and normal that are related and push their x, y and z values to verList in the specified order.

## Part 2: Set Mesh Colour
Mesh colour can be set by changing the global value of `colorID`. To make the colour loop through the colour table one by one, we can simply modulo the new colorID by `(sizeof(colorTable) / sizeof(colorTable[0]))`

## Part 3: Rotate and Translate Model
Rotating and translating the model can be done with the use of the glm functions `rotate` and `translate`. 

## Part 4: Scale Model
Scaling the model can be done with the use of the glm function `scale`
