/*
 
NAME - MANJOT SINGH
STUDENT ID - 1141657

*/

#include "SVGHelpers.h"


char *attributeToString(void *data)
{
    char *tmpStr;
    Attribute *atr;
    int len;

    if (data == NULL)
    {
        return NULL;
    }

    atr = (Attribute *)data;

    len = strlen(atr->name) + strlen(atr->value) + strlen(" : ") + 1; 

    tmpStr = (char *)malloc(sizeof(char) * len);

    sprintf(tmpStr, "%s : %s", atr->name, atr->value); //storing data of othersttributes in tmpStr

    return tmpStr;
}
void deleteAttribute(void *data)
{

    Attribute *tmpName;

    if (data == NULL)
    {
        return;
    }

    tmpName = (Attribute *)data;

    free(tmpName->name);          //freeing to prevent memory leaks
    free(tmpName);
}
int compareAttributes(const void *first, const void *second)
{
    return 0;
}

void deleteRectangle(void *data)
{
    Rectangle *tmpName;

    if (data == NULL)
    {
        return;
    }

    tmpName = (Rectangle *)data;

    freeList(tmpName->otherAttributes);   //freeing to prevent memory leaks
    free(tmpName);
}

char *rectangleToString(void *data)
{

    Rectangle *rect;

    rect = (Rectangle *)data;

    char *tmpStr;
    int len;
    if (data == NULL)
    {
        return NULL;
    }
    char *pp = toString(rect->otherAttributes);
    len = strlen(pp) + strlen(rect->units) + strlen("x: \ny: \nwidth: \nheight: \nunits: \nAttributes: \n") + 81;
    tmpStr = (char *)malloc(sizeof(char) * len);

    sprintf(tmpStr, "x: %f\ny: %f\nwidth: %f\nheight: %f\nunits: %s\nAttributes:%s\n", rect->x, rect->y, rect->width, rect->height, rect->units, pp);
    //storing data of rectangles in tmpStr
    free(pp);

    return tmpStr;
}
int compareRectangles(const void *first, const void *second)
{
    return 0;
}

void deleteCircle(void *data)
{
    Circle *tmpName;

    if (data == NULL)
    {
        return;
    }

    tmpName = (Circle *)data;

    
    freeList(tmpName->otherAttributes); //freeing to prevent memory leaks
    free(tmpName);
}
char *circleToString(void *data)
{
    Circle *cir;

    cir = (Circle *)data;

    char *tmpStr;
    int len;
    if (data == NULL)
    {
        return NULL;
    }
    char *pp = toString(cir->otherAttributes);
    len = strlen(pp) + strlen(cir->units) + strlen("cx : \ncy : \nr : \nunits : \nAttributes :") + 61;
    tmpStr = (char *)malloc(sizeof(char) * len);

    sprintf(tmpStr, "cx : %f\ncy : %f\nr : %f\nunits : %s\nAttributes :%s", cir->cx, cir->cy, cir->r, cir->units, pp); //storing data of circles in tmpStr

    free(pp);

    return tmpStr;
}
int compareCircles(const void *first, const void *second)
{
    return 0;
}

void deletePath(void *data)
{
    Path *tmpName;

    if (data == NULL)
    {
        return;
    }

    tmpName = (Path *)data;

    freeList(tmpName->otherAttributes);  //freeing for no memory leaks
    free(tmpName);
}
char *pathToString(void *data)
{

    char *tmpStr;
    Path *pa;
    int len;

    if (data == NULL)
    {
        return NULL;
    }

    pa = (Path *)data;
    char *pp = toString(pa->otherAttributes);

    len = strlen(pp) + strlen(pa->data) + strlen("d=\n") + 1;

    tmpStr = (char *)malloc(sizeof(char) * len);

    sprintf(tmpStr, "d=%s%s\n", pa->data, pp);//storing data of paths in tmpStr

    free(pp);

    return tmpStr;
}
int comparePaths(const void *first, const void *second)
{
    return 0;
}

void deleteGroup(void *data)
{

    Group *tmpName;

    if (data == NULL)
    {
        return;
    }

    tmpName = (Group *)data;

    freeList(tmpName->circles);  //freeing all for no memory leaks
    freeList(tmpName->rectangles);
    freeList(tmpName->paths);
    freeList(tmpName->groups);
    freeList(tmpName->otherAttributes);

    free(tmpName);
}
char *groupToString(void *data){

    char* tmpStr;
	Group* group;
	int len;
	
	if (data == NULL){
		return NULL;
	}
	
	group = (Group*)data;
    char* pp=toString(group->circles);
    char *pp2=toString(group->paths);
    char *pp3=toString(group->rectangles);
    char *pp4=toString(group->otherAttributes);
    char *pp5=toString(group->groups);

	len=strlen(pp) + strlen(pp2)+strlen(pp3)+strlen(pp4)+strlen(pp5)+strlen("Circle: \nPath: \nRectangle: \nother Attribute\nGrrp:\n")+1;

	tmpStr = (char*)malloc(sizeof(char)*len);
	
	sprintf(tmpStr, "Circle: %s\nPath: %s\nRectangle: %s\nother Attribute%s\nGrrp:%s\n",pp,pp2,pp3,pp4,pp5); //storing data of groups in tmpStr

    free(pp);
    free(pp2);
    free(pp3);
	free(pp4);
    free(pp5);

	return tmpStr; 

}
int compareGroups(const void *first, const void *second)
{
    return 0;
}




SVG *createSVG(const char *fileName)
{

    if (fileName == NULL)   //if filename is not provided
    {
        return NULL;
        
    }


    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION

    SVG *svg = (SVG *)malloc(sizeof(SVG));

    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL)  //if file is empty or corrupted
    {
        
        return NULL;
    }

    root_element = xmlDocGetRootElement(doc);

    svg->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes); //list for otherattributes
    strcpy(svg->namespace, "");
    strcpy(svg->title, "");
    strcpy(svg->description, "");
    strcpy(svg->namespace, (char *)root_element->ns->href); //getting namespace from svg file

    svg->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    svg->circles = initializeList(circleToString, deleteCircle, compareCircles);
    svg->paths = initializeList(pathToString, deletePath, comparePaths);
    svg->groups = initializeList(groupToString, deleteGroup, compareGroups);
    
    for (xmlNode *cur_node = root_element->children; cur_node != NULL; cur_node = cur_node->next)
    {
        

        if (strcmp((char *)cur_node->name, "title") == 0)
        {
            xmlNode *child = cur_node->children;
            if (child->content != NULL)
            {
                strcpy(svg->title, (char *)child->content); //getting title from svg file
            }
        }
        if (strcmp((char *)cur_node->name, "desc") == 0)
        {
            xmlNode *child = cur_node->children;
            if (child->content != NULL)
            {
                strcpy(svg->description, (char *)child->content); //getting description from svg file
            }
        }
        if (strcmp((char *)cur_node->name, "rect") == 0)
        {

            Rectangle *store_r = rectFunc(cur_node);  //for parsing rects from svg
            insertBack(svg->rectangles, store_r);
        }
        if (strcmp((char *)cur_node->name, "circle") == 0)
        {

            Circle *store_C = circleFunc(cur_node); //for parsing circles from svg
            insertBack(svg->circles, store_C);
        }
        if (strcmp((char *)cur_node->name, "path") == 0)
        {

            Path *store_path = pathFunc(cur_node);  //for parsing paths from svg
            insertBack(svg->paths, store_path);
        }
        if (strcmp((char *)cur_node->name, "g") == 0)
        {
            Group *store_group = group_func(cur_node);  //for parsing groups from svg
            insertBack(svg->groups, store_group);
        }
    }
    for (xmlAttr *attr = root_element->properties; attr != NULL; attr = attr->next)
    {
        Attribute *store = otherAtr(attr);   //for parsing otherattributes from svg

        insertBack(svg->otherAttributes, store);
    }

    xmlFreeDoc(doc);

    xmlCleanupParser();

    return svg;
}

char *SVGToString(const SVG *img)
{
    char *pp = toString(img->otherAttributes);  // geeting all otherattributes after parsing
    char *pp2 = toString(img->rectangles);      // geeting all rectangles after parsing
    char *pp3 = toString(img->circles);         // geeting all circles after parsing
    char *pp4 = toString(img->paths);           // geeting all paths after parsing
    char *pp5 = toString(img->groups);          // geeting all groups after parsing

    int len = strlen(pp) + strlen(pp2) + strlen(pp3) + strlen(pp4) + strlen(pp5) +strlen(img->namespace) + strlen(img->description) + strlen(img->title) + strlen("namespace: \ntitle: \ndesc: \nAttributes: \n\nRectangle:\nCircle:\nPath:\nGroup\n") + 1;

    char *a = (char *)malloc(sizeof(char) * len);

    sprintf(a, "namespace: %s\ntitle: %s\ndesc: %s\nAttributes: %s\n\nRectangle:%s\nCircle:%s\nPath:%s\nGroup%s\n", img->namespace, img->title, img->description, pp, pp2, pp3, pp4,pp5);

    free(pp);   //freeing to prevent memory leaks
    free(pp2);
    free(pp3);
    free(pp4);
    free(pp5);

    return a;
}

void deleteSVG(SVG *img)
{
    if (img == NULL)
    {
        return;
    }

    clearList(img->otherAttributes);    //clearing all the lists to prevent memory leaks
    clearList(img->rectangles);
    clearList(img->circles);
    clearList(img->paths);
    clearList(img->groups);
    free(img->otherAttributes);    //freeing lists to prevent memory leaks
    free(img->rectangles);
    free(img->circles);
    free(img->paths);
    free(img->groups);
    free(img);
}

/* ********************************************   MODULE 2 ******************************** */


List* getGroups(const SVG* img){          //for storing all the groups inside a list
    if(img == NULL){
        return NULL;
    }
    
    void* elem;
    List *list = initializeList(groupToString,delete, compareGroups); //to store all data of groups

    ListIterator iter = createIterator(img->groups);
    while ((elem = nextElement(&iter)) != NULL){   //iterate till  groups are present
       

        gethelpher((Group *)elem,list);  //if groups are inside groups
    }
   

    return list;

}



List* getRects(const SVG* img){     //for storing all the rects inside a list
    if(img == NULL){
        return NULL;
    }

    
    void* elem;
    void* elem2;
    List *list = initializeList(rectangleToString,delete, compareRectangles); //to store all data of rects

    ListIterator iter = createIterator(img->rectangles);//iterate till  rects are present
    while ((elem = nextElement(&iter)) != NULL){
 

        
        insertBack(list,elem);  //storing data in list


    }
    List *group_rect= getGroups(img);
    ListIterator iter2 = createIterator(group_rect);  //for rects in groups
    while ((elem = nextElement(&iter2)) != NULL){

        Group *E_convert = (Group *)elem;
        ListIterator iter3 = createIterator(E_convert->rectangles); //iterate till rects in groups
        while((elem2 = nextElement(&iter3))){

            
            insertBack(list,elem2);  //storing data in list

        }
    }
    freeList(group_rect);
    return list;

}


List* getCircles(const SVG* img){   //for storing all the circles inside a list
    if(img == NULL){
        return NULL;
    }

    void* elem;
    void* elem2;
    List *list = initializeList(circleToString,delete, compareCircles); //to store all data of circles

    ListIterator iter = createIterator(img->circles);//iterate till  circles are present
    while ((elem = nextElement(&iter)) != NULL){

        insertBack(list,elem);//storing data in list

    }
    List *group_circle= getGroups(img);
    ListIterator iter2 = createIterator(group_circle);
    while ((elem = nextElement(&iter2)) != NULL){

        Group *E_convert = (Group *)elem;
        ListIterator iter3 = createIterator(E_convert->circles);//iterate till circles in groups
        while((elem2 = nextElement(&iter3))){

            insertBack(list,elem2);//storing data in list

        }
    }

    freeList(group_circle);
    return list;

}


List* getPaths(const SVG* img){   //for storing all the paths inside a list
    if(img == NULL){
        return NULL;
    }

    void* elem;
    void* elem2;
    List *list = initializeList(pathToString,delete, comparePaths);

    ListIterator iter = createIterator(img->paths);//iterate till paths in svgfile
    while ((elem = nextElement(&iter)) != NULL){
 
        insertBack(list,elem);//storing data in list

    }
    List *group_path= getGroups(img);
    ListIterator iter2 = createIterator(group_path);
    while ((elem = nextElement(&iter2)) != NULL){
    
        Group *E_convert = (Group *)elem;  //iterate till paths in groups
        ListIterator iter3 = createIterator(E_convert->paths);
        while((elem2 = nextElement(&iter3))){

            insertBack(list,elem2);//storing data in list

        }
    }
    freeList(group_path);
    return list;

}


int numRectsWithArea(const SVG* img, float area){
    if(img == NULL){
        return 0;
    }
    if(area <0){
        return 0;
    }

    List *rect_list = getRects(img);  //using getrects for getting all rectangels from svgfile
    void* elem;
    float wid=0;
    float height=0;
    int count =0;

    ListIterator iter = createIterator(rect_list);
    while ((elem = nextElement(&iter)) != NULL){


        Rectangle *rect = (Rectangle *)elem;
        wid=rect->width;

        height=rect->height;
        double multiply = wid*height;
        double result = ceil(multiply);

        if(result == area){         //if area is equal to calculated area of current rect
            count++;
        }
    }
    freeList(rect_list);

    return count;

}
int numCirclesWithArea(const SVG* img, float area){
    if(img == NULL){
        return 0;
    }
    if(area <0){
        return 0;
    }

    List *circle_list = getCircles(img);  //using getCircles for getting all circles from svgfile
    void* elem;

    float r=0;
    float multiply =0;
    int count =0;

    ListIterator iter = createIterator(circle_list);
    while ((elem = nextElement(&iter)) != NULL){

        Circle *circle = (Circle *)elem;
        
        r=circle->r;
        multiply =   3.1415926535 * (r * r);

        if(ceil(multiply) == ceil(area)){  //if area is equal to calculated area of current circle
            count++;
        }
    }
    freeList(circle_list);

    return count;

}

int numPathsWithdata(const SVG* img, const char* data){
    if(img == NULL){
        return 0;
    }
    if(data==NULL){
        return 0;
    }

    List *path_list = getPaths(img); //using getPaths for getting all Paths from svgfile

    void* elem;
    int count =0;

    ListIterator iter = createIterator(path_list);
    while ((elem = nextElement(&iter)) != NULL){

        Path *path = (Path *)elem;

        if(strcmp(path->data,data)==0){   //if data is equal
            count++;
        }
    

    }
    freeList(path_list);

    return count;

}

int numGroupsWithLen(const SVG* img, int len){
    if(img == NULL){
        return 0;
    }
    if(len<0){
        return 0;
    }
    List *group_list = getGroups(img);  //using getGroups for getting all groups from svgfile
    void* elem;
    int number=0;
    int count =0;

    ListIterator iter = createIterator(group_list);
    while ((elem = nextElement(&iter)) != NULL){


        Group *group = (Group *)elem;
        
        //using getlength for getting lenght of required attributes

        number = getLength(group->circles) + getLength(group->groups) + getLength(group->paths)+ getLength(group->rectangles);
        
        if(number == len){
            count++;
        }
    }
    freeList(group_list);

    return count;

}

int numAttr(const SVG* img){
    if(img == NULL){
        return 0;
    }
    void *elem;
    void *elem2;
    void *elem3;
    void *elem4;

    int total=0;    

    //Itterating data from all get functions to count number of otherattributes 

    total = getLength(img->otherAttributes);

    List *path= getPaths(img);
    ListIterator iter = createIterator(path);
    while ((elem = nextElement(&iter)) != NULL){
    
        Path *E_convert = (Path *)elem;
        total = total + getLength(E_convert->otherAttributes);
    }

    List *rect= getRects(img);
    ListIterator iter2 = createIterator(rect);
    while ((elem2 = nextElement(&iter2)) != NULL){
    
        Rectangle *E_convert = (Rectangle *)elem2;
        total = total + getLength(E_convert->otherAttributes);
       
    }

    List *circle= getCircles(img);
    ListIterator iter3 = createIterator(circle);
    while ((elem3 = nextElement(&iter3)) != NULL){
    
        Circle *E_convert = (Circle *)elem3;
        total = total + getLength(E_convert->otherAttributes);
    }

    List *group= getGroups(img);
    ListIterator iter4 = createIterator(group);
    while ((elem4 = nextElement(&iter4)) != NULL){
    
        Group *E_convert = (Group *)elem4;
        total = total + getLength(E_convert->otherAttributes);
    }

    freeList(path);
    freeList(rect);
    freeList(circle);
    freeList(group);

    return total;
}