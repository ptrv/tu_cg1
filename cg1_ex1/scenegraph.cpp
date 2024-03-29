/* ----------------------------------------------------------------
   name:           scenegraph.c
   purpose:        implementation of the scenegraph functions
   version:	   SKELETON CODE
   TODO:           traverse reset
   author:         katrin lang
           computer graphics
           tu berlin
   ------------------------------------------------------------- */

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include "win32/glut.h"
#else
#include <GL/glut.h>
#endif

#include "scenegraph.h"

// without this line,
// printline debugging won't work
using namespace std;

// this is our scenegraph
SceneGraph *sceneGraph;

SceneGraph::SceneGraph(Node *root) : root(root), selected(root) {
    selected->select();
}

SceneGraph::~SceneGraph(){
    clear(root);
}

// traverse and draw the scenegraph
// nothing to do here
// (see helper function)
void SceneGraph::traverse(){
    traverse(root);
}

// reset all rotations in the scenegraph
// nothing to do here
// (see helper function)
void SceneGraph::reset(){
    reset(root);
}

// navigation in tree
// (needed for node selection)
void SceneGraph::up(){
    if(selected->getParent() == NULL) return;
    selected->deselect();
    selected= selected->getParent();
    selected->select();
}
void SceneGraph::down(){
    if(selected->getChild() == NULL) return;
    selected->deselect();
    selected= selected->getChild();
    selected->select();
}
void SceneGraph::left(){
    if(selected->getPrevious() == NULL) return;
    selected->deselect();
    selected= selected->getPrevious();
    selected->select();
}
void SceneGraph::right(){
    if(selected->getNext() == NULL) return;
    selected->deselect();
    selected= selected->getNext();
    selected->select();
}

// increment / decrement rotation of selected node
void SceneGraph::rotate(float x, float y, float z){
    selected->rotate(x, y, z);
}

// traverse and draw the scenegraph from a given node
// XXX: NEEDS TO BE IMPLEMENTED
void SceneGraph::traverse(Node *node){

    if(node == NULL) return;

    // store current modelview (transformation) matrix
    // XXX

    // INSERT YOUR CODE HERE

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // END XXX

    // apply local transformation
    node->transform();
    // draw the current node
    node->draw();

    // continue concatenating transformations
    // if this node has children
    // XXX

    // INSERT YOUR CODE HERE
    if(node->child)
    {
        traverse(node->child);
    }

    // END XXX

    // after this scenegraph branch
    // restore previous transformation
    // XXX

    // INSERT YOUR CODE HERE
    glPopMatrix();
    // END XXX

    // and traverse possible siblings
    // XXX

    // INSERT YOUR CODE HERE
    if(node->next)
    {
        traverse(node->next);
    }
    // END XXX
}

void SceneGraph::clear(Node *node){

    if(node == NULL) return;
    delete node;
    clear(node->getChild());
    clear(node->getNext());
}

// reset all rotations below a given node
// XXX: NEEDS TO BE IMPLEMENTED
void SceneGraph::reset(Node* node){
    if(node == NULL)
        return;
    // reset rotations
    // XXX
    // INSERT YOUR CODE HERE
    node->rotx = node->initRotx;
    node->roty = node->initRoty;
    node->rotz = node->initRotz;
    reset(node->child);
    reset(node->next);
    // END XXX
}

bool SceneGraph::selectName(int name)
{
    return selectName(root, name);
}

bool SceneGraph::selectName(Node* node, int name)
{
    if(node == NULL)
        return false;

    if(node->nodeName == name)
    {
        selected->deselect();
        selected = node;
        selected->select();
        return true;
    }
    else
    {
        bool selectedChild=false;
        if(node->child)
        {
            selectedChild = selectName(node->child, name);
        }
        if(selectedChild)
        {
            return true;
        }
        else if(node->next)
        {
            return selectName(node->next, name);
        }
    }
    return false;
}
