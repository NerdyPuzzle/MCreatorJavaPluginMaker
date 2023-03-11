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
		float min;
		float max;
		float step;

		//selectors only
		std::string selector_type;
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

	Rectangle editingPluginText = { 10, 10, 170, 580 };
	Rectangle mainScrollPane = { 200, 10, 750, 580 };
	Rectangle mainPaneContent = { 200, 10, 750, 580 };

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
	float numberfieldstep = 0;
	Rectangle numberfieldmaxRec = { 570, 320, 25, 25 };
	float numberfieldmax = 0;
	Rectangle numberfieldminRec = { 570, 355, 25, 25 };
	float numberfieldmin = 0;
	Rectangle addbuttontextfieldRec = { 500, 405, 100, 30 };
	Rectangle cancelbuttontextfieldRec = { 610, 405, 100, 30 };
};

void save(PluginInfo info) {
	buildDir("saves/" + (std::string)info.name + "/");
	std::ofstream variables("saves/" + (std::string)info.name + "/variables.cfg");
	std::ofstream pluginname("saves/name/plgn.dat");

	pluginname << info.name;

	variables << info.name << std::endl;
	variables << info.id << std::endl;
	variables << info.weight << std::endl;
	variables << info.author << std::endl;
	variables << info.description << std::endl;
	variables << info.credit << std::endl;

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

void buildOrLoadSaves(bool& hasSave, PluginInfo& info) {
	buildDir("saves/name/");
	std::ifstream pluginname("saves/name/plgn.dat");
	std::string name;
	pluginname >> name;
	buildDir("saves/" + name + "/");
	std::ifstream variables("saves/" + name + "/variables.cfg");

	if (variables.is_open()) {
		variables >> info.name;
		variables >> info.id;
		variables >> info.weight;
		variables >> info.author;
		variables >> info.description;
		variables >> info.credit;
		hasSave = true;
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
}

void buildJavaLauncher(PluginInfo info) {
	std::string name = (std::string)info.name;
	lowerCaseString(name);
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

	Camera3D camera = { 0 };
	camera.position = { 30.0f, 20.0f, 30.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 70.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	const int numBlocks = 15;

	Texture2D texture = LoadTexture("mcreator.png");

	// IMPORTANT
	buildOrLoadSaves(hasSaveFile, info);

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
			GuiGroupBox(sources.pageborderRec, "Pages");
			sources.selectedPage = GuiListView(sources.pagelistRec, sources.pages.c_str(), &sources.pageIndex, sources.selectedPage);
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
				if (GuiButton(sources.cancelbuttonRec, "cancel"))
					current_type = NO_TYPE;
				
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
				DrawText("Textfield max length:", 370, 290, 15, WHITE);
				GuiSpinner(sources.textfieldlengthRec, "", &sources.textfieldlength, 0, 100, false);
				DrawText("Validate TextField text:", 370, 325, 15, WHITE);
				GuiCheckBox(sources.textfieldvalidateRec, "Check to enable", sources.textfieldvalidate);
				DrawText("Fill with element name:", 370, 360, 15, WHITE);
				GuiCheckBox(sources.textfieldelementtextRec, "Check to enable", sources.textfieldelementtext);

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
				if (GuiButton(sources.cancelbuttontextfieldRec, "cancel"))
					current_type = NO_TYPE;

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

			}
		}

		EndDrawing();
	}

	UnloadImage(icon);
	UnloadTexture(texture);
	CloseWindow();

	return 0;
}