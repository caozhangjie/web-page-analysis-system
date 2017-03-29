#ifndef EXPERIMENT_HTMLTAG_H
#define EXPERIMENT_HTMLTAG_H

#include "Vector.h"
#include "Stack.h"
#include "CharStringLink.h"

struct HtmlTag {
    int hash;
    CharString* data;
};

struct HtmlNode {
    HtmlTag tag;
    HtmlNode* parent;
    Vector<HtmlNode*> children;
};

struct HtmlListNode{
    HtmlNode* data;
    int stack_status;
};

class HtmlTree {
private:
    HtmlNode* root;
    bool searchAllNode(int, HtmlNode*, Vector<HtmlNode*>&, CharString&);
public:
    HtmlTree() { root = nullptr; }
	void clear();
	void deleteNode(HtmlNode* d);
    void setRoot(HtmlNode* r) { root = r; }
    void extractInfo(CharString& input_data);
    Vector<HtmlNode*> search(CharString&, CharString&);
	static void outputSubTree(HtmlNode* root_node, CharStringLink& result);
	static void outputNode(HtmlNode* root_node, CharStringLink& result);
};

#endif //EXPERIMENT_HTMLTAG_H
