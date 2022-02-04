/*
 
NAME - MANJOT SINGH
STUDENT ID - 1141657

*/

#include "SVGHelpers.h"

void delete(void* data){
        
}
char * units(char * cont){               //used for getting units for rectangel or circle
    int i, j;
    for (i = 0; cont[i] != '\0'; ++i)
    {
        while (!(((cont[i] >= 'a') && (cont[i] <= 'z')) || (((cont[i] >= 'A') && (cont[i] <= 'Z')) || (cont[i] == '\0'))))
        {
            for (j = i; cont[j] != '\0'; ++j)
            {
                cont[j] = cont[j + 1];
            }
            cont[j] = '\0';
        }
    }
    return cont;
}

Attribute *otherAtr(xmlAttr *attr)         //finds other attributes
{

    xmlNode *value = attr->children;
    char *attrName = (char *)attr->name;
    char *cont = (char *)(value->content);
    Attribute *atridata = (Attribute *)malloc(sizeof(Attribute) + strlen(cont) + 1);
    atridata->name = malloc(strlen(attrName) + 1);


    strcpy(atridata->name, attrName);    //name of attribute
    strcpy(atridata->value, cont);       // value of attribute

    return atridata;
}


Rectangle *rectFunc(xmlNode *rect_node)         
{
    Rectangle *r = (Rectangle *)malloc(sizeof(Rectangle));

    r->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes); //initilizing list for otherattributes in rectangle
 
    strcpy(r->units,"");
    for (xmlAttr *attr = rect_node->properties; attr != NULL; attr = attr->next)
    {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);

        if (strcmp(attrName, "x") == 0)  //if it contains x
        {

            float xC = strtof(cont, &cont);  //stores float value of x
            r->x = xC;
            strcpy(r->units, units(cont)); // for units 
        }
        else if (strcmp(attrName, "y") == 0) //if it contains y
        {
            float yC = strtof(cont, &cont);  //stores float value of y
            r->y = yC;

            strcpy(r->units, units(cont));   // for units 
        }
        else if (strcmp(attrName, "height") == 0)  
        {
            float heightC = strtof(cont, &cont);
            if(heightC >= 0){                  //if height is negative
                r->height = heightC;
            }
            else{   
                freeList(r->otherAttributes);

                //return;
                return r;
            }
            strcpy(r->units, units(cont));
        }
        else if (strcmp(attrName, "width") == 0)
        {
            
            float widthC = strtof(cont, &cont);
            if(widthC >= 0){              //if width is negative
                r->width = widthC;
            }
            else{
                freeList(r->otherAttributes);

                return r;
            }
            strcpy(r->units, units(cont));
        }
        else
        {
            insertBack(r->otherAttributes, otherAtr(attr));  //for getting other attributes of rectangles
        }
    }
    return r;
}

Circle *circleFunc(xmlNode *circle_node)
{
    Circle *circle = (Circle *)malloc(sizeof(Circle));
    circle->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);//initilizing list for otherattributes in Circles

    for (xmlAttr *attr = circle_node->properties; attr != NULL; attr = attr->next)//till attributes are there in svg file
    {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;  //name of attributes
        char *cont = (char *)(value->content); //value of attributes
        if (strcmp(attrName, "cx") == 0)
        {
    
            float cx_circle = strtof(cont, &cont);
            circle->cx = cx_circle;

            strcpy(circle->units, units(cont));
        }
        else if (strcmp(attrName, "cy") == 0)
        {
         
            float cy_circle = strtof(cont, &cont);
            circle->cy = cy_circle;

            strcpy(circle->units, units(cont));
        }
        else if (strcmp(attrName, "r") == 0)
        {
           
            float r_circle = strtof(cont, &cont);
            if(r_circle >= 0){
                circle->r = r_circle;


            }
            else{
                return circle;
            }
            strcpy(circle->units, units(cont));
        }
        else
        {
            insertBack(circle->otherAttributes, otherAtr(attr)); //for getting other attributes of circles
        }
    }
    return circle;
}

Path *pathFunc(xmlNode *path_node)
{

    Path *pa = NULL;
  
    for (xmlAttr *attr = path_node->properties; attr != NULL; attr = attr->next)
    {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);
        if (strcmp(attrName, "d") == 0)  //if there is data in path
        {
            pa = (Path *)malloc(sizeof(Path) + strlen(cont) + 1);  //malloc when there is data in path
            pa->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
            //insertBack(pa->otherAttributes,"");
            strcpy(pa->data,"");
            strcpy(pa->data, cont);
       
        }
        
        else
        {

            insertBack(pa->otherAttributes, otherAtr(attr));  //for other attributes in path
        }
    }
    return pa;
}

Group *group_func(xmlNode *group_node)
{

    Group *group = (Group *)malloc(sizeof(Group));
   
    // initilizing all the lists for storing data
    
    group->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    group->circles = initializeList(circleToString, deleteCircle, compareCircles);
    group->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    group->paths = initializeList(pathToString, deletePath, comparePaths);
    group->groups = initializeList(groupToString, deleteGroup, compareGroups);

    for (xmlAttr *attr = group_node->properties; attr != NULL; attr = attr->next)
    {
        insertBack(group->otherAttributes,otherAtr(attr));
    }
    for (xmlNode *cur = group_node->children; cur != NULL; cur = cur->next)
    {
        if (strcmp((char *)cur->name, "circle") == 0)
        {
            Circle *group_cir = circleFunc(cur);  
            insertBack(group->circles, group_cir); //circles in group
            
        }
        else if (strcmp((char *)cur->name, "path") == 0)
        {
            Path *group_path = pathFunc(cur);
            insertBack(group->paths, group_path); //path in group
        }
        else if (strcmp((char *)cur->name, "rect")==0){
            Rectangle *group_rect = rectFunc(cur);
            insertBack(group->rectangles,group_rect); //rectangel in group
        }
        else if (strcmp((char *)cur->name, "g")==0){
            Group *group_group = group_func(cur);
            insertBack(group->groups,group_group);//group in group
        }

    }
    return group;

}




/************* M2 ***************/

void  gethelpher(Group* tmp,List* list){  //for groups in group
    void * elem;
    
    insertBack(list,(void *)tmp);
  
    ListIterator iter = createIterator(tmp->groups);
    while ((elem = nextElement(&iter)) != NULL){
        Group* tmpName = (Group*)elem;

        gethelpher(tmpName,list);
    }

}
