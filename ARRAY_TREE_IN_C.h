#ifndef ARRAY_IN_C_H
#define ARRAY_IN_C_H

#include <stdlib.h>

///////////////////////
typedef struct NodeList NodeList;
typedef struct Node Node;
//typedef struct Vec2 Vec2;
typedef struct NodeArray NodeArray;

int getNodeIndexInArray(NodeArray* na, Node* n);
void printMatrix(Node* n );

//struct Vec2{
//    int x, y;
//};

struct Node{
//    int matrix[3][3];
//    bool active;
//    int distFim; //inicia com -1
//    int distCusto;
    NodeList * nodeListMainParent;
    NodeArray * childs;
};

struct NodeList{
    NodeArray * mainArray; // main linked list
    NodeList * nextNode;
    NodeList * prevNode;
    Node * node;
};

struct NodeArray{
    Node* mainNode;
    NodeList* head;
    NodeList* tail;
    int size;
};

///
/// \brief createNodeList Cria um objeto nodeList.
/// \return
///
NodeList* createNodeList()
{
    NodeList* p = (NodeList*) malloc(sizeof(NodeList));
    p->mainArray = NULL;
    p->nextNode = NULL;
    p->prevNode = NULL;
    p->node = NULL;
    return p;
}

///
/// \brief CreateNode Cria o objeto node
/// \return
///
Node* CreateNode()
{
    Node* n = (Node*) malloc(sizeof(Node));

//    n->active = true;
//    n->distFim = -1;
//    n->distCusto = 0;
    n->nodeListMainParent = NULL;
    n->childs = NULL;

    return n;
}

///
/// \brief createNodeArray Cria o objeto node array
/// \return
///
NodeArray* createNodeArray()
{
    NodeArray* nA = (NodeArray*) malloc(sizeof(NodeArray));
    nA->head = NULL;
    nA->tail = NULL;
    nA->mainNode = NULL;
    nA->size = 0;

    return nA;
}

///
/// \brief void_push esta funcao faz o push simples de um node para um array,
/// \brief porém, não alterará o nodeList parent do node.
/// \param nodeArray
/// \param node_
///
void void_push(NodeArray* nodeArray, Node* node_)
{
    NodeList* nl = createNodeList();
    nl->node = node_;

    if(nodeArray == NULL)
    {
        nodeArray = createNodeArray();
    }

    nl->mainArray = nodeArray;

    if(nodeArray->head == NULL)
    {
        nodeArray->head = nl;
        nodeArray->tail = nl;
    }
    else
    {
        NodeList* tmpNodeList = nodeArray->tail;
        nodeArray->tail = nl;
        tmpNodeList->nextNode = nl;
        nl->prevNode = tmpNodeList;
    }
    nodeArray->size += 1;
}

///
/// \brief push Esta função faz o push de um node para um array.
/// \param nodeArray
/// \param node_
///
void push(NodeArray* nodeArray, Node* node_)
{

    NodeList* nl = createNodeList();
    nl->node = node_;
    node_->nodeListMainParent = nl;

    if(nodeArray == NULL)
    {
        nodeArray = createNodeArray();
    }

    nl->mainArray = nodeArray;

    if(nodeArray->head == NULL || nodeArray == NULL)
    {
        nodeArray->head = nl;
        nodeArray->tail = nl;
    }
    else
    {
        NodeList* tmpNodeList = nodeArray->tail;
        nodeArray->tail = nl;
        tmpNodeList->nextNode = nl;
        nl->prevNode = tmpNodeList;
    }
    //nodeArray->size += 1;
}

///
/// \brief getNodeAt Esta função retorna o node na posição indicada do array
/// \param array
/// \param index
/// \return
///
Node* getNodeAt(NodeArray* array, int index)
{
//    if(index <= 0)
//        exit(14);

    NodeList* tmp = array->head;

    for(int i = 0; i < index; i++)
    {
        tmp = tmp->nextNode;
    }
    return tmp->node;
}

///
/// \brief getNodeListAt Esta função retorna o nodeList (controlador do array de node)
/// \param array
/// \param index
/// \return
///
NodeList* getNodeListAt(NodeArray* array, int index)
{
//    if(index <= 0)
//        exit(14);

    NodeList* tmp = array->head;

    for(int i = 0; i < index; i++)
    {
        tmp = tmp->nextNode;
    }
    return tmp;
}

///
/// \brief removeAt remove o arraylist, concerta a continuidade da array e retorna o ponteiro para NodeList, podendo trata-lo, ou deleta-lo
/// \param nArr
/// \param index
/// \return
///
NodeList* removeAt(NodeArray* nArr, int index)
{
    Node* delIt = getNodeAt(nArr, index);
    NodeList* delNl = delIt->nodeListMainParent;
    NodeList* delNl_left = delNl->prevNode;
    NodeList* delNl_right = delNl->nextNode;

    if(delNl_left == NULL)
    {
        delNl_right->prevNode = NULL;
        nArr->head = delNl->nextNode;
    }
    else if(delNl_right == NULL)
    {
        delNl_left->nextNode = NULL;
        nArr->tail = delNl->prevNode;
    }
    else
    {
        delNl_right->prevNode = delNl->prevNode;
        delNl_left->nextNode = delNl->nextNode;

    }

    delNl->prevNode = NULL;
    delNl->nextNode = NULL;
    nArr->size -= 1;

    return delNl;
}

///
/// \brief removeNodeFromArray Remove o node do array, e retorna
/// \brief o nodelist deste node, para então deleta-lo ou realoca-lo.
/// \param nn node
/// \return
///
NodeList* removeNodeFromArray(Node* nn)
{
    Node* delIt = nn;
    NodeList* delNl = delIt->nodeListMainParent;
    NodeList* delNl_left;
    NodeList* delNl_right;

    NodeArray* nArr = delNl->mainArray;

    if(delNl->prevNode == NULL)
    {
        delNl_right = NULL;
    }
    else
        delNl_right = delNl->prevNode;

    if(delNl->nextNode == NULL)
    {
        delNl_left = NULL;
    }
    else
        delNl_left = delNl->nextNode;

    if(delNl_right != NULL)
    {
        if(delNl_left != NULL)
            delNl_right->prevNode = delNl_left;
        else
            delNl_right->prevNode = NULL;
    }

    if(delNl_left != NULL)
    {
        if(delNl_right != NULL)
            delNl_left->prevNode = delNl_right;
        else
            delNl_left->prevNode = NULL;
    }

    delNl->prevNode = NULL;
    delNl->nextNode = NULL;
    delNl->mainArray = NULL;
    nArr->size -= 1;

    return delNl;
}

///
/// \brief getHeadNodeOfArray retorna o Node principal, pai da array de nodes que
/// \brief contém o node passado como parâmetro.
/// \param node
/// \return
///
Node* getHeadNodeOfArray(Node* node)
{
    Node* p = node->nodeListMainParent->mainArray->head->node;
    return p;

}


///
/// \brief voidRemoveNodeFromArray remove o node de um array, sem alterar o array pai do nodeList
/// \param nn node
/// \param nA nodeArray
/// \return
///
NodeList* voidRemoveNodeFromArray(Node* nn, NodeArray* nA)
{

    Node* delIt = nn;
    NodeList* delNl = delIt->nodeListMainParent;
    NodeList* delNl_left;
    NodeList* delNl_right;


    if(delNl->prevNode == NULL)
    {
        delNl_right = NULL;
    }
    else
        delNl_right = delNl->prevNode;

    if(delNl->nextNode == NULL)
    {
        delNl_left = NULL;
    }
    else
        delNl_left = delNl->nextNode;

    if(delNl_right != NULL)
    {
        if(delNl_left != NULL)
            delNl_right->prevNode = delNl_left;
        else
            delNl_right->prevNode = NULL;
    }

    if(delNl_left != NULL)
    {
        if(delNl_right != NULL)
            delNl_left->prevNode = delNl_right;
        else
            delNl_left->prevNode = NULL;
    }

    delNl->prevNode = NULL;
    delNl->nextNode = NULL;
    // FIX to see if nodeList will keep with own main array variable
//    delNl->mainArray = NULL;

    nA->size--;

    return delNl;
}

///
/// \brief deleteChildsFromNode isto vai deletar todos os childs de childs de uma array
/// \param node
///
void deleteChildsFromNode(Node* node)
{
    for( int i = 0; i < node->childs->size; i++ )
    {

        Node* n = node->childs->head->node;

        if(n != NULL)
            deleteChildsFromNode(n);

        NodeList* nl = removeNodeFromArray(node);

        free( nl->node );
        free( nl );


    }
    node->childs = NULL;
}

///
/// \brief deleteNodesFromArray isto vai deletar apenas os nodes do nodeArray, sem deletar seus filhos.
/// \param nA
///
void deleteNodesFromArray(NodeArray* nA)
{


    for( int i = 0; i < nA->size; i++ )
    {

        Node* n = nA->head->node;

        if((n != NULL))
        {
            if(n->childs->size > 0 )
            {
                for( int i = 0; i < n->childs->size; i++ )
                {
                    Node* nn = n->childs->head->node;
                    if(nn != NULL)
                        deleteChildsFromNode(n);


                }

            }
        }

        NodeList* nl = removeNodeFromArray(n);
        free(nl->node);
        free(nl);
    }
    NodeArray* pn = nA; //reseta o nodeArray
    nA = createNodeArray(); //nao sei se isto funcionará
    free(pn);
}

#endif // ARRAY_IN_C_H
