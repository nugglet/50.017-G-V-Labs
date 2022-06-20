///=========================================================================================///
///
///                       Functions to be filled in for Assignment 2   
///
///           IMPORTANT: you ONLY need to work on functions with TODO in this section    
///    
///=========================================================================================///


#include "SkeletalModel.h"


///=========================================================================================///
///                                    Load .skel File    
///=========================================================================================///


// TODO: Load the skeleton from file here, create hierarchy of joints
//       (i.e., set values for m_rootJoint and m_joints)
void SkeletalModel::loadSkeleton( const char* filename )
{
    
    string line;
    ifstream file;
    file.open(filename);

    int line_index = 0;

    if (!file.is_open()) {
        cerr << "Could not open the file - '"
            << filename << "'" << endl;
    }

    // read line by line
    while (getline(file, line)) {

        float x, y, z;
        int index;

        stringstream ss(line);
        ss >> x >> y >> z >> index;

        Joint* joint = new Joint;
        joint->transform = glm::mat4(
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1
        );
            
        m_joints.push_back(joint);

        // update children
        if (index == -1) {
            m_rootJoint = joint;
        }
        else {
            m_joints[index]->children.push_back(joint);
        }
    }

   file.close();
}




///=========================================================================================///
///                         Compute transformations for Joints and Bones     
///=========================================================================================///

void SkeletalModel::computeTransforms()
{
    if( m_joints.size() == 0 )
        return;

    computeJointTransforms();

    computeBoneTransforms();
}

// Compute a transformation matrix for each joint (i.e., ball) of the skeleton
void SkeletalModel::computeJointTransforms( )
{
    jointMatList.clear();

    m_matrixStack.clear();

    computeJointTransforms(m_rootJoint, m_matrixStack);
}

// TODO: You will need to implement this recursive helper function to traverse the joint hierarchy for computing transformations of the joints
void SkeletalModel::computeJointTransforms(Joint* joint, MatrixStack matrixStack)
{
    matrixStack.push(joint->transform);
    jointMatList.push_back(matrixStack.top());

    for (unsigned i = 0; i < joint->children.size(); i++) {
        computeJointTransforms(joint->children[i], matrixStack);
    }
    matrixStack.pop();
}


// Compute a transformation matrix for each bone (i.e., cylinder) between each pair of joints in the skeleton
void SkeletalModel::computeBoneTransforms( )
{
    boneMatList.clear();

    m_matrixStack.clear();

    computeBoneTransforms(m_rootJoint, m_matrixStack);
}

// TODO: You will need to implement this recursive helper function to traverse the joint hierarchy for computing transformations of the bones
void SkeletalModel::computeBoneTransforms(Joint* joint, MatrixStack matrixStack)
{
    matrixStack.push(joint->transform);

    if (joint->children.size() > 0) {
        // joint has children
        for (unsigned i = 0; i < joint->children.size(); i++) {

            // get distance vector
            glm::vec3 joint_pos = glm::transpose(joint->children[i]->transform)[3];

            // Translate it in z such that the cylinder ranges from [-0.5, -0.5, 0] to[0.5, 0.5, 1].
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.5));

            // Scale the cylinder so that it ranges from [-0.01, -0.01, 0] to[0.01, 0.01, d], 
            // where d is the distance to the next joint in your recursion.
            float d = glm::length(joint_pos);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 0.01f, d));

            // Finally, you need to rotate the z - axis so that it is aligned with the direction to the parent joint :
            glm::vec3 r(0, 0, 1);
            glm::vec3 z = glm::normalize(joint_pos);
            glm::vec3 y = glm::normalize(glm::cross(z, r));
            glm::vec3 x = glm::normalize(glm::cross(y, z));  

            glm::mat3 rot(x, y, z);
            glm::mat4 rotate = glm::mat4(rot);
           
            glm::mat4 transform = glm::transpose(rotate * scale * translate) * matrixStack.top();
            boneMatList.push_back(transform);

            computeBoneTransforms(joint->children[i], matrixStack);
        }
    }
    matrixStack.pop();
}


///=========================================================================================///
///                              Set Joint Angles for Transform     
///=========================================================================================///

// TODO: Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
void SkeletalModel::setJointTransform(int jointIndex, float angleX, float angleY, float angleZ)
{
    glm::mat4 rotate_X = glm::rotate(m_joints[jointIndex]->transform, angleX, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat4 rotate_XY = glm::rotate(rotate_X, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotate_XYZ = glm::rotate(rotate_XY, angleY, glm::vec3(0.0f, 0.0f, 1.0f));
    m_joints[jointIndex]->transform = (0, 0, rotate_XYZ);
}







