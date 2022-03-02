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
    }
    for (xmlAttr *attr = path_node->properties; attr != NULL; attr = attr->next)
    {
    char *attrName = (char *)attr->name;
    if(strcmp(attrName, "d") != 0)
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






/*************************** A2 **********************/



bool checkSVG(xmlDoc* doc ,const char *xsd){
    if (doc == NULL || xsd ==NULL)     //checking 
    {
    return false;
    }
    //xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt1;
    ctxt1 = xmlSchemaNewParserCtxt(xsd);
    if(ctxt1 == NULL){
        return false;
    }
    schema = xmlSchemaParse(ctxt1);
    xmlSchemaFreeParserCtxt(ctxt1);
    if(schema == NULL){
        return false;
    }
    xmlSchemaValidCtxtPtr ctxt;
    int ret;
    ctxt = xmlSchemaNewValidCtxt(schema);
    if(ctxt == NULL){
        xmlSchemaFree(schema);
        xmlSchemaCleanupTypes();
        return false;
    }
    ret = xmlSchemaValidateDoc(ctxt, doc);
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(ctxt);
    xmlSchemaCleanupTypes();
    if (ret != 0)
    {
        return false;
    }
    return true;

}



xmlDoc * parseDoc(const SVG * img){

    //  make a tree xmlDoc * doc
    //  root_element ; fragment
    //  svg xmlnode of svg
    //  new namespace svgNode , 
    // (title , description xmlNewTextChild)
    // other attributes (properties) xmlattr
    //rect,circle,path,group
    xmlDocPtr doc = xmlNewDoc((xmlChar *)"1.0"); 
   xmlNodePtr frag = xmlNewDocFragment(doc);
    xmlNodePtr svg = xmlNewChild(frag,NULL,(xmlChar *)"svg",NULL);
   // xmlNode * svg = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, svg);
    xmlNsPtr ns = xmlNewNs(svg,(xmlChar *)img->namespace,NULL);
    xmlSetNs(svg,ns);


    if(strcmp(img->title,"") != 0){
    xmlNewTextChild(svg,NULL,(xmlChar *)"title",(const xmlChar *)img->title);
    }
    if(strcmp(img->description,"") != 0){

    xmlNewTextChild(svg,NULL,(xmlChar *)"desc",(const xmlChar *)img->description);
    }

   // xmlNodePtr rect = xmlNewChild(svg,NULL,(xmlChar *)"rect",(const xmlChar *)img->rectangles);
    parseAttr(svg,img->otherAttributes);
    parseRect(svg,img->rectangles);
    parseCircle(svg,img->circles);
    parsePath(svg,img->paths);
    parseGroup(svg,img->groups);
    xmlFreeNode(frag);
  
    return doc;


}





void  parseAttr(xmlNode * node,List * otherAtr){
    if(node == NULL || otherAtr == NULL){
        return ;
    }
    void * elem;
    ListIterator iter= createIterator(otherAtr);
    while((elem = nextElement(&iter))!=NULL){
        Attribute *atr = (Attribute *) elem;
        xmlNewProp(node,(const xmlChar *) atr->name,(const xmlChar *)atr->value);

    }
}

void parseRect(xmlNode * node,List * rect){
    if(node == NULL || rect == NULL){
        return;
    }
    void *elem;
    ListIterator iter= createIterator(rect);
    while((elem = nextElement(&iter))!=NULL){
        Rectangle *rectangle = (Rectangle *) elem;
        xmlNode * rectt= xmlNewChild(node,NULL,(xmlChar *)"rect",NULL);
        char floatConvert[10000];

        sprintf(floatConvert,"%.2f%s",rectangle->x,rectangle->units);
        xmlNewProp(rectt,(const xmlChar *) "x",(const xmlChar *)floatConvert);
        
        sprintf(floatConvert,"%.2f%s",rectangle->y,rectangle->units);
        xmlNewProp(rectt,(const xmlChar *) "y",(const xmlChar *)floatConvert);

        sprintf(floatConvert,"%.2f%s",rectangle->width,rectangle->units);
        xmlNewProp(rectt,(const xmlChar *) "width",(const xmlChar *)floatConvert);

        sprintf(floatConvert,"%.2f%s",rectangle->height,rectangle->units);
        xmlNewProp(rectt,(const xmlChar *) "height",(const xmlChar *)floatConvert);

        // xmlNewProp(rectt,(const xmlChar *) "units",(const xmlChar *)rectangle->units);

        parseAttr(rectt,rectangle->otherAttributes);
    }
}

void parseCircle(xmlNode * node,List * circ){
    if(node == NULL || circ == NULL){
        return;
    }
    void *elem;
    ListIterator iter= createIterator(circ);
    while((elem = nextElement(&iter))!=NULL){
        Circle *circle = (Circle *) elem;
        xmlNode * cir= xmlNewChild(node,NULL,(xmlChar *)"circle",NULL);
        char floatConvert[10000];

        sprintf(floatConvert,"%f%s",circle->cx,circle->units);
        xmlNewProp(cir,(const xmlChar *) "cx",(const xmlChar *)floatConvert);
        
        sprintf(floatConvert,"%f%s",circle->cy,circle->units);
        xmlNewProp(cir,(const xmlChar *) "cy",(const xmlChar *)floatConvert);

        sprintf(floatConvert,"%f%s",circle->r,circle->units);
        xmlNewProp(cir,(const xmlChar *) "r",(const xmlChar *)floatConvert);

       // xmlNewProp(cir,(const xmlChar *) "units",(const xmlChar *)circle->units);

        parseAttr(cir,circle->otherAttributes);
    }

}


void parsePath(xmlNode * node,List * pa){
    if(node == NULL || pa == NULL){
        return;
    }
    void *elem;
    ListIterator iter= createIterator(pa);
    while((elem = nextElement(&iter))!=NULL){
        Path *path = (Path *) elem;
        xmlNode * pathh= xmlNewChild(node,NULL,(xmlChar *)"path",NULL);

        xmlNewProp(pathh,(const xmlChar *) "d",(const xmlChar *)path->data);
        parseAttr(pathh,path->otherAttributes);
    }


}


void  parseGroup(xmlNode * node,List * g){
    if(node == NULL || g == NULL){
        return;
    }
    void *elem;
    ListIterator iter= createIterator(g);
    while((elem = nextElement(&iter))!=NULL){
        Group *group = (Group *) elem;
        xmlNode * grp = xmlNewChild(node,NULL,(xmlChar *)"g",NULL);
        parseRect(grp,group->rectangles);
        parseCircle(grp,group->circles);
        parsePath(grp,group->paths);
        parseAttr(grp,group->otherAttributes);
        parseGroup(grp,group->groups);
        

    }
}

void findAttr(List * list, Attribute* newAttribute){
    void *elem;
    ListIterator iter= createIterator(list);
    while((elem = nextElement(&iter))!=NULL){
        Attribute *atr = (Attribute *) elem;
        if(strcmp(atr->name,newAttribute->name)==0){
            strcpy(atr->value,newAttribute->value);
            free(newAttribute->name);          //freeing to prevent memory leaks
            free(newAttribute);
            return;
        }
    }
    insertBack(list,newAttribute);
}

bool checkatrbsdk(List * list){
    void *elem;
    ListIterator iter = createIterator(list);
    while((elem = nextElement(&iter)) != NULL) {
        Attribute *currAttr = (Attribute *)elem;
        if (currAttr -> name == NULL) {
            return false;
        }
    }
    return true;
}

bool checkRect(const SVG * img){

    void *elem;
    List *list = getRects(img);
    ListIterator iter = createIterator(list);

    while((elem = nextElement(&iter)) != NULL) {
        Rectangle *rect = (Rectangle *)elem;

        if (rect -> otherAttributes == NULL || rect -> width < 0 || rect -> height < 0) {
            freeList(list);
            return false;
        }
        bool a = checkatrbsdk(rect->otherAttributes);
        if(!a){
            freeList(list);
            return false;
        }
    }
    freeList(list);
    return true;
}


bool checkCirc(const SVG * img){
    List * list = getCircles(img);
    ListIterator iter = createIterator(list);
    void * elem;

    while((elem = nextElement(&iter)) != NULL) {
        Circle *circ = (Circle *)elem;

        if (circ -> otherAttributes == NULL || circ -> r < 0) {
            freeList(list);
            return false;
        }

        bool a = checkatrbsdk(circ->otherAttributes);
        if(!a){
            freeList(list);
            return false;
        }
    }
    freeList(list);
    return true;
}
bool checkPath(const SVG * img){

    List *list = getPaths(img);
    ListIterator iter = createIterator(list);
    void * elem;

    while((elem = nextElement(&iter)) != NULL) {
        Path *pa = (Path *)elem;

        if (pa -> otherAttributes == NULL || pa -> data == NULL) {
            freeList(list);
            return false;
        }
        bool a = checkatrbsdk(pa->otherAttributes);
        if(!a){
            freeList(list);
            return false;
        }
    
    }
    freeList(list);
    return true;
}

bool checkGroup(const SVG * img){
    List * list = getGroups(img);
    ListIterator iter = createIterator(list);
    void * elem;

    while((elem = nextElement(&iter)) != NULL) {
        Group *g = (Group *)elem;
        

        if (g -> rectangles == NULL || g -> circles == NULL || g -> paths == NULL
        || g -> groups == NULL || g -> otherAttributes == NULL) {
            freeList(list);
            return false;
        }
        
        bool a = checkatrbsdk(g->otherAttributes);
        if(!a){
            freeList(list);
            return false;
        }
    }


    freeList(list);
    return true;


}

