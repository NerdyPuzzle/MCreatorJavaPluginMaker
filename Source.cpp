#define _CRT_SECURE_NO_WARNINGS

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") 

#include <raylib.h>
#include <string>
#include "generaleaselib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_STATIC
#include <raygui.h>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <sstream>

#define screenWidth 1200
#define screenHeight 600

using namespace gez;

enum ComponentType {
	NO_TYPE,
	CHECKBOX_TYPE,
	TEXTFIELD_TYPE,
	NUMBER_TYPE,
	EMPTY_BOX,
	TEXTURE_TYPE,
	MODEL_TYPE,
	ITEM_TYPE,
	DROPDOWN_TYPE
};

class Components {
public:
	struct Widget {
		ComponentType component_type;
		int page_index;
		std::string name;
		std::string label;
		std::string has_tooltip;

		//checkbox only
		std::string should_append;

		//textfield only
		std::string is_validated;
		std::string has_elementname;
		int length;

		//numberfield only
		int min;
		int max;
		int step;

		//selectors only
		std::string selector_content;

		//static dropdown only
		std::vector<std::string> members;
	};

	//int is page
	std::map<int, std::vector<Widget>> widgets;
	//page, size
	std::map<int, int> indexes;
	//page, text
	std::map<int, std::string> panel_list;

	Components() {
		indexes[0] = 0;
	}
};

struct PluginInfo {
	char name[64] = { 0 };
	char id[64] = { 0 };
	int weight = 0;
	char author[64] = { 0 };
	char description[64] = { 0 };
	char credit[64] = { 0 };
};

struct GuiComponentSources {
	Rectangle button1Rect = { 10, 10, 170, 45 };
	Rectangle button2Rect = { 10, 60, 170, 45 };
	Rectangle button3Rect = { 10, 110, 170, 45 };
	Rectangle deleteDialogButton1 = { ((screenWidth - 500) / 2) + 50, ((screenHeight - 250) / 2) + 175, 70, 45 };
	Rectangle deleteDialogButton2 = { ((screenWidth - 500) / 2) + 375, ((screenHeight - 250) / 2) + 175, 70, 45 };
	Rectangle textbox1Rect = { (screenWidth - 100) / 2, (screenHeight - 380) / 2, 170, 45 };
	Rectangle creationPanelRect = { (screenWidth - 500) / 2, (screenHeight - 500) / 2, 500, 500 };
	Rectangle textbox2Rect = { (screenWidth - 100) / 2, (screenHeight - 255) / 2, 170, 45 };
	Rectangle spinner1Rect = { (screenWidth - 100) / 2, (screenHeight - 130) / 2, 170, 45 };
	Rectangle textbox3Rect = { (screenWidth - 100) / 2, (screenHeight - 10) / 2, 170, 45 };
	Rectangle textbox4Rect = { (screenWidth - 100) / 2, (screenHeight + 110) / 2, 170, 45 };
	Rectangle textbox5Rect = { (screenWidth - 100) / 2, (screenHeight + 230) / 2, 170, 45 };
	Rectangle finishPluginRect = { (screenWidth - 100) / 2, (screenHeight + 360) / 2, 170, 45 };

	bool textbox1enabled = false;
	bool textbox2enabled = false;
	bool textbox3enabled = false;
	bool textbox4enabled = false;
	bool textbox5enabled = false;

	int index;
	int selected = -1;
	int old = -1;
	int cache;

	Rectangle editingPluginText = { 10, 10, 170, 500 };
	Rectangle mainScrollPane = { 200, 10, 750, 580 };

	//edit, delete, main menu buttons
	Rectangle editwidgetRec = { 965, 10, 225, 35 };
	Rectangle deletewidgetRec = { 965, 50, 225, 35 };
	Rectangle mainmenuRec = { 965, 90, 225, 35 };

	//save and export buttons
	Rectangle savebuttonRec = { 10, 525, 170, 30 };
	Rectangle exportbuttonRec = { 10, 560, 170, 30 };

	//side panel widgets
	Rectangle checkboxRect = { 15, 20, 160, 35 };
	Rectangle textfieldRect = { 15, 60, 160, 35 };
	Rectangle spinnerRect = { 15, 100, 160, 35 };
	Rectangle emptyboxRect = { 15, 140, 160, 35 };
	Rectangle texturesRect = { 15, 180, 160, 35 };
	Rectangle modelsRect = { 15, 220, 160, 35 };
	Rectangle itemselectorRect = { 15, 260, 160, 35 };
	Rectangle staticdropRect = { 15, 300, 160, 35 };

	Rectangle pageborderRec = { 965, 505, 225, 85 };
	Rectangle pagelistRec = { 970, 513, 215, 72 };
	Rectangle addpagebuttonRec = { 965, 460, 108, 35 };
	Rectangle removepagebuttonRec = { 1081, 460, 108, 35 };

	int pageIndex;
	int selectedPage = 0;
	std::string pages = "1";
	int pagesCount = 1;

	//add checkbox
	Rectangle checkboxDialog = { (screenWidth - 500) / 2, (screenHeight - 280) / 2, 500, 280 };
	Rectangle checkboxnameRec = { 570, 195, 265, 25 };
	char checkboxname[64] = { 0 };
	bool checkboxnameEnabled = false;
	Rectangle checkboxlabelRec = { 570, 230, 265, 25 };
	char checkboxlabel[64] = { 0 };
	bool checkboxlabelEnabled = false;
	Rectangle checkboxtooltipRec = { 570, 265, 265, 25 };
	char checkboxtooltip[64] = { 0 };
	bool checkboxtooltipEnabled = false;
	Rectangle checkboxappendRec = { 570, 300, 25, 25 };
	bool checkboxappendEnabled = false;
	Rectangle addbuttonRec = { 500, 385, 100, 30 };
	Rectangle cancelbuttonRec = { 610, 385, 100, 30 };

	//add textfield
	Rectangle textfieldDialog = { (screenWidth - 500) / 2, (screenHeight - 310) / 2, 500, 310 };
	Rectangle textfieldnameRec = { 570, 180, 265, 25 };
	char textfieldname[64] = { 0 };
	bool textfieldnameEnabled = false;
	Rectangle textfieldlabelRec = { 570, 215, 265, 25 };
	char textfieldlabel[64] = { 0 };
	bool textfieldlabelEnabled = false;
	Rectangle textfieldtooltipRec = { 570, 250, 265, 25 };
	char textfieldtooltip[64] = { 0 };
	bool textfieldtooltipEnabled = false;
	Rectangle textfieldlengthRec = { 570, 285, 265, 25 };
	int textfieldlength = 0;
	Rectangle textfieldvalidateRec = { 570, 320, 25, 25 };
	bool textfieldvalidate = false;
	Rectangle textfieldelementtextRec = { 570, 355, 25, 25 };
	bool textfieldelementtext = false;
	Rectangle addbuttontextfieldRec = { 500, 405, 100, 30 };
	Rectangle cancelbuttontextfieldRec = { 610, 405, 100, 30 };

	//add numberfield
	Rectangle numberfieldDialog = { (screenWidth - 500) / 2, (screenHeight - 310) / 2, 500, 310 };
	Rectangle numberfieldnameRec = { 570, 180, 265, 25 };
	char numberfieldname[64] = { 0 };
	bool numberfieldnameEnabled = false;
	Rectangle numberfieldlabelRec = { 570, 215, 265, 25 };
	char numberfieldlabel[64] = { 0 };
	bool numberfieldlabelEnabled = false;
	Rectangle numberfieldtooltipRec = { 570, 250, 265, 25 };
	char numberfieldtooltip[64] = { 0 };
	bool numberfieldtooltipEnabled = false;
	Rectangle numberfieldstepRec = { 570, 285, 265, 25 };
	int numberfieldstep = 0;
	Rectangle numberfieldmaxRec = { 570, 320, 265, 25 };
	int numberfieldmax = 0;
	Rectangle numberfieldminRec = { 570, 355, 265, 25 };
	int numberfieldmin = 0;
	Rectangle addbuttonnumberfieldRec = { 500, 405, 100, 30 };
	Rectangle cancelbuttonnumberfieldRec = { 610, 405, 100, 30 };

	//add empty box
	Rectangle emptyboxDialog = { (screenWidth - 500) / 2, (screenHeight - 100) / 2, 500, 100 };
	Rectangle addbuttonemptyboxRec = { 500, 295, 100, 30 };
	Rectangle cancelbuttonemptyboxRec = { 610, 295, 100, 30 };\

	//add texture selector
	Rectangle textureselectorDialog = { (screenWidth - 500) / 2, (screenHeight - 280) / 2, 500, 280 };
	Rectangle textureselectornameRec = { 570, 195, 265, 25 };
	char textureselectorname[64] = { 0 };
	bool textureselectornameEnabled = false;
	Rectangle textureselectorlabelRec = { 570, 230, 265, 25 };
	char textureselectorlabel[64] = { 0 };
	bool textureselectorlabelEnabled = false;
	Rectangle textureselectortooltipRec = { 570, 265, 265, 25 };
	char textureselectortooltip[64] = { 0 };
	bool textureselectortooltipEnabled = false;
	Rectangle textureselectortypeRec = { 570, 300, 265, 25 };
	std::string textureselectortext = "BLOCK\nITEM\nENTITY\nEFFECT\nPARTICLE\nSCREEN\nARMOR\nOTHER";
	int textureselectorindex = 0;
	bool textureselectorEnabled = false;
	Rectangle addbuttontextureRec = { 500, 385, 100, 30 };
	Rectangle cancelbuttontextureRec = { 610, 385, 100, 30 };

	//add model selector
	Rectangle modelselectorDialog = { (screenWidth - 500) / 2, (screenHeight - 280) / 2, 500, 280 };
	Rectangle modelselectornameRec = { 570, 195, 265, 25 };
	char modelselectorname[64] = { 0 };
	bool modelselectornameEnabled = false;
	Rectangle modelselectorlabelRec = { 570, 230, 265, 25 };
	char modelselectorlabel[64] = { 0 };
	bool modelselectorlabelEnabled = false;
	Rectangle modelselectortooltipRec = { 570, 265, 265, 25 };
	char modelselectortooltip[64] = { 0 };
	bool modelselectortooltipEnabled = false;
	Rectangle modelselectortypeRec = { 570, 300, 265, 25 };
	std::string modelselectortext = "JAVA\nJSON\nOBJ";
	int modelselectorindex = 0;
	bool modelselectorEnabled = false;
	Rectangle addbuttonmodelRec = { 500, 385, 100, 30 };
	Rectangle cancelbuttonmodelRec = { 610, 385, 100, 30 };

	//add item selector
	Rectangle itemselectorDialog = { (screenWidth - 500) / 2, (screenHeight - 280) / 2, 500, 280 };
	Rectangle itemselectornameRec = { 570, 195, 265, 25 };
	char itemselectorname[64] = { 0 };
	bool itemselectornameEnabled = false;
	Rectangle itemselectorlabelRec = { 570, 230, 265, 25 };
	char itemselectorlabel[64] = { 0 };
	bool itemselectorlabelEnabled = false;
	Rectangle itemselectortooltipRec = { 570, 265, 265, 25 };
	char itemselectortooltip[64] = { 0 };
	bool itemselectortooltipEnabled = false;
	Rectangle itemselectortypeRec = { 570, 300, 265, 25 };
	std::string itemselectortext = "BLOCKS AND ITEMS\nBLOCKS ONLY";
	int itemselectorindex = 0;
	bool itemselectorEnabled = false;
	Rectangle addbuttonitemRec = { 500, 385, 100, 30 };
	Rectangle cancelbuttonitemRec = { 610, 385, 100, 30 };

	//add static dropdown
	Rectangle dropdownDialog = { (screenWidth - 500) / 2, (screenHeight - 280) / 2, 500, 280 };
	Rectangle dropdownnameRec = { 570, 195, 265, 25 };
	char dropdownname[64] = { 0 };
	bool dropdownnameEnabled = false;
	Rectangle dropdownlabelRec = { 570, 230, 265, 25 };
	char dropdownlabel[64] = { 0 };
	bool dropdownlabelEnabled = false;
	Rectangle dropdowntooltipRec = { 570, 265, 265, 25 };
	char dropdowntooltip[64] = { 0 };
	bool dropdowntooltipEnabled = false;
	Rectangle dropdownmembersRec = { 570, 300, 265, 25 };
	char dropdownmembers[128] = { 0 };
	bool dropdownmembersEnabled = false;
	Rectangle addbuttondropdownRec = { 500, 385, 100, 30 };
	Rectangle cancelbuttondropdownRec = { 610, 385, 100, 30 };

};

void save(PluginInfo info) {
	buildDir("saves/" + (std::string)info.name + "/");
	std::ofstream variables("saves/" + (std::string)info.name + "/variables.cfg");
	std::ofstream pluginname("saves/name/plgn.dat");

	pluginname << info.name;

	variables << info.name << " \\n" << std::endl;
	variables << info.id << std::endl;
	variables << info.weight << std::endl;
	variables << info.author << std::endl;
	variables << info.description << std::endl;
	variables << info.credit << std::endl;

	variables.close();
	pluginname.close();

}

void deleteAllDirs(PluginInfo info) {
	std::string path = "/src/main/resources/";
	std::string path1 = "/src/main/";
	std::string path2 = "/src/";
	std::string path3 = "/";
	std::string path4 = "saves/";
	deleteDir(info.name + path);
	deleteDir(info.name + path1);
	deleteDir(info.name + path2);
	deleteDir(info.name + path3);
	deleteDir(path4 + info.name);
}

void buildOrLoadSaves(bool& hasSave, PluginInfo& info, GuiComponentSources& sources, Components& components) {
	buildDir("saves/name/");
	std::ifstream pluginname("saves/name/plgn.dat");
	std::string name;
	pluginname >> name;
	pluginname.close();
	buildDir("saves/" + name + "/");
	std::ifstream variables("saves/" + name + "/variables.cfg");

	if (variables.is_open()) {
		char tempc[64] = { 0 };
		std::string temps = "";
		variables >> temps;
		while (temps != "\\n") {
			for (int i = 0; i < temps.size(); i++)
				tempc[i] = temps[i];
			variables >> temps;
		}
		std::strcpy(info.name, tempc);
		variables >> info.id;
		std::string tempstR;
		variables >> tempstR;
		info.weight = std::stoi(tempstR);
		variables >> info.author;
		variables >> info.description;
		variables >> info.credit;
		hasSave = true;
		variables.close();
	}

	std::ifstream in("saves/" + name + "/plugin.data");

	if (in.is_open()) {
		std::string temp;
		in >> temp; in >> temp; //get the string of the pages list numbers
		size_t pos = 0;
		while ((pos = temp.find("\\n", pos)) != std::string::npos) { //replace with newline characters
			temp.replace(pos, 2, "\n");
			pos += 1;
		}
		sources.pages = temp; //set the string to the parsed result
		in >> temp; in >> temp; //get the int for the pagesCount from the line
		sources.pagesCount = std::stoi(temp); //convert and set the value
		for (int i = 0; i < sources.pagesCount; i++) { //iterate through the pages parsed
			in >> temp; in >> temp; //find the first word of the string
			std::string newline = ""; //temporary string to hold the value
			while ((pos = temp.find("INDEX_")) == std::string::npos) { //iterate through the line
				newline += temp + " ";
				in >> temp;
			}
			temp = "";
			for (int j = 0; j < newline.size() - 1; j++) //get rid of the last extra space in the string
				temp += newline[j];
			newline = temp;
			pos = 0;
			while ((pos = newline.find("\\n", pos)) != std::string::npos) { //replace with newline characters in the string
				newline.replace(pos, 2, "\n");
				pos += 1;
			}
			components.panel_list[i] = newline; //set the list to the parsed string
			in >> temp; //get the index value
			components.indexes[i] = std::stoi(temp); //convert and set the value
		}
		for (int i = 0; i < sources.pagesCount; i++) { //iterate through the pages again
			in >> temp; in >> temp; 
			for (int j = 0; j < components.indexes[i]; j++) { //iterate through the components of the page
				std::string type;
				in >> temp; type = temp; in >> temp;
				Components::Widget comp;
				in >> temp;
				comp.page_index = std::stoi(temp); //get the page index, same for all types
				if (type != "EMPTY_BOX") { //if not empty box, get default attributes (name, label, tooltip)
					in >> comp.name;
					std::string label = "";
					std::string temps;
					in >> temps;
					while (temps != "\\n") { //get the entire label instead of the first word
						label += temps + " ";
						in >> temps;
					}
					temps = "";
					for (int p = 0; p < label.size() - 1; p++)
						temps += label[p];
					comp.label = temps;
					in >> comp.has_tooltip;
					if (type == "CHECKBOX") {
						comp.component_type = CHECKBOX_TYPE;
						in >> comp.should_append;
					}
					else if (type == "TEXTFIELD") {
						comp.component_type = TEXTFIELD_TYPE;
						in >> comp.is_validated;
						in >> comp.has_elementname;
						in >> temp;
						comp.length = std::stoi(temp);
					}
					else if (type == "NUMBERFIELD") {
						comp.component_type = NUMBER_TYPE;
						in >> temp;
						comp.step = std::stoi(temp);
						in >> temp;
						comp.max = std::stoi(temp);
						in >> temp;
						comp.min = std::stoi(temp);
					}
					else if (type == "TEXTURESELECTOR") {
						comp.component_type = TEXTURE_TYPE;
						in >> comp.selector_content;
					}
					else if (type == "MODELSELECTOR") {
						comp.component_type = MODEL_TYPE;
						in >> comp.selector_content;
					}
					else if (type == "ITEMSELECTOR") {
						comp.component_type = ITEM_TYPE;
						in >> comp.selector_content;
					}
					else if (type == "STATICDROPDOWN") {
						comp.component_type = DROPDOWN_TYPE;
						in >> temp;
						std::string linenew = "";
						for (int k = 0; k < temp.size(); k++) {
							if (temp[k] != ',')
								linenew += temp[k];
							else {
								comp.members.push_back(linenew);
								linenew = "";
							}
						}
						comp.members.push_back(linenew);
					}
					components.widgets[i].push_back(comp);
					in >> temp; //component parsed, move on
				}
				else {
					comp.component_type = EMPTY_BOX;
					components.widgets[i].push_back(comp);
					in >> temp; //this is an empty box, move on
				}
			}
			in >> temp; //end of this page's components
		}
		in.close();
	}

}

void buildJsonSave(PluginInfo info) {
	std::string path = "/src/main/resources/";
	JsonUtil util;
	std::string lowername = (std::string)info.name;
	std::string weightTemp = std::to_string(info.weight);
	const char* weightChar = weightTemp.c_str();
	buildDir(info.name + path);
	std::ofstream out(info.name + path + "plugin.json");
	lowerCaseString(lowername);
	removeSpaces(lowername);

	out << "{" << std::endl;
	out << "  " << util.getProperty("id", (std::string)info.id) << ',' << std::endl;
	out << "  " << util.simpleString("weight") + ':' + " " + weightChar << ',' << std::endl;
	out << "  " << util.getProperty("javaplugin", (std::string)("net.nerdypuzzle." + lowername + ".Launcher")) << ',' << std::endl;
	out << "  " << util.simpleString("info") + ":  {" << std::endl;
	out << "    " << util.getProperty("name", (std::string)info.name) << ',' << std::endl;
	out << "    " << util.getProperty("version", (std::string)"1.0") << ',' << std::endl;
	out << "    " << util.getProperty("description", (std::string)info.description) << ',' << std::endl;
	out << "    " << util.getProperty("author", (std::string)info.author) << ',' << std::endl;
	out << "    " << util.getProperty("credits", (std::string)info.credit) << std::endl;
	out << "  }" << std::endl;
	out << "}";

	out.close();
}

void buildJavaLauncher(PluginInfo info) {
	std::string name = (std::string)info.name;
	lowerCaseString(name);
	removeSpaces(name);
	std::string path = "/src/main/java/net/nerdypuzzle/" + name + "/";
	buildDir(info.name + path);
	std::ofstream java((std::string)info.name + path + "Launcher.java");
	JsonUtil jUtil;

	java << "package net.nerdypuzzle." + name + ";" << std::endl << std::endl;
	java << "public class Launcher extends JavaPlugin {" << std::endl << std::endl;
	java << "   public static final Logger LOG = LogManager.getLogger(" + jUtil.simpleString((std::string)info.name) + ");" << std::endl;
	java << "   public Launcher(Plugin plugin) {" << std::endl;
	java << "       super(plugin);" << std::endl;
	java << "       addListener(PreGeneratorsLoadingEvent.class, event -> PluginElementTypes.load());" << std::endl;
	java << "       LOG.info(" + jUtil.simpleString("Plugin was loaded") + ");" << std::endl;
	java << "   }" << std::endl;
	java << "}";

	java.close();
}

void saveComponentData(GuiComponentSources sources, Components components) {
	if (!components.widgets.empty()) {
		std::ifstream pluginname("saves/name/plgn.dat");
		std::string name;
		pluginname >> name;
		pluginname.close();

		std::ofstream out("saves/" + name + "/plugin.data");
		out << "PAGES_STRING" << " ";
		std::istringstream stemp(sources.pages);
		std::string stempstring;
		while (getline(stemp, stempstring)) {
			out << stempstring;
			if (!stemp.eof())
				out << "\\" << "n";
		}
		out << std::endl;
		out << "PAGES_INT" << " " << std::to_string(sources.pagesCount) << std::endl;
		for (int i = 0; i < sources.pagesCount; i++) {
			out << "PAGE_" + std::to_string(i) << " ";
			std::istringstream iss(components.panel_list.at(i));
			std::string iterator;
			while (getline(iss, iterator)) {
				out << iterator;
				if (!iss.eof())
					out << "\\" << "n";
			}
			out << std::endl;
			out << "INDEX_" + std::to_string(i) << " " << components.indexes.at(i) << std::endl;
		}
		for (int i = 0; i < sources.pagesCount; i++) {
			out << "PAGE_" << std::to_string(i) << "_COMPONENTS [" << std::endl;
			for (Components::Widget widget : components.widgets[i]) {
				if (widget.component_type == EMPTY_BOX) {
					out << "EMPTY_BOX {" << std::endl;
					out << std::to_string(widget.page_index) << std::endl;
					out << "}" << std::endl;
				}
				else {
					ComponentType current_type = NO_TYPE;
					switch (widget.component_type) {
					case CHECKBOX_TYPE:
						out << "CHECKBOX {\n";
						current_type = CHECKBOX_TYPE;
						break;
					case TEXTFIELD_TYPE:
						out << "TEXTFIELD {\n";
						current_type = TEXTFIELD_TYPE;
						break;
					case NUMBER_TYPE:
						out << "NUMBERFIELD {\n";
						current_type = NUMBER_TYPE;
						break;
					case TEXTURE_TYPE:
						out << "TEXTURESELECTOR {\n";
						current_type = TEXTURE_TYPE;
						break;
					case MODEL_TYPE:
						out << "MODELSELECTOR {\n";
						current_type = MODEL_TYPE;
						break;
					case ITEM_TYPE:
						out << "ITEMSELECTOR {\n";
						current_type = ITEM_TYPE;
						break;
					case DROPDOWN_TYPE:
						out << "STATICDROPDOWN {\n";
						current_type = DROPDOWN_TYPE;
						break;
					}
					out << std::to_string(widget.page_index) << std::endl;
					out << widget.name << std::endl;
					out << widget.label << " \\n" << std::endl;
					out << widget.has_tooltip << std::endl;
					switch (current_type) {
					case CHECKBOX_TYPE:
						out << widget.should_append << std::endl;
						break;
					case TEXTFIELD_TYPE:
						out << widget.is_validated << std::endl;
						out << widget.has_elementname << std::endl;
						out << std::to_string(widget.length) << std::endl;
						break;
					case NUMBER_TYPE:
						out << std::to_string(widget.step) << std::endl;
						out << std::to_string(widget.max) << std::endl;
						out << std::to_string(widget.min) << std::endl;
						break;
					case TEXTURE_TYPE:
					case MODEL_TYPE:
					case ITEM_TYPE:
						out << widget.selector_content << std::endl;
						break;
					case DROPDOWN_TYPE:
						bool first = true;
						for (std::string member : widget.members) {
							if (first) {
								first = false;
								out << member;
							}
							else
								out << "," << member;
						}
						out << std::endl;
						break;
					}

					out << "}" << std::endl;
				}
			}
			out << "]" << std::endl;
		}
		out.close();
	}
}

void exportPlugin(PluginInfo info, Components components, int pages) {
	std::string nameS = (std::string)info.name;
	lowerCaseString(nameS);
	removeSpaces(nameS);
	std::string path = (std::string)info.name + "/src/main/java/net/nerdypuzzle/" + nameS + "/"; //folder paths
	std::string element_path = path + "element/types/";
	std::string gui_path = path + "ui/modgui/";

	buildDir(element_path); //make the dirs
	buildDir(gui_path);

	std::ofstream element_types(element_path + "PluginElementTypes.java"); //export the element registry
	element_types << "package net.nerdypuzzle." + nameS + ".element.types;\n\n";
	element_types << "public class PluginElementTypes {\n";
	element_types << "	public static ModElementType<?> PLUGINELEMENT;\n\n";
	element_types << "	public static void load() {\n";
	element_types << "		PLUGINELEMENT = register(\n";
	element_types << "			new ModElementType<>(" + sstring("pluginelement") + ", (Character) null, BaseType.OTHER, PluginElementGUI::new, PluginElement.class)\n";
	element_types << "		);\n";
	element_types << "	}\n";
	element_types << "}";
	element_types.close();

	std::ofstream element_type(element_path + "PluginElement.java"); //export the element type
	element_type << "package net.nerdypuzzle." + nameS + ".element.types;\n\n";
	element_type << "public class PluginElement extends GeneratableElement {\n";
	for (int i = 0; i < pages; i++) {
		for (Components::Widget widget : components.widgets[i]) { //export all the variables
			switch (widget.component_type) {
			case CHECKBOX_TYPE:
				element_type << "	public boolean " + widget.name + ";\n";
				break;
			case TEXTFIELD_TYPE:
			case DROPDOWN_TYPE:
			case TEXTURE_TYPE:
			case MODEL_TYPE:
				element_type << "	public String " + widget.name + ";\n";
				break;
			case NUMBER_TYPE:
				element_type << "	public float " + widget.name + ";\n";
				break;
			case ITEM_TYPE:
				element_type << "	public MItemBlock " + widget.name + ";\n";
				break;
			}
		}
	}
	element_type << std::endl;
	element_type << "	private PluginElement() {\n";
	element_type << "		this(null);\n";
	element_type << "	}\n\n";
	element_type << "	public PluginElement(ModElement element) {\n";
	element_type << "		super(element);\n";
	element_type << "	}\n";
	element_type << "}";
	element_type.close();

	std::ofstream element_gui(gui_path + "PluginElementGUI.java"); //initialize all the variables of the GUI
	element_gui << "package net.nerdypuzzle." + nameS + ".ui.modgui;\n\n";
	element_gui << "public class PluginElementGUI extends ModElementGUI<PluginElement> {\n";
	for (int i = 0; i < pages; i++) {
		for (Components::Widget widget : components.widgets[i]) {
			switch (widget.component_type) {
			case CHECKBOX_TYPE:
				if (widget.should_append == "yes")
					element_gui << "	private final JCheckBox " + widget.name + " = L10N.checkbox(" + sstring("elementgui.common.enable") + ");\n";
				else
					element_gui << "	private final JCheckBox " + widget.name + " = new JCheckBox();\n";
				break;
			case TEXTFIELD_TYPE:
				if (widget.is_validated == "yes")
					element_gui << "	private final VTextField " + widget.name + " = new VTextField(" + std::to_string(widget.length) + ");\n";
				else
					element_gui << "	private final JTextField " + widget.name + " = new JTextField(" + std::to_string(widget.length) + ");\n";
				break;
			case NUMBER_TYPE:
				element_gui << "	private final JSpinner " + widget.name + " = new JSpinner(new SpinnerNumberModel(1.0, " + std::to_string(widget.min) + ", " + std::to_string(widget.max) + ", " + std::to_string(widget.step * 0.1) + "));\n";
				break;
			case TEXTURE_TYPE:
				element_gui << "	private final VComboBox<String> " + widget.name + " = new SearchableComboBox<>();\n";
				break;
			case MODEL_TYPE:
				element_gui << "	private final Model " + widget.name + "_default = new Model.BuiltInModel(" + sstring("Default") + ");\n";
				element_gui << "	private final SearchableComboBox<Model> " + widget.name + " = new SearchableComboBox<>(new Model[] { " + widget.name + "_default });\n";
				break;
			case ITEM_TYPE:
				element_gui << "	private MCItemHolder " + widget.name + ";\n";
				break;
			case DROPDOWN_TYPE:
				element_gui << "	private final JComboBox<String> " + widget.name + " = new JComboBox<>(\n";
				element_gui << "		new String[] { ";
				bool firstMember = true;
				for (std::string member : widget.members) {
					if (firstMember) {
						firstMember = false;
						element_gui << sstring(member);
					}
					else
						element_gui << ", " + sstring(member);
				}
				element_gui << " });\n";
				break;
			}
		}
	} //end of variable listing
	element_gui << std::endl;
	for (int i = 0; i < pages; i++) //add the validation groups
		element_gui << "	private final ValidationGroup page" + std::to_string(i + 1) + "group = new ValidationGroup();\n";
	element_gui << std::endl;
	element_gui << "	public PluginElementGUI(MCreator mcreator, ModElement modElement, boolean editingMode) {\n";
	element_gui << "		super(mcreator, modElement, editingMode);\n";
	element_gui << "		this.initGUI();\n";
	element_gui << "		super.finalizeGUI();\n";
	element_gui << "	}\n\n";
	element_gui << "	@Override\n";
	element_gui << "	protected void initGUI() {\n";
	for (int i = 0; i < pages; i++) { //initialize item holders
		for (Components::Widget widget : components.widgets[i]) {
			switch (widget.component_type) {
			case ITEM_TYPE:
				element_gui << "		" + widget.name + " = new MCItemHolder(mcreator, ElementUtil::";
				if (widget.selector_content == "items")
					element_gui << "loadBlocksAndItems);\n";
				else if (widget.selector_content == "blocks")
					element_gui << "loadBlocks);\n";
				break;
			}
		}
	} //end of listing
	element_gui << std::endl;
	for (int i = 0; i < pages; i++) { //write all the panel code
		std::string pageIndexStr = std::to_string(i + 1);
		element_gui << "		JPanel pane" + pageIndexStr + " = new JPanel(new BorderLayout(10, 10));\n";
		element_gui << "		JPanel page" + pageIndexStr + "Panel = new JPanel(new GridLayout(" + std::to_string(components.indexes[i]) + ", 2, 10, 10));\n";
		element_gui << "		pane" + pageIndexStr + ".setOpaque(false);\n";
		element_gui << "		page" + pageIndexStr + "Panel.setOpaque(false);\n\n";
		for (Components::Widget widget : components.widgets[i]) {
			bool hasTooltip = widget.has_tooltip != "null";
			switch (widget.component_type) {
			case CHECKBOX_TYPE:
				if (hasTooltip) {
					element_gui << "		page" + pageIndexStr + "Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry(" + sstring(widget.has_tooltip) + "),\n";
					element_gui << "				L10N.label(\"elementgui.element." + toLowerCaseStr(widget.name) + "\")));\n";
				}
				else
					element_gui << "		page" + pageIndexStr + "Panel.add(L10N.label(\"elementgui.element." + toLowerCaseStr(widget.name) + "\"));\n";
				element_gui << "		page" + pageIndexStr + "Panel.add(" + widget.name + ");\n\n";
				break;
			case TEXTFIELD_TYPE:
			case NUMBER_TYPE:
			case TEXTURE_TYPE:
			case MODEL_TYPE:
			case ITEM_TYPE:
			case DROPDOWN_TYPE:
				if (hasTooltip) {
					element_gui << "		page" + pageIndexStr + "Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry(" + sstring(widget.has_tooltip) + "),\n";
					element_gui << "				L10N.label(\"elementgui.element." + toLowerCaseStr(widget.name) + "\")));\n";
				}
				else
					element_gui << "		page" + pageIndexStr + "Panel.add(L10N.label(\"elementgui.element." + toLowerCaseStr(widget.name) + "\"));\n";
				element_gui << "		page" + pageIndexStr + "Panel.add(" + widget.name + ");\n\n";
				break;
			case EMPTY_BOX:
				element_gui << "		page" + pageIndexStr + "Panel.add(new JEmptyBox()); page" + pageIndexStr + "Panel.add(new JEmptyBox());\n\n";
				break;
			}
		}
		element_gui << "		pane" + pageIndexStr + ".add(" + sstring("Center") + ", PanelUtils.totalCenterInPanel(page" + pageIndexStr + "Panel));\n\n";
	} //end of panel sorting
	for (int i = 0; i < pages; i++) { //set checkboxes opaque
		for (Components::Widget widget : components.widgets[i]) {
			switch (widget.component_type) {
			case CHECKBOX_TYPE:
				element_gui << "		" + widget.name + ".setOpaque(false);\n";
				break;
			}
		}
	} //end of listing
	element_gui << std::endl;
	for (int i = 0; i < pages; i++) { //add validated elements
		for (Components::Widget widget : components.widgets[i]) {
			switch (widget.component_type) {
			case TEXTFIELD_TYPE:
				if (widget.is_validated == "yes")
					element_gui << "		page" + std::to_string(i + 1) + "group.addValidationElement(" + widget.name + ");\n";
				break;
			case TEXTURE_TYPE:
			case MODEL_TYPE:
				element_gui << "		page" + std::to_string(i + 1) + "group.addValidationElement(" + widget.name + ");\n";
				break;
			}
		}
	} //end of listing
	element_gui << std::endl;
	for (int i = 0; i < pages; i++) { //set element name in textfields
		for (Components::Widget widget : components.widgets[i]) {
			switch (widget.component_type) {
			case TEXTFIELD_TYPE:
				if (widget.has_elementname == "yes") {
					element_gui << "		if (!isInEditingMode) {\n";
					element_gui << "			" + widget.name + ".setText(StringUtils.machineToReadableName(modElement.getName()));\n";
					element_gui << "		}\n";
				}
				break;
			}
		}
	} //end of listing
	element_gui << std::endl;
	for (int i = 0; i < pages; i++)
		element_gui << "		addPage(L10N.t(\"elementgui.element.page" + std::to_string(i + 1) + "\"), pane" + std::to_string(i + 1) + ");\n";
	element_gui << "	}\n\n";
	element_gui << "	@Override\n";
	element_gui << "	protected AggregatedValidationResult validatePage(int page) {\n";
	for (int i = 0; i < pages; i++) {
		element_gui << "		if (page == " + std::to_string(i) + ")\n";
		element_gui << "			return new AggregatedValidationResult(page" + std::to_string(i + 1) + "group);\n";
	}
	element_gui << "	}\n\n";
	element_gui.close();
}

int main() {

	Image icon = LoadImage("mcreator.png");

	Color dark;
	dark.r = 38;
	dark.g = 38;
	dark.b = 38;

	Color grey;
	grey.r = 63;
	grey.g = 64;
	grey.b = 61;

	InitWindow(screenWidth, screenHeight, "MCreator Plugin Wizard");
	SetWindowIcon(icon);
	SetWindowState(FLAG_VSYNC_HINT);
	GuiLoadStyle("styles/dark/dark.rgs");

	GuiComponentSources sources;
	ComponentType current_type = NO_TYPE;
	PluginInfo info;
	Components components;

	bool hasSaveFile = false;
	bool viewDeleteDialog = false;
	bool viewPreferencesMenu = false;
	bool creatingPlugin = false;
	bool editingPlugin = false;
	bool canSetType = false;
	bool editingWidget = false;

	int widgetIndex[2];
	int tempIndex;

	Camera3D camera = { 0 };
	camera.position = { 30.0f, 20.0f, 30.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 70.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	const int numBlocks = 15;

	Texture2D texture = LoadTexture("mcreator.png");

	buildOrLoadSaves(hasSaveFile, info, sources, components);

	while (!WindowShouldClose()) {

		float sqrtMouse = sqrt(pow(GetMouseX(), 2) + pow(GetMouseY(), 2));

		double time = GetTime();
		float scale = (2.0f + (float)sin(time)) * 0.7f;
		double cameraTime = time * 0.3;
		camera.position.x = (float)cos(cameraTime) * 40.0f + (sqrtMouse * 0.01);
		camera.position.z = (float)sin(cameraTime) * 40.0f + (sqrtMouse * 0.01);
		camera.position.y = (float)tan(cameraTime) * 40.0f + (sqrtMouse * 0.01);

		BeginDrawing();

		BeginMode3D(camera);

		ClearBackground(dark);

		DrawGrid(10, 5.0f);

		for (int x = 0; x < numBlocks; x++)
		{
			for (int y = 0; y < numBlocks; y++)
			{
				for (int z = 0; z < numBlocks; z++)
				{
					float blockScale = (x + y + z) / 30.0f;
					float scatter = sinf(blockScale * 20.0f + (float)(time * 4.0f));
					Vector3 cubePos = {
						(float)(x - numBlocks / 2) * (scale * 3.0f) + scatter ,
						(float)(y - numBlocks / 2) * (scale * 2.0f) + scatter,
						(float)(z - numBlocks / 2) * (scale * 3.0f) + scatter
					};
					Color cubeColor = ColorFromHSV((float)(((x + y + z) * 18) % 360), 0.75f, 0.9f);
					float cubeSize = (2.4f - scale) * blockScale;
					DrawCube(cubePos, cubeSize, cubeSize, cubeSize, cubeColor);
				}
			}
		}

		Vector3 position = { 0.0f, 6.0f, 0.0f };
		DrawBillboard(camera, texture, position, 11.0f, WHITE);

		EndMode3D();

		if (!viewPreferencesMenu && !creatingPlugin && !editingPlugin && !viewDeleteDialog) {
			if (GuiButton(sources.button1Rect, (hasSaveFile ? "Load Plugin" : "Create New Plugin"))) {
				if (hasSaveFile)
					editingPlugin = true;
				else
					creatingPlugin = true;
			}

			if (GuiButton(sources.button2Rect, "Delete Current Plugin") && hasSaveFile)
				viewDeleteDialog = true;

			GuiButton(sources.button3Rect, "Preferences Menu");
		}

		if (viewDeleteDialog) {
			DrawRectangle((screenWidth - 506) / 2, (screenHeight - 256) / 2, 506, 256, BLACK);
			DrawRectangle((screenWidth - 500) / 2, (screenHeight - 250) / 2, 500, 250, grey);
			DrawText("Are you sure you want to delete this plugin?", (screenWidth - 370) / 2, (screenHeight - 75) / 2, 17, WHITE);
			if (GuiButton(sources.deleteDialogButton1, "Yes")) {
				viewDeleteDialog = false;
				hasSaveFile = false;
				deleteAllDirs(info);
			}
			if (GuiButton(sources.deleteDialogButton2, "No"))
				viewDeleteDialog = false;
		}

		if (creatingPlugin) {
			GuiPanel(sources.creationPanelRect, "Plugin Creation");
			DrawText("Plugin Name:", (screenWidth - 300) / 2, (screenHeight - 350) / 2, 15, WHITE);
			GuiTextBox(sources.textbox1Rect, info.name, 64, sources.textbox1enabled);
			DrawText("Plugin ID:", (screenWidth - 300) / 2, (screenHeight - 220) / 2, 15, WHITE);
			GuiTextBox(sources.textbox2Rect, info.id, 64, sources.textbox2enabled);
			DrawText("Weight:", (screenWidth - 300) / 2, (screenHeight - 100) / 2, 15, WHITE);
			GuiSpinner(sources.spinner1Rect, "", &info.weight, 0, 9999, false);
			DrawText("Author:", (screenWidth - 300) / 2, (screenHeight + 20) / 2, 15, WHITE);
			GuiTextBox(sources.textbox3Rect, info.author, 64, sources.textbox3enabled);
			DrawText("Description:", (screenWidth - 300) / 2, (screenHeight + 140) / 2, 15, WHITE);
			GuiTextBox(sources.textbox4Rect, info.description, 64, sources.textbox4enabled);
			DrawText("Credits:", (screenWidth - 300) / 2, (screenHeight + 260) / 2, 15, WHITE);
			GuiTextBox(sources.textbox5Rect, info.credit, 64, sources.textbox5enabled);


			if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
				int tempX = GetMouseX();
				int tempY = GetMouseY();
				Vector2 pos = { tempX, tempY };

				sources.textbox1enabled = false;
				sources.textbox2enabled = false;
				sources.textbox3enabled = false;
				sources.textbox4enabled = false;
				sources.textbox5enabled = false;

				if (CheckCollisionPointRec(pos, sources.textbox1Rect))
					sources.textbox1enabled = true;
				if (CheckCollisionPointRec(pos, sources.textbox2Rect))
					sources.textbox2enabled = true;
				if (CheckCollisionPointRec(pos, sources.textbox3Rect))
					sources.textbox3enabled = true;
				if (CheckCollisionPointRec(pos, sources.textbox4Rect))
					sources.textbox4enabled = true;
				if (CheckCollisionPointRec(pos, sources.textbox5Rect))
					sources.textbox5enabled = true;
			}

			if (GuiButton(sources.finishPluginRect, "Create")) {
				creatingPlugin = false;
				hasSaveFile = true;
				buildJsonSave(info);
				buildJavaLauncher(info);
				save(info);
			}
		}

		if (editingPlugin && current_type == NO_TYPE) {
			GuiGroupBox(sources.editingPluginText, "Widget Selector");

			if (canSetType) {
				if (GuiButton(sources.checkboxRect, "add checkbox"))
					current_type = CHECKBOX_TYPE;
				if (GuiButton(sources.textfieldRect, "add textfield"))
					current_type = TEXTFIELD_TYPE;
				if (GuiButton(sources.spinnerRect, "add number field"))
					current_type = NUMBER_TYPE;
				if (GuiButton(sources.emptyboxRect, "add empty box"))
					current_type = EMPTY_BOX;
				if (GuiButton(sources.texturesRect, "add texture selector"))
					current_type = TEXTURE_TYPE;
				if (GuiButton(sources.modelsRect, "add model selector"))
					current_type = MODEL_TYPE;
				if (GuiButton(sources.itemselectorRect, "add item selector"))
					current_type = ITEM_TYPE;
				if (GuiButton(sources.staticdropRect, "add static dropdown"))
					current_type = DROPDOWN_TYPE;
			}
			else
				canSetType = true;

			int view = GuiListView(sources.mainScrollPane, components.panel_list[sources.selectedPage].c_str(), &sources.index, sources.selected);
			sources.selected = view;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (view != -1)
					sources.cache = view;
				if (sources.old == view) {
					view = -1;
					sources.selected = -1;
				}
			}

			sources.old = view;

			//add and remove page buttons
			if (GuiButton(sources.addpagebuttonRec, "add page")) {
				sources.pagesCount++;
				sources.pages += ("\n" + std::to_string(sources.pagesCount));
				components.indexes[sources.pagesCount - 1] = 0;
			}
			if (GuiButton(sources.removepagebuttonRec, "remove page")) {
				if (sources.pagesCount > 1) {
					sources.pagesCount--;
					std::string newStr = "";
					for (int i = 1; i <= sources.pagesCount; i++) {
						newStr += std::to_string(i) + (sources.pagesCount > i ? "\n" : "");
					}
					sources.pages = newStr;
				}
			}

			//pages list
			GuiGroupBox(sources.pageborderRec, "Pages");
			sources.selectedPage = GuiListView(sources.pagelistRec, sources.pages.c_str(), &sources.pageIndex, sources.selectedPage);

			//right side buttons
			if (GuiButton(sources.editwidgetRec, "edit widget")) {
				editingWidget = true;
				for (int i = 0; i < components.widgets[sources.selectedPage].size(); i++)
					if (components.widgets[sources.selectedPage][i].page_index == sources.cache) {
						Components::Widget tempWidget = components.widgets[sources.selectedPage][i];
						ComponentType type = tempWidget.component_type;
						widgetIndex[0] = sources.selectedPage;
						widgetIndex[1] = i;
						tempIndex = tempWidget.page_index;
						switch (type) {
						case CHECKBOX_TYPE:
							std::strcpy(sources.checkboxname, tempWidget.name.c_str());
							std::strcpy(sources.checkboxlabel, tempWidget.label.c_str());
							std::strcpy(sources.checkboxtooltip, tempWidget.has_tooltip.c_str());
							sources.checkboxappendEnabled = (tempWidget.should_append == "yes" ? true : false);
							break;
						case TEXTFIELD_TYPE:
							std::strcpy(sources.textfieldname, tempWidget.name.c_str());
							std::strcpy(sources.textfieldlabel, tempWidget.label.c_str());
							std::strcpy(sources.textfieldtooltip, tempWidget.has_tooltip.c_str());
							sources.textfieldlength = tempWidget.length;
							sources.textfieldvalidate = (tempWidget.is_validated == "yes" ? true : false);
							sources.textfieldelementtext = (tempWidget.has_elementname == "yes" ? true : false);
							break;
						case NUMBER_TYPE:
							std::strcpy(sources.numberfieldname, tempWidget.name.c_str());
							std::strcpy(sources.numberfieldlabel, tempWidget.label.c_str());
							std::strcpy(sources.numberfieldtooltip, tempWidget.has_tooltip.c_str());
							sources.numberfieldstep = tempWidget.step;
							sources.numberfieldmax = tempWidget.max;
							sources.numberfieldmin = tempWidget.min;
							break;
						case TEXTURE_TYPE:
							std::strcpy(sources.textureselectorname, tempWidget.name.c_str());
							std::strcpy(sources.textureselectorlabel, tempWidget.label.c_str());
							std::strcpy(sources.textureselectortooltip, tempWidget.has_tooltip.c_str());
							int index1;
							if (tempWidget.selector_content == "block_textures")
								index1 = 0;
							else if (tempWidget.selector_content == "item_textures")
								index1 = 1;
							else if (tempWidget.selector_content == "entity_textures")
								index1 = 2;
							else if (tempWidget.selector_content == "effect_textures")
								index1 = 3;
							else if (tempWidget.selector_content == "particle_textures")
								index1 = 4;
							else if (tempWidget.selector_content == "screen_textures")
								index1 = 5;
							else if (tempWidget.selector_content == "armor_textures")
								index1 = 6;
							else if (tempWidget.selector_content == "other_textures")
								index1 = 7;
							sources.textureselectorindex = index1;
							break;
						case MODEL_TYPE:
							std::strcpy(sources.modelselectorname, tempWidget.name.c_str());
							std::strcpy(sources.modelselectorlabel, tempWidget.label.c_str());
							std::strcpy(sources.modelselectortooltip, tempWidget.has_tooltip.c_str());
							int index2;
							if (tempWidget.selector_content == "java_models")
								index2 = 0;
							else if (tempWidget.selector_content == "json_models")
								index2 = 1;
							else if (tempWidget.selector_content == "obj_models")
								index2 = 2;
							sources.modelselectorindex = index2;
							break;
						case ITEM_TYPE:
							std::strcpy(sources.itemselectorname, tempWidget.name.c_str());
							std::strcpy(sources.itemselectorlabel, tempWidget.label.c_str());
							std::strcpy(sources.itemselectortooltip, tempWidget.has_tooltip.c_str());
							int index3;
							if (tempWidget.selector_content == "items")
								index3 = 0;
							else if (tempWidget.selector_content == "blocks")
								index3 = 1;
							sources.itemselectorindex = index3;
							break;
						case DROPDOWN_TYPE:
							std::strcpy(sources.dropdownname, tempWidget.name.c_str());
							std::strcpy(sources.dropdownlabel, tempWidget.label.c_str());
							std::strcpy(sources.dropdowntooltip, tempWidget.has_tooltip.c_str());
							bool first1 = true;
							std::string membersStr = "";
							for (std::string member : tempWidget.members) {
								if (first1) {
									first1 = false;
									membersStr += member;
								}
								else
									membersStr += ", " + member;
							}
							std::strcpy(sources.dropdownmembers, membersStr.c_str());
							break;
						}
						if (type != EMPTY_BOX)
							current_type = type;
					}
			}
			if (GuiButton(sources.deletewidgetRec, "delete widget")) {
				std::vector<Components::Widget> widgetslist;
				std::string panellist = "";
				int offset = 0;
				bool first2 = true;
				for (Components::Widget widget : components.widgets[sources.selectedPage]) {
					if (widget.page_index == sources.cache) {
						offset++;
						components.indexes[sources.selectedPage]--;
					}
					else {
						switch (widget.component_type) {
						case CHECKBOX_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"Checkbox - " + widget.name;
							widget.page_index -= offset;
							break;
						case TEXTFIELD_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"TextField - " + widget.name;
							widget.page_index -= offset;
							break;
						case NUMBER_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"NumberField - " + widget.name;
							widget.page_index -= offset;
							break;
						case EMPTY_BOX:
							panellist += (!first2 ? "\n" : "") + (std::string)"Empty Box";
							widget.page_index -= offset;
							break;
						case TEXTURE_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"Texture Selector - " + widget.name;
							widget.page_index -= offset;
							break;
						case MODEL_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"Model Selector - " + widget.name;
							widget.page_index -= offset;
							break;
						case ITEM_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"Item Selector - " + widget.name;
							widget.page_index -= offset;
							break;
						case DROPDOWN_TYPE:
							panellist += (!first2 ? "\n" : "") + (std::string)"Static Dropdown - " + widget.name;
							widget.page_index -= offset;
							break;
						}
						first2 = false;
						widgetslist.push_back(widget);
					}
				}
				components.widgets[sources.selectedPage] = widgetslist;
				components.panel_list[sources.selectedPage] = panellist;
			}
			if (GuiButton(sources.mainmenuRec, "main menu")) {
				editingPlugin = false;
				canSetType = false;
			}

			//left botton save and export buttons
			if (GuiButton(sources.savebuttonRec, "save plugin"))
				saveComponentData(sources, components);
			if (GuiButton(sources.exportbuttonRec, "export plugin"))
				exportPlugin(info, components, sources.pagesCount);
		}

		if (current_type != NO_TYPE) {
			if (current_type == CHECKBOX_TYPE) {
				GuiPanel(sources.checkboxDialog, "Checkbox Editor");
				DrawText("Checkbox variable name:", 370, 200, 15, WHITE);
				GuiTextBox(sources.checkboxnameRec, sources.checkboxname, 64, sources.checkboxnameEnabled);
				DrawText("Checkbox label text:", 370, 235, 15, WHITE);
				GuiTextBox(sources.checkboxlabelRec, sources.checkboxlabel, 64, sources.checkboxlabelEnabled);
				DrawText("Checkbox tooltip source:", 370, 270, 15, WHITE);
				GuiTextBox(sources.checkboxtooltipRec, sources.checkboxtooltip, 64, sources.checkboxtooltipEnabled);
				DrawText("Append common label:", 370, 305, 15, WHITE);
				GuiCheckBox(sources.checkboxappendRec, "Check to enable", sources.checkboxappendEnabled);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttonRec, "add")) {
						Components::Widget checkbox;
						checkbox.component_type = CHECKBOX_TYPE;
						checkbox.name = sources.checkboxname;
						checkbox.label = sources.checkboxlabel;
						checkbox.has_tooltip = sources.checkboxtooltip;
						checkbox.page_index = components.indexes.at(sources.selectedPage);
						checkbox.should_append = (sources.checkboxappendEnabled ? "yes" : "no");
						components.widgets[sources.selectedPage].push_back(checkbox);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"Checkbox - " + (std::string)sources.checkboxname);
						*sources.checkboxname = { 0 };
						*sources.checkboxlabel = { 0 };
						*sources.checkboxtooltip = { 0 };
						sources.checkboxappendEnabled = false;
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttonRec, "edit")) {
						Components::Widget checkbox;
						checkbox.component_type = CHECKBOX_TYPE;
						checkbox.name = sources.checkboxname;
						checkbox.label = sources.checkboxlabel;
						checkbox.has_tooltip = sources.checkboxtooltip;
						checkbox.page_index = tempIndex;
						checkbox.should_append = (sources.checkboxappendEnabled ? "yes" : "no");
						components.widgets[widgetIndex[0]][widgetIndex[1]] = checkbox;
						*sources.checkboxname = { 0 };
						*sources.checkboxlabel = { 0 };
						*sources.checkboxtooltip = { 0 };
						sources.checkboxappendEnabled = false;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}
				if (GuiButton(sources.cancelbuttonRec, "cancel")) {
					current_type = NO_TYPE;
					*sources.checkboxname = { 0 };
					*sources.checkboxlabel = { 0 };
					*sources.checkboxtooltip = { 0 };
					sources.checkboxappendEnabled = false;
					editingWidget = false;
				}
				
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.checkboxnameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.checkboxnameRec);
					sources.checkboxlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.checkboxlabelRec);
					sources.checkboxtooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.checkboxtooltipRec);
					if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.checkboxappendRec))
						sources.checkboxappendEnabled = !sources.checkboxappendEnabled;
				}
			}
			else if (current_type == TEXTFIELD_TYPE) {
				GuiPanel(sources.textfieldDialog, "TextField Editor");
				DrawText("TextField variable name:", 370, 185, 15, WHITE);
				GuiTextBox(sources.textfieldnameRec, sources.textfieldname, 64, sources.textfieldnameEnabled);
				DrawText("TextField label text:", 370, 220, 15, WHITE);
				GuiTextBox(sources.textfieldlabelRec, sources.textfieldlabel, 64, sources.textfieldlabelEnabled);
				DrawText("TextField tooltip source:", 370, 255, 15, WHITE);
				GuiTextBox(sources.textfieldtooltipRec, sources.textfieldtooltip, 64, sources.textfieldtooltipEnabled);
				DrawText("TextField max length:", 370, 290, 15, WHITE);
				GuiSpinner(sources.textfieldlengthRec, "", &sources.textfieldlength, 0, 100, false);
				DrawText("Validate TextField text:", 370, 325, 15, WHITE);
				GuiCheckBox(sources.textfieldvalidateRec, "Check to enable", sources.textfieldvalidate);
				DrawText("Fill with element name:", 370, 360, 15, WHITE);
				GuiCheckBox(sources.textfieldelementtextRec, "Check to enable", sources.textfieldelementtext);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttontextfieldRec, "add")) {
						Components::Widget textfield;
						textfield.component_type = TEXTFIELD_TYPE;
						textfield.name = sources.textfieldname;
						textfield.label = sources.textfieldlabel;
						textfield.has_tooltip = sources.textfieldtooltip;
						textfield.length = sources.textfieldlength;
						textfield.is_validated = (sources.textfieldvalidate ? "yes" : "no");
						textfield.has_elementname = (sources.textfieldelementtext ? "yes" : "no");
						textfield.page_index = components.indexes.at(sources.selectedPage);
						components.widgets[sources.selectedPage].push_back(textfield);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"TextField - " + (std::string)sources.textfieldname);
						*sources.textfieldname = { 0 };
						*sources.textfieldlabel = { 0 };
						*sources.textfieldtooltip = { 0 };
						sources.textfieldlength = 0;
						sources.textfieldvalidate = false;
						sources.textfieldelementtext = false;
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttontextfieldRec, "edit")) {
						Components::Widget textfield;
						textfield.component_type = TEXTFIELD_TYPE;
						textfield.name = sources.textfieldname;
						textfield.label = sources.textfieldlabel;
						textfield.has_tooltip = sources.textfieldtooltip;
						textfield.length = sources.textfieldlength;
						textfield.is_validated = (sources.textfieldvalidate ? "yes" : "no");
						textfield.has_elementname = (sources.textfieldelementtext ? "yes" : "no");
						textfield.page_index = tempIndex;
						components.widgets[widgetIndex[0]][widgetIndex[1]] = textfield;
						*sources.textfieldname = { 0 };
						*sources.textfieldlabel = { 0 };
						*sources.textfieldtooltip = { 0 };
						sources.textfieldlength = 0;
						sources.textfieldvalidate = false;
						sources.textfieldelementtext = false;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}
				if (GuiButton(sources.cancelbuttontextfieldRec, "cancel")) {
					*sources.textfieldname = { 0 };
					*sources.textfieldlabel = { 0 };
					*sources.textfieldtooltip = { 0 };
					sources.textfieldlength = 0;
					sources.textfieldvalidate = false;
					sources.textfieldelementtext = false;
					editingWidget = false;
					current_type = NO_TYPE;
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.textfieldnameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textfieldnameRec);
					sources.textfieldlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textfieldlabelRec);
					sources.textfieldtooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textfieldtooltipRec);
					if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textfieldvalidateRec))
						sources.textfieldvalidate = !sources.textfieldvalidate;
					if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textfieldelementtextRec))
						sources.textfieldelementtext = !sources.textfieldelementtext;
				}
			}
			else if (current_type == NUMBER_TYPE) {
				GuiPanel(sources.numberfieldDialog, "NumberField Editor");
				DrawText("NumberField variable name:", 370, 185, 15, WHITE);
				GuiTextBox(sources.numberfieldnameRec, sources.numberfieldname, 64, sources.numberfieldnameEnabled);
				DrawText("NumberField label text:", 370, 220, 15, WHITE);
				GuiTextBox(sources.numberfieldlabelRec, sources.numberfieldlabel, 64, sources.numberfieldlabelEnabled);
				DrawText("NumberField tooltip source:", 370, 255, 15, WHITE);
				GuiTextBox(sources.numberfieldtooltipRec, sources.numberfieldtooltip, 64, sources.numberfieldtooltipEnabled);
				DrawText("NumberField step amount:", 370, 290, 15, WHITE);
				GuiSpinner(sources.numberfieldstepRec, "", &sources.numberfieldstep, 0, 10, false);
				DrawText("NumberField max value:", 370, 325, 15, WHITE);
				GuiSpinner(sources.numberfieldmaxRec, "", &sources.numberfieldmax, 0, 100, false);
				DrawText("NumberField min value:", 370, 360, 15, WHITE);
				GuiSpinner(sources.numberfieldminRec, "", &sources.numberfieldmin, -100, 100, false);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttonnumberfieldRec, "add")) {
						Components::Widget numberfield;
						numberfield.component_type = NUMBER_TYPE;
						numberfield.name = sources.numberfieldname;
						numberfield.label = sources.numberfieldlabel;
						numberfield.has_tooltip = sources.numberfieldtooltip;
						numberfield.step = sources.numberfieldstep;
						numberfield.max = sources.numberfieldmax;
						numberfield.min = sources.numberfieldmin;
						numberfield.page_index = components.indexes.at(sources.selectedPage);
						components.widgets[sources.selectedPage].push_back(numberfield);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"NumberField - " + (std::string)sources.numberfieldname);
						*sources.numberfieldname = { 0 };
						*sources.numberfieldlabel = { 0 };
						*sources.numberfieldtooltip = { 0 };
						sources.numberfieldstep = 0;
						sources.numberfieldmax = 0;
						sources.numberfieldmin = 0;
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttonnumberfieldRec, "edit")) {
						Components::Widget numberfield;
						numberfield.component_type = NUMBER_TYPE;
						numberfield.name = sources.numberfieldname;
						numberfield.label = sources.numberfieldlabel;
						numberfield.has_tooltip = sources.numberfieldtooltip;
						numberfield.step = sources.numberfieldstep;
						numberfield.max = sources.numberfieldmax;
						numberfield.min = sources.numberfieldmin;
						numberfield.page_index = tempIndex;
						components.widgets[widgetIndex[0]][widgetIndex[1]] = numberfield;
						*sources.numberfieldname = { 0 };
						*sources.numberfieldlabel = { 0 };
						*sources.numberfieldtooltip = { 0 };
						sources.numberfieldstep = 0;
						sources.numberfieldmax = 0;
						sources.numberfieldmin = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}
				if (GuiButton(sources.cancelbuttonnumberfieldRec, "cancel")) {
					*sources.numberfieldname = { 0 };
					*sources.numberfieldlabel = { 0 };
					*sources.numberfieldtooltip = { 0 };
					sources.numberfieldstep = 0;
					sources.numberfieldmax = 0;
					sources.numberfieldmin = 0;
					editingWidget = false;
					current_type = NO_TYPE;
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.numberfieldnameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.numberfieldnameRec);
					sources.numberfieldlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.numberfieldlabelRec);
					sources.numberfieldtooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.numberfieldtooltipRec);
				}
			}
			else if (current_type == EMPTY_BOX) {
				GuiPanel(sources.emptyboxDialog, "Empty Box Editor");
				if (GuiButton(sources.addbuttonemptyboxRec, "add")) {
					Components::Widget emptybox;
					emptybox.component_type = EMPTY_BOX;
					emptybox.page_index = components.indexes[sources.selectedPage];
					components.widgets[sources.selectedPage].push_back(emptybox);
					components.indexes[sources.selectedPage]++;
					components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"Empty Box");
					current_type = NO_TYPE;
				}
				if (GuiButton(sources.cancelbuttonemptyboxRec, "cancel"))
					current_type = NO_TYPE;
			}
			else if (current_type == TEXTURE_TYPE) {
				GuiPanel(sources.textureselectorDialog, "Texture Selector Editor");
				DrawText("Selector variable name:", 370, 200, 15, WHITE);
				GuiTextBox(sources.textureselectornameRec, sources.textureselectorname, 64, sources.textureselectornameEnabled);
				DrawText("Selector label text:", 370, 235, 15, WHITE);
				GuiTextBox(sources.textureselectorlabelRec, sources.textureselectorlabel, 64, sources.textureselectorlabelEnabled);
				DrawText("Selector tooltip source:", 370, 270, 15, WHITE);
				GuiTextBox(sources.textureselectortooltipRec, sources.textureselectortooltip, 64, sources.textureselectortooltipEnabled);
				DrawText("Selector texture type:", 370, 305, 15, WHITE);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttontextureRec, "add")) {
						Components::Widget texture_selector;
						texture_selector.component_type = TEXTURE_TYPE;
						texture_selector.name = sources.textureselectorname;
						texture_selector.label = sources.textureselectorlabel;
						texture_selector.has_tooltip = sources.textureselectortooltip;
						switch (sources.textureselectorindex) {
						case 0:
							texture_selector.selector_content = "block_textures";
							break;
						case 1:
							texture_selector.selector_content = "item_textures";
							break;
						case 2:
							texture_selector.selector_content = "entity_textures";
							break;
						case 3:
							texture_selector.selector_content = "effect_textures";
							break;
						case 4:
							texture_selector.selector_content = "particle_textures";
							break;
						case 5:
							texture_selector.selector_content = "screen_textures";
							break;
						case 6:
							texture_selector.selector_content = "armor_textures";
							break;
						case 7:
							texture_selector.selector_content = "other_textures";
							break;
						}
						texture_selector.page_index = components.indexes.at(sources.selectedPage);
						components.widgets[sources.selectedPage].push_back(texture_selector);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"Texture Selector - " + (std::string)sources.textureselectorname);
						*sources.textureselectorname = { 0 };
						*sources.textureselectorlabel = { 0 };
						*sources.textureselectortooltip = { 0 };
						sources.textureselectorEnabled = false;
						sources.textureselectorindex = 0;
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttontextureRec, "edit")) {
						Components::Widget texture_selector;
						texture_selector.component_type = TEXTURE_TYPE;
						texture_selector.name = sources.textureselectorname;
						texture_selector.label = sources.textureselectorlabel;
						texture_selector.has_tooltip = sources.textureselectortooltip;
						switch (sources.textureselectorindex) {
						case 0:
							texture_selector.selector_content = "block_textures";
							break;
						case 1:
							texture_selector.selector_content = "item_textures";
							break;
						case 2:
							texture_selector.selector_content = "entity_textures";
							break;
						case 3:
							texture_selector.selector_content = "effect_textures";
							break;
						case 4:
							texture_selector.selector_content = "particle_textures";
							break;
						case 5:
							texture_selector.selector_content = "screen_textures";
							break;
						case 6:
							texture_selector.selector_content = "armor_textures";
							break;
						case 7:
							texture_selector.selector_content = "other_textures";
							break;
						}
						texture_selector.page_index = tempIndex;
						components.widgets[widgetIndex[0]][widgetIndex[1]] = texture_selector;
						*sources.textureselectorname = { 0 };
						*sources.textureselectorlabel = { 0 };
						*sources.textureselectortooltip = { 0 };
						sources.textureselectorEnabled = false;
						sources.textureselectorindex = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				GuiDropdownBox(sources.textureselectortypeRec, sources.textureselectortext.c_str(), &sources.textureselectorindex, sources.textureselectorEnabled);

				if (!sources.textureselectorEnabled) {
					if (GuiButton(sources.cancelbuttontextureRec, "cancel")) {
						*sources.textureselectorname = { 0 };
						*sources.textureselectorlabel = { 0 };
						*sources.textureselectortooltip = { 0 };
						sources.textureselectorEnabled = false;
						sources.textureselectorindex = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.textureselectornameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textureselectornameRec);
					sources.textureselectorlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textureselectorlabelRec);
					sources.textureselectortooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textureselectortooltipRec);
					if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.textureselectortypeRec))
						sources.textureselectorEnabled = !sources.textureselectorEnabled;
				}
			}
			else if (current_type == MODEL_TYPE) {
				GuiPanel(sources.modelselectorDialog, "Model Selector Editor");
				DrawText("Selector variable name:", 370, 200, 15, WHITE);
				GuiTextBox(sources.modelselectornameRec, sources.modelselectorname, 64, sources.modelselectornameEnabled);
				DrawText("Selector label text:", 370, 235, 15, WHITE);
				GuiTextBox(sources.modelselectorlabelRec, sources.modelselectorlabel, 64, sources.modelselectorlabelEnabled);
				DrawText("Selector tooltip source:", 370, 270, 15, WHITE);
				GuiTextBox(sources.modelselectortooltipRec, sources.modelselectortooltip, 64, sources.modelselectortooltipEnabled);
				DrawText("Selector texture type:", 370, 305, 15, WHITE);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttonmodelRec, "add")) {
						Components::Widget model_selector;
						model_selector.component_type = MODEL_TYPE;
						model_selector.name = sources.modelselectorname;
						model_selector.label = sources.modelselectorlabel;
						model_selector.has_tooltip = sources.modelselectortooltip;
						switch (sources.modelselectorindex) {
						case 0:
							model_selector.selector_content = "java_models";
							break;
						case 1:
							model_selector.selector_content = "json_models";
							break;
						case 2:
							model_selector.selector_content = "obj_models";
							break;
						}
						model_selector.page_index = components.indexes.at(sources.selectedPage);
						components.widgets[sources.selectedPage].push_back(model_selector);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"Model Selector - " + (std::string)sources.modelselectorname);
						*sources.modelselectorname = { 0 };
						*sources.modelselectorlabel = { 0 };
						*sources.modelselectortooltip = { 0 };
						sources.modelselectorEnabled = false;
						sources.modelselectorindex = 0;
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttonmodelRec, "edit")) {
						Components::Widget model_selector;
						model_selector.component_type = MODEL_TYPE;
						model_selector.name = sources.modelselectorname;
						model_selector.label = sources.modelselectorlabel;
						model_selector.has_tooltip = sources.modelselectortooltip;
						switch (sources.modelselectorindex) {
						case 0:
							model_selector.selector_content = "java_models";
							break;
						case 1:
							model_selector.selector_content = "json_models";
							break;
						case 2:
							model_selector.selector_content = "obj_models";
							break;
						}
						model_selector.page_index = tempIndex;
						components.widgets[widgetIndex[0]][widgetIndex[1]] = model_selector;
						*sources.modelselectorname = { 0 };
						*sources.modelselectorlabel = { 0 };
						*sources.modelselectortooltip = { 0 };
						sources.modelselectorEnabled = false;
						sources.modelselectorindex = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				GuiDropdownBox(sources.modelselectortypeRec, sources.modelselectortext.c_str(), &sources.modelselectorindex, sources.modelselectorEnabled);

				if (!sources.modelselectorEnabled) {
					if (GuiButton(sources.cancelbuttonmodelRec, "cancel")) {
						*sources.modelselectorname = { 0 };
						*sources.modelselectorlabel = { 0 };
						*sources.modelselectortooltip = { 0 };
						sources.modelselectorEnabled = false;
						sources.modelselectorindex = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.modelselectornameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.modelselectornameRec);
					sources.modelselectorlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.modelselectorlabelRec);
					sources.modelselectortooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.modelselectortooltipRec);
					if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.modelselectortypeRec))
						sources.modelselectorEnabled = !sources.modelselectorEnabled;
				}
			}
			else if (current_type == ITEM_TYPE) {
				GuiPanel(sources.itemselectorDialog, "Item Selector Editor");
				DrawText("Selector variable name:", 370, 200, 15, WHITE);
				GuiTextBox(sources.itemselectornameRec, sources.itemselectorname, 64, sources.itemselectornameEnabled);
				DrawText("Selector label text:", 370, 235, 15, WHITE);
				GuiTextBox(sources.itemselectorlabelRec, sources.itemselectorlabel, 64, sources.itemselectorlabelEnabled);
				DrawText("Selector tooltip source:", 370, 270, 15, WHITE);
				GuiTextBox(sources.itemselectortooltipRec, sources.itemselectortooltip, 64, sources.itemselectortooltipEnabled);
				DrawText("Selector texture type:", 370, 305, 15, WHITE);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttonitemRec, "add")) {
						Components::Widget item_selector;
						item_selector.component_type = ITEM_TYPE;
						item_selector.name = sources.itemselectorname;
						item_selector.label = sources.itemselectorlabel;
						item_selector.has_tooltip = sources.itemselectortooltip;
						switch (sources.itemselectorindex) {
						case 0:
							item_selector.selector_content = "items";
							break;
						case 1:
							item_selector.selector_content = "blocks";
							break;
						}
						item_selector.page_index = components.indexes.at(sources.selectedPage);
						components.widgets[sources.selectedPage].push_back(item_selector);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"Item Selector - " + (std::string)sources.itemselectorname);
						*sources.itemselectorname = { 0 };
						*sources.itemselectorlabel = { 0 };
						*sources.itemselectortooltip = { 0 };
						sources.itemselectorEnabled = false;
						sources.itemselectorindex = 0;
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttonitemRec, "edit")) {
						Components::Widget item_selector;
						item_selector.component_type = ITEM_TYPE;
						item_selector.name = sources.itemselectorname;
						item_selector.label = sources.itemselectorlabel;
						item_selector.has_tooltip = sources.itemselectortooltip;
						switch (sources.itemselectorindex) {
						case 0:
							item_selector.selector_content = "items";
							break;
						case 1:
							item_selector.selector_content = "blocks";
							break;
						}
						item_selector.page_index = tempIndex;
						components.widgets[widgetIndex[0]][widgetIndex[1]] = item_selector;
						*sources.itemselectorname = { 0 };
						*sources.itemselectorlabel = { 0 };
						*sources.itemselectortooltip = { 0 };
						sources.itemselectorEnabled = false;
						sources.itemselectorindex = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				GuiDropdownBox(sources.itemselectortypeRec, sources.itemselectortext.c_str(), &sources.itemselectorindex, sources.itemselectorEnabled);

				if (!sources.itemselectorEnabled) {
					if (GuiButton(sources.cancelbuttonitemRec, "cancel")) {
						*sources.itemselectorname = { 0 };
						*sources.itemselectorlabel = { 0 };
						*sources.itemselectortooltip = { 0 };
						sources.itemselectorEnabled = false;
						sources.itemselectorindex = 0;
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.itemselectornameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.itemselectornameRec);
					sources.itemselectorlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.itemselectorlabelRec);
					sources.itemselectortooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.itemselectortooltipRec);
					if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.itemselectortypeRec))
						sources.itemselectorEnabled = !sources.itemselectorEnabled;
				}
			}
			else if (current_type == DROPDOWN_TYPE) {
				GuiPanel(sources.dropdownDialog, "Dropdown Editor");
				DrawText("Dropdown variable name:", 370, 200, 15, WHITE);
				GuiTextBox(sources.dropdownnameRec, sources.dropdownname, 64, sources.dropdownnameEnabled);
				DrawText("Dropdown label text:", 370, 235, 15, WHITE);
				GuiTextBox(sources.dropdownlabelRec, sources.dropdownlabel, 64, sources.dropdownlabelEnabled);
				DrawText("Dropdown tooltip source:", 370, 270, 15, WHITE);
				GuiTextBox(sources.dropdowntooltipRec, sources.dropdowntooltip, 64, sources.dropdowntooltipEnabled);
				DrawText("Dropdown static members:", 370, 305, 15, WHITE);
				GuiTextBox(sources.dropdownmembersRec, sources.dropdownmembers, 64, sources.dropdownmembersEnabled);

				if (!editingWidget) {
					if (GuiButton(sources.addbuttondropdownRec, "add")) {
						Components::Widget dropdown;
						dropdown.component_type = DROPDOWN_TYPE;
						dropdown.name = sources.dropdownname;
						dropdown.label = sources.dropdownlabel;
						dropdown.has_tooltip = sources.dropdowntooltip;
						std::vector<std::string> members;
						std::string member = "";
						for (int i = 0; i < (sizeof(sources.dropdownmembers) / sizeof(char)) - 1; i++) {
							if (sources.dropdownmembers[i] != ' ' && sources.dropdownmembers[i] != ',' && sources.dropdownmembers[i] != NULL)
								member += sources.dropdownmembers[i];
							else if (sources.dropdownmembers[i] == ',') {
								members.push_back(member);
								member = "";
							}
						}
						members.push_back(member);
						dropdown.members = members;
						dropdown.page_index = components.indexes.at(sources.selectedPage);
						components.widgets[sources.selectedPage].push_back(dropdown);
						components.indexes[sources.selectedPage]++;
						components.panel_list[sources.selectedPage] += ((components.indexes.at(sources.selectedPage) > 1 ? "\n" : "") + (std::string)"Static Dropdown - " + (std::string)sources.dropdownname);
						*sources.dropdownname = { 0 };
						*sources.dropdownlabel = { 0 };
						*sources.dropdowntooltip = { 0 };
						*sources.dropdownmembers = { 0 };
						current_type = NO_TYPE;
					}
				}
				else {
					if (GuiButton(sources.addbuttondropdownRec, "edit")) {
						Components::Widget dropdown;
						dropdown.component_type = DROPDOWN_TYPE;
						dropdown.name = sources.dropdownname;
						dropdown.label = sources.dropdownlabel;
						dropdown.has_tooltip = sources.dropdowntooltip;
						std::vector<std::string> members;
						std::string member = "";
						for (int i = 0; i < (sizeof(sources.dropdownmembers) / sizeof(char)) - 1; i++) {
							if (sources.dropdownmembers[i] != ' ' && sources.dropdownmembers[i] != ',' && sources.dropdownmembers[i] != NULL)
								member += sources.dropdownmembers[i];
							else if (sources.dropdownmembers[i] == ',') {
								members.push_back(member);
								member = "";
							}
						}
						members.push_back(member);
						dropdown.members = members;
						dropdown.page_index = tempIndex;
						components.widgets[widgetIndex[0]][widgetIndex[1]] = dropdown;
						*sources.dropdownname = { 0 };
						*sources.dropdownlabel = { 0 };
						*sources.dropdowntooltip = { 0 };
						*sources.dropdownmembers = { 0 };
						editingWidget = false;
						current_type = NO_TYPE;
					}
				}

				if (GuiButton(sources.cancelbuttondropdownRec, "cancel")) {
					*sources.dropdownname = { 0 };
					*sources.dropdownlabel = { 0 };
					*sources.dropdowntooltip = { 0 };
					*sources.dropdownmembers = { 0 };
					editingWidget = false;
					current_type = NO_TYPE;
				}

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					sources.dropdownnameEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.dropdownnameRec);
					sources.dropdownlabelEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.dropdownlabelRec);
					sources.dropdowntooltipEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.dropdowntooltipRec);
					sources.dropdownmembersEnabled = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, sources.dropdownmembersRec);
				}
			}
		}

		EndDrawing();
	}

	UnloadImage(icon);
	UnloadTexture(texture);
	CloseWindow();

	return 0;
}