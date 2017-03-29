#include "CharString.h"
#include "HtmlTag.h"
#include "HashTable.h"
#include <fstream>
#include <string>
#include <locale>

using namespace std;

int main(int argc, char * argv[]) {
	locale::global(locale("chs"));

	std::string input_file_name;
	std::string output_file_prefix;
	int input_file_size;
	std::string utf8_input;
    std::wifstream input_stream;
	std::ifstream utf8_input_stream;
    std::wofstream output_stream;
    CharString page;
    CharString dictionary;
    HtmlTree doc;
    HtmlNode* result;
    Vector<HtmlNode*> all_result;
    CharString tag;
    CharString attr;
    CharString* title;
    CharString* q_title;
    CharString* author;
    CharString* content;
    WordTable word_table;
	CharStringLink divide_result;
	CharStringLink info_result;
	
    input_stream.open("./ansi_dict.dic");
	std::wstring input((std::istreambuf_iterator<wchar_t>(input_stream)),
                 std::istreambuf_iterator<wchar_t>());
	dictionary.spaceToSpace(input.c_str());
	input.clear();
    word_table.initDictionary(dictionary);
	input_stream.close();
	
	for(int i = 1; i < argc; i++){
		input_file_name = argv[i];
		input_file_size = input_file_name.size();
		output_file_prefix = input_file_name.substr(0, input_file_size-5);

		utf8_input_stream.open("./input/" + input_file_name);
		while(!utf8_input_stream.eof()){
			std::getline(utf8_input_stream, utf8_input);
			page.utf8ToWchar(utf8_input.c_str());
			utf8_input.clear();
		}
		utf8_input.clear();
		utf8_input_stream.close();
				
		doc.extractInfo(page);

		output_stream.open("./output/"+output_file_prefix+".info");
		tag = L"h1";
		attr = L" class=\"headline-title\"";
		all_result = doc.search(tag, attr);
		result = all_result[0];

		if(result->children.size() > 0){
			title = result->children[0]->tag.data;
			output_stream << title << std::endl;
		}
		else{
			title = new CharString;
			output_stream << title << std::endl;
			delete title;
		}

		tag = L"h2";
		attr = L" class=\"question-title\"";
		all_result = doc.search(tag, attr);
		result = all_result[0];
		if(result->children.size() > 0){
			q_title = result->children[0]->tag.data;
			output_stream << q_title << std::endl;
		}
		else{
			q_title = new CharString;
			output_stream << q_title << std::endl;
			delete q_title;
		}

		tag = L"span";
		attr = L" class=\"author\"";
		all_result = doc.search(tag, attr);
		result = all_result[0];
		if(result->children.size() > 0){
			author = result->children[0]->tag.data;
			author->stripChinese();
			output_stream << author << std::endl;
		}
		else{
			author = new CharString;
			output_stream << author << std::endl;
			delete author;
		}

		tag = L"div";
		attr = L" class=\"content\"";
		all_result = doc.search(tag, attr);
		result = all_result[1];
		HtmlTree::outputSubTree(result, info_result);
		int len = info_result.size();
		content = new CharString;
		for(int i = 0; i < len; i++){
			content = (*content).concat(*info_result.nextNode(false));
		}
		output_stream << content << std::endl;
		word_table.divideWords(*content, divide_result);
		output_stream.close();

		output_stream.open("./output/"+output_file_prefix+".txt");
		output_stream << divide_result;
		output_stream.close();

		page.clear();
		doc = HtmlTree();
		info_result = CharStringLink();
	}
    return 0;
}