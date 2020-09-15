#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>



using namespace std;

int CharLineCompare (char left [257], char right [257]){
    int i = 0;
    while (i < 257 && (left[i] != '\0' && right[i] != '\0')){
        if (left[i] > right[i]){
            return 1;
        }
        if (left[i] < right[i]){
            return -1;
        }
        i++;
    }

    if ( left[i] != right[i] ){
        if (left[i] == '\0'){
            return -1;
        }
        return 1;
    }
    return 0;
}

class TTreeNode{

    public:
        unsigned long long key;
        char word[257];
        int ballance;
        int depth;
        TTreeNode* left;
        TTreeNode* right;
        TTreeNode* parent;

        TTreeNode (){
            this->key = 0;
            this->word[0] = '\0';
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->ballance = 0;
            this->depth = 0;
        }

        TTreeNode (unsigned long long inkey, char inword [257]){
            this->key = inkey;
            int i = 0;
            while (inword[i] != '\0'){
                this->word[i] = inword[i];
                ++ i;
            }
            this->word[i] = '\0';
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->ballance = 0;
            this->depth = 0;
        }

        TTreeNode (const TTreeNode& orig){
            this->key = orig.key;
            int i = 0;
            while (orig.word[i] != '\0'){
                this->word[i] = orig.word[i];
                ++ i;
            }
            this->word[i] = '\0';
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->ballance = 0;
            this->depth = 0;
        }

        int lDepth (){
            if (this->left != nullptr){
                return this->left->depth;
            }
            return 0;
        }

        int rDepth (){
            if (this->right != nullptr){
                return this->right->depth;
            }
            return 0;
        }

        bool Add (TTreeNode& innode){

            int cmpr = CharLineCompare(this->word, innode.word);

            if (cmpr < 0 && this->right != nullptr){
                //cout << "Going right" << endl;
                return this->right->Add(innode);
            }
            else if(cmpr > 0 && this->left != nullptr){
                //cout << "Going left" << endl;
                return this->left->Add(innode);
            }
            else  if (cmpr == 0){
                cout << "Exist" << endl;
                return true;
            }
            else{
                if (cmpr < 0){
                    //adding on the right
                //cout << "Adding right" << endl;

                this->right = new TTreeNode(innode);
                this->right->depth = 1;
                this->right->parent = this;
            }
            else{
                //adding on the left
               // cout << "Adding left :";
                this->left = new TTreeNode(innode);
                this->left->parent = this;
                this->left->depth = 1;
                //this->left->Print();
                //cout << endl;
            }
            }
            TTreeNode * found = this->parent;
            TTreeNode * parent = this->parent;
            this->depth = max(this->lDepth() + 1, this->rDepth() + 1 );

            while (parent != nullptr){
                parent->depth += 1 ;
                parent = parent->parent;
            }

            while (found != nullptr){
                found->ballance = found->lDepth() - found->rDepth();
                if (found->ballance == 0){
                    break;
                }
                if (found->ballance == 2 || found->ballance == -2){
                    found->ReBal();
                }
                found->depth = max(found->lDepth(),found->rDepth()) + 1;
                found = found->parent;
            }

            cout << "OK" << endl;
            //cout << "added a node: " << innode.key << endl;
            return true;
        }

        void ReBal(){
            //cout << "changing ballance" << endl;
            if (this == nullptr){
                return;
            }
            cout << "touching : ";
            this->Print();
            this->ballance = this->lDepth() - this->rDepth();
            if (this->ballance > 0){
                if (this->left->rDepth() > this->left->lDepth()){
                    this->left->RightSonTurn();
                }
                this->LeftSonTurn();
            }else {
                if (this->right->lDepth() > this->right->rDepth()){
                    this->right->LeftSonTurn();
                }
                this->RightSonTurn();
            }

            return;
        }

        void RightSonTurn(){
            TTreeNode* parent = this->parent;


            this->parent = this->right;
            cout << "rst: rson = ";
            this->right->Print();

            this->right->parent = parent;
            this->right = this->right->left;
            this->parent->left = this;
            this->depth = max(this->lDepth(), this->rDepth()) + 1;
            if (parent != nullptr){
                cout << "rst: parent = ";
                parent->Print();
                int cmpr = CharLineCompare(parent->word, this->word);
                if (cmpr > 0){
                    parent->left = this->parent;
                }
                else {
                    parent->right = this-> parent;
                }
                parent = this->parent;
                parent->depth = max(parent->lDepth(), parent->lDepth())+ 1;
                parent = parent->parent;
                parent->depth = max(parent->lDepth(), parent->lDepth())+ 1;
            }
            parent = this->parent;
            parent->depth = max(parent->lDepth(), parent->lDepth())+ 1;
            return;
        }

        void LeftSonTurn(){
            TTreeNode* parent = this->parent;
            this->parent = this->left;
            cout << "lst: lson = ";
            this->left->Print();
            this->parent->parent = parent;
            this->left = this->left->right;;
            this->parent->right = this;
            this->depth = max(this->lDepth(), this->rDepth()) + 1;
            if (parent != nullptr){
                cout << "lst: parent = ";
                parent->Print();
                int cmpr = CharLineCompare(parent->word, this->word);
                if (cmpr > 0){
                    parent->left = this->parent;
                }
                else {
                    parent->right = this-> parent;
                }
                parent = this->parent;
                parent->depth = max(parent->lDepth(), parent->lDepth())+ 1;
                parent = parent->parent;
                parent->depth = max(parent->lDepth(), parent->lDepth())+ 1;
            }
            parent = this->parent;
            parent->depth = max(parent->lDepth(), parent->lDepth())+ 1;
            return;
        }

        void Print (){
            int i = 0;
            while (this->word[i] != '\0'){
                cout << word[i];
                ++i;
            }
            cout << ' ' << this->key << endl;
            return;
        }

        void Delete (TTreeNode* innode){
            int cmpr = CharLineCompare(this->word, innode->word);
            if (cmpr > 0){
                //cout << "Going left" << endl;
                return this->left->Delete(innode);
            }
            else if (cmpr < 0){
                 //cout << "Going right" << endl;
                return this->right->Delete(innode);
            }
            else {
                cmpr = CharLineCompare(parent->word, this->word);
                TTreeNode* parent, * replacer;
                parent = this->parent;
                replacer = this->right;
                if (!replacer){
                    //cout << "There is no right son for the target!" << endl;
                    if (cmpr > 0){
                        parent->left = this->left;
                    }
                    else {
                        parent->right = this->left;
                    }

                    if (this->left){
                            this->left->parent = this->parent;
                    }
                    parent->depth --;

                    while (parent != nullptr){
                        parent->ballance = parent->lDepth() - parent->rDepth();
                        if (parent->ballance == 0){
                            break;
                        }
                        if (parent->ballance == 2 || parent->ballance == -2){
                            parent->ReBal();
                        }
                        parent->depth = max(parent->lDepth(),parent->rDepth()) + 1;
                        parent = parent->parent;
                    }
                    return;
                }

                if (replacer->left){
                    cout << "Replacer has a left son" << endl;
                    while (replacer->left != nullptr){
                        replacer = replacer->left;
                    }
                    cout << "got max left" << endl;
                    replacer->parent->left = replacer->right;
                    if (replacer->right){
                        replacer->right->parent = replacer->parent;
                    }
                    cout << "excluded replacer from chain" << endl;

                    replacer->parent->depth = max(replacer->parent->lDepth(), replacer->parent->rDepth()) + 1;
                    TTreeNode* tempor = replacer->parent;
                    cout << "rebalancing the tree" << endl;
                    while (tempor->parent != this){
                        tempor = tempor->parent;
                        tempor->depth = max(tempor->lDepth(), tempor->rDepth()) + 1;
                        tempor->ballance = tempor->lDepth() - tempor->rDepth();
                        if (tempor->ballance == 2 || tempor->ballance == -2){
                            tempor->ReBal();
                        }
                    }
                }
                else {
                    cout << "Replacer has no left son" << endl;
                    this->right = replacer->right;
                }

                if (cmpr > 0){
                    parent->left = replacer;
                }
                else{
                    parent->right = replacer;
                }

                cout << "including repl " << endl;
                replacer->parent = parent;
                this->right->Print();
                replacer->right = this->right;
                replacer->right->Print();
                this->right->Print();
                if (this->right){
                    this->right->parent = replacer;
                }
                replacer->left = this->left;
                if (this->left){
                    this->left->parent = replacer;
                }

                cout << "checking ballance of replacer" << endl;
                replacer->depth = max(replacer->rDepth(), replacer->lDepth()) + 1;
                replacer->right->Print();
                this->right->Print();
                replacer->ballance = replacer->lDepth() - replacer->rDepth();
                if (replacer->ballance == 2 || replacer->ballance == -2){
                    replacer->ReBal();
                }

                cout << "rebalancing the tree" << endl;
                while(parent != nullptr){
                    parent->depth = max(parent->rDepth(), parent->lDepth()) + 1;
                    parent->ballance = parent->lDepth() - parent->rDepth();
                    if (parent->ballance == 2 || parent->ballance == -2){
                        parent->ReBal();
                    }
                    if (parent->ballance == 0){
                        break;
                    }
                    parent = parent->parent;
                }
                //cout << "Finished excluding" << endl;
            }

            return;
        }

        TTreeNode* Find(char inword [257]){
            int cmpr = CharLineCompare(this->word, inword);

            if (cmpr == 0){
                //cout << "OK: " << this->key << endl;
                return this;
            }
            if (cmpr > 0){
                if (this->left != nullptr){
                    return this->left->Find(inword);
                }
                else {
                    //cout << "NoSuchWord" << endl;
                    return nullptr;
                }
            }
            else {
                if (this->right != nullptr){
                    return this->right->Find(inword);
                }
                else {
                    //cout << "NoSuchWord" << endl;
                    return nullptr;
                }
            }
            return nullptr;
        }

        void PrintToFile (ofstream& writer){
            int children = 0;
            if (this->left){
                children += 2;
            }
            if (this->right){
                children += 1;
            }

            cout << "Writing : " << children << ' ' << this->key << endl;

            writer << children << ' ';

            int i = 0;
            while (this->word[i] != '\0'){
                writer << word[i];
                ++i;
            }
            writer << ' ' << this->key << ' ';

            if(this->left){
                this->left->PrintToFile(writer);
            }
            if(this->right){
                this->right->PrintToFile(writer);
            }
            return;
        }

        void PrintAll (int depth){
            if (this == nullptr){
                return;
            }
            int i = 0;
            this->right->PrintAll(depth + 1);
            while ( i < depth){
                cout << '\t';
                ++ i;
            }
            this->Print();
            this->left->PrintAll(depth + 1);
        }

        ~TTreeNode(){
            if (this->left){
                delete this->left;
            }
            if (this->right){
                delete this->right;
            }
        }
};

class TTree {
public:
    TTreeNode* root;

    TTree(){
        this->root = nullptr;
    }
};

TTreeNode* ReadFromFile(ifstream& reader){
            int children, i;
            unsigned long long key = 0;
            char word[257];
            char simbol;

            cout << "Starting reading" << endl;
            reader >> children;

            i = 0;
            reader >> simbol;
            cout << "Reading word" << endl;
            while (simbol >= 'a' && simbol <= 'z'){
                word[i] = simbol;
                ++i;
                reader >> simbol;
            }

            cout << "Reading key" << endl;
            reader >> key;
            reader >> simbol;

            //return nullptr;

            cout << "Creating node" << endl;
            TTreeNode* mynode = new TTreeNode(key, word);
            if (children - 2 >= 0){
                cout << "Adding left son" << endl;
                mynode->left = ReadFromFile(reader);
                if (mynode->left == nullptr){
                    return nullptr;
                }
                children -= 2;
            }
            if (children - 1 == 0){
                cout << "Adding right son" << endl;
                mynode->right = ReadFromFile(reader);
                if (mynode->right == nullptr){
                    return nullptr;
                }
            }
            return mynode;

        }

int main()
{
    TTreeNode* mytree = nullptr;

    unsigned long long readkey = 0;
    char buffer[257];
    int ch = getchar();
    int i = 0;

    while (ch != EOF){
        readkey = 0;


        if (ch == '+'){
            ch = getchar();
            while (ch == ' ' || ch == '\t'){
                ch = getchar();
            }

            i = 0;
            while ((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z')){
                buffer[i] = tolower(ch);
                i++;
                ch = getchar();
            }


            buffer[i]= '\0';

            while (ch == ' ' || ch == '\t'){
                ch = getchar();
            }

            i = 0;
            while (ch >= '0' && ch <= '9'){
                readkey = readkey * 10 + ch - '0';
                i++;
                ch = getchar();
            }
                TTreeNode newel = TTreeNode(readkey, buffer);
                //newel.Print();
                if (mytree == nullptr){
                    mytree = new TTreeNode(newel);
                    if (mytree == nullptr){
                        cout << "Error while adding a node" << endl;
                        return 0;
                    }
                    cout << "OK" << endl;
                }
                else {
                    mytree->Add(newel);
                    while (mytree->parent != nullptr){
                        mytree = mytree->parent;
                    }
                }
        }
        else if (ch == '-'){
            ch = getchar();
            while (ch == ' ' || ch == '\t'){
                ch = getchar();
            }


            i = 0;
            while ((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z')){
                buffer[i] = ch;
                i++;
                ch = getchar();
            }
            buffer[i]= '\0';
            TTreeNode* found = mytree->Find(buffer);
            if (!found){
                cout << "NoSuchWord" << endl;
            }
            else{
                if (mytree == found){
                    if (!mytree->right) {
                        mytree = mytree->left;
                        if (mytree){
                            mytree->parent = nullptr;
                        }
                        delete found;
                    }
                    else{
                        found = mytree->right;
                        if (!found->left){
                            found->left = mytree->left;
                            if (mytree->left){
                                mytree->left->parent = found;
                            }
                            found->depth = max(found->lDepth(), found->rDepth()) + 1;
                            found->ballance = found->lDepth() - found->rDepth();
                            if (found->ballance == 2 || found->ballance == -2){
                                found->ReBal();
                            }
                        }
                        else{
                            while (found->left != nullptr){
                                found = found->left;
                            }
                            TTreeNode* parent = found->parent;
                            parent->left = found->right;
                            if (found->right){
                                found->right->parent = parent;
                            }
                            parent->depth = max(parent->lDepth(), parent->rDepth()) + 1;
                            parent->ballance = parent->lDepth() - parent->rDepth();

                            while (parent->parent != mytree){
                                parent->depth = max(parent->lDepth(), parent->rDepth()) + 1;
                                parent->ballance = parent->lDepth() - parent->rDepth();
                                if (parent->ballance == 2 || parent->ballance == -2){
                                    parent->ReBal();
                                }
                                else if (parent->ballance == 0){
                                    break;
                                }
                            }

                            found->parent = nullptr;
                            found->right = mytree->right;
                            found->right->parent = found;
                            found->depth = max(found->lDepth(), found->rDepth()) + 1;
                            found->ballance = found->lDepth()- found->rDepth();
                            if (found->ballance == 2 || found->ballance == -2){
                                found->ReBal();
                            }
                            mytree->left = nullptr;
                            mytree->right = nullptr;
                            delete mytree;
                            mytree = found;
                        }
                    }
                    //deleting the root
                }
                else {
                    mytree->Delete(found);
                    found->left = nullptr;
                    found->right = nullptr;
                    delete found;

                }
                while (mytree->parent){
                    mytree = mytree->parent;
                }
                cout << "OK" << endl;
            }
        }
        else if ((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z')){
            i = 0;
            ch = tolower(ch);
            while ((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z')){
                buffer[i] = ch;
                i++;
                ch = getchar();
                tolower(ch);
            }
            buffer[i]= '\0';

            TTreeNode* found = mytree->Find(buffer);
            if (found){
                cout << "OK: " << found->key << endl;
            }else{
                cout << "NoSuchWord" << endl;
            }
        }
        else if (ch == '?'){
            mytree->PrintAll(0);
            ch = getchar();
        }
        else if (ch == '!'){
            //cout << "In special features." << endl;
            do{
                ch = getchar();
                //cout << "redaing separ" << endl;
            }while (ch == ' ' || ch == '\t');
            //ch = getchar();
            if (ch == 'S'){
                for (int i = 0; i < 3; i++){
                    ch = getchar();
                    //cout << "redaing SAVE" << endl;
                }
                do{
                    ch = getchar();
                    //cout << "redaing separ" << endl;
                }while (ch == ' ' || ch == '\t');
                int i = 0;
                char path [257];
                while(ch != '\n'){
                    path[i] = ch;
                    ++i;
                    ch = getchar();
                }
                path[i] = '\0';
                //cout << "Creating ofstream" << endl;
                ofstream writer;
                //cout << "Opening ofstram" << endl;
                writer.open(path);
                //cout << "Starting the print" << endl;
                mytree->PrintToFile(writer);
                writer.close();

                //Do something to save a tree in a file at /path
            }
            else {
                for (int i = 0; i < 3; i++){
                    ch = getchar();
                    //cout << "redaing SAVE" << endl;
                }
                do{
                    ch = getchar();
                    //cout << "redaing separ" << endl;
                }while (ch == ' ' || ch == '\t');
                int i = 0;
                char path [257];
                while(ch != '\n'){
                    path[i] = ch;
                    ++i;
                    ch = getchar();
                }
                path[i] = '\0';
                ifstream reader;
                reader.open(path);
                TTreeNode* newtree = ReadFromFile(reader);
                reader.close();
                if (newtree){
                    delete(mytree);
                    mytree = newtree;
                }
                else {
                    cout << "ERROR" << endl;
                }
                // Do something to load a file from
            }
        }

        while (ch == '\n'){
            ch = getchar();
        }
    }

    return 0;
}



/*
+ aaaaa 5
+ aaaa 4
+ aaaa 4
+ aaa 3
+ aa 2
+ aaaaa 5
+ a 1
*/


/*
+ b 2
+ g 7
+ j 10
+ m 13
+ e 5
+ a 1
+ h 8
+ l 12
+ c 3
! Save tree_sv.txt
*/
