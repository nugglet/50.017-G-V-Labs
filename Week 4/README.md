# Graphics and Visualisation Assignment 2
Victoria Yong 1004455

## loadSkeleton
This function takes in the filename as input, which is the path given when running the program. Since the build file is in a separate directory, the path given should be relative to the build file (i.e. './data/Model1.skel').

This function loads the file given and creates a hierarchy of joints. The file is read line by line using an `ifstream`, where the first 3 numbers of the line are transformation data and the last number is the index of the parent joint. The function iteratively loops through the file line by line, creates a new `Joint` object for each line, and updates the list of joints (`m_joints`) with the new joint, and adds the joint to the parent as one of its child objects. If the index of the parent joint is -1, then the new joint is the root joint of the whole skeleton, and we update `m_rootJoint` accordingly.

## computeJointTransforms
This function is a recursive helper function that pushes the transform data of each joint to the global stack of joints (`m_matrixStack`) in order. The function starts from the root joint (`m_rootJoint`), and iteratively traverses down the hierarchy of joints, pushing the transformation of the joint to the stack at each recursion. 

The main function in main.cpp then renders the data from 'm_matrixStack'.

### computeBoneTransforms
This function operates similarly to the computeJointTransforms. However, since each bone is not just a point, but a cylindrical shape, we must compute the relevant transformation for each bone since by default they have the same size, radius, rotation and positions. 

To get the distance from the current joint to its parent, I take the last column of the joint's transform data (`glm::vec3 joint_pos = glm::transpose(joint->children[i]->transform)[3];`), which is the transform data read from the file. Since the data is recorded as the transform relative to its parent, the distance between the joint and its parent would be the distance of its transformation data. 

To calculate the transformation matrix, translate an identity matrix by (0, 0, 0.5),  such that the cylinder ranges from [-0.5, -0.5, 0] to[0.5, 0.5, 1].

The cylinder needs to be scaled down to match the size of the joints. The default cylinder is with radius 1.0 and height 1.0 centred around the origin. The cylinders are drawn using 3 variables, (top_radius, base_radius, length). To match the size of the sphere joints, the radius should be scaled by a maximum factor of 0.2. In order for the cylinders to be distinguished from the joints, the radius can be reduced (in this case 0.1). The length of the cylinder is determined by the distance between the current joint and its parent (`glm::length(glm::transpose(joint->children[i]->transform)[3];);`)

For the rotation, the bone must be rotated by the z - axis so that it is aligned with the direction to the parent joint. The z vector can be obtained by normalizing the transformation data of the joint. The x and y rotations can be calculated as described in the handout. Subsequently, the rotation matrix can be formed by constructing a 4d matrix using the calculated x, y and z vectors.

Finally, to compute the final transformation data, multiply the matrices in this order: `rotate * scale * translate * matrixStack.top()`. Finally, similar to computeJointTransforms, the data can be pushed to the global `boneMatList` stack and the function can continue to traverse the hierarchy recursively.

## setJointTransform
This function enables the joints to be rotated and moved by specifying the rotation angles for each axis. This can be done using the `glm::rotate` function, which takes in the matrix to be translated, the angle of rotation, and the axis of rotation.