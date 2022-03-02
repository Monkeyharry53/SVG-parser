/*
 
NAME - MANJOT SINGH
STUDENT ID - 1141657

*/

#ifndef SVGHELPERS_H
#define SVGHELPERD_H

#include "SVGParser.h"
#include "LinkedListAPI.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>


/**
 * @brief this function contains nothing so we can use it whne we initilize list for mudule 2(get functions)
 * @param data 
 */
void delete(void* data);

/**
 * @brief check number of other attributes in the element 
 * 
 * @param attr - takes the attribute to find other attributes in it
 * @return Attribute* 
 */
Attribute *otherAtr(xmlAttr *attr);

/**
 * @brief checks the information in rectangle
 * 
 * @param rect - takes the current node
 * @return Rectangle* - return all the properties that rectangles have
 */
Rectangle *rectFunc(xmlNode *rect);
/**
 * @brief checks the information in circle
 * 
 * @param circle_node -takes the current node
 * @return Circle* - return all the properties that Circles have
 */
Circle *circleFunc(xmlNode *circle_node);
/**
 * @brief checks the information in path
 * 
 * @param path_node -takes the current node
 * @return Path* - return all the properties that Paths have
 */
Path *pathFunc(xmlNode *path_node);
/**
 * @brief checks the information in group
 * 
 * @param group_node -takes the current node
 * @return Group* - return all the properties that groups have
 */
Group *group_func(xmlNode *group_node);
/**
 * @brief checks groups inside group and store iin list
 * 
 * @param tmp -takes the current group
 * @param list -takes the list so it can insertback thr data in list
 */
void  gethelpher(Group* tmp,List* list);











bool checkSVG(xmlDoc* doc ,const char *xsd);
xmlDoc * parseDoc(const SVG * img);

void  parseAttr(xmlNode * node,List * otherAtr);
void parseRect(xmlNode * node,List * rect);
void parseCircle(xmlNode * node,List * circ);
void parsePath(xmlNode * node,List * pa);
void  parseGroup(xmlNode * node,List * g);
void findAttr(List * list, Attribute* newAttribute);

bool checkRect(const SVG * img);
bool checkCirc(const SVG * img);
bool checkPath(const SVG * img);
bool checkGroup(const SVG * img);

bool checkatrbsdk(List * list);

bool checkValidAttr(List *attrList);


#endif
