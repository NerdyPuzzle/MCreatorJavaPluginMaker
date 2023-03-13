#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include <utility>
#include <string>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <direct.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace gez {

    template <typename T>
    class JavaList {
    public:
        JavaList() {}

        int size() const { return data_.size(); }
        bool isEmpty() const { return data_.empty(); }
        void add(const T& element) { data_.push_back(element); }
        void add(int index, const T& element) { data_.insert(data_.begin() + index, element); }
        T get(int index) const { return data_[index]; }
        T remove(int index) {
            T removed_element = data_[index];
            data_.erase(data_.begin() + index);
            return removed_element;
        }
        void clear() { data_.clear(); }
        void forEach(std::function<void(const T&)> function) const {
            for (const T& element : data_) {
                function(element);
            }
        }
        bool contains(const T& element) const {
            return std::find(data_.begin(), data_.end(), element) != data_.end();
        }
        int indexOf(const T& element) const {
            auto it = std::find(data_.begin(), data_.end(), element);
            return (it == data_.end() ? -1 : std::distance(data_.begin(), it));
        }
        int lastIndexOf(const T& element) const {
            auto rit = std::find(data_.rbegin(), data_.rend(), element);
            return (rit == data_.rend() ? -1 : std::distance(rit, data_.rend() - 1));
        }
        T* toArray() { return data_.data(); }
        void sort(std::function<bool(const T&, const T&)> compare) {
            std::sort(data_.begin(), data_.end(), compare);
        }
        void reverse() { std::reverse(data_.begin(), data_.end()); }
        void set(int index, const T& element) { data_[index] = element; }
        static JavaList<T> of(std::initializer_list<T> elements) {
            JavaList<T> list;
            for (const T& element : elements) {
                list.add(element);
            }
            return list;
        }

    private:
        std::vector<T> data_;
    };

    template<typename K, typename V>
    class JavaMap {
    public:
        void put(const K& key, const V& value) {
            mMap.insert(std::pair<K, V>(key, value));
        }

        V get(const K& key) const {
            typename std::map<K, V>::const_iterator it = mMap.find(key);
            if (it != mMap.end()) {
                return it->second;
            }
            return V();
        }

        void remove(const K& key) {
            mMap.erase(key);
        }

        int size() const {
            return mMap.size();
        }

        bool isEmpty() const {
            return mMap.empty();
        }

        void clear() {
            mMap.clear();
        }

        bool containsKey(const K& key) const {
            return mMap.count(key) != 0;
        }

        bool containsValue(const V& value) const {
            for (typename std::map<K, V>::const_iterator it = mMap.begin(); it != mMap.end(); ++it) {
                if (it->second == value) {
                    return true;
                }
            }
            return false;
        }

        std::vector<K> keySet() const {
            std::vector<K> keys;
            for (typename std::map<K, V>::const_iterator it = mMap.begin(); it != mMap.end(); ++it) {
                keys.push_back(it->first);
            }
            return keys;
        }

        std::vector<V> values() const {
            std::vector<V> vals;
            for (typename std::map<K, V>::const_iterator it = mMap.begin(); it != mMap.end(); ++it) {
                vals.push_back(it->second);
            }
            return vals;
        }

    private:
        std::map<K, V> mMap;
    };

    class JsonUtil {
    public:
        std::string getProperty(std::string name, std::string property) {
            return '"' + name + '"' + ':' + " " + '"' + property + '"';
        }
        std::string getProperty(std::string name, bool property) {
            return '"' + name + '"' + ':' + " " + (property ? "true" : "false");
        }
        std::string getProperty(std::string name, const char* property) {
            return '"' + name + '"' + ':' + " " + ("" + (std::string)property);
        }
        std::string simpleString(std::string name) {
            return '"' + name + '"';
        }
    };

    class GuiBuilder {
    public:
        char getKeyInput() {
            char input = _getch();
            return input;
        }
        void displayTextDialog(std::string text, int width, int height) {
            for (int i = 0; i < width; i++)
                std::cout << "=";
            std::cout << std::endl;
            for (int i = 0; i < height; i++) {
                if (i != height / 2) {
                    std::cout << "||";
                    for (int h = 0; h < width - 4; h++)
                        std::cout << " ";
                    std::cout << "||" << std::endl;
                }
                else {
                    int stringLength = text.length();
                    int placement = (width - stringLength) / 2;
                    int spaces = width - stringLength;
                    std::cout << "||";
                    int counter = 0;
                    while (counter < spaces - 4) {
                        std::cout << " ";
                        counter++;
                        if (counter == placement - 2)
                            std::cout << text;
                    }
                    std::cout << "||" << std::endl;
                }
            }
            for (int i = 0; i < width; i++)
                std::cout << "=";
            std::cout << std::endl;
        }
        void displayListDialog(JavaList<std::string> text, int width, int height) {
            for (int i = 0; i < width; i++)
                std::cout << "=";
            std::cout << std::endl;
            int arraySize = text.size();
            int emptyPanel = (height - arraySize) / 2;
            int textLoaded = -1;
            for (int i = 0; i < height; i++) {
                if (i < emptyPanel || i > emptyPanel + arraySize - 1) {
                    std::cout << "||";
                    for (int h = 0; h < width - 4; h++)
                        std::cout << " ";
                    std::cout << "||" << std::endl;
                }
                else {
                    textLoaded++;
                    int stringLength = text.get(textLoaded).length();
                    int placement = (width - stringLength) / 2;
                    int spaces = width - stringLength;
                    std::cout << "||";
                    int counter = 0;
                    while (counter < spaces - 4) {
                        std::cout << " ";
                        counter++;
                        if (counter == placement - 2)
                            std::cout << text.get(textLoaded);
                    }
                    std::cout << "||" << std::endl;
                }
            }
            for (int i = 0; i < width; i++)
                std::cout << "=";
            std::cout << std::endl;
        }
    };

    int random() {
        srand(time(nullptr));
        int random_number = rand() % 100 + 1;
        return random_number;
    }

    const char* dirPath = "";

    void buildDir(const std::string& path) {
        std::vector<std::string> dirs;
        std::string folder;
        for (char c : path) {
            if (c != '/') {
                folder += c;
            }
            else {
                if (!folder.empty()) {
                    dirs.push_back(folder);
                    folder = "";
                }
            }
        }
        if (!folder.empty()) {
            dirs.push_back(folder);
        }

        std::string dirPath;
        for (const auto& dir : dirs) {
            dirPath += dir + '/';
            if (_mkdir(dirPath.c_str()) != 0) {
                if (errno == EEXIST) {
                    std::cout << "Directory " << dirPath << " already exists\n";
                }
                else {
                    std::cout << "Failed to create directory " << dirPath << "\n";
                }
            }
        }
    }

    void deleteDir(const std::string& dir_path) {
        try {
            fs::remove_all(dir_path);
            std::cout << "Directory " << dir_path << " and its contents were successfully deleted" << std::endl;
        }
        catch (const std::exception& ex) {
            std::cerr << "Error deleting directory " << dir_path << ": " << ex.what() << std::endl;
        }
    }

    void lowerCaseString(std::string& string) {
        std::transform(string.begin(), string.end(), string.begin(),
            [](unsigned char c) { return std::tolower(c); });
    }

    std::string toLowerCaseStr(std::string string) {
        std::transform(string.begin(), string.end(), string.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return string;
    }

    void removeSpaces(std::string& inputStr) {
        std::string outputStr = "";
        for (int i = 0; i < inputStr.length(); i++) {
            if (inputStr[i] != ' ') {
                outputStr += inputStr[i];
            }
        }
        inputStr = outputStr;
    }

    std::string sstring(std::string string) {
        return '"' + string + '"';
    }

    /*
    SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_FULscLSCREEN_MODE);
    ToggleFullscreen();
    */
}