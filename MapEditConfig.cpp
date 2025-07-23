#include "MapEditConfig.h"
#include <Windows.h>
#include <string>

MapEditConfig LoadMapEditConfig(const std::string& iniPath)
{
	MapEditConfig Ecfg;
	Ecfg.MAP_WIDTH = GetPrivateProfileInt("MapEdit", "MAP_WIDTH", 20, "./myMapEditSetUp.ini");
	Ecfg.MAP_HEIGHT = GetPrivateProfileInt("MapEdit", "MAP_HEIGHT", 20, "./myMapEditSetUp.ini");
	Ecfg.MAP_IMAGE_SIZE = GetPrivateProfileInt("MapEdit", "MAP_IMAGE_SIZE", 32, "./myMapEditSetUp.ini");
	Ecfg.LEFT_MARGIN = GetPrivateProfileInt("MapEdit", "LEFT_MARGIN", 100, "./myMapEditSetUp.ini");
	Ecfg.TOP_MARGIN = GetPrivateProfileInt("MapEdit", "TOP_MARGIN", 100, "./myMapEditSetUp.ini");
	return Ecfg;
}
const MapEditConfig& GetMapEditConfig()
{
	static MapEditConfig Econfig = LoadMapEditConfig("./myMapEditSetUp.ini");
	return Econfig;
}
