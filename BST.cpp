#include "BST.h"

int BST::getHeight(Node* helproot){ // usage in getBalanceFactor to find heights
    if (helproot == nullptr){
        return -1;
    }
    int leftHeight = getHeight(helproot->left);
    int rightHeight = getHeight(helproot->right);
    return std::max(leftHeight, rightHeight) + 1;
}

int BST::getBalanceFactor(Node* helproot){ // gets balance factor for helperInsert
    int leftHeight;
    int rightHeight;
    if (helproot == nullptr){
        return 0;
    }
    leftHeight = getHeight(helproot->left);
    rightHeight = getHeight(helproot->right);
    return (leftHeight - rightHeight);
}

BST::Node* BST::rotateLeft(Node* helproot){
    Node* temp = helproot->right;
    Node* var = temp->left;

    temp->left = helproot;
    helproot->right = var;

    // helproot->height = 1 + std::max(helproot->left->height, helproot->right->height);
    // temp->height = 1 + std::max(temp->left->height, temp->right->height);

    return temp;
}

BST::Node* BST::rotateRight(Node* helproot){ // same as left but opposites
    Node* temp = helproot->left;
    Node* var = temp->right;

    temp->right = helproot;
    helproot->left = var;

    // helproot->height = 1 + std::max(helproot->left->height, helproot->right->height);
    // temp->height = 1 + std::max(temp->left->height, temp->right->height);

    return temp;
}

BST::Node* BST::rotateLeftRight(Node* helproot){
    helproot->left = rotateLeft(helproot->left);
    return rotateRight(helproot);
}

BST::Node* BST::rotateRightLeft(Node* helproot){
    helproot->right = rotateRight(helproot->right);
    return rotateLeft(helproot);
}

bool BST::checkIfIDExists(Node* helproot, int &id){ // do not put more than one of the same UFID in the tree
    if (helproot == nullptr){
        return false;
    }
    if (id == helproot->ufid){
        return true;
    }
    else if (id < helproot->ufid)
    {
        return checkIfIDExists(helproot->left, id);
    }
    else{
        return checkIfIDExists(helproot->right, id);
    }
}

bool BST::checkIfNameExists(Node* helproot, std::string &name){
    if (helproot == nullptr){
        return false;
    }
    if (name == helproot->name){
        return true;
    }
    else if (name < helproot->name)
    {
        return checkIfNameExists(helproot->left, name);
    }
    else{
        return checkIfNameExists(helproot->right, name);
    }
}

BST::Node* BST::helperInsert(BST::Node* helpRoot, int &id, std::string &name){
    if (helpRoot == nullptr){
        return new Node(id, name);
    }
    else if (id < helpRoot->ufid){
        helpRoot->left = helperInsert(helpRoot->left, id, name);
    }
    else {
        helpRoot->right = helperInsert(helpRoot->right, id, name);
    }
    
    // balance factor and balancing tree
    balancefactor = getBalanceFactor(helpRoot);
    // std::cout << "The balance factor currently is: " << balancefactor << std::endl;

    if (balancefactor > 1 && id < helpRoot->left->ufid){
        // right rotate
        // std::cout << "Does a right rotate\n";
        return rotateRight(helpRoot);
    }
    if (balancefactor < -1 && id > helpRoot->right->ufid){
        // left rotate
        // std::cout << "Does a left rotate\n";
        return rotateLeft(helpRoot);
    }
    if (balancefactor > 1 && id < helpRoot->left->ufid){
        // left rotate then right rotate
        // std::cout << "Does a Left Right rotate\n";
        return rotateLeftRight(helpRoot);
    }
    if (balancefactor < -1 && id < helpRoot->right->ufid){
        // right rotate then left rotate
        // std::cout << "Does a Right Left rotate\n";
        return rotateRightLeft(helpRoot);
    }
    return helpRoot;
}

void BST::helperInorder(BST::Node* helpRoot, bool &comma){ // Left Node Right
    if (helpRoot == NULL){
        std::cout << "";
    }
    else{
        helperInorder(helpRoot->left, comma);
        if (!comma) // no comma at end of std::cout line
        {
            std::cout << ", ";
        }
        else{
            comma = false;
        }
        std::cout << helpRoot->name;
        helperInorder(helpRoot->right, comma);
    }
}

BST::Node* BST::helperremove(Node* helproot, int &id){
    if (helproot == nullptr){
        std::cout << "unsuccessful\n";
        return nullptr;
    }
    // go to node to be deleted
    if (id < helproot->ufid){
        helproot->left = helperremove(helproot->left, id);
        return helproot;
    }
    else if (id > helproot->ufid){
        helproot->right = helperremove(helproot->right, id);
        return helproot;
    }
    else{
        // one child right
        if (helproot->left == nullptr){
            Node* temp = helproot->right;
            delete helproot;
            std::cout << "successful\n";
            return temp;
        }
        // one child left
        else if (helproot->right == nullptr){
            Node* temp = helproot->left;
            delete helproot;
            std::cout << "successful\n";
            return temp;
        }
        else{ // two children must find successor
            Node* localroot = helproot;
            Node* successor = helproot->right;
            while (successor->left != nullptr){ // move pointer all the way to find the left most node in the right subtree
                localroot = successor;
                successor = successor->left;
            }
            if (localroot != helproot){ // reassigning pointer values
                localroot->left = successor->right; 
            }
            else{
                localroot->right = successor->right;
            }
            helproot->ufid = successor->ufid;
            helproot->name = successor->name;
            delete successor;
            std::cout << "successful\n";
            return helproot;
        }
    }

}

BST::Node* BST::helpersearchID(Node* helpRoot, int &ID){
    if (helpRoot == nullptr){
        return nullptr;
    }
    
    if (ID < helpRoot->ufid)
    {
        helpersearchID(helpRoot->left, ID);
    }
    else if (ID > helpRoot->ufid)
    {
        helpersearchID(helpRoot->right, ID);
    }
    else{
        return helpRoot;
    }
}

// BST::Node* BST::helpersearchNAME(Node* helpRoot, std::string &name){
// // DO a full traversal to find the name
// // then print out the IDs of anyone who has that name (FIX ME)
//     if (helpRoot == nullptr)
//     {
//         return nullptr;
//     }
//     else{
//         if (helpersearchNAME(helpRoot->left, name) != nullptr){
//             return helpersearchNAME(helpRoot->left, name);
//         }
//         else if (helpRoot->name == name)
//         {
//             return helpRoot;
//         }
        
//         else if (helpersearchNAME(helpRoot->right, name) != nullptr)
//         {
//             return helpersearchNAME(helpRoot->right, name);
//         }
//     }
// }

void BST::newsearchNAME(Node* helproot, std::string &name){
    if (helproot == nullptr){
        return;
    }
    else{
        newsearchNAME(helproot->left, name);
        if (helproot->name == name){
            std::cout << helproot->ufid << std::endl;
        }
        newsearchNAME(helproot->right, name);
    }
}

void BST::helperPreorder(BST::Node* helpRoot, bool &comma){ //Node Left Right
    if (helpRoot == NULL){
        std::cout << "";
    }
    else{
        if (!comma)
        {
            std::cout << ", ";
        }
        else{
            comma = false;
        }
        std::cout << helpRoot->name;
        helperPreorder(helpRoot->left, comma);
        helperPreorder(helpRoot->right, comma);
    }
}

void BST::helperPostOrder(BST::Node* helpRoot, bool &comma){ // Left Right Node
    if (helpRoot == NULL){
        std::cout << "";
    }
    else {
        helperPostOrder(helpRoot->left, comma);
        helperPostOrder(helpRoot->right, comma);
        if (!comma)
        {
            std::cout << ", ";
        }
        else{
            comma = false;
        }
        std::cout << helpRoot->name;
    }
}

int BST::helperprintLevelCount(Node* helproot){
    if (helproot == nullptr){
        return 0;
    }
    return std::max(helperprintLevelCount(helproot->left), helperprintLevelCount(helproot->right)) + 1;
}

void BST::inorderTraversal(Node* helproot, std::vector<Node*> &nodesInorder){
    // make vector and add node to it
    if (helproot == nullptr){
        return;
    }
    inorderTraversal(helproot->left, nodesInorder);
    nodesInorder.push_back(helproot);
    inorderTraversal(helproot->right, nodesInorder);
}

BST::Node* BST::helperremoveInorder(Node* helproot, int &n){ // inorder LNR
    // make a vector that places all nodes in list inorderwise
    // then remove that node that that location
    if (helproot == nullptr){
        return nullptr;
    }
    // vector to be added to
    std::vector<Node*> nodesInorder;
    inorderTraversal(helproot, nodesInorder);
    // std::cout << "Should be removed: " << nodesInorder[n]->ufid << std::endl;
    Node* temp = helperremove(this->root, nodesInorder[n]->ufid);
    return temp;
    
}


// public functions
void BST::insert(int id, std::string name){
    if (checkIfIDExists(this->root, id) == true)
    {
        std::cout << "unsuccessful\n";
    }
    else{
        this->root = helperInsert(this->root, id, name);
        if (this->root != nullptr)
        {
            std::cout << "successful\n";
        }
        else{
            std::cout << "unsuccessful\n";
        }
    }
}
void BST::remove(int id){
    BST::Node* temp;
    temp = helperremove(this->root, id);
}
void BST::searchID(int id){
    BST::Node* temp;
    temp = helpersearchID(this->root, id);
    if (temp != nullptr){
        std::cout << temp->name << std::endl;
    }
    else{
        std::cout << "unsuccessful\n";
    }
    
}

void BST::searchNAME(std::string name){
    if (checkIfNameExists(this->root, name))
    {
        newsearchNAME(this->root, name);
    }
    else{
        std::cout << "unsuccessful\n";
        return;
    }
    
}


void BST::inorder(){
    bool comma = true;
    helperInorder(this->root, comma);
    std::cout << std::endl;
}
void BST::preorder(){
    bool comma = true;
    helperPreorder(this->root, comma);
    std::cout << std::endl;
}
void BST::postorder(){
    bool comma = true;
    helperPostOrder(this->root, comma);
    std::cout << std::endl;
}
void BST::printlevelcount(){
    int value = helperprintLevelCount(this->root);
    std::cout << value << std::endl;
}

void BST::removeInorder(int n){
    Node* temp;
    temp = helperremoveInorder(this->root, n);
}