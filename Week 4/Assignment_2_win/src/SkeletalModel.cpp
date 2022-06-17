///=========================================================================================///
///
///                       Functions to be filled in for Assignment 2   
///
///           IMPORTANT: you ONLY need to work on functions with TODO in this section    
///    
///=========================================================================================///


#include "SkeletalModel.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Sphere.h"


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
        
        string token;
        float t;
        int parent_idx;
        
        // temp arrays
        float temp_transforms[3];
            
        // string searching
        string delimiter = " ";
        size_t pos = 0;

        // split line into 4 tokens
        for (int i = 0; i < 4; i++) {

            pos = line.find(delimiter);
            token = line.substr(0, pos);  

            if (i == 3) {
                // index of parent, update m_joints[token] (parent joint) with child
                // update m_joints[line_index] with transforms (current joint)
                // if index is -1, set as root               

                parent_idx = stoi(token);
                glm::mat4 transforms = glm::make_mat4(temp_transforms);    
                Joint* new_joint = new Joint();
                m_joints.push_back(new_joint);
                
                // add to m_joints
                m_joints[line_index]->transform = transforms;                 
                
                if (parent_idx == -1) {
                    // no parent, set root joint
                    m_rootJoint = m_joints[line_index];
                }
                else {
                    // not root joint. Find parent and add current joint as child.
                    m_joints[parent_idx]->children.push_back(m_joints[line_index]);
                }                
            }   
            else {
                // floats: joint translation relative to parent
                t = atof(token.c_str());               
                temp_transforms[i] = t;      

            }
            line.erase(0, pos + delimiter.length());            
        }
        line_index++;
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

    for (int i = 0; i < joint->children.size(); i++) {
        computeJointTransforms(joint->children[i], matrixStack);
    }

    //Sphere sphere(0.025f, 12, 12, true);
    
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
    /*Vector4f vectorDiff(joint->transform[12], joint->transform[13], joint->transform[14], 0);
    Matrix4f translate_z = Matrix4f::translation(0, 0, 0.5);
    float distance = vectorDiff.abs();
    Matrix4f scale = Matrix4f::scaling(0.05f, 0.05f, distance);
    Vector3f rnd(0, 0, 1);
    Vector3f z = vectorDiff.normalized().xyz();
    Vector3f y = Vector3f::cross(z, rnd).normalized();
    Vector3f x = Vector3f::cross(y, z).normalized();
    Matrix3f tempRot = Matrix3f(x, y, z);
    Matrix4f rot = Matrix4f::identity();
    rot.setSubmatrix3x3(0, 0, tempRot);

    m_matrixStack.push(rot * scale * translate_z);
    glLoadMatrixf(m_matrixStack.top());
    glutSolidCube(1.0f);
    m_matrixStack.pop();*/

    matrixStack.push(joint->transform);
    boneMatList.push_back(matrixStack.top());

    for (unsigned i = 0; i < joint->children.size(); i++) {
        cout << joint->children.size() << endl;
        computeBoneTransforms(joint->children[i], matrixStack);
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







