#include "HtmlTag.h"

void HtmlTree::clear(){
	int len = root->children.size();

    for(int i = 0; i < len; i++){
		deleteNode(root->children[i]);
    }
	delete root->tag.data;
	delete root;
	root = nullptr;
}

void HtmlTree::deleteNode(HtmlNode* d){
	int len = d->children.size();

    for(int i = 0; i < len; i++){
		deleteNode(d->children[i]);
    }
	delete d->tag.data;
	delete d;
}

void HtmlTree::extractInfo(CharString& input_data){
    Vector<HtmlListNode*> temp_node_list;
    HtmlListNode* temp_list_node;
    Stack<HtmlNode*> node_stack;
    HtmlNode* end_tag;
    HtmlNode* start_tag;
    CharString* tag_name;
    int start_pos;
    int space_pos;
    int end_pos1;
    int end_pos2;
    int end_pos3;
    int temp_length;

    start_pos = 0;
    start_pos = input_data.indexOf(L'<', start_pos);
    end_pos1 = input_data.indexOf(L'>', start_pos);

    start_pos = input_data.indexOf(L'<', start_pos+1);
    end_pos3 = input_data.indexOf(L"</", start_pos);
    end_pos1 = input_data.indexOf(L"/>", start_pos);
    end_pos2 = input_data.indexOf(L'>', start_pos);
    while(start_pos != -1){
        if(end_pos3 != -1 && end_pos3 == start_pos){
            end_tag = new HtmlNode;
            space_pos = input_data.indexOf(L' ', start_pos);
            if(space_pos >= 0 && end_pos2 > space_pos){
                tag_name = input_data.substring(start_pos+2, space_pos);
                end_tag->tag.hash = tag_name->htmlHash();
                end_tag->tag.data = input_data.substring(space_pos, end_pos2);
				//end_tag->tag.data = tag_name;
                delete tag_name;
            }
            else {
                tag_name = input_data.substring(start_pos+2, end_pos2);
                end_tag->tag.hash = tag_name->htmlHash();
                end_tag->tag.data = new CharString;
				//end_tag->tag.data = tag_name;
                delete tag_name;
            }
            while(!node_stack.empty() && node_stack.top()->tag.hash != end_tag->tag.hash){
                temp_list_node = new HtmlListNode;
                temp_list_node->stack_status = node_stack.size();
                temp_list_node->data = node_stack.top();
                temp_node_list.push(temp_list_node);
                node_stack.pop();
            }
            start_tag = node_stack.top();
            node_stack.pop();
            delete end_tag;

            if(!temp_node_list.empty()){
                temp_list_node = temp_node_list.back();
            }
            while(!temp_node_list.empty() && temp_list_node->stack_status > node_stack.size()){
                start_tag->children.push(temp_list_node->data);
                delete temp_list_node;
                temp_node_list.pop();
                if(!temp_node_list.empty()) {
                    temp_list_node = temp_node_list.back();
                }
            }
            temp_length = start_tag->children.size();
            for (int j = 0; j < temp_length; j++) {
                start_tag->children[j]->parent = start_tag;
            }
            temp_list_node = new HtmlListNode;
            temp_list_node->data = start_tag;
            temp_list_node->stack_status = node_stack.size();
            temp_node_list.push(temp_list_node);

            start_pos = input_data.indexOf(L'<', start_pos + 1);
            end_pos3 = input_data.indexOf(L"</", start_pos);
            end_pos2 = input_data.indexOf(L'>', start_pos);
        }
        else if(end_pos1 == -1 || end_pos2 <= end_pos1){
            node_stack.push(new HtmlNode);
            space_pos = input_data.indexOf(L' ', start_pos);
            if(space_pos >= 0 && end_pos2 > space_pos){
                tag_name = input_data.substring(start_pos+1, space_pos);
                node_stack.top()->tag.hash = tag_name->htmlHash();
                node_stack.top()->tag.data = input_data.substring(space_pos, end_pos2);
				//node_stack.top()->tag.data = tag_name;
                delete tag_name;
            }
            else{
                tag_name = input_data.substring(start_pos+1, end_pos2);
                node_stack.top()->tag.hash = tag_name->htmlHash();
                node_stack.top()->tag.data = new CharString();
				//node_stack.top()->tag.data = tag_name;
                delete tag_name;
            }
            start_pos = input_data.indexOf(L'<', start_pos + 1);
            if(end_pos2 + 1 < start_pos) {
                node_stack.push(new HtmlNode);
                node_stack.top()->tag.hash = -2;
                node_stack.top()->tag.data = input_data.substring(end_pos2 + 1, start_pos);
            }
            end_pos2 = input_data.indexOf(L'>', start_pos);
        }
        else {
            temp_list_node = new HtmlListNode;
            temp_list_node->stack_status = node_stack.size();
            temp_list_node->data = new HtmlNode;
            temp_node_list.push(temp_list_node);
            space_pos = input_data.indexOf(L' ', start_pos);
            if (space_pos >= 0 && end_pos1 > space_pos) {
                tag_name = input_data.substring(start_pos+1, space_pos);
                temp_node_list.back()->data->tag.hash = tag_name->htmlHash();
                temp_node_list.back()->data->tag.data = input_data.substring(space_pos, end_pos1);
				//temp_node_list.back()->data->tag.data = tag_name;
                delete tag_name;
            }
            else {
                tag_name = input_data.substring(start_pos+1, end_pos1);
                temp_node_list.back()->data->tag.hash = tag_name->htmlHash();
                temp_node_list.back()->data->tag.data = new CharString();
                //temp_node_list.back()->data->tag.data = tag_name;
				delete tag_name;
            }
            start_pos = input_data.indexOf(L'<', start_pos + 1);
            if(end_pos1 + 1 < start_pos) {
                node_stack.push(new HtmlNode);
                node_stack.top()->tag.hash = -2;
                node_stack.top()->tag.data = input_data.substring(end_pos1 + 1, start_pos);
            }
            end_pos1 = input_data.indexOf(L"/>", start_pos);
            end_pos2 = input_data.indexOf(L'>', start_pos);
        }
		if(start_pos == -1){
		   int  t = 1;
		}
    }
    root = temp_node_list[0]->data;
    delete temp_node_list[0];
	root->parent = nullptr;
    temp_node_list.clear();
}

Vector<HtmlNode*> HtmlTree::search(CharString& s, CharString& attr) {
    int s_hash = s.htmlHash();
    Vector<HtmlNode*> result;
    bool find;

    find = searchAllNode(s_hash, root, result, attr);
    if(find){
        return result;
    }
    else{
        return result;
    }
}

bool HtmlTree::searchAllNode(int hash, HtmlNode* current, Vector<HtmlNode*>& result, CharString& attr){
    bool find;

    find = false;
	//std::wcout << current->tag.data << L' ' << current->tag.hash << std::endl;
    if (current->tag.hash == hash && *(current->tag.data) == attr) {
        result.push(current);
        return true;
    }
    else{
        int len = current->children.size();
        for(int i = 0; i < len; i++){
            find |= searchAllNode(hash, current->children[i], result, attr);
        }
        return find;
    }
}

void HtmlTree::outputSubTree(HtmlNode* root_node, CharStringLink& result){
	int len = root_node->children.size();

    for(int i = 0; i < len; i++){
		outputNode(root_node->children[i], result);
    }
}

void HtmlTree::outputNode(HtmlNode* root_node, CharStringLink& result){
	int len = root_node->children.size();

	if(root_node->tag.hash == -2){
		result.add(*(root_node->tag.data));
	}
    for(int i = 0; i < len; i++){
		outputNode(root_node->children[i], result);
    }	
}